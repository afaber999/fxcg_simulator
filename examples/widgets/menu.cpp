#include "menu.h"

#include <fxcg/keyboard.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "rect.h"


  // constructor
MenuWidget::MenuWidget(const MenuItems& menu) 
    : m_items(menu)
{
    m_focus = 0;
    m_selected = -1;
    m_closed = false;
}

MenuWidget::~MenuWidget() {
}


short MenuWidget::get_focus() const {
  return m_focus;
}

short MenuWidget::get_selected() const {
  return m_selected;
}

bool MenuWidget::is_close() const {
  return m_closed;
}


void MenuWidget::render(VRAMPointer v, int x, int y, bool open){
    const int MENU_ITEM_HEIGHT = 30;
    const int MENU_ITEM_X_PADDING = 10;

    if (open) {
        int height = m_items.count*MENU_ITEM_HEIGHT;
        int width = 150;

        // popover
        rect_fill(v, x, y, width, height, COLOR_WHITE);

        // focus
        rect_fill(v, x, y+m_focus*MENU_ITEM_HEIGHT, width, MENU_ITEM_HEIGHT, COLOR_LIGHTGRAY);
        rect_border(v, x, y, width, height, COLOR_BLACK);

        for (auto i = 0; i < m_items.count; i++){
            auto& menu_item = m_items.items[i];

            // TODO: -15 FIXXX!!!!!
            const short TEXT_MENU_CORRECTION = -15;
            render_mini_text(x + MENU_ITEM_X_PADDING, y + MENU_ITEM_HEIGHT * i + TEXT_MENU_CORRECTION, menu_item.label, COLOR_BLACK);
        }
    } else {
        render_mini_text(50, 50, "TEST 123 bababbaba", COLOR_BROWN);
    }
}

bool MenuWidget::update(int key) {
    m_selected = -1;

    switch (key) {
        case KEY_CTRL_UP:
            if (m_focus > 0){
                m_focus--;
            }
            return true;
        case KEY_CTRL_DOWN:
            if (m_focus < m_items.count - 1){
                m_focus++;
            }
            return true;
        case KEY_CTRL_EXE:
            m_selected = m_items.items[m_focus].id;
            return true;
        case KEY_CTRL_EXIT:
            m_closed = true;
            return true;
    }
    return false;
}
