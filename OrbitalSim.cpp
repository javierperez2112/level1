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

static void accelerationCalc(OrbitalSim* sim, int bodyNumber1);
static Vector3 linealFunction(Vector3 b, Vector3 m, float x);

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
    sim->bodyNum = bodyNum;
    sim->bodyArray = (OrbitalBody(*)[])malloc(sizeof(OrbitalBody) * bodyNum);
    for(int i = 0; i < bodyNum; i++){
        (*sim->bodyArray)[i] = {
            system[i].mass,
            system[i].radius,
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
    int bodyCount;

    for (bodyCount = 0; bodyCount < sim->bodyNum; bodyCount++) {
        accelerationCalc(sim, bodyCount);
    }

    for (bodyCount = 0; bodyCount < sim->bodyNum; bodyCount++) {
        (sim->bodyArray[bodyCount])->velocity = linealFunction((sim->bodyArray[bodyCount])->velocity, (sim->bodyArray[bodyCount])->acceleration, sim->timeStep);
        (sim->bodyArray[bodyCount])->position = linealFunction((sim->bodyArray[bodyCount])->position, (sim->bodyArray[bodyCount])->velocity, sim->timeStep);
    }
}

/**
 * @brief Calculates and sets the acceleration of an OrbitalBody
 *
 * @param sim The orbital simulation
 * @param bodyI Position of the OrbitalBody in the bodyArray
 * @return void
 */
static void accelerationCalc(OrbitalSim *sim, int bodyI) 
{
    Vector3 gravitationalForce, netForce = Vector3Zero();
    int counter;

    for (counter = 0; counter < sim->bodyNum ; counter++) 
    {
        if (counter != bodyI) 
        {
            Vector3 substractedVectors = Vector3Subtract(sim->bodyArray[bodyI]->position, sim->bodyArray[counter]->position);
            double constant, norm = sqrt(substractedVectors.x * substractedVectors.x + substractedVectors.y * substractedVectors.y + substractedVectors.z * substractedVectors.z);
            constant = -(GRAVITATIONAL_CONSTANT * sim->bodyArray[bodyI]->mass * sim->bodyArray[counter]->mass) / (norm * norm);
            gravitationalForce = Vector3Scale(Vector3Scale(substractedVectors, 1 / norm), constant);
            netForce = Vector3Add(netForce, gravitationalForce);
        }
    }
    sim->bodyArray[bodyI]->acceleration = Vector3Scale(netForce, 1 / sim->bodyArray[bodyI]->mass);
}

/**
 * @brief Calculates a lineal function with Vector3
 *
 * @param b Independent term
 * @param m Slope
 * @param x X
 * @return Vector with solution
 */
static Vector3 linealFunction(Vector3 b, Vector3 m, float x) 
{
    return Vector3Add(b, Vector3Scale(m, x));
}