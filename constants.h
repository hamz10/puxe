//
// Created by Hamza Nisar on 16/12/2025.
//

#ifndef GRIDRAY_CONSTANTS_H
#define GRIDRAY_CONSTANTS_H
#include "raylib.h"
namespace constants {
    constexpr static int WINDOW_WIDTH  {1000};
    constexpr static int WINDOW_HEIGHT {1000};
    constexpr static int PIXEL_SIZE {20};
    constexpr static int WIDTH_PIXEL_COUNT {WINDOW_WIDTH/PIXEL_SIZE}; //50
    constexpr static int HEIGHT_PIXEL_COUNT {WINDOW_HEIGHT/PIXEL_SIZE}; //50
    constexpr static int GRAVITY {1};
    constexpr static int STATIC_DENSITY {999};
    constexpr static Color BK_CLR {DARKGRAY};
    constexpr static Color HOVER_CLR {BLUE};
}

#endif //GRIDRAY_CONSTANTS_H
