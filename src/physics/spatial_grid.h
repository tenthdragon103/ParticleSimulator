//
// Created by tdragon on 9/8/26.
//

#ifndef PARTICLESIMULATOR_SPATIAL_GRID_H
#define PARTICLESIMULATOR_SPATIAL_GRID_H

#include <stddef.h>

#include "particle_system.h"

typedef struct
{
    float cell_size;

    int width;
    int height;

    size_t cell_count;

    /*
     * Start/end ranges into particle_indices.
     */
    size_t *cell_start;
    size_t *cell_end;

    /*
     * Particles sorted by cell.
     */
    size_t *particle_indices;

    /*
     * Cell ID for every particle.
     */
    size_t *particle_cells;

    size_t particle_capacity;

} SpatialGrid;

int spatial_grid_init(
    SpatialGrid *grid,
    int width,
    int height,
    float cell_size,
    size_t particle_capacity
);

void spatial_grid_destroy(
    SpatialGrid *grid
);

int spatial_grid_resize_particles(
    SpatialGrid *grid,
    size_t particle_capacity
);

void spatial_grid_build(
    SpatialGrid *grid,
    const ParticleSystem *particles
);

int spatial_grid_get_cell(
    const SpatialGrid *grid,
    float x,
    float y
);

#endif //PARTICLESIMULATOR_SPATIAL_GRID_H
