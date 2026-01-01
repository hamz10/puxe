//
// Created by Hamza Nisar on 16/12/2025.
//
#include "../include/grid.h"
#include "../include/random.h"

void grid::initActiveCells(std::unordered_set<int>& active) {
    active.clear();
    active.reserve(5000);
}

void grid::insertActiveCells(std::unordered_set<int>& active, int cellIDX) {
    active.insert(cellIDX);
    entities::cellGrid.at(cellIDX).frames_stationary = 0;
}

void grid::drawGridLines(Color color) {
    int x{0};
    int y{0};
    for (; x < constants::WINDOW_WIDTH; x = x + constants::PIXEL_SIZE) {
        DrawLine(x, y, x, y + constants::WINDOW_HEIGHT, color);
    }
    x = 0;
    for (; y < constants::WINDOW_HEIGHT; y = y + constants::PIXEL_SIZE) {
        DrawLine(x, y, x + constants::WINDOW_WIDTH, y, color);
    }
}

void grid::paintGrid(const std::vector<entities::Cell>& cellGrid){

    for(int yIdx{0}; yIdx < constants::HEIGHT_PIXEL_COUNT; ++yIdx){
        for(int xIdx{0}; xIdx < constants::WIDTH_PIXEL_COUNT; ++xIdx){
            const int xCoord = xIdx * constants::PIXEL_SIZE;
            const int yCoord = yIdx * constants::PIXEL_SIZE;
            const int cellIdx = yIdx * constants::WIDTH_PIXEL_COUNT + xIdx;
            assert(cellIdx >= 0 && cellIdx < cellGrid.size());
            const entities::Element& blueprint {entities::ELEMENT_PROPERTIES[static_cast<std::size_t>(cellGrid.at(cellIdx).type)]};
            DrawRectangle(xCoord, yCoord, constants::PIXEL_SIZE, constants::PIXEL_SIZE, blueprint.m_color);
        }
    }
}

int grid::calcCellIDX(const int x, const int y){
    return y * constants::WIDTH_PIXEL_COUNT + x;
}

bool grid::isValidIDX(const int x, const int y){
return((x >= 0 && x < constants::WIDTH_PIXEL_COUNT) && (y >= 0 && y <constants::HEIGHT_PIXEL_COUNT));
}


std::optional<int> grid::isValidAdjacentCell(const std::vector<entities::Cell> &cellGrid, const entities::Element& blueprint, const int x, const int y){
    if (!isValidIDX(x, y))
        return std::nullopt;
    const int cellIdx {calcCellIDX(x, y)};
    if (cellGrid.at(cellIdx).type == entities::ElementType::AIR ||
        (entities::ELEMENT_PROPERTIES[static_cast<std::size_t>(cellGrid.at(cellIdx).type)].m_density < blueprint.m_density))   {
        return cellIdx;
    }
    return std::nullopt;

}

std::optional<int> grid::checkAdjacentCell(const std::vector<entities::Cell> &cellGrid, const entities::Element& blueprint, const int& x, const int& y) {
    auto cellIdx {isValidAdjacentCell(cellGrid, blueprint, x, y+1)};
    if (cellIdx){
        return cellIdx;
    }

    const int direc {(Random::get(0,1))? 1 : -1};
    const std::array<int,2> offsets{direc, -direc};
    for (int offset: offsets) {
        if (auto idx {isValidAdjacentCell(cellGrid, blueprint, x+offset, y+1)}) {
            return idx;
        }
    }
    if (blueprint.m_density < 5) { //check lateral movements for liquids
        for (int offset: offsets) {
            if (auto idx {isValidAdjacentCell(cellGrid, blueprint, x+offset, y)}) {
                return idx;
            }
        }
    }
    return std::nullopt;
}

//MAKE TEMPLATED VERSION FOR DELETION OF BLOCK! WILL HAVE TO TURN ARRAY OF PAIRS INTO A PARAMETER RATHER THAN HARDCODED

template <std::size_t N>
void grid::wakeNeighbour(std::vector<entities::Cell> &cellGrid, std::unordered_set<int>& active, const int cellIDX, std::array<std::pair<int,int>,N>& neighbours)
     {
    int x {cellIDX % constants::WIDTH_PIXEL_COUNT};
    int y {cellIDX / constants::WIDTH_PIXEL_COUNT};

    for (auto [nx, ny]: neighbours) {
        int ax = x+nx;
        int ay = y+ny;
        if (isValidIDX(ax, ay)) {
            int neighbourIdx { calcCellIDX(ax,ay)};
            grid::insertActiveCells(active, neighbourIdx);
        }
    }
}

void grid::updateSimulation(std::vector<entities::Cell> &cellGrid, std::unordered_set<int>& active) {
    auto start {std::chrono::high_resolution_clock::now()};
    std::vector<int> to_inactive{};

    for(auto& cell : active) cellGrid.at(cell).updated_this_frame = false;

    for (int cellIDX: active) {
        if (cellGrid.at(cellIDX).updated_this_frame) {
            continue;
        }
        const int xIdx {cellIDX % constants::WIDTH_PIXEL_COUNT};
        const int yIdx {cellIDX / constants::WIDTH_PIXEL_COUNT};

        const entities::Element& blueprint {
            (entities::ELEMENT_PROPERTIES[static_cast<std::size_t>(cellGrid.at(cellIDX).type)])};

        if(!blueprint.m_isMovable){
            continue; //Items that do not move, don't move!
        }
        auto targetIDX {checkAdjacentCell(cellGrid, blueprint, xIdx, yIdx)};
        if(!targetIDX){
            cellGrid.at(cellIDX).updated_this_frame = true;
            if (cellGrid.at(cellIDX).frames_stationary < 3) {
                cellGrid.at(cellIDX).frames_stationary++;
            } else {
                to_inactive.push_back(cellIDX);
            }
            continue; //Nowhere to move!
        }
        entities::ElementType swap {cellGrid.at(*targetIDX).type};
        cellGrid.at(*targetIDX).type = cellGrid.at(cellIDX).type;
        cellGrid.at(cellIDX).type = swap;
        cellGrid.at(*targetIDX).updated_this_frame = true;
        wakeNeighbour(cellGrid, active, cellIDX, grid::neighbours_middle_top);
        wakeNeighbour(cellGrid, active, *targetIDX, grid::neighbours_middle_bot);

    }

    for (int cellIDX: to_inactive) {
        active.erase(cellIDX);
    }



    auto end {std::chrono::high_resolution_clock::now()};
    auto delta { std::chrono::duration_cast<std::chrono::microseconds>(end-start)};

    total_time += delta.count();
    frame_count++;

    if (frame_count % 100 == 0) {
        std::cout << "Average update time: " << (total_time / frame_count)
                  << "microseconds\n";
    }

}

//Essentially a bottom-up update looping the full grid to check for potential movements
