#include "rect.h"

#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


void rect_fill(VRAMPointer v, short x, short y, short width, short height, color_t color){
    for (int yi=y; yi<y+height; yi++){
        int line_offset = yi*SCREEN_WIDTH;

        for (int xi=x; xi<x+width; xi++){
            v[xi+line_offset] = color;
        }
    }
}

void rect_border(VRAMPointer v, short x, short y, short width, short height, color_t color){
    int line_offset = y * SCREEN_WIDTH;
    for (int xi = x; xi < x + width; xi++){
        v[xi + line_offset] = color;
    }

    line_offset = (y + 1) * SCREEN_WIDTH;
    for (int yi=y + 1; yi < y + height - 1; yi++){        
        v[line_offset + x] = color;
        v[line_offset + x + width - 1] = color;
        line_offset += SCREEN_WIDTH;
    }

    line_offset = (y + height - 1) * SCREEN_WIDTH;
    for (int xi = x; xi < x + width; xi++){
        v[xi + line_offset] = color;
    }
}

void render_mini_text(int x, int y, const char* text, color_t color) {
    PrintMini(&x, &y, text, 0x02, 0xFFFFFFFF, 0, 0, color, COLOR_WHITE, 1, 0);
}

void render_centered_mini_text(int CELL_X, int CELL_Y, int CELL_WIDTH, const char* text, color_t color){
    int x = 0;
    int y = CELL_Y - 15;
    PrintMini(&x, &y, text, 0x02, 0xFFFFFFFF, 0, 0, color, COLOR_WHITE, 1, 1);

    x = CELL_X + (CELL_WIDTH - x)/2;
    PrintMini(&x, &y, text, 0x02, 0xFFFFFFFF, 0, 0, color, COLOR_WHITE, 1, 0);
}
