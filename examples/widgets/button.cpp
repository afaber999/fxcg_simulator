#include "button.h"

#include <fxcg/keyboard.h>
#include <fxcg/display.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "rect.h"

ButtonWidget::ButtonWidget(const char* label) 
    : m_label(label)
{
    m_state = ButtonState::ENABLED;
    m_bg = COLOR_GREEN;
}

ButtonWidget::~ButtonWidget() {
}

void ButtonWidget::render(VRAMPointer v, int x, int y, int width, int height){
    switch (m_state) {
        case ButtonState::ENABLED:
            rect_fill(v, x, y, width, height, m_bg);
            render_centered_mini_text(x, y, width, "ENABLED", COLOR_BLACK);
            break;
        case ButtonState::DISABLED:
            rect_fill(v, x, y, width, height, m_bg);
            render_centered_mini_text(x, y, width, "DISABLED", COLOR_BLACK);
            break;
        case ButtonState::SELECTED:
            rect_fill(v, x, y, width, height, m_bg);
            render_centered_mini_text(x, y, width, "SELECTED", COLOR_BLACK);
            break;
    }

    rect_border(v, x, y, width, height, COLOR_BLACK);
}

bool ButtonWidget::update(int key) {
    // switch (m_state) {
    //     case ButtonState::ENABLED:
    //         m_bg = COLOR_GREENYELLOW;
            switch (key) {
                case KEY_CTRL_EXE:
                    m_bg = COLOR_BLUE;
                    m_state = ButtonState::SELECTED;
                    return true;
            }
    //         break;
    // }
    return false;
}