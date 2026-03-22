//
// Created by Hamza Nisar on 16/12/2025.
//
#include "../include/entities.h"

namespace entities {

    std::vector<Cell> cellGrid(constants::WIDTH_PIXEL_COUNT * constants::HEIGHT_PIXEL_COUNT);

    void saveGridState(std::vector<Cell> &cellGrid) {
    std::ofstream outFile {"savefile.txt", std::ios::trunc | std::ios::binary};
        if (!outFile) {
            std::cerr << "Error creating savefile.txt" << '\n';
            return;
        }

        size_t size = cellGrid.size();
        outFile.write(reinterpret_cast<char*>(&size), sizeof(size_t));

        outFile.write(reinterpret_cast<char*>(&cellGrid[0]), cellGrid.size() * sizeof(Cell));

        outFile.close();
        std::cout << "SAVED GRID" << '\n';

    }

    void loadGridState(std::vector<Cell> &cellGrid) {
        std::ifstream inFile {"savefile.txt", std::ios::binary};
        if (!inFile) {
            std::cerr << "Error opening savefile.txt" << '\n';
            return;
        }

        size_t size = cellGrid.size();
        size_t checksum{};
        inFile.read(reinterpret_cast<char*>(&checksum), sizeof(size_t));
        if (!inFile) {
            std::cerr << "Error reading from savefile.txt" << std::endl;
            return;
        }
        if (size != checksum) {
            std::cerr << "Incorrect grid size! checksum size: " << checksum << " != " << size << std::endl;
            return;
        }
        inFile.read(reinterpret_cast<char*>(cellGrid.data()), size * sizeof(Cell));

        std::cout << "LOADED GRID" << '\n';

    }

    void entities::UDPupdateGrid(std::vector<Cell> &cellGrid, Cell *buffer) {
        memmove(buffer, cellGrid.data(), cellGrid.size() * sizeof(Cell));
    }

}