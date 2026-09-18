#include "renderer.h"
#include "drawings.h"
#include "ui.h"
#include "physics/physics.h"

#include <stdlib.h>
#include <time.h>

#define PARTICLE_COUNT 5000
#define WINDOW_INIT_SIZE_W 1400 //1280
#define WINDOW_INIT_SIZE_H 840 //720

int main(void)
{
    Renderer renderer;

    if (!renderer_init(
        &renderer,
        WINDOW_INIT_SIZE_W,
        WINDOW_INIT_SIZE_H,
        "Particle Simulator"
    ))
    {
        return 1;
    }

    UI ui;
    ui_init(&ui);

    Physics physics;

    if (!physics_init(
        &physics,
        WINDOW_INIT_SIZE_W,
        WINDOW_INIT_SIZE_H,
        PARTICLE_COUNT
    ))
    {
        renderer_shutdown(&renderer);
        return 1;
    }

    /*
     * Create particles.
     *
     * We arrange them in a grid so they don't
     * start overlapping each other.
     */
    int columns = 50;
    srand((unsigned int)time(NULL));

    for (int i = 0; i < PARTICLE_COUNT; ++i)
    {
        int column = i % columns;
        int row = i / columns;

        float x = 50.0f + column * 12.0f;
        float y = 50.0f + row * 12.0f;

        /*
         * Give each particle a small initial
         * horizontal velocity.
         */

        const float vx = (rand() % 100) - 50;
        const float vy = (rand() % 100) - 50;
        const float mass = (rand() % 5) + 1;

        physics_add_particle(
            &physics,
            x,
            y,
            vx,
            vy,
            mass,
            mass
        );
    }

    while (!renderer_should_close(&renderer))
    {
        float dt =
            renderer_get_delta_time(&renderer);

        ui_update(&ui);

        if (ui.mouseDown)
        {
            physics_set_mouse_particle(
                &physics,
                ui.mouseX,
                ui.mouseY
            );
        }

        if (!ui_is_paused(&ui))
        {
            physics_step(
                &physics,
                dt
            );
        }

        renderer_begin_frame(&renderer);

        /*
         * Draw particles.
         */
        ParticleSystem *particles =
            physics_particles(&physics);

        for (
            size_t i = 0;
            i < particles->count;
            i++
        )
        {
            Particle particle = {
                .x = particles->x[i],
                .y = particles->y[i],
                .vx = particles->vx[i],
                .vy = particles->vy[i],
                .massAmu = particles->mass[i],
                .radius = particles->radius[i],
                .makeup = "particle"
            };

            draw_particle(
                &renderer,
                &particle
            );
        }

        renderer_end_frame(&renderer);
    }

    physics_destroy(&physics);

    renderer_shutdown(&renderer);

    return 0;
}