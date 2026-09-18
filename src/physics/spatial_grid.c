//
// Created by tdragon on 9/8/26.
//

#include "spatial_grid.h"

#include <stdlib.h>
#include <string.h>

static size_t cell_index(
    const SpatialGrid *grid,
    int x,
    int y
)
{
    return (size_t)y * (size_t)grid->width
         + (size_t)x;
}

int spatial_grid_init(
    SpatialGrid *grid,
    int width,
    int height,
    float cell_size,
    size_t particle_capacity
)
{
    if (
        grid == NULL ||
        width <= 0 ||
        height <= 0 ||
        cell_size <= 0.0f
    )
    {
        return 0;
    }

    memset(grid, 0, sizeof(SpatialGrid));

    grid->width = width;
    grid->height = height;
    grid->cell_size = cell_size;

    grid->cell_count =
        (size_t)width * (size_t)height;

    grid->cell_start = calloc(
        grid->cell_count,
        sizeof(size_t)
    );

    grid->cell_end = calloc(
        grid->cell_count,
        sizeof(size_t)
    );

    if (
        grid->cell_start == NULL ||
        grid->cell_end == NULL
    )
    {
        spatial_grid_destroy(grid);
        return 0;
    }

    return spatial_grid_resize_particles(
        grid,
        particle_capacity
    );
}

void spatial_grid_destroy(
    SpatialGrid *grid
)
{
    if (grid == NULL)
    {
        return;
    }

    free(grid->cell_start);
    free(grid->cell_end);

    free(grid->particle_indices);
    free(grid->particle_cells);

    memset(grid, 0, sizeof(SpatialGrid));
}

int spatial_grid_resize_particles(
    SpatialGrid *grid,
    size_t particle_capacity
)
{
    if (grid == NULL)
    {
        return 0;
    }

    if (particle_capacity <= grid->particle_capacity)
    {
        return 1;
    }

    size_t *indices = realloc(
        grid->particle_indices,
        particle_capacity * sizeof(size_t)
    );

    size_t *cells = realloc(
        grid->particle_cells,
        particle_capacity * sizeof(size_t)
    );

    if (
        indices == NULL ||
        cells == NULL
    )
    {
        return 0;
    }

    grid->particle_indices = indices;
    grid->particle_cells = cells;

    grid->particle_capacity = particle_capacity;

    return 1;
}

int spatial_grid_get_cell(
    const SpatialGrid *grid,
    float x,
    float y
)
{
    int cx = (int)(x / grid->cell_size);
    int cy = (int)(y / grid->cell_size);

    if (cx < 0)
    {
        cx = 0;
    }

    if (cy < 0)
    {
        cy = 0;
    }

    if (cx >= grid->width)
    {
        cx = grid->width - 1;
    }

    if (cy >= grid->height)
    {
        cy = grid->height - 1;
    }

    return (int)cell_index(grid, cx, cy);
}

void spatial_grid_build(
    SpatialGrid *grid,
    const ParticleSystem *particles
)
{
    if (
        grid == NULL ||
        particles == NULL
    )
    {
        return;
    }

    memset(
        grid->cell_start,
        0,
        grid->cell_count * sizeof(size_t)
    );

    memset(
        grid->cell_end,
        0,
        grid->cell_count * sizeof(size_t)
    );

    /*
     * Count particles per cell.
     */
    for (size_t i = 0; i < particles->count; i++)
    {
        size_t cell = (size_t)spatial_grid_get_cell(
            grid,
            particles->x[i],
            particles->y[i]
        );

        grid->particle_cells[i] = cell;

        grid->cell_end[cell]++;
    }

    /*
     * Convert counts to ranges.
     */
    size_t offset = 0;

    for (size_t i = 0; i < grid->cell_count; i++)
    {
        size_t count = grid->cell_end[i];

        grid->cell_start[i] = offset;

        offset += count;

        grid->cell_end[i] = offset;
    }

    /*
     * Temporary positions used while filling
     * the sorted particle array.
     */
    size_t *write_positions = calloc(
        grid->cell_count,
        sizeof(size_t)
    );

    if (write_positions == NULL)
    {
        return;
    }

    memcpy(
        write_positions,
        grid->cell_start,
        grid->cell_count * sizeof(size_t)
    );

    for (size_t i = 0; i < particles->count; i++)
    {
        size_t cell = grid->particle_cells[i];

        size_t position =
            write_positions[cell]++;

        grid->particle_indices[position] = i;
    }

    free(write_positions);
}