/**
 * @brief Orbital simulation
 * @author Marc S. Ressl
 * @author Camila A. Castro
 * @author Javier B. Pérez Losada
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

    #if defined(BONUS_EASTER_EGG)
        phi = 0;
    #endif

    // https://en.wikipedia.org/wiki/Circular_orbit#Velocity
    float v = sqrtf(GRAVITATIONAL_CONSTANT * centerMass / r) * getRandomFloat(0.6F, 1.2F);
    float vy = getRandomFloat(-1E2F, 1E2F);

    body->mass = 1E12F;  // Typical asteroid weight: 1 billion tons
    body->radius = 2E3F; // Typical asteroid radius: 2km
    body->scaledRadius = RAD_SCALE(body->radius);
    body->color = GRAY;
    body->position = {r * cosf(phi), 0, r * sinf(phi)};
    body->velocity = {-v * sinf(phi), vy, v * cosf(phi)};
}

/**
 * @brief Constructs an orbital simulation
 *
 * @param timeStep The time step
 * @return The orbital simulation
 */
OrbitalSim *constructOrbitalSim(float timeStep)
{
    #if defined(BONUS_ALPHA_CENTAURI)
        #define ASTEROID_COUNT 0
        int bodyNum = ALPHACENTAURISYSTEM_BODYNUM;
        EphemeridesBody * system = alphaCentauriSystem;
    #else
        #ifndef ASTEROID_COUNT
            #define ASTEROID_COUNT 500
        #endif
        int bodyNum = SOLARSYSTEM_BODYNUM;
        EphemeridesBody * system = solarSystem;
    #endif
    OrbitalSim * sim = new OrbitalSim;
    sim->timeStep = timeStep;
    sim->timeStamp = 0.0F;
    sim->bodyNum = bodyNum + ASTEROID_COUNT;
    sim->bodyArray = (OrbitalBody(*)[])malloc(sizeof(OrbitalBody) * (bodyNum + ASTEROID_COUNT));
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
    float centerMass = 0.0F;
    for(int i = 0; i < bodyNum; i++){
        if(system[i].mass > centerMass){
            centerMass = system[i].mass;
        }
    }
    for(int i = bodyNum; i < sim->bodyNum; i++){
        configureAsteroid(&(*sim->bodyArray)[i], centerMass);
    }

    return sim;
}

/**
 * @brief Destroys an orbital simulation
 */
void destroyOrbitalSim(OrbitalSim *sim)
{
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
    // Update accelerations
    for(int i = 0; i < sim->bodyNum; i++){
        OrbitalBody *body = &(*sim->bodyArray)[i];
        body->acceleration = Vector3Zero();
    }

    for(int i = 0; i < sim->bodyNum; i++){
        OrbitalBody *bodyI = &(*sim->bodyArray)[i];
        for(int j = 0; j < sim->bodyNum - ASTEROID_COUNT; j++){
            if(i == j){
                continue;
            }
            OrbitalBody *bodyJ = &(*sim->bodyArray)[j];
            Vector3 differenceVector = Vector3Subtract(bodyJ->position, bodyI->position);
            float normSquared = Vector3LengthSqr(differenceVector);
            Vector3 unitVector = Vector3Normalize(differenceVector);
            bodyI->acceleration = Vector3Add(bodyI->acceleration, Vector3Scale(unitVector,
                                  GRAVITATIONAL_CONSTANT * bodyJ->mass / normSquared));
        }
    }

    // Update velocities and positions
    for(int i = 0; i < sim->bodyNum; i++){
        OrbitalBody *bodyI = &(*sim->bodyArray)[i];
        bodyI->velocity = Vector3Add(bodyI->velocity, Vector3Scale(bodyI->acceleration, sim->timeStep));
        bodyI->position = Vector3Add(bodyI->position, Vector3Scale(bodyI->velocity, sim->timeStep));
    }

    sim->timeStamp += sim->timeStep;
}