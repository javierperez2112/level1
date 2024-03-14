/**
 * @brief Orbital simulation main module
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 */

#include "OrbitalSim.h"
#include "View.h"

#define SECONDS_PER_DAY 86400

int main()
{
    int fps = 60;                                 // Frames per second
    float timeMultiplier = 100 * SECONDS_PER_DAY; // Simulation speed: 100 days per simulation second
    float timeStep = timeMultiplier / fps;

    OrbitalSim *sim = constructOrbitalSim(timeStep);
    View *view = constructView(fps);

    while (isViewRendering(view))
    {
        updateOrbitalSim(sim);

        renderView(view, sim);
    }

    destroyView(view);
    destroyOrbitalSim(sim);

    return 0;
}
