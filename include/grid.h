//
// Created by Hamza Nisar on 16/12/2025.
//

#ifndef GRIDRAY_GRID_H
#define GRIDRAY_GRID_H
#include <cassert>
#include <optional>
#include <unordered_set>
#include <chrono>
#include <iostream>
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

    void initActiveCells(std::unordered_set<int>& active);
    void insertActiveCells(std::unordered_set<int>& active, int cellIDX);
   void drawGridLines(Color color);
    inline int calcCellIDX(const int x, const int y);
    inline bool isValidIDX(const int x, const int y);
    std::optional<int> isValidAdjacentCell(const std::vector<entities::Cell> &cellGrid, const entities::Element& blueprint, const int x, const int y);
    std::optional<int> checkAdjacentCell(const std::vector<entities::Cell> &cellGrid, const entities::Element& blueprint, const int& x, const int& y);
    void paintGrid(const std::vector<entities::Cell> &cellGrid);
    template <std::size_t N> void wakeNeighbour(std::vector<entities::Cell> &cellGrid, std::unordered_set<int>& active, const int cellIDX, std::array<std::pair<int,int>,N>& direc);
    void heatDiffuseNeighbour(std::vector<entities::Cell> &cellGrid,const int cellIDX, std::array<std::pair<int,int>,8>& direc);
    void updateSimulation(std::vector<entities::Cell> &cellGrid, std::unordered_set<int>& active);

    inline std::unordered_set<int> active_cells;
    inline std::array<std::pair<int,int>, 5> neighbours_middle_bot {
            {
                {1, 1},
                {-1, 1},
                {0, 1},
                {1, 0},
                {-1, 0},
            }};
    inline std::array<std::pair<int,int>, 5> neighbours_middle_top {
                {
                    {-1, -1},
                    {0, -1},
                    {1, -1},
                    {1, 0},
                    {-1, 0},
                }};
    inline std::array<std::pair<int,int>, 8> neighbours_all {
                    {
                        {-1, -1},
                        { 0, -1},
                        { 1, -1},
                        { 1,  0},
                        {-1,  0},
                        {-1,  1},
                        { 0,  1},
                        { 1,  1}
                    }};
    inline int frame_count {0};
    inline long long total_time {0};
}
#endif //GRIDRAY_GRID_H
