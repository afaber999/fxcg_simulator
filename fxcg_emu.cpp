#include <stdio.h>


#include "fxcg/display.h"
#include "fxcg/keyboard.h"
#include "fxcg/system.h"
#include <cstring>

#include <chrono>
#include <thread>

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
        // assume fixed size font for now
        *x = strlen(MB_string) * 8;
        return;
    }

    auto ch = (char*)MB_string;
    auto vram = (short*)libfxcg_vram;

    int xstart = *x; 
    while ( *ch != '\0') {
        for ( int yi = 0; yi < 8; yi++  ) {
            for ( int xi = xstart + 2; xi < xstart + 6; xi++  ) {
                vram[ xstart + (*y + yi ) * 8 ] = color;
            }                
        }    
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