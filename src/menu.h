#pragma once


#include "common.h"

struct MenuItem {
    short id;
    char* label;
};

struct MenuItems {
    short count;
    struct MenuItem items[];
};

class MenuWidget {
    short m_focus;
    short m_selected;
    bool m_closed;

public:
    const MenuItems& m_items;

    // constructor
    MenuWidget(const MenuItems& menu);
    short get_focus() const;
    short get_selected() const;
    bool is_close() const;
    ~MenuWidget();

    void render(VRAMPointer v, int x, int y, bool open = false);
    bool update(int key);
};