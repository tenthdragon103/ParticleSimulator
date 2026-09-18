//
// Created by tdragon on 9/8/26.
//

typedef struct Particle
{
    float x;
    float y;
    float z;

    float vx;
    float vy;
    float vz;

    float massAmu;

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