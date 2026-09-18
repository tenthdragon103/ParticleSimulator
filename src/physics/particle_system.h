//
// Created by tdragon on 9/8/26.
//

#ifndef PARTICLESIMULATOR_PARTICLE_SYSTEM_H
#define PARTICLESIMULATOR_PARTICLE_SYSTEM_H

#include <stddef.h>

typedef struct
{
    size_t count;
    size_t capacity;

    float *x;
    float *y;

    float *vx;
    float *vy;

    float *ax;
    float *ay;

    float *mass;
    float *radius;

} ParticleSystem;

int particle_system_init(
    ParticleSystem *system,
    size_t initial_capacity
);

void particle_system_destroy(
    ParticleSystem *system
);

int particle_system_reserve(
    ParticleSystem *system,
    size_t capacity
);

size_t particle_system_add(
    ParticleSystem *system,
    float x,
    float y,
    float vx,
    float vy,
    float mass,
    float radius
);

void particle_system_remove(
    ParticleSystem *system,
    size_t index
);

void particle_system_clear(
    ParticleSystem *system
);

#endif //PARTICLESIMULATOR_PARTICLE_SYSTEM_H
