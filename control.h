//
// Created by Hamza Nisar on 16/12/2025.
//

#ifndef GRIDRAY_CONTROL_H
#define GRIDRAY_CONTROL_H
#include "raylib.h"
#include "constants.h"
#include "entities.h"

namespace control{

    struct Point{
        int x{};
        int y{};
    };

    struct Mouse {

        enum class mouseMode : int {
            Neutral,
            Place,
            Delete,
            MAX_MODES
        };

        Mouse() :
                mode{mouseMode::Neutral},
                current_element{entities::ElementType::AIR},
                is_down{false},
                prev_pos{0, 0},
                screen_pos{GetMousePosition()} {};

        [[nodiscard]] Point positionToPoint() const;
        void updateMousePos();
        void drawMouseHover() const;
        void changeMouseElement(entities::ElementType type);
        static void mouseAction(/*mouseMode mode -- Implemented later!*/);
        [[nodiscard]] int getMouseCellIDX() const;

        //
        mouseMode mode{};
        entities::ElementType current_element;
        bool is_down{};
        Vector2 prev_pos{};
        Vector2 screen_pos{};
    };

    struct UserInput {

        static void parseKeyStroke(int input);
        static void isValidKeyPressed();
        static void isMouseDown();

    };

    void updateGridElement(std::vector<entities::Cell>& Grid, Mouse& mouse);

    extern Mouse mouse;
}

#endif //GRIDRAY_CONTROL_H
