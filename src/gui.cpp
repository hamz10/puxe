#include "../include/gui.h"

void GUI::openMenu() {
    GuiPanel({GUI::menuOriginX, GUI::menuOriginY, GUI::menuWidth, GUI::menuHeight}, "menu");
    GuiButton({GUI::menuOriginX + 20, GUI::menuOriginY + (GUI::menuWidth/2), constants::BUTTON_WIDTH_HEIGHT, constants::BUTTON_WIDTH_HEIGHT}, "<-");
    GuiButton({GUI::menuOriginX + GUI::menuWidth - 20 - constants::BUTTON_WIDTH_HEIGHT, GUI::menuOriginY + (GUI::menuWidth/2), constants::BUTTON_WIDTH_HEIGHT, constants::BUTTON_WIDTH_HEIGHT}, "->");

}

