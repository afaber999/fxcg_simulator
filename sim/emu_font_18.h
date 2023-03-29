#pragma once
#include <cstdint>

struct FontBmp18 { 
    char ch;
    int width;
    uint32_t bmp[18];
};


extern FontBmp18 fonts_18[];
extern size_t num_fonts_18;

int find_font_18_idx(char ch);
