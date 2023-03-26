#include <stdio.h>


#include "fxcg/display.h"
#include "fxcg/keyboard.h"
#include "fxcg/system.h"
#include <cstring>

#include <chrono>
#include <thread>


#include "emu_font_18.h"

void* libfxcg_vram = nullptr;
int libfxcg_keypressed_val = -1;
int* libfxcg_keypressed = &libfxcg_keypressed_val;

void emu_init() {
    libfxcg_vram = new short [LCD_HEIGHT_PX*LCD_WIDTH_PX];
}

void *GetVRAMAddress(void) {return libfxcg_vram;}
void Bdisp_EnableColor( int n ) {}


void Bdisp_AllClr_VRAM() {
    memset(libfxcg_vram, sizeof(short) * LCD_HEIGHT_PX * LCD_WIDTH_PX, 0 );
}

int GetKey(int*key) {
    *libfxcg_keypressed = -1;
    printf("WAIT FOR KEY\n");

    while ( *((volatile int*)libfxcg_keypressed) == -1 ) {
        OS_InnerWait_ms(10);
    }
    *key = *libfxcg_keypressed;
    printf("WAIT FOR KEY RETURNS %d\n", *key);
    return *key;
}

void OS_InnerWait_ms(int wait_ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(wait_ms) );
}

void PrintMini( int *x, int *y, const char *MB_string, int mode_flags, unsigned int xlimit, int P6, int P7, int color, int back_color, int writeflag, int P11 ) {

    if (P11 == 1 ) {

        *x = 0;
        auto ch = (char*)MB_string;
        while ( *ch != '\0') {
            auto idx = find_font_idx(*ch);
            auto& fnt = fonts_18[idx];
            *x += fnt.width;
            ch++;
        }
        //println("STR LEN %d\n", *x)
        return;
    }

    auto ch = (char*)MB_string;
    auto vram = (short*)libfxcg_vram;

    int xstart = *x; 

    // loop through characters
    while ( *ch != '\0') {

        auto idx = find_font_idx(*ch);
        auto& fnt = fonts_18[idx];

        // loop through lines
        for ( int yi = 0; yi < 18; yi++  ) {

            auto lv = fnt.bmp[yi];
            // loop through pixels
            for ( int xi = 0; xi < fnt.width; xi++  ) {
                int yp = (*y + yi ) + 24;
                int pi = xstart + xi  + yp * LCD_WIDTH_PX; 
                if (  (lv & (1<< ( fnt.width - xi )) ) != 0 ) {
                    vram[ pi ] = color;
                }
            }

        }
        xstart += fnt.width;
         
        ch++;
    }
}

void PrintMiniMini( int *x, int *y, const char *MB_string, int mode1, char color, int mode2 ) {
    if (mode2 == 1 ) {
        // assume fixed size font for now
        *x = strlen(MB_string) * 8;
        return;
    }

    auto ch = (char*)MB_string;
    auto vram = (short*)libfxcg_vram;

    int xstart = *x; 
    while (*ch != '\0') {
        for ( int yi = 0; yi < 8; yi++  ) {
            for ( int xi = xstart + 2; xi < xstart + 6; xi++  ) {
                vram[ xstart + (*y + yi ) * 8 ] = color;
            }                
        }    
        ch++;
    }
}



void Bdisp_Fill_VRAM( int color, int mode ) {
    // todo implement mode
    for (int pix = 0; pix < LCD_HEIGHT_PX* LCD_WIDTH_PX; pix++ ) {
        auto vram = (short*)libfxcg_vram;
        vram[ pix ] = color;
    }    
}


// wxh 384 x 216
// menu header is 24 px
// screen size without header = 216 - 24 = 192 pixels
// large fornt 24 pix  8 lines + header
// Mini font is 18 pixels => 216/18 = 12 lines, width is variable
// 16 pixel font BDIS_MMPrint
// 10 pixel font 21 lines (mini mini)

