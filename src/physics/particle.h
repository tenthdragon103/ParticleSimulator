//
// Created by tdragon on 9/8/26.
//

#ifndef PARTICLESIMULATOR_PARTICLE_H
#define PARTICLESIMULATOR_PARTICLE_H

typedef struct Particle
{
    float x;
    float y;
    float z;

    float vx;
    float vy;
    float vz;

    float massAmu;
    float radius;

    const char *makeup; // always "particle" for now
} Particle;

/*
 * Creates a particle with the supplied properties.
 */
Particle particle_create(
    float x,
    float y,
    float z,
    float vx,
    float vy,
    float vz,
    float massAmu
);

#endif //PARTICLESIMULATOR_PARTICLE_H
