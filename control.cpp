//
// Created by Hamza Nisar on 16/12/2025.
//
#include <iostream>
#include "control.h"

namespace control {

    void Mouse::updateMousePos() {
        prev_pos = screen_pos;
        screen_pos = GetMousePosition();
    }

    Point Mouse::positionToPoint() const{
        int c_x = std::clamp(static_cast<int>(screen_pos.x), 0, constants::WINDOW_WIDTH - 1);
        int c_y = std::clamp(static_cast<int>(screen_pos.y), 0, constants::WINDOW_HEIGHT - 1);
        int x_idx = c_x / constants::PIXEL_SIZE;
        int y_idx = c_y / constants::PIXEL_SIZE;
        return Point{x_idx, y_idx};
    }

    void Mouse::drawMouseHover() const {
        Point mousePoint {positionToPoint()};
        DrawRectangle(mousePoint.x * constants::PIXEL_SIZE, mousePoint.y * constants::PIXEL_SIZE, constants::PIXEL_SIZE,
                      constants::PIXEL_SIZE, constants::HOVER_CLR);
    }

    void Mouse::changeMouseElement(entities::ElementType type){
        if (mouse.current_element == type) { return;}

        mouse.current_element = type;
        std::cout << "Element changed to " << entities::getElemSV(type) << "\n";
    }

    void Mouse::mouseAction() {
        control::updateGridElement(entities::cellGrid, control::mouse);
    }

    int Mouse::getMouseCellIDX() const {
        Point mousePoint {positionToPoint()};
        return mousePoint.y * constants::WIDTH_PIXEL_COUNT + mousePoint.x;

    }

    Mouse mouse{};

    void UserInput::parseKeyStroke(int input){
        switch (input) {
            case KEY_ZERO:
            case KEY_ONE:
            case KEY_TWO:
            case KEY_THREE:
            case KEY_FOUR:
                mouse.changeMouseElement(static_cast<entities::ElementType>(input - KEY_ONE));
                break;
            default:
                break;
        }
    }

    void UserInput::isValidKeyPressed(){
        int key {GetKeyPressed()};
        if (key >= KEY_ZERO && key <= KEY_NINE){
        parseKeyStroke(key);
        }
    }

    void UserInput::isMouseDown() {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            Mouse::mouseAction();
        }
    }

    void control::updateGridElement(std::vector<entities::Cell>& Grid, Mouse& mouse){
        const int cell_idx = mouse.getMouseCellIDX();
        assert(cell_idx >= 0 && cell_idx < Grid.size());
        if(Grid.at(cell_idx).type != mouse.current_element && Grid.at(cell_idx).type == entities::ElementType::AIR) {
            Grid.at(cell_idx).type = mouse.current_element;
        }
    }

}