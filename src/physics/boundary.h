//
// Created by tdragon on 9/8/26.
//

#ifndef PARTICLESIMULATOR_BOUNDARY_H
#define PARTICLESIMULATOR_BOUNDARY_H

#include "particle_system.h"

typedef struct {
    float min_x;
    float min_y;
    float max_x;
    float max_y;
    float restitution;
} Boundary;

void boundary_resolve_particles(
    ParticleSystem *particles,
    const Boundary *boundary
);

#endif //PARTICLESIMULATOR_BOUNDARY_H
