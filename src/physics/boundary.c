//
// Created by tdragon on 9/8/26.
//

#include "boundary.h"

void boundary_resolve_particles(
    ParticleSystem *particles,
    const Boundary *boundary)
{
    if (particles == NULL || boundary == NULL) {
        return;
    }

    for (size_t i = 0; i < particles->count; ++i) {
        float radius = particles->radius[i];

        float min_x = boundary->min_x + radius;
        float max_x = boundary->max_x - radius;

        float min_y = boundary->min_y + radius;
        float max_y = boundary->max_y - radius;

        /*
         * Left wall
         */
        if (particles->x[i] < min_x) {
            particles->x[i] = min_x;

            if (particles->vx[i] < 0.0f) {
                particles->vx[i] =
                    -particles->vx[i] * boundary->restitution;
            }
        }

        /*
         * Right wall
         */
        if (particles->x[i] > max_x) {
            particles->x[i] = max_x;

            if (particles->vx[i] > 0.0f) {
                particles->vx[i] =
                    -particles->vx[i] * boundary->restitution;
            }
        }

        /*
         * Top wall
         */
        if (particles->y[i] < min_y) {
            particles->y[i] = min_y;

            if (particles->vy[i] < 0.0f) {
                particles->vy[i] =
                    -particles->vy[i] * boundary->restitution;
            }
        }

        /*
         * Bottom wall
         */
        if (particles->y[i] > max_y) {
            particles->y[i] = max_y;

            if (particles->vy[i] > 0.0f) {
                particles->vy[i] =
                    -particles->vy[i] * boundary->restitution;
            }
        }
    }
}