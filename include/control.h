//
// Created by Hamza Nisar on 16/12/2025.
//

#ifndef GRIDRAY_CONTROL_H
#define GRIDRAY_CONTROL_H
#include "raylib.h"
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
                screen_pos{GetMousePosition()},
                mouseSize{1}
                {};

        [[nodiscard]] Point positionToPoint() const;

        void updateMousePos();
        void drawMouseHover() const;
        void drawMouseTemp() const;
        void changeMouseElement(entities::ElementType type);
        void changeMouseSize(bool increase);
        [[nodiscard]] std::string_view mouseModeToSV() const;
        void cycleMouseMode(bool clockwise);
        static void mouseAction(Mouse& mouse);
        [[nodiscard]] int getMouseCellIDX() const;

        //
        mouseMode mode{};
        entities::ElementType current_element;
        bool is_down{};
        Vector2 prev_pos{};
        Vector2 screen_pos{};
        std::uint16_t mouseSize{};
    };

    struct UserInput {

        static void parseKeyStroke(int input);
        static void isValidKeyPressed();
        static void isMouseDown();

    };

    [[nodiscard]] int pointToCellIDX(Point& point) ;
    void updateGridElement(std::vector<entities::Cell>& Grid, Point& location, int radius, bool mode);
    void transformGridElement(std::vector<entities::Cell>& Grid, int cell_idx, bool Mode);

    extern Mouse mouse;
    constexpr std::array<Mouse::mouseMode,static_cast<std::size_t>(Mouse::mouseMode::MAX_MODES)> mouseModes = {
        {
            Mouse::mouseMode::Neutral, Mouse::mouseMode::Place,Mouse::mouseMode::Delete,
        }};

}

#endif //GRIDRAY_CONTROL_H
