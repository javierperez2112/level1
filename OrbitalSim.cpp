/**
 * @brief Orbital simulation
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 */

// Enables M_PI #define in Windows
#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <math.h>

#include "OrbitalSim.h"
#include "ephemerides.h"

#define GRAVITATIONAL_CONSTANT 6.6743E-11F
#define ASTEROIDS_MEAN_RADIUS 4E11F

void updatePositions(OrbitalSim *sim);
void updateAccelerations(OrbitalSim *sim);

/**
 * @brief Gets a uniform random value in a range
 *
 * @param min Minimum value
 * @param max Maximum value
 * @return The random value
 */
float getRandomFloat(float min, float max)
{
    return min + (max - min) * rand() / (float)RAND_MAX;
}

/**
 * @brief Configures an asteroid
 *
 * @param body An orbital body
 * @param centerMass The mass of the most massive object in the star system
 */
void configureAsteroid(OrbitalBody *body, float centerMass)
{
    // Logit distribution
    float x = getRandomFloat(0, 1);
    float l = logf(x) - logf(1 - x) + 1;

    // https://mathworld.wolfram.com/DiskPointPicking.html
    float r = ASTEROIDS_MEAN_RADIUS * sqrtf(fabsf(l));
    float phi = getRandomFloat(0, 2.0F * (float)M_PI);

    // Surprise!
    // phi = 0;

    // https://en.wikipedia.org/wiki/Circular_orbit#Velocity
    float v = sqrtf(GRAVITATIONAL_CONSTANT * centerMass / r) * getRandomFloat(0.6F, 1.2F);
    float vy = getRandomFloat(-1E2F, 1E2F);

    // Fill in with your own fields:
    // body->mass = 1E12F;  // Typical asteroid weight: 1 billion tons
    // body->radius = 2E3F; // Typical asteroid radius: 2km
    // body->color = GRAY;
    // body->position = {r * cosf(phi), 0, r * sinf(phi)};
    // body->velocity = {-v * sinf(phi), vy, v * cosf(phi)};
}

/**
 * @brief Constructs an orbital simulation
 *
 * @param float The time step
 * @return The orbital simulation
 */
OrbitalSim *constructOrbitalSim(float timeStep)
{
    // Your code goes here...
    int bodyNum = SOLARSYSTEM_BODYNUM;
    EphemeridesBody * system = solarSystem;
    OrbitalSim * sim = new OrbitalSim;
    sim->timeStep = timeStep;
    sim->timeStamp = 0.0F;
    sim->bodyNum = bodyNum;
    sim->bodyArray = (OrbitalBody(*)[])malloc(sizeof(OrbitalBody) * bodyNum);
    for(int i = 0; i < bodyNum; i++){
        (*sim->bodyArray)[i] = {
            system[i].mass,
            system[i].radius,
            RAD_SCALE(system[i].radius),
            system[i].color,
            system[i].position,
            system[i].velocity,
            Vector3Zero(),
        };
    }

    return sim; // This should return your orbital sim
}

/**
 * @brief Destroys an orbital simulation
 */
void destroyOrbitalSim(OrbitalSim *sim)
{
    // Your code goes here...
    free(sim->bodyArray);
    delete sim;

}

/**
 * @brief Simulates a timestep
 *
 * @param sim The orbital simulation
 */
void updateOrbitalSim(OrbitalSim *sim)
{
    // Your code goes here...
    updateAccelerations(sim);
    updatePositions(sim);
    sim->timeStamp += sim->timeStep;

}

/**
 * @brief Updates accelerations based on position
 * 
 * @param sim The orbital simulation
*/
void updateAccelerations(OrbitalSim *sim){
    for(int i = 0; i < sim->bodyNum; i++){
        (*sim->bodyArray)[i].acceleration = {0.0F, 0.0F, 0.0F};
    }
    Vector3 differenceVector, unitVector, force;
    float normSquaredInverse;
    OrbitalBody *bodyI;
    OrbitalBody *bodyJ;
    for(int i = 0; i < sim->bodyNum; i++){
        bodyI = &(*sim->bodyArray)[i];
        for(int j = i + 1; j < sim->bodyNum; j++){
            bodyJ = &(*sim->bodyArray)[j];
            differenceVector = Vector3Subtract(bodyI->position, bodyJ->position);
            unitVector = Vector3Normalize(differenceVector);
            normSquaredInverse = 1.0F / Vector3LengthSqr(differenceVector);
            bodyI->acceleration = Vector3Add(bodyI->acceleration, 
                                  Vector3Scale(unitVector, -1.0F * normSquaredInverse * GRAVITATIONAL_CONSTANT * bodyJ->mass));
            bodyJ->acceleration = Vector3Add(bodyJ->acceleration, 
                                  Vector3Scale(unitVector, normSquaredInverse * GRAVITATIONAL_CONSTANT * bodyI->mass));
        }
    }
}

/**
 * @brief Updates positions
 * 
 * @param sim The orbital simulation
*/
void updatePositions(OrbitalSim *sim){
    for(int i = 0; i < sim->bodyNum; i++){
        OrbitalBody *bodyI = &(*sim->bodyArray)[i];
        bodyI->velocity = Vector3Add(bodyI->velocity, Vector3Scale(bodyI->acceleration, sim->timeStep));
        bodyI->position = Vector3Add(bodyI->position, Vector3Scale(bodyI->velocity, sim->timeStep));
    }
}

float highestMass(EphemeridesBody *system, int size){
    float highestMass = 0.0F;
    for(int i = 0; i < size; i++){
        if(system[i].mass > highestMass){
            highestMass = system[i].mass;
        }
    }
    return highestMass;
}
