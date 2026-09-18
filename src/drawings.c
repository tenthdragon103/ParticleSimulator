//
// Created by tdragon on 9/8/26.
//

#include "drawings.h"

#include <stddef.h>

void draw_particle(
    const Renderer *renderer,
    const Particle *particle
)
{
    if (particle == NULL)
    {
        return;
    }

    renderer_draw_particle(
        renderer,
        particle->x,
        particle->y,
        particle->radius
    );
}

void draw_particles(
    const Renderer *renderer,
    const Particle *particles,
    int count
)
{
    if (particles == NULL || count <= 0)
    {
        return;
    }

    for (int i = 0; i < count; i++)
    {
        draw_particle(renderer, &particles[i]);
    }
}

void draw_axes(
    const Renderer *renderer
)
{
    renderer_draw_line(
        renderer,
        0.0f,
        renderer->height / 2.0f,
        (float)renderer->width,
        renderer->height / 2.0f
    );

    renderer_draw_line(
        renderer,
        renderer->width / 2.0f,
        0.0f,
        renderer->width / 2.0f,
        (float)renderer->height
    );
}

void draw_grid(
    const Renderer *renderer,
    float spacing
)
{
    if (spacing <= 0.0f)
    {
        return;
    }

    /*
     * Vertical lines.
     */
    for (float x = 0.0f; x <= renderer->width; x += spacing)
    {
        renderer_draw_line(
            renderer,
            x,
            0.0f,
            x,
            (float)renderer->height
        );
    }

    /*
     * Horizontal lines.
     */
    for (float y = 0.0f; y <= renderer->height; y += spacing)
    {
        renderer_draw_line(
            renderer,
            0.0f,
            y,
            (float)renderer->width,
            y
        );
    }
}