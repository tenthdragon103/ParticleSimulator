//
// Created by tdragon on 9/8/26.
//

#ifndef PARTICLESIMULATOR_PHYSICS_WORLD_H
#define PARTICLESIMULATOR_PHYSICS_WORLD_H

#include "particle_system.h"
#include "spatial_grid.h"
#include "collision.h"
#include "boundary.h"

typedef struct
{
    float gravity_x;
    float gravity_y;

    float world_width;
    float world_height;

    float restitution;

    float cell_size;

} PhysicsWorldSettings;

typedef struct {
    ParticleSystem particles;
    SpatialGrid grid;
    CollisionSettings collision;
    Boundary boundary;
    PhysicsWorldSettings settings;
} PhysicsWorld;

int physics_world_init(
    PhysicsWorld *world,
    const PhysicsWorldSettings *settings,
    size_t particle_capacity
);

void physics_world_destroy(
    PhysicsWorld *world
);

void physics_world_step(
    PhysicsWorld *world,
    float dt
);


#endif //PARTICLESIMULATOR_PHYSICS_WORLD_H
