//
// Created by tdragon on 9/8/26.
//

#include "physics.h"

#include <string.h>
#include <stdint.h>

#define INVALID_PARTICLE_INDEX ((size_t)-1)

int physics_init(
    Physics *physics,
    float width,
    float height,
    size_t initial_particle_capacity
)
{
    if (physics == NULL)
    {
        return 0;
    }

    memset(
        physics,
        0,
        sizeof(Physics)
    );

    physics->mouse_particle = INVALID_PARTICLE_INDEX;

    PhysicsWorldSettings settings = {
        .gravity_x = 0.0f,
        .gravity_y = 980.0f,

        .world_width = width,
        .world_height = height,

        .restitution = 0.8f,

        /*
         * This should generally be at least
         * approximately the particle diameter.
         */
        .cell_size = 10.0f
    };

    return physics_world_init(
        &physics->world,
        &settings,
        initial_particle_capacity
    );
}

void physics_set_mouse_particle(
    Physics *physics,
    float x,
    float y)
{
    if (physics == NULL) {
        return;
    }

    ParticleSystem *particles =
        &physics->world.particles;

    /*
     * Create the mouse particle the first time
     * this function is called.
     */
    if (physics->mouse_particle == INVALID_PARTICLE_INDEX)
    {
        size_t index = particles->count;

        if (!particle_system_add(
                particles,
                x,
                y,
                0.0f,
                0.0f,
                1000000.0f,
                20.0f))
        {
            return;
        }

        physics->mouse_particle = index;
    }

    size_t i = physics->mouse_particle;

    /*
     * Mouse controls position directly.
     */
    particles->x[i] = x;
    particles->y[i] = y;

    /*
     * It isn't supposed to have its own velocity.
     */
    particles->vx[i] = 0.0f;
    particles->vy[i] = 0.0f;

    /*
     * Don't let gravity move it.
     */
    particles->ax[i] = 0.0f;
    particles->ay[i] = 0.0f;
}

void physics_destroy(
    Physics *physics
)
{
    if (physics == NULL)
    {
        return;
    }

    physics_world_destroy(
        &physics->world
    );
}

void physics_step(
    Physics *physics,
    float dt
)
{
    if (physics == NULL)
    {
        return;
    }

    physics_world_step(
        &physics->world,
        dt
    );
}

size_t physics_add_particle(
    Physics *physics,
    float x,
    float y,
    float vx,
    float vy,
    float mass,
    float radius
)
{
    if (physics == NULL)
    {
        return SIZE_MAX;
    }

    return particle_system_add(
        &physics->world.particles,
        x,
        y,
        vx,
        vy,
        mass,
        radius
    );
}

ParticleSystem *physics_particles(
    Physics *physics
)
{
    if (physics == NULL)
    {
        return NULL;
    }

    return &physics->world.particles;
}