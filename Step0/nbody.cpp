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

/**
 * @brief Constructor
 * @param N - Number of particles
 */
Velocities::Velocities(const unsigned N): mN(N)
{
  velocities = new float3[N];
  #pragma acc enter data copyin(this)
  #pragma acc enter data create(velocities[0:mN])
}

/// @brief Destructor
Velocities::~Velocities()
{
  #pragma acc exit data delete(velocities)
  #pragma acc exit data delete(this)
  delete[] velocities;
}

/**
 * @brief Copy velocities from host to device
 */
void Velocities::copyToDevice()
{
  #pragma acc update device(velocities[0:mN])
}

/**
 * @brief Copy velocities from device to host
 */
void Velocities::copyToHost()
{
  #pragma acc update host(velocities[0:mN])
}

/*********************************************************************************************************************/

/**
 * Calculate gravitation velocity
 * @param p      - particles
 * @param tmpVel - temp array for velocities
 * @param N      - Number of particles
 * @param dt     - Size of the time step
 */
void calculateGravitationVelocity(Particles& p, Velocities& tmpVel, const unsigned N, float dt)
{
  /*******************************************************************************************************************/
  /*                    TODO: Calculate gravitation velocity, see reference CPU version,                             */
  /*                            you can use overloaded operators defined in Vec.h                                    */
  /*******************************************************************************************************************/

  #pragma acc parallel loop present(p, tmpVel)
  for (unsigned i = 0u; i < N; ++i)
  {
      float3 newVel{};
      const float3 currPos = {p.positions_weights[i].x, p.positions_weights[i].y, p.positions_weights[i].z};
      const float currWeight = p.positions_weights[i].w;

      #pragma acc loop seq
      for (unsigned j = 0u; j < N; ++j)
      {
        const float3 otherPos = {p.positions_weights[j].x, p.positions_weights[j].y, p.positions_weights[j].z};
        const float3 d = otherPos - currPos;
        const float r = d.abs();
        const float r2 = r * r;
        const float f = G * currWeight * p.positions_weights[j].w / (r2 + std::numeric_limits<float>::min());
        
        if (r > COLLISION_DISTANCE)
        {
            newVel += d / r * f;
        }
      }
      tmpVel.velocities[i] = newVel * (dt / currWeight);
  }
}// end of calculate_gravitation_velocity
//----------------------------------------------------------------------------------------------------------------------

/**
 * Calculate collision velocity
 * @param p      - particles
 * @param tmpVel - temp array for velocities
 * @param N      - Number of particles
 * @param dt     - Size of the time step
 */
void calculateCollisionVelocity(Particles& __restrict p, Velocities& __restrict tmpVel, const unsigned N, float dt)
{
  /*******************************************************************************************************************/
  /*                    TODO: Calculate collision velocity, see reference CPU version,                               */
  /*                            you can use overloaded operators defined in Vec.h                                    */
  /*******************************************************************************************************************/
  
  #pragma acc parallel loop present(p, tmpVel) tile(32, 32)
  for (unsigned i = 0u; i < N; ++i)
  {
    float3 newVel = tmpVel.velocities[i];

    const float4 particle = p.positions_weights[i];
    const float3 particleVel  = p.velocities[i];

    #pragma acc loop seq
    for (unsigned j = 0u; j < N; ++j)
    {
      const float4 otherParticle = p.positions_weights[j];
      const float3 otherParticleVel  = p.velocities[j];

      const float4 diff = otherParticle - particle;

      const float r = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);

      if (r > 0.f && r < COLLISION_DISTANCE) {
        const float invWeightSum = 1 / (particle.w + otherParticle.w);
        newVel += 2.f * otherParticle.w * (otherParticleVel - particleVel) * invWeightSum;
      }
    }

    tmpVel.velocities[i] = newVel;
  }
}// end of calculate_collision_velocity
//----------------------------------------------------------------------------------------------------------------------

/**
 * Update particles
 * @param p      - particles
 * @param tmpVel - temp array for velocities
 * @param N      - Number of particles
 * @param dt     - Size of the time step
 */
void updateParticles(Particles& p, Velocities& tmpVel, const unsigned N, float dt)
{
  /*******************************************************************************************************************/
  /*                    TODO: Update particles position and velocity, see reference CPU version,                     */
  /*                            you can use overloaded operators defined in Vec.h                                    */
  /*******************************************************************************************************************/
# pragma acc parallel loop present(p, tmpVel)
  for (unsigned i = 0u; i < N; ++i)
  {
    float4 particle = p.positions_weights[i];
    float3 vel  = p.velocities[i];

    const float3 newVel = tmpVel.velocities[i];

    vel += newVel;

    p.velocities[i] = vel;

    particle.x += vel.x * dt;
    particle.y += vel.y * dt;
    particle.z += vel.z * dt;

    p.positions_weights[i] = particle;
  }
}// end of update_particle
//----------------------------------------------------------------------------------------------------------------------

/**
 * Calculate particles center of mass
 * @param p    - particles
 * @param com  - pointer to a center of mass
 * @param lock - pointer to a user-implemented lock
 * @param N    - Number of particles
 */
void centerOfMass(Particles& p, float4& com, int* lock, const unsigned N)
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
