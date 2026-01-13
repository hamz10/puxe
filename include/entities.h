//
// Created by Hamza Nisar on 16/12/2025.
//

#ifndef GRIDRAY_ENTITIES_H
#define GRIDRAY_ENTITIES_H

#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string_view>
#include <cassert>
#include "constants.h"


namespace entities {
    enum class ElementType {
        AIR,
        SAND,
        WATER,
        STONE,
        FIRE,
        MAX_ELEM
    };

    inline std::string_view getElemSV(ElementType ID){
        assert(ID < ElementType::MAX_ELEM);
        switch (static_cast<std::size_t>(ID)) {
            case static_cast<std::size_t>(ElementType::AIR):
                return "AIR";
            case static_cast<std::size_t>(ElementType::SAND):
                return "SAND";
            case static_cast<std::size_t>(ElementType::WATER):
                return "WATER";
            case static_cast<std::size_t>(ElementType::STONE):
                return "STONE";
            case static_cast<std::size_t>(ElementType::FIRE):
                return "FIRE";
            default: return "ERR";
        }
    }


    struct Element{
        ElementType m_type;
        Color m_color;
        int m_weight;
        int m_density;
        bool m_isMovable;

        constexpr Element() = delete;
        constexpr Element(ElementType type, Color color, int weight, int density, bool movable) : // Default will be AIR
                m_type{type},
                m_color{color}, // Uses BK_CLR for visual consistency
                m_weight{weight},
                m_density{density},
                m_isMovable{movable}
        {};
        ~Element() = default;



    };

    constexpr std::size_t ElemCount {static_cast<std::size_t>(ElementType::MAX_ELEM)};

    constexpr Element ELEMENT_PROPERTIES[ElemCount] = {
            Element{
                ElementType::AIR,
                constants::BK_CLR,
                -1,
                -1,
                false
            },
            Element{
                ElementType::SAND,
                YELLOW,
                5,
                5,
                true
            },
            Element{
                ElementType::WATER,
                BLUE,
                3,
                1,
                true
            },
            Element{
                ElementType::STONE,
                GRAY,
                -1,
                constants::STATIC_DENSITY,
                false
            },
            Element{
                ElementType::FIRE,
                RED,
                0,
                0,
                true
        },

    };

    struct Cell {
        ElementType type;
        bool updated_this_frame;
        int frames_stationary; //fuel timer for fires
        std::int16_t temperature;

        Cell() : type{ElementType::AIR}, updated_this_frame{false}, frames_stationary {0}, temperature {constants::AMBIENT_TEMPERATURE} {};
        ~Cell() = default;

    };


    extern std::vector<Cell> cellGrid;

    void saveGridState(std::vector<Cell> &cellGrid);
    void loadGridState(std::vector<Cell> &cellGrid);
}

#endif //GRIDRAY_ENTITIES_H
