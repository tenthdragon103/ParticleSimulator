//
// Created by tdragon on 9/8/26.
//

#ifndef PARTICLESIMULATOR_COLLISION_H
#define PARTICLESIMULATOR_COLLISION_H

#include <stddef.h>

#include "particle_system.h"
#include "spatial_grid.h"

typedef struct
{
    float restitution;
} CollisionSettings;

void collision_detect_and_resolve(
    ParticleSystem *particles,
    const SpatialGrid *grid,
    const CollisionSettings *settings
);

void collision_resolve_pair(
    ParticleSystem *particles,
    size_t a,
    size_t b,
    float restitution
);

#endif //PARTICLESIMULATOR_COLLISION_H
