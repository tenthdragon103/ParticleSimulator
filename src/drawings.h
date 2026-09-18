//
// Created by tdragon on 9/8/26.
//

#ifndef PARTICLESIMULATOR_DRAWINGS_H
#define PARTICLESIMULATOR_DRAWINGS_H

#include "renderer.h"
#include "physics/particle.h"

/*
 * Draw a single particle.
 */
void draw_particle(
    const Renderer *renderer,
    const Particle *particle
);

/*
 * Draw multiple particles.
 */
void draw_particles(
    const Renderer *renderer,
    const Particle *particles,
    int count
);

/*
 * Draw the simulation coordinate axes.
 */
void draw_axes(
    const Renderer *renderer
);

/*
 * Draw a grid across the simulation area.
 */
void draw_grid(
    const Renderer *renderer,
    float spacing
);

#endif //PARTICLESIMULATOR_DRAWINGS_H
