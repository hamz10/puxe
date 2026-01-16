//
// Created by Hamza Nisar on 16/12/2025.
//

#ifndef GRIDRAY_CONSTANTS_H
#define GRIDRAY_CONSTANTS_H
#include "raylib.h"
#include <cstdint>



namespace constants {
    constexpr static int WINDOW_WIDTH  {1000};
    constexpr static int WINDOW_HEIGHT {1000};
    constexpr static int PIXEL_SIZE {20};
    constexpr static int WIDTH_PIXEL_COUNT {WINDOW_WIDTH/PIXEL_SIZE}; //50
    constexpr static int HEIGHT_PIXEL_COUNT {WINDOW_HEIGHT/PIXEL_SIZE}; //50
    //constexpr static int GRAVITY {1};
    constexpr static int STATIC_DENSITY {999};
    constexpr static std::int16_t AMBIENT_TEMPERATURE {20};
    constexpr static std::int16_t MIN_TEMPERATURE {-273};
    constexpr static std::int16_t MAX_TEMPERATURE {2000};
    constexpr static std::int16_t EQUILIBRIUM_RATE {5};
    constexpr static std::int16_t COOLING_RATE {20};
    constexpr static std::int16_t FIRE_TEMPERATURE {800};
    constexpr static std::int16_t NO_STATE_CHANGE {-275};
    constexpr static std::uint8_t MAX_MOUSE_SIZE {3};
    constexpr static Color BK_CLR {DARKGRAY};
    constexpr static Color HOVER_CLR {BLUE};
    constexpr static bool TRANSFORM_ELEM_PLACE {false};
    constexpr static bool TRANSFORM_ELEM_DELETE {true};
}

#endif //GRIDRAY_CONSTANTS_H
