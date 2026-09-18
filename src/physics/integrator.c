//
// Created by tdragon on 9/8/26.
//

#include "integrator.h"

void integrator_semi_implicit_euler(
    ParticleSystem *particles,
    float dt
)
{
    if (particles == NULL)
    {
        return;
    }

    for (size_t i = 0; i < particles->count; i++)
    {
        /*
         * Velocity.
         */
        particles->vx[i] +=
            particles->ax[i] * dt;

        particles->vy[i] +=
            particles->ay[i] * dt;

        /*
         * Position.
         */
        particles->x[i] +=
            particles->vx[i] * dt;

        particles->y[i] +=
            particles->vy[i] * dt;
    }
}