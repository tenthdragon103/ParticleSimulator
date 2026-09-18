//
// Created by tdragon on 9/8/26.
//

#ifndef PARTICLESIMULATOR_UI_H
#define PARTICLESIMULATOR_UI_H

#include <stdbool.h>

typedef struct UI
{
    bool paused;

    bool showGrid;
    bool showAxes;

    float simulationSpeed;

    float mouseX;
    float mouseY;

    bool mouseDown;
    bool mousePressed;
    bool mouseReleased;

    bool resetPressed;

} UI;

/*
 * Initialize UI state.
 */
void ui_init(UI *ui);

/*
 * Read keyboard and mouse input for the current frame.
 */
void ui_update(UI *ui);

/*
 * Returns whether the simulation is currently paused.
 */
bool ui_is_paused(const UI *ui);

/*
 * Returns the simulation speed multiplier.
 */
float ui_get_simulation_speed(const UI *ui);

/*
 * Returns the current mouse X coordinate.
 */
float ui_get_mouse_x(const UI *ui);

/*
 * Returns the current mouse Y coordinate.
 */
float ui_get_mouse_y(const UI *ui);

/*
 * Returns true if the mouse button is currently held.
 */
bool ui_is_mouse_down(const UI *ui);

/*
 * Returns true for the frame the mouse button was pressed.
 */
bool ui_is_mouse_pressed(const UI *ui);

/*
 * Returns true for the frame the mouse button was released.
 */
bool ui_is_mouse_released(const UI *ui);

/*
 * Returns true when the user requested a reset.
 */
bool ui_reset_requested(const UI *ui);

#endif //PARTICLESIMULATOR_UI_H
