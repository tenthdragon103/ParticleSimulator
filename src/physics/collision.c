//
// Created by tdragon on 9/8/26.
//

#include "collision.h"

#include <math.h>

void collision_resolve_pair(
    ParticleSystem *particles,
    size_t a,
    size_t b,
    float restitution
)
{
    float dx =
        particles->x[b] -
        particles->x[a];

    float dy =
        particles->y[b] -
        particles->y[a];

    float distance_squared =
        dx * dx + dy * dy;

    float radius_sum =
        particles->radius[a] +
        particles->radius[b];

    if (
        distance_squared >=
        radius_sum * radius_sum
    )
    {
        return;
    }

    /*
     * Prevent division by zero if two particles
     * occupy exactly the same position.
     */
    if (distance_squared < 0.0000001f)
    {
        dx = 0.0001f;
        dy = 0.0f;

        distance_squared = dx * dx;
    }

    float distance = sqrtf(distance_squared);

    float nx = dx / distance;
    float ny = dy / distance;

    /*
     * Relative velocity.
     */
    float rvx =
        particles->vx[b] -
        particles->vx[a];

    float rvy =
        particles->vy[b] -
        particles->vy[a];

    /*
     * Relative velocity along collision normal.
     */
    float velocity_normal =
        rvx * nx + rvy * ny;

    /*
     * Already moving apart.
     */
    if (velocity_normal > 0.0f)
    {
        return;
    }

    float inv_mass_a =
        particles->mass[a] > 0.0f
            ? 1.0f / particles->mass[a]
            : 0.0f;

    float inv_mass_b =
        particles->mass[b] > 0.0f
            ? 1.0f / particles->mass[b]
            : 0.0f;

    float impulse =
        -(1.0f + restitution)
        * velocity_normal;

    impulse /=
        inv_mass_a +
        inv_mass_b;

    float impulse_x = impulse * nx;
    float impulse_y = impulse * ny;

    particles->vx[a] -=
        impulse_x * inv_mass_a;

    particles->vy[a] -=
        impulse_y * inv_mass_a;

    particles->vx[b] +=
        impulse_x * inv_mass_b;

    particles->vy[b] +=
        impulse_y * inv_mass_b;

    /*
     * Positional correction.
     *
     * Prevent particles from remaining overlapped.
     */
    float penetration =
        radius_sum - distance;

    const float correction_percent = 0.8f;

    float correction =
        penetration *
        correction_percent /
        (inv_mass_a + inv_mass_b);

    particles->x[a] -=
        correction * nx * inv_mass_a;

    particles->y[a] -=
        correction * ny * inv_mass_a;

    particles->x[b] +=
        correction * nx * inv_mass_b;

    particles->y[b] +=
        correction * ny * inv_mass_b;
}

void collision_detect_and_resolve(
    ParticleSystem *particles,
    const SpatialGrid *grid,
    const CollisionSettings *settings
)
{
    if (
        particles == NULL ||
        grid == NULL ||
        settings == NULL
    )
    {
        return;
    }

    /*
     * Check every cell against itself and neighboring
     * cells.
     */
    for (int cy = 0; cy < grid->height; cy++)
    {
        for (int cx = 0; cx < grid->width; cx++)
        {
            size_t cell =
                (size_t)cy *
                (size_t)grid->width +
                (size_t)cx;

            size_t start =
                grid->cell_start[cell];

            size_t end =
                grid->cell_end[cell];

            /*
             * Check particles inside this cell.
             */
            for (size_t i = start; i < end; i++)
            {
                size_t a =
                    grid->particle_indices[i];

                /*
                 * Neighboring cells.
                 */
                for (
                    int ny = cy - 1;
                    ny <= cy + 1;
                    ny++
                )
                {
                    if (
                        ny < 0 ||
                        ny >= grid->height
                    )
                    {
                        continue;
                    }

                    for (
                        int nx = cx - 1;
                        nx <= cx + 1;
                        nx++
                    )
                    {
                        if (
                            nx < 0 ||
                            nx >= grid->width
                        )
                        {
                            continue;
                        }

                        size_t neighbor =
                            (size_t)ny *
                            (size_t)grid->width +
                            (size_t)nx;

                        size_t neighbor_start =
                            grid->cell_start[neighbor];

                        size_t neighbor_end =
                            grid->cell_end[neighbor];

                        for (
                            size_t j =
                                neighbor_start;
                            j < neighbor_end;
                            j++
                        )
                        {
                            size_t b =
                                grid->particle_indices[j];

                            if (a >= b)
                            {
                                continue;
                            }

                            collision_resolve_pair(
                                particles,
                                a,
                                b,
                                settings->restitution
                            );
                        }
                    }
                }
            }
        }
    }
}