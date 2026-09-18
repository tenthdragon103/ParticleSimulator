#include "particle_system.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void particle_system_free_arrays(
    ParticleSystem *system
)
{
    free(system->x);
    free(system->y);

    free(system->vx);
    free(system->vy);

    free(system->ax);
    free(system->ay);

    free(system->mass);
    free(system->radius);

    system->x = NULL;
    system->y = NULL;

    system->vx = NULL;
    system->vy = NULL;

    system->ax = NULL;
    system->ay = NULL;

    system->mass = NULL;
    system->radius = NULL;
}

int particle_system_init(
    ParticleSystem *system,
    size_t initial_capacity
)
{
    if (system == NULL)
    {
        return 0;
    }

    memset(system, 0, sizeof(ParticleSystem));

    if (initial_capacity == 0)
    {
        initial_capacity = 1024;
    }

    return particle_system_reserve(
        system,
        initial_capacity
    );
}

void particle_system_destroy(
    ParticleSystem *system
)
{
    if (system == NULL)
    {
        return;
    }

    particle_system_free_arrays(system);

    system->count = 0;
    system->capacity = 0;
}

int particle_system_reserve(
    ParticleSystem *system,
    size_t capacity
)
{
    if (system == NULL)
    {
        return 0;
    }

    if (capacity <= system->capacity)
    {
        return 1;
    }

    float *x = realloc(
        system->x,
        capacity * sizeof(float)
    );

    float *y = realloc(
        system->y,
        capacity * sizeof(float)
    );

    float *vx = realloc(
        system->vx,
        capacity * sizeof(float)
    );

    float *vy = realloc(
        system->vy,
        capacity * sizeof(float)
    );

    float *ax = realloc(
        system->ax,
        capacity * sizeof(float)
    );

    float *ay = realloc(
        system->ay,
        capacity * sizeof(float)
    );

    float *mass = realloc(
        system->mass,
        capacity * sizeof(float)
    );

    float *radius = realloc(
        system->radius,
        capacity * sizeof(float)
    );

    if (
        x == NULL ||
        y == NULL ||
        vx == NULL ||
        vy == NULL ||
        ax == NULL ||
        ay == NULL ||
        mass == NULL ||
        radius == NULL
    )
    {
        /*
         * We don't free the successfully reallocated
         * arrays here because doing so would leave the
         * original pointers invalid.
         *
         * For production code we should replace this
         * with a transactional allocation strategy.
         */
        return 0;
    }

    system->x = x;
    system->y = y;

    system->vx = vx;
    system->vy = vy;

    system->ax = ax;
    system->ay = ay;

    system->mass = mass;
    system->radius = radius;

    system->capacity = capacity;

    return 1;
}

size_t particle_system_add(
    ParticleSystem *system,
    float x,
    float y,
    float vx,
    float vy,
    float mass,
    float radius
)
{
    if (system == NULL)
    {
        return SIZE_MAX;
    }

    if (system->count >= system->capacity)
    {
        size_t new_capacity =
            system->capacity == 0
                ? 1024
                : system->capacity * 2;

        if (!particle_system_reserve(
            system,
            new_capacity
        ))
        {
            return SIZE_MAX;
        }
    }

    size_t index = system->count;

    system->x[index] = x;
    system->y[index] = y;

    system->vx[index] = vx;
    system->vy[index] = vy;

    system->ax[index] = 0.0f;
    system->ay[index] = 0.0f;

    system->mass[index] = mass;
    system->radius[index] = radius;

    system->count++;

    return index;
}

void particle_system_remove(
    ParticleSystem *system,
    size_t index
)
{
    if (
        system == NULL ||
        index >= system->count
    )
    {
        return;
    }

    size_t last = system->count - 1;

    if (index != last)
    {
        system->x[index] = system->x[last];
        system->y[index] = system->y[last];

        system->vx[index] = system->vx[last];
        system->vy[index] = system->vy[last];

        system->ax[index] = system->ax[last];
        system->ay[index] = system->ay[last];

        system->mass[index] = system->mass[last];
        system->radius[index] = system->radius[last];
    }

    system->count--;
}

void particle_system_clear(
    ParticleSystem *system
)
{
    if (system == NULL)
    {
        return;
    }

    system->count = 0;
}