#pragma once

#include "common.h"
#include <fxcg/display.h>

void rect_fill(VRAMPointer v, short x, short y, short width, short height, color_t color);
void rect_border(VRAMPointer v, short x, short y, short width, short height, color_t color);
void render_mini_text(int x, int y, const char* text, color_t color);
void render_centered_mini_text(int CELL_X, int CELL_Y, int CELL_WIDTH, const char* text, color_t color);
