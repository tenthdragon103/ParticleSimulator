//
// Created by tdragon on 9/8/26.
//

#include "physics_world.h"
#include "integrator.h"

#include <string.h>

int physics_world_init(
    PhysicsWorld *world,
    const PhysicsWorldSettings *settings,
    size_t particle_capacity
)
{
    if (world == NULL || settings == NULL) {
        return 0;
    }

    memset(world, 0, sizeof(PhysicsWorld));

    world->settings = *settings;
    world->collision.restitution = settings->restitution;

    world->boundary.min_x = 0.0f;
    world->boundary.min_y = 0.0f;
    world->boundary.max_x = settings->world_width;
    world->boundary.max_y = settings->world_height;
    world->boundary.restitution = settings->restitution;

    if (!particle_system_init(
            &world->particles,
            particle_capacity))
    {
        return 0;
    }

    int grid_width =
        (int)(settings->world_width / settings->cell_size);

    int grid_height =
        (int)(settings->world_height / settings->cell_size);

    if (grid_width < 1) {
        grid_width = 1;
    }

    if (grid_height < 1) {
        grid_height = 1;
    }

    if (!spatial_grid_init(
            &world->grid,
            grid_width,
            grid_height,
            settings->cell_size,
            particle_capacity))
    {
        particle_system_destroy(&world->particles);
        return 0;
    }

    return 1;
}

void physics_world_destroy(PhysicsWorld *world)
{
    if (world == NULL) {
        return;
    }

    spatial_grid_destroy(&world->grid);
    particle_system_destroy(&world->particles);
}

void physics_world_step(
    PhysicsWorld *world,
    float dt)
{
    if (world == NULL || dt <= 0.0f) {
        return;
    }

    /*
     * Apply global acceleration.
     *
    for (size_t i = 0; i < world->particles.count; ++i) {
        world->particles.ax[i] =
            world->settings.gravity_x;

        world->particles.ay[i] =
            world->settings.gravity_y;
    }*/

    /*
     * Integrate velocity and position.
     */
    integrator_semi_implicit_euler(
        &world->particles,
        dt
    );

    /*
     * Rebuild broad-phase spatial grid.
     */
    spatial_grid_build(
        &world->grid,
        &world->particles
    );

    /*
     * detect and resolve boundary collisions
     */

    integrator_semi_implicit_euler(
        &world->particles,
        dt
    );

    boundary_resolve_particles(
        &world->particles,
        &world->boundary
    );

    spatial_grid_build(
        &world->grid,
        &world->particles
    );

    collision_detect_and_resolve(
        &world->particles,
        &world->grid,
        &world->collision
    );

    /*
     * Detect and resolve particle collisions.
     */
    collision_detect_and_resolve(
        &world->particles,
        &world->grid,
        &world->collision
    );
}