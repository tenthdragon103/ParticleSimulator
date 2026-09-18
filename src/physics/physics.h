//
// Created by tdragon on 9/8/26.
//

#ifndef PARTICLESIMULATOR_PHYSICS_H
#define PARTICLESIMULATOR_PHYSICS_H

#include <stddef.h>

#include "physics_world.h"

typedef struct
{
    PhysicsWorld world;
    size_t mouse_particle;

} Physics;

int physics_init(
    Physics *physics,
    float width,
    float height,
    size_t initial_particle_capacity
);

void physics_destroy(
    Physics *physics
);

void physics_step(
    Physics *physics,
    float dt
);

size_t physics_add_particle(
    Physics *physics,
    float x,
    float y,
    float vx,
    float vy,
    float mass,
    float radius
);

void physics_set_mouse_particle(
    Physics *physics,
    float x,
    float y
);

ParticleSystem *physics_particles(
    Physics *physics
);

#endif //PARTICLESIMULATOR_PHYSICS_H
