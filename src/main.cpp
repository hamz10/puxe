#include <iostream>
#include <cassert>
#include <algorithm>
#include "../include/constants.h"
#include "../include/entities.h"
#include "../include/control.h"
#include "../include/grid.h"
#include "raylib.h"
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
//#include "raygui.h"

void update(){
    control::mouse.updateMousePos();
    control::UserInput::isValidKeyPressed();
    control::UserInput::isMouseDown();
    grid::updateSimulation(entities::cellGrid);
}

void drawScreen(){
    BeginDrawing();
    grid::paintGrid(entities::cellGrid);
    control::mouse.drawMouseHover();
    grid::drawGridLines(BLACK);
    EndDrawing();
}

int main() {
    InitWindow(constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT, "raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        update();
        drawScreen();
    }

    CloseWindow();
    return 0;
    }

/*
Coord orientation:
origin--------->
|         +x
|
|
| +y
|
v
*/