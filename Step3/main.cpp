/**
 * @file      main.cpp
 *
 * @author    Name Surname \n
 *            Faculty of Information Technology \n
 *            Brno University of Technology \n
 *            xlogin00@fit.vutbr.cz
 *
 * @brief     PCG Assignment 2
 *
 * @version   2023
 *
 * @date      04 October   2023, 09:00 (created) \n
 */

#include <cmath>
#include <cstdio>
#include <chrono>
#include <string>
#include <cstring>


#include "nbody.h"
#include "h5Helper.h"

/**
 * Main rotine
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv)
{
  if (argc != 7)
  {
    std::printf("Usage: %s <N> <dt> <steps> <write intesity> <input> <output>\n", argv[0]);
    std::exit(1);
  }

  // Number of particles
  const unsigned N         = static_cast<unsigned>(std::stoul(argv[1]));
  // Length of time step
  const float    dt        = std::stof(argv[2]);
  // Number of steps
  const unsigned steps     = static_cast<unsigned>(std::stoul(argv[3]));
  // Write frequency
  const unsigned writeFreq = static_cast<unsigned>(std::stoul(argv[4]));

  // Log benchmark setup
  std::printf("       NBODY GPU simulation\n"
              "N:                       %u\n"
              "dt:                      %f\n"
              "steps:                   %u\n",
              N, dt, steps);

  const std::size_t recordsCount = (writeFreq > 0) ? (steps + writeFreq - 1) / writeFreq : 0;

  Particles particles[2]{Particles{N}, Particles{N}};

  /********************************************************************************************************************/
  /*                                     TODO: Fill memory descriptor parameters                                      */
  /********************************************************************************************************************/

  /*
   * Caution! Create only after CPU side allocation
   * parameters:
   *                            Stride of two            Offset of the first
   *       Data pointer       consecutive elements        element in FLOATS,
   *                          in FLOATS, not bytes            not bytes
  */
  MemDesc md(&particles[0].positions_weights[0].x,                  4,                          0,
             &particles[0].positions_weights[0].y,                  4,                          0,
             &particles[0].positions_weights[0].z,                  4,                          0,
             &particles[0].velocities[0].x,                         3,                          0,
             &particles[0].velocities[0].y,                         3,                          0,
             &particles[0].velocities[0].z,                         3,                          0,
             &particles[0].positions_weights[0].w,                  4,                          0,
             N,
             recordsCount);

  // Initialisation of helper class and loading of input data
  H5Helper h5Helper(argv[5], argv[6], md);

  try
  {
    h5Helper.init();
    h5Helper.readParticleData();
  }
  catch (const std::exception& e)
  {
    std::fprintf(stderr, "Error: %s\n", e.what());
    return EXIT_FAILURE;
  }

  /********************************************************************************************************************/
  /*                   TODO: Allocate memory for center of mass buffer. Remember to clear it.                         */
  /********************************************************************************************************************/
  float *comBuffer = new float[4];
  #pragma acc enter data create(comBuffer[0:4])
  float4 comFinal = {0.f, 0.f, 0.f, 0.f};
  /********************************************************************************************************************/
  /*                                      TODO: Set openacc stream ids                                                */
  /********************************************************************************************************************/
  // #pragma acc set device_num(calculateVelocityStream) device_type(acc_device_nvidia)
  // #pragma acc set device_num(centerOfMassStream) device_type(acc_device_nvidia)
  // #pragma acc set device_num(dataTransferStream) device_type(acc_device_nvidia)

  /********************************************************************************************************************/
  /*                                     TODO: Memory transfer CPU -> GPU                                             */
  /********************************************************************************************************************/
  std::memcpy(particles[1].velocities, particles[0].velocities, sizeof(float3) * N);
  std::memcpy(particles[1].positions_weights, particles[0].positions_weights, sizeof(float4) * N);

  particles[0].copyToDevice();
  particles[1].copyToDevice();

  // Lambda for checking if we should write current step to the file
  auto shouldWrite = [writeFreq](unsigned s) -> bool
  {
    return writeFreq > 0u && (s % writeFreq == 0u);
  };

  // Lamda for getting record number
  auto getRecordNum = [writeFreq](unsigned s) -> unsigned
  {
    return s / writeFreq;
  };
  
  // Start measurement
  const auto start = std::chrono::steady_clock::now();

  /********************************************************************************************************************/
  /*            TODO: Edit the loop to work asynchronously and overlap computation with data transfers.               */
  /*                  Use shouldWrite lambda to determine if data should be outputted to file.                        */
  /*                           if (shouldWrite(s, writeFreq)) { ... }                                                 */
  /*                        Use getRecordNum lambda to get the record number.                                         */
  /********************************************************************************************************************/
  unsigned int recordNum;
  for (unsigned s = 0u; s < steps; ++s)
  {
    const unsigned srcIdx = s % 2;        // source particles index
    const unsigned dstIdx = (s + 1) % 2;  // destination particles index

    /******************************************************************************************************************/
    /*                                        GPU computation                                                         */
    /******************************************************************************************************************/
    #pragma acc wait(calculateVelocityStream)
    calculateVelocity(particles[srcIdx], particles[dstIdx], N, dt);
    
    if (shouldWrite(s)) {
      recordNum = getRecordNum(s);
      // transfer data to host
      #pragma acc update host(particles[srcIdx].positions_weights[0:N]) async(dataTransferStream)
      #pragma acc update host(particles[srcIdx].velocities[0:N]) async(dataTransferStream)

      // clear the comBuffer in device
      std::memset(comBuffer, 0, sizeof(float) * 4);
      // clear the comBuffer in device
      #pragma acc data copyin(comBuffer[0:4]) copyout(comBuffer[0:4])
      {
        // calculate center of mass
        centerOfMass(particles[srcIdx], comBuffer, N);
      }
      // wait for the center of mass calculation
      comFinal = {comBuffer[0], comBuffer[1], comBuffer[2], comBuffer[3]};
      // write the center of mass to the file
      h5Helper.writeCom(comFinal, recordNum);
      
      // wait for the data transfer and write the particle data to the file
      #pragma acc wait(dataTransferStream)
      h5Helper.writeParticleData(recordNum);
    }

  }
  const unsigned resIdx = steps % 2;    // result particles index

  /********************************************************************************************************************/
  /*                          TODO: Invocation of center of mass kernel, do not forget to add                         */
  /*                              additional synchronization and set appropriate stream                               */
  /********************************************************************************************************************/
  std::memset(comBuffer, 0, sizeof(float) * 4);
  #pragma acc data copyin(comBuffer[0:4]) copyout(comBuffer[0:4])
  {
    centerOfMass(particles[resIdx], comBuffer, N);
  }

  comFinal = {comBuffer[0], comBuffer[1], comBuffer[2], comBuffer[3]};
  
  // End measurement
  const auto end = std::chrono::steady_clock::now();

  // Approximate simulation wall time
  const float elapsedTime = std::chrono::duration<float>(end - start).count();
  std::printf("Time: %f s\n", elapsedTime);

  /********************************************************************************************************************/
  /*                                     TODO: Memory transfer GPU -> CPU                                             */
  /********************************************************************************************************************/
  #pragma acc wait(dataTransferStream)
  #pragma acc wait(calculateVelocityStream)
  particles[resIdx].copyToHost();

  // Compute reference center of mass on CPU
  const float4 refCenterOfMass = centerOfMassRef(md);

  std::printf("Reference center of mass: %f, %f, %f, %f\n",
              refCenterOfMass.x,
              refCenterOfMass.y,
              refCenterOfMass.z,
              refCenterOfMass.w);

  std::printf("Center of mass on GPU: %f, %f, %f, %f\n",
              comFinal.x,
              comFinal.y,
              comFinal.z,
              comFinal.w);

  // Writing final values to the file
  h5Helper.writeComFinal(comFinal);
  h5Helper.writeParticleDataFinal();

  /********************************************************************************************************************/
  /*                                TODO: Free center of mass buffer memory                                           */
  /********************************************************************************************************************/
  #pragma acc exit data delete(comBuffer[0:4])
  delete[] comBuffer;
}// end of main
//----------------------------------------------------------------------------------------------------------------------
