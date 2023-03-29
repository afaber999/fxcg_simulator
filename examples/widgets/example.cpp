#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <string.h>
#include <stddef.h>
//#include <fxcg/file.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "menu.h"
#include "button.h"
#include "rect.h"


int main() {

    Bdisp_EnableColor(1);
    auto vram = VRAMPointer(GetVRAMAddress());

    static MenuItems mmi = {4, {{21, "Aqua"}, {22, "Seagreen"}, {23, "Indigo"}, {24, "White"}}};
    MenuWidget main_menu(mmi);

    ButtonWidget test_button("T");

    auto background_color = COLOR_WHITE;
    bool main_menu_active = false;

    while(1){
        Bdisp_Fill_VRAM(background_color, 4);

        test_button.render(vram, 20, 20, 140, 30);
        main_menu.render(vram, 20, 20 + 30 + 5, main_menu_active);

        int key;
        GetKey(&key);

        test_button.update(key);
        
        switch (test_button.get_state()) {
            case ButtonState::ENABLED:
                render_mini_text(50, 50, "E", COLOR_BLACK);
                break;
            case ButtonState::DISABLED:
                render_mini_text(50, 50, "D", COLOR_BLACK);
                break;
            case ButtonState::SELECTED:
                render_mini_text(50, 50, "S", COLOR_BLACK);
                break;
        }

        if (test_button.get_state() == ButtonState::SELECTED) {
            background_color = COLOR_YELLOW;
            main_menu_active = true;
        }

        main_menu.update(key);

        if (main_menu.is_close()) {
            test_button.set_state(ButtonState::ENABLED);
            main_menu_active = false;
            background_color = COLOR_SKYBLUE;
        }

        if (main_menu_active) {
            switch (main_menu.get_selected()) {
                case 21:
                    background_color = COLOR_AQUA;
                    break;
                case 22:
                    background_color = COLOR_SEAGREEN;
                    break;
                case 23:
                    background_color = COLOR_INDIGO;
                    break;
                case 24:
                    background_color = COLOR_WHITE;
                    break;                
                default:
                    break;
            }
        }
    }

    return 0;
}
