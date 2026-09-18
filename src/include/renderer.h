//
// Created by tdragon on 9/8/26.
//

#ifndef PARTICLESIMULATOR_RENDERER_H
#define PARTICLESIMULATOR_RENDERER_H

#include <stdbool.h>

typedef struct Renderer
{
    int width;
    int height;
    const char *title;
} Renderer;

/*
 * Initialize the renderer and create the window.
 *
 * Returns true on success.
 */
bool renderer_init(
    Renderer *renderer,
    int width,
    int height,
    const char *title
);

/*
 * Returns true when the application should exit.
 */
bool renderer_should_close(const Renderer *renderer);

/*
 * Time elapsed since the previous frame.
 */
float renderer_get_delta_time(const Renderer *renderer);

/*
 * Begin rendering a frame.
 */
void renderer_begin_frame(const Renderer *renderer);

/*
 * Finish rendering a frame.
 */
void renderer_end_frame(const Renderer *renderer);

/*
 * Draw a particle.
 */
void renderer_draw_particle(
    const Renderer *renderer,
    float x,
    float y,
    float radius
);

/*
 * Draw a line.
 */
void renderer_draw_line(
    const Renderer *renderer,
    float x1,
    float y1,
    float x2,
    float y2
);

/*
 * Shut down the renderer and close the window.
 */
void renderer_shutdown(Renderer *renderer);


#endif //PARTICLESIMULATOR_RENDERER_H
