/**
 * @brief Orbital simulation
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 */

#ifndef ORBITALSIM_H
#define ORBITALSIM_H

#include "raylib.h"
#include "raymath.h"

#define RAD_SCALE(x) (0.005f * (logf(x)))
#define ASTEROID_COUNT 500

/**
 * @brief Orbital body definition
 */
struct OrbitalBody
{
    // Fill in your code here...
    float mass;		  // [kg]
    float radius;	  // [m]
    float scaledRadius;
    Color color;	  // Raylib color
    Vector3 position; // [m]
    Vector3 velocity; // [m/s]
    Vector3 acceleration;   // [m/s^2]
};

/**
 * @brief Orbital simulation definition
 */
struct OrbitalSim
{
    float timeStep;     // [s]
    float timeStamp;    // [s]
    int bodyNum;
    OrbitalBody (*bodyArray)[];

};

OrbitalSim *constructOrbitalSim(float timeStep);
void destroyOrbitalSim(OrbitalSim *sim);

void updateOrbitalSim(OrbitalSim *sim);

#endif
