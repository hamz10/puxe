//
// Created by Hamza Nisar on 16/12/2025.
//

#ifndef GRIDRAY_GRID_H
#define GRIDRAY_GRID_H
#include <cassert>
#include <optional>
#include "constants.h"
#include "entities.h"

namespace grid {

  /*  enum class dir {
        down,
        left,
        right,
        down_left,
        down_right,
        MAX_DIR
    };
*/ // Will implement this when needed for specific viscosity behaviours!


    void drawGridLines(Color color);
    static int calcCellIDX(const int x, const int y);
    static bool isValidIDX(const int x, const int y);
    std::optional<int> isValidAdjacentCell(const std::vector<entities::Cell> &cellGrid, const entities::Element& blueprint, const int x, const int y);
    std::optional<int> checkAdjacentCell(const std::vector<entities::Cell> &cellGrid, const entities::Element& blueprint, const int& x, const int& y);
    void paintGrid(const std::vector<entities::Cell> &cellGrid);
    void updateSimulation(std::vector<entities::Cell> &cellGrid);

}
#endif //GRIDRAY_GRID_H
