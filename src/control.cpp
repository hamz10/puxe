//
// Created by Hamza Nisar on 16/12/2025.
//
#include <iostream>
#include <string>
#include "../include/control.h"
#include "../include/grid.h"

namespace control {

    void Mouse::updateMousePos() {
        prev_pos = screen_pos;
        screen_pos = GetMousePosition();
    }

    Point Mouse::positionToPoint() const{
        const int c_x = std::clamp(static_cast<int>(screen_pos.x), 0, constants::WINDOW_WIDTH - 1);
        const int c_y = std::clamp(static_cast<int>(screen_pos.y), 0, constants::WINDOW_HEIGHT - 1);
        const int x_idx = c_x / constants::PIXEL_SIZE;
        const int y_idx = c_y / constants::PIXEL_SIZE;
        return Point{x_idx, y_idx};
    }

    void Mouse::drawMouseHover() const {
        Point mousePoint {positionToPoint()};
        DrawRectangle(mousePoint.x * constants::PIXEL_SIZE, mousePoint.y * constants::PIXEL_SIZE, constants::PIXEL_SIZE,
                      constants::PIXEL_SIZE, constants::HOVER_CLR);
    }

    void Mouse::drawMouseTemp() const {
        int hoverIDX {getMouseCellIDX()};
        std::int16_t temperature { entities::cellGrid.at(hoverIDX).temperature};
        std::string str { "    "};
        std::to_chars(str.data(), str.data() + str.size(), temperature);
        DrawText(str.c_str(), 50, 50, 20, BLACK );
    }

    void Mouse::changeMouseElement(entities::ElementType type){
        if (mouse.current_element == type) { return;}

        mouse.current_element = type;
        std::cout << "Element changed to " << entities::getElemSV(type) << "\n";
    }

    std::string_view Mouse::mouseModeToSV() const {
        switch (mouse.mode) {
            case Mouse::mouseMode::Neutral: return "Neutral";
            case Mouse::mouseMode::Place: return "Place";
            case Mouse::mouseMode::Delete: return "Delete";
            case Mouse::mouseMode::MAX_MODES:
            default: assert(false && "mouseModeToSV invalid input");
        }
    }

    void Mouse::cycleMouseMode(bool clockwise) {
    if (clockwise) {
        if (mouse.mode == mouseModes[static_cast<std::size_t>(Mouse::mouseMode::MAX_MODES) - 1]) {
        mouse.mode = mouseModes[0];
        } else {
            mouse.mode = mouseModes[static_cast<std::size_t>(mouse.mode) + 1];
        }
    } else {
        if (mouse.mode == mouseModes[0]) {
            mouse.mode = mouseModes[static_cast<std::size_t>(Mouse::mouseMode::MAX_MODES) - 1];
        } else {
            mouse.mode = mouseModes[static_cast<std::size_t>(mouse.mode) - 1];
        }
    }
        std::cout << mouseModeToSV() << '\n';
        return;
    }

    void changeMouseSize(bool increase) {
        if (increase) {
            if (mouse.mouseSize == constants::MAX_MOUSE_SIZE) {
                return;
            } else {
                mouse.mouseSize++;

            }
        } else {
            if (mouse.mouseSize == 0) {
                return;
            } else {
                mouse.mouseSize--;
            }
        }
        std::cout << "Mouse size: " << mouse.mouseSize << '\n';
    }




    void Mouse::mouseAction(Mouse& mouse) {
        Point pos {mouse.positionToPoint()};
        if (mouse.mode == Mouse::mouseMode::Place) {
            control::updateGridElement(entities::cellGrid, pos, mouse.mouseSize, constants::TRANSFORM_ELEM_PLACE);
        } else if (mouse.mode == Mouse::mouseMode::Delete) {
            control::updateGridElement(entities::cellGrid, pos, mouse.mouseSize, constants::TRANSFORM_ELEM_DELETE);
        }
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
            case KEY_FIVE:
                mouse.changeMouseElement(static_cast<entities::ElementType>(input - KEY_ONE));
                break;
            case KEY_Q:
                mouse.cycleMouseMode(false);
                break;
            case KEY_E:
                mouse.cycleMouseMode(true);
                break;
            case KEY_KP_SUBTRACT:
                entities::saveGridState(entities::cellGrid);
                break;
            case KEY_KP_ADD:
                entities::loadGridState(entities::cellGrid);
                break;
            case KEY_MINUS:
                changeMouseSize(false);
                break;
            case KEY_EQUAL:
                changeMouseSize(true);
                break;
            default:
                break;
        }
    }

    void UserInput::isValidKeyPressed(){
        int key {GetKeyPressed()};
        parseKeyStroke(key);

    }

    void UserInput::isMouseDown() {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            Mouse::mouseAction(mouse);
        }
    }

    int control::pointToCellIDX(Point& point){
        return point.y * constants::WIDTH_PIXEL_COUNT + point.x;
    }

    void control::updateGridElement(std::vector<entities::Cell>& Grid,Point& location, int radius, bool mode){
        const int cell_idx = control::pointToCellIDX(location);
        assert(cell_idx >= 0 && cell_idx < Grid.size());
        for (auto y{-radius}; y <= radius; y++) {
            for (auto x{-radius}; x <= radius; x++) {
                int place_x {location.x + x};
                int place_y {location.y + y};
                if (grid::isValidIDX(place_x, place_y)) {
                    transformGridElement(Grid, grid::calcCellIDX(place_x,place_y), mode);
                }
            }
        }

    }


    void control::transformGridElement(std::vector<entities::Cell>& Grid, int cell_idx, bool Mode) {
        if (Mode == constants::TRANSFORM_ELEM_PLACE) {
            if(Grid.at(cell_idx).type == entities::ElementType::AIR) {
                Grid.at(cell_idx).type = mouse.current_element;
                //grid::insertActiveCells(grid::active_cells, cell_idx);
                Grid.at(cell_idx).frames_stationary = 0;  // Fresh placement
                grid::active_cells.insert(cell_idx);
                grid::wakeNeighbour(Grid, grid::active_cells, cell_idx, grid::neighbours_middle_bot);
                }
            }
        if (Mode == constants::TRANSFORM_ELEM_DELETE) {
            if (Grid.at(cell_idx).type != entities::ElementType::AIR) {
                Grid.at(cell_idx).type = entities::ElementType::AIR;
                grid::active_cells.erase(cell_idx);
                grid::wakeNeighbour(Grid, grid::active_cells, cell_idx, grid::neighbours_middle_top);
            }
        }
    }


}
