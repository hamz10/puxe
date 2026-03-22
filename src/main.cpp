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
#include "../include/UDP_client.h"

static int runType {-1};

void update() {
    if (runType == 0) {
        control::mouse.updateMousePos();
        control::UserInput::isValidKeyPressed();
        control::UserInput::isMouseDown();
        {
            std::lock_guard<std::mutex> lock(UDP_Client::getInstance().get_mutex());
            grid::updateSimulation(entities::cellGrid, grid::active_cells);
        }
    } else {
        control::mouse.updateMousePos();

    }
    //Update server buffer here?
}

void drawScreen() {
    BeginDrawing();
    {
        std::lock_guard<std::mutex> lock(UDP_Client::getInstance().get_mutex());
        grid::paintGrid(entities::cellGrid);
    }
    control::mouse.drawMouseHover();
    grid::drawGridLines(BLACK);
    control::mouse.drawMouseTemp();
    GUI::getInstance().openMenu();
    EndDrawing();
}

void init() {
    if (runType == 0) {
        grid::initActiveCells(grid::active_cells);
        UDP_Server::getInstance().generate_socket();
    } else {
        UDP_Client::getInstance().generate_listener();
    }
}

int getOption() {
    int x;
    std::cin >> x;
    if (x == 0 || x == 1) {
        return x;
    } else {
        std::cerr << "Wrong option. Please try again.";
        exit(-1);
    }
}

int main() {
    std::cout << "Server - 0 or Client - 1?";
    runType = getOption();
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