//
// Created by tdragon on 9/8/26.
//

#include "renderer.h"

#include <raylib.h>
#include <stddef.h>

bool renderer_init(
    Renderer *renderer,
    int width,
    int height,
    const char *title
)
{
    if (renderer == NULL)
    {
        return false;
    }

    renderer->width = width;
    renderer->height = height;
    renderer->title = title;

    InitWindow(width, height, title);

    if (!IsWindowReady())
    {
        return false;
    }

    SetTargetFPS(144);

    return true;
}

bool renderer_should_close(const Renderer *renderer)
{
    (void)renderer;

    return WindowShouldClose();
}

float renderer_get_delta_time(const Renderer *renderer)
{
    (void)renderer;

    return GetFrameTime();
}

void renderer_begin_frame(const Renderer *renderer)
{
    (void)renderer;

    BeginDrawing();

    ClearBackground(BLACK);
}

void renderer_end_frame(const Renderer *renderer)
{
    (void)renderer;

    EndDrawing();
}

void renderer_draw_particle(
    const Renderer *renderer,
    float x,
    float y,
    float radius
)
{
    (void)renderer;

    DrawCircle(
        (int)x,
        (int)y,
        radius,
        WHITE
    );
}

void renderer_draw_line(
    const Renderer *renderer,
    float x1,
    float y1,
    float x2,
    float y2
)
{
    (void)renderer;

    DrawLine(
        (int)x1,
        (int)y1,
        (int)x2,
        (int)y2,
        WHITE
    );
}

void renderer_shutdown(Renderer *renderer)
{
    (void)renderer;

    CloseWindow();
}