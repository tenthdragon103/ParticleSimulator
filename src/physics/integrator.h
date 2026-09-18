//
// Created by tdragon on 9/8/26.
//

#ifndef PARTICLESIMULATOR_INTEGRATOR_H
#define PARTICLESIMULATOR_INTEGRATOR_H

#include "particle_system.h"

void integrator_semi_implicit_euler(
    ParticleSystem *particles,
    float dt
);

#endif //PARTICLESIMULATOR_INTEGRATOR_H
