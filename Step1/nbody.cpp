/**
 * @file      nbody.cpp
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

#include <cfloat>
#include <cmath>

#include "nbody.h"
#include "Vec.h"

/* Constants */
constexpr float G                  = 6.67384e-11f;
constexpr float COLLISION_DISTANCE = 0.01f;

/*********************************************************************************************************************/
/*                TODO: Fullfill Partile's and Velocitie's constructors, destructors and methods                     */
/*                                    for data copies between host and device                                        */
/*********************************************************************************************************************/

/**
 * @brief Constructor
 * @param N - Number of particles
 */
Particles::Particles(const unsigned N): mN(N)
{
  positions_weights = new float4[N];
  velocities = new float3[N];

  #pragma acc enter data copyin(this[0:1])
  #pragma acc enter data create(positions_weights[0:mN])
  #pragma acc enter data create(velocities[0:mN])
}

/// @brief Destructor
Particles::~Particles()
{
  #pragma acc exit data delete(positions_weights)
  #pragma acc exit data delete(velocities)
  #pragma acc exit data delete(this)

  delete[] positions_weights;
  delete[] velocities;
}

/**
 * @brief Copy particles from host to device
 */
void Particles::copyToDevice()
{
  #pragma acc update device(positions_weights[0:mN])
  #pragma acc update device(velocities[0:mN])
}

/**
 * @brief Copy particles from device to host
 */
void Particles::copyToHost()
{
  #pragma acc update host(positions_weights[0:mN])
  #pragma acc update host(velocities[0:mN])
}

/*********************************************************************************************************************/

/**
 * Calculate velocity
 * @param pIn  - particles input
 * @param pOut - particles output
 * @param N    - Number of particles
 * @param dt   - Size of the time step
 */
void calculateVelocity(Particles& pIn, Particles& pOut, const unsigned N, float dt)
{
  /*******************************************************************************************************************/
  /*                    TODO: Calculate gravitation velocity, see reference CPU version,                             */
  /*                            you can use overloaded operators defined in Vec.h                                    */
  /*******************************************************************************************************************/
  #pragma acc parallel loop present(pIn, pOut)
  for (unsigned i = 0u; i < N; ++i) {
    float4 newVelGrav{};
    float3 newVelColl{};

    const float4 particle = pIn.positions_weights[i];
    const float3 particleVel = pIn.velocities[i];

    #pragma acc loop seq
    for (unsigned j = 0u; j < N; ++j) {
      const float4 otherParticle = pIn.positions_weights[j];
      const float3 otherParticleVel = pIn.velocities[j];

      const float4 diff = otherParticle - particle;
      const float r2 = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
      const float r = std::sqrt(r2);

      if (r > COLLISION_DISTANCE) {
        const float r3 = r2 * r;
        const float f = G * otherParticle.w / (r3 + FLT_MIN);
        newVelGrav += diff * f;

      } else if (r > 0.f && r < COLLISION_DISTANCE) {
        const float invWeightSum = 1 / (particle.w + otherParticle.w);
        newVelColl += 2.f * otherParticle.w * (otherParticleVel - particleVel) * invWeightSum;
      }
    }

    const float updatedVelX = particleVel.x + (newVelGrav.x * dt) + newVelColl.x;
    const float updatedVelY = particleVel.y + (newVelGrav.y * dt) + newVelColl.y;
    const float updatedVelZ = particleVel.z + (newVelGrav.z * dt) + newVelColl.z;

    pOut.positions_weights[i].x = particle.x + (updatedVelX * dt);
    pOut.positions_weights[i].y = particle.y + (updatedVelY * dt);
    pOut.positions_weights[i].z = particle.z + (updatedVelZ * dt);

    pOut.velocities[i].x = updatedVelX;
    pOut.velocities[i].y = updatedVelY;
    pOut.velocities[i].z = updatedVelZ;
  }
}// end of calculate_gravitation_velocity
//----------------------------------------------------------------------------------------------------------------------

/**
 * Calculate particles center of mass
 * @param p    - particles
 * @param com  - pointer to a center of mass
 * @param lock - pointer to a user-implemented lock
 * @param N    - Number of particles
 */
void centerOfMass(Particles& p, float4* comBuffer, const unsigned N)
{

}// end of centerOfMass
//----------------------------------------------------------------------------------------------------------------------

/**
 * CPU implementation of the Center of Mass calculation
 * @param particles - All particles in the system
 * @param N         - Number of particles
 */
float4 centerOfMassRef(MemDesc& memDesc)
{
  float4 com{};

  for (std::size_t i{}; i < memDesc.getDataSize(); i++)
  {
    const float3 pos = {memDesc.getPosX(i), memDesc.getPosY(i), memDesc.getPosZ(i)};
    const float  w   = memDesc.getWeight(i);

    // Calculate the vector on the line connecting current body and most recent position of center-of-mass
    // Calculate weight ratio only if at least one particle isn't massless
    const float4 d = {pos.x - com.x,
                      pos.y - com.y,
                      pos.z - com.z,
                      ((memDesc.getWeight(i) + com.w) > 0.0f)
                        ? ( memDesc.getWeight(i) / (memDesc.getWeight(i) + com.w))
                        : 0.0f};

    // Update position and weight of the center-of-mass according to the weight ration and vector
    com.x += d.x * d.w;
    com.y += d.y * d.w;
    com.z += d.z * d.w;
    com.w += w;
  }

  return com;
}// enf of centerOfMassRef
//----------------------------------------------------------------------------------------------------------------------
