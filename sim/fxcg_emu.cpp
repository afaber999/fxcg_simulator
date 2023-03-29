#include <stdio.h>


#include "include/fxcg/display.h"
#include "include/fxcg/keyboard.h"
#include "include/fxcg/system.h"
#include "include/fxcg/rtc.h"
#include <cstring>

#include <chrono>
#include <thread>

#include "emu_font_18.h"
#include "emu_font_large.h"

// local state
static unsigned locate_x = 1;
static unsigned locate_y = 1;
static uint8_t C16 = 0;

void* libfxcg_vram = nullptr;
int libfxcg_keypressed_val = -1;
int* libfxcg_keypressed = &libfxcg_keypressed_val;

void emu_init() {
    libfxcg_vram = new short [LCD_HEIGHT_PX*LCD_WIDTH_PX];
}


static uint16_t C3toC16(unsigned c){
    return (c & 1 ? 0x1F : 0) | (c & 2 ? 0x7E0 : 0) | (c & 4 ? 0xF800 : 0);
}
static uint16_t C16toC3(unsigned c){
    return (c & 0x8000 ? 0xF800 : 0) | (c & 0x400 ? 0x7E0 : 0) | (c & 0x10 ? 0x1F : 0);
}


void *GetVRAMAddress(void) {return libfxcg_vram;}

void VRAM_XORSprite(const color_t* data, int x, int y, int width, int height)
{
    auto ptr = (color_t*)libfxcg_vram;
    ptr += (LCD_WIDTH_PX * y + x);
    uint16_t i, j;
    for(j = y; j < y + height; j++) {
        for(i = x; i < x + width;  i++) {
            *(ptr++) ^= *(data++);
        }
        ptr += (LCD_WIDTH_PX - width);
    }
}

void VRAM_CopySprite(const color_t* data, int x, int y, int width, int height) {
    auto ptr = (color_t*)libfxcg_vram;
    ptr += (LCD_WIDTH_PX * y + x);
    uint16_t i, j;
    for(j = y; j < y + height; j++) {
        for(i = x; i < x + width;  i++) {
            *(ptr++) = *(data++);
        }
        ptr += (LCD_WIDTH_PX - width);
    }
}

void VRAM_CopySprite_Char(const color_t* data, int x, int y, int width, int height, char drawBack, char invert, short textColor) {
    auto ptr = (color_t*)libfxcg_vram;
    ptr += (LCD_WIDTH_PX * y + x);
    short i, j;
    for(j = y; j < y + height; j++) {
       
        for(i = x; i < x + width;  i++) {
            short color = *(data++);
            if(invert) {
                color = (color == 0 ? 0xffff : 0);
            }

            if((drawBack && color) || !color) {
                *(ptr++) = color | textColor;
            } else {
                ptr++;
            }
        }
        ptr += (LCD_WIDTH_PX - width);
    }
}

void Print_OS( unsigned char*msg, int mode, int zero2 ) {
    // AF TODO
    // int i;

    // if(locate_x > 22 || locate_x < 1)
    //     return;
    // if(locate_y > 8 || locate_y < 1)
    //     return;

    // for(i = 0; locate_x < 22 && i < strlen(msg); i++) {
    //     unsigned char* sprite;

    //     LARGE_GET(msg[i],sprite);

    //     if(!sprite) {
    //         printf("Invalid character: '%c'\n", msg[i]);
    //         continue; // INVALID CHARACTER
    //     }

    //     unsigned char w = *(sprite++);
    //     unsigned char h = *(sprite++);

    //     VRAM_CopySprite_Char((color_t*)sprite, (locate_x-1)*w, (locate_y-1)*h+0x24, w, h, !(mode & TEXT_MODE_TRANSPARENT_BACKGROUND), mode & TEXT_MODE_INVERT, 0);

    //     locate_x++;
    // }
}

void Bdisp_EnableColor( int n ) {
    C16 = n & 1;
}

void Bdisp_AllClr_VRAM() {
    memset(libfxcg_vram, sizeof(short) * LCD_HEIGHT_PX * LCD_WIDTH_PX, 0xFF );
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
            auto idx = find_font_18_idx(*ch);
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

        auto idx = find_font_18_idx(*ch);
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

static clock_t rtc_base = clock();

int RTC_GetTicks(void){
    // return 1/128 ticks since midnight ...
    auto delta = clock() - rtc_base;
    return delta * 128 / CLOCKS_PER_SEC;
}


// AF TODO
void SetQuitHandler(void (*fx)()) {
    printf("todo ");
} // sets callback to be run when user exits through the main menu from one app to another. eActivity uses this in the "Save file?" dialog


unsigned short Bdisp_GetPoint_VRAM( int x, int y ) {
    return x + y * LCD_WIDTH_PX;
}

void Bdisp_SetPointWB_VRAM( int x, int y, int color ) {
    auto vram = (short*)libfxcg_vram;
    vram[ Bdisp_GetPoint_VRAM(x,y)] = color;
}

void HourGlass( void ) {
    // TODO
}

void Bdisp_PutDisp_DD( void ) {
    // TODO
    Bdisp_AllClr_VRAM();
}