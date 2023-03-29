#pragma once
#include <cstdint>

struct FontBmpLarge { 
    char ch;
    int width;
    uint32_t bmp[24];
};


extern FontBmpLarge fonts_large[];
extern size_t num_fonts_large;

int find_font_large_idx(char ch);
