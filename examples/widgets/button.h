#pragma once

#include "common.h"
#include <fxcg/display.h>


enum ButtonState {
  ENABLED,
  DISABLED,
  SELECTED,
};

class ButtonWidget {
  private:
    const char* m_label;
    ButtonState m_state;
    color_t m_bg;

  public:
    ButtonWidget(const char* label);
    
    ButtonState get_state() const {
      return m_state;
    }

    void set_state(ButtonState state) {
      m_state = state;
    }

    ~ButtonWidget();

    void render(VRAMPointer v, int x, int y, int width, int height);
    bool update(int key);
};