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
        WOOD,
        ICE,
        FROST,
        MAX_ELEM
    };

    constexpr ElementType NULL_ELEMENT {ElementType::MAX_ELEM};

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
            case static_cast<std::size_t>(ElementType::WOOD):
                return "WOOD";
            case static_cast<std::size_t>(ElementType::ICE):
                return "ICE";
            case static_cast<std::size_t>(ElementType::FROST):
                return "FROST";
            default: return "ERR";
        }
    }


    struct Element{
        ElementType m_type;
        Color m_color;
        int m_weight;
        int m_density;
        bool m_isMovable;
        std::int16_t m_melting_point;
        ElementType m_meltIntoElement;
        std::int16_t m_ignition_point;
        ElementType m_igniteIntoElement;
        std::int16_t m_freezing_point;
        ElementType m_freezeIntoElement;

        constexpr Element() = delete;
        constexpr Element(ElementType type, Color color, int weight, int density, bool movable,
                            std::int16_t melting_point, ElementType meltIntoElement, std::int16_t ignition_point,
                            ElementType igniteIntoElement, std::int16_t freezing_point, ElementType freezeIntoElement) : // Default will be AIR
                m_type{type},
                m_color{color}, // Uses BK_CLR for visual consistency
                m_weight{weight},
                m_density{density},
                m_isMovable{movable},
                m_melting_point{melting_point},
                m_meltIntoElement{meltIntoElement},
                m_ignition_point{ignition_point},
                m_igniteIntoElement{igniteIntoElement},
                m_freezing_point{freezing_point},
                m_freezeIntoElement{freezeIntoElement}
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
                false,
                constants::NO_STATE_CHANGE,
                NULL_ELEMENT,
                constants::NO_STATE_CHANGE,
                NULL_ELEMENT,
                constants::NO_STATE_CHANGE,
                NULL_ELEMENT,
            },
            Element{
                ElementType::SAND,
                YELLOW,
                5,
                5,
                true,
                constants::NO_STATE_CHANGE,
                NULL_ELEMENT,
                constants::NO_STATE_CHANGE,
                NULL_ELEMENT,
                constants::NO_STATE_CHANGE,
                NULL_ELEMENT,
            },
            Element{
                ElementType::WATER,
                BLUE,
                3,
                1,
                true,
                constants::NO_STATE_CHANGE,
                NULL_ELEMENT,
                constants::NO_STATE_CHANGE,
                NULL_ELEMENT,
                0,
                ElementType::ICE,
            },
            Element{
                ElementType::STONE,
                GRAY,
                -1,
                constants::STATIC_DENSITY,
                false,
                constants::NO_STATE_CHANGE,
                NULL_ELEMENT,
                constants::NO_STATE_CHANGE,
                NULL_ELEMENT,
                constants::NO_STATE_CHANGE,
                NULL_ELEMENT,
            },
            Element{
                ElementType::FIRE,
                RED,
                0,
                0,
                true,
                constants::NO_STATE_CHANGE,
                NULL_ELEMENT,
                constants::NO_STATE_CHANGE,
                NULL_ELEMENT,
                constants::NO_STATE_CHANGE,
                NULL_ELEMENT,
        },
        Element{
            ElementType::WOOD,
            BROWN,
            -1,
            constants::STATIC_DENSITY,
            false,
            100,
            ElementType::FIRE,
            constants::NO_STATE_CHANGE,
            NULL_ELEMENT,
            constants::NO_STATE_CHANGE,
            NULL_ELEMENT,
    },
        Element{
            ElementType::ICE,
            SKYBLUE,
            -1,
            constants::STATIC_DENSITY,
            false,
            50,
            ElementType::WATER,
            constants::NO_STATE_CHANGE,
            NULL_ELEMENT,
            constants::NO_STATE_CHANGE,
            NULL_ELEMENT,
    },
        Element{
            ElementType::FROST,
            LIGHTGRAY,
            0,
            0,
            true,
            constants::NO_STATE_CHANGE,
            NULL_ELEMENT,
            constants::NO_STATE_CHANGE,
            NULL_ELEMENT,
            constants::NO_STATE_CHANGE,
            NULL_ELEMENT,
    },

    };

    struct Cell {
        ElementType type;
        bool updated_this_frame;
        std::int8_t frames_stationary; //fuel timer for fires
        std::int16_t temperature;

        Cell() : type{ElementType::AIR}, updated_this_frame{false}, frames_stationary {0}, temperature {constants::AMBIENT_TEMPERATURE} {};
        ~Cell() = default;

    };


    extern std::vector<Cell> cellGrid;

    void saveGridState(std::vector<Cell> &cellGrid);
    void loadGridState(std::vector<Cell> &cellGrid);
}

#endif //GRIDRAY_ENTITIES_H
