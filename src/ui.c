//
// Created by tdragon on 9/8/26.
//

#include "ui.h"

#include <raylib.h>
#include <stddef.h>

void ui_init(UI *ui)
{
    if (ui == NULL) {
        return;
    }

    ui->paused = false;
    ui->showGrid = false;
    ui->showAxes = false;
    ui->simulationSpeed = 1.0f;

    ui->mouseX = 0.0f;
    ui->mouseY = 0.0f;

    ui->mouseDown = false;
    ui->mousePressed = false;
    ui->mouseReleased = false;
    ui->resetPressed = false;
}

void ui_update(UI *ui)
{
    if (ui == NULL) {
        return;
    }

    /*
     * Continuously track the mouse.
     */
    Vector2 mouse = GetMousePosition();

    ui->mouseX = mouse.x;
    ui->mouseY = mouse.y;

    /*
     * Mouse buttons.
     */
    ui->mouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    ui->mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    ui->mouseReleased = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);

    /*
     * Keyboard controls.
     */
    if (IsKeyPressed(KEY_SPACE)) {
        ui->paused = !ui->paused;
    }

    if (IsKeyPressed(KEY_G)) {
        ui->showGrid = !ui->showGrid;
    }

    if (IsKeyPressed(KEY_A)) {
        ui->showAxes = !ui->showAxes;
    }

    if (IsKeyPressed(KEY_R)) {
        ui->resetPressed = true;
    }

    if (IsKeyPressed(KEY_ONE)) {
        ui->simulationSpeed = 0.25f;
    }

    if (IsKeyPressed(KEY_TWO)) {
        ui->simulationSpeed = 0.5f;
    }

    if (IsKeyPressed(KEY_THREE)) {
        ui->simulationSpeed = 1.0f;
    }

    if (IsKeyPressed(KEY_FOUR)) {
        ui->simulationSpeed = 2.0f;
    }

    if (IsKeyPressed(KEY_FIVE)) {
        ui->simulationSpeed = 4.0f;
    }
}

bool ui_is_paused(const UI *ui)
{
    return ui != NULL && ui->paused;
}

float ui_get_simulation_speed(const UI *ui)
{
    if (ui == NULL)
    {
        return 1.0f;
    }

    return ui->simulationSpeed;
}

float ui_get_mouse_x(const UI *ui)
{
    return ui != NULL ? ui->mouseX : 0.0f;
}

float ui_get_mouse_y(const UI *ui)
{
    return ui != NULL ? ui->mouseY : 0.0f;
}

bool ui_is_mouse_down(const UI *ui)
{
    return ui != NULL && ui->mouseDown;
}

bool ui_is_mouse_pressed(const UI *ui)
{
    return ui != NULL && ui->mousePressed;
}

bool ui_is_mouse_released(const UI *ui)
{
    return ui != NULL && ui->mouseReleased;
}

bool ui_reset_requested(const UI *ui)
{
    return ui != NULL && ui->resetPressed;
}