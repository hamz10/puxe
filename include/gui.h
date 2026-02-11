#ifndef GRIDRAY_GUI_H
#define GRIDRAY_GUI_H
#include "raygui.h"
#include "constants.h"

class GUI {
    public:
    static GUI& getInstance() { //static allows the function to be called via GUI::getInstance
        static GUI instance; //initialize singleton instance when called first time as static
        return instance;
    }
    private:
        GUI() : isMenuOpen{false}, menuWidth{constants::MENU_WIDTH},
                menuHeight {constants::MENU_HEIGHT}, menuOriginX{constants::MENU_ORIGIN_X},
                menuOriginY  {constants::MENU_ORIGIN_Y} {};

    bool isMenuOpen;
    float menuWidth;
    float menuHeight;
    float menuOriginX;
    float menuOriginY;


public:
    GUI(GUI const&) = delete;
    void operator=(GUI const&) = delete;
    void openMenu();

};


#endif //GRIDRAY_GUI_H