#include <iostream>
#include <cassert>
#include <algorithm>
#include "../include/constants.h"
#include "../include/entities.h"
#include "../include/control.h"
#include "../include/grid.h"
#include "../include/gui.h"
#include "../include/UDP_server.h"
#include "raylib.h"
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"



void update(){
    control::mouse.updateMousePos();
    control::UserInput::isValidKeyPressed();
    control::UserInput::isMouseDown();
    grid::updateSimulation(entities::cellGrid, grid::active_cells);
    //Update server buffer here?
}

void drawScreen(){
    BeginDrawing();
    grid::paintGrid(entities::cellGrid);
    control::mouse.drawMouseHover();
    grid::drawGridLines(BLACK);
    control::mouse.drawMouseTemp();
    GUI::getInstance().openMenu();
    EndDrawing();
}

void init() {
    grid::initActiveCells(grid::active_cells);
    UDP_Server::getInstance().generate_socket();
}

int main() {
    InitWindow(constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT, "puxe");
    SetTargetFPS(60);

    init();
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