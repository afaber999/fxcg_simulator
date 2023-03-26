#define SDL_MAIN_HANDLED
/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>

#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>
#include "fxcg/display.h"
#include "fxcg/keyboard.h"

extern void* libfxcg_vram;
extern int* libfxcg_keypressed;

void emu_init();

extern int main_();


int main(int argc, char** argv)
{
    printf("STARTING EMU \n");
    
    emu_init();

    const int w=LCD_WIDTH_PX;
    const int h=LCD_HEIGHT_PX;
    const int bpp=16;
    SDL_Window *window=NULL;
    SDL_Surface *screen=NULL;
    SDL_Texture *texture=NULL;
    SDL_Renderer *renderer=NULL;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("main", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STREAMING, w, h);

    std::thread t([](){
        main_();
    });

    std::string input;

    for (;;) {
	    static const unsigned char* keys = SDL_GetKeyboardState( NULL );
	    SDL_Event e;
        
        // Event loop
        while ( SDL_PollEvent( &e ) != 0 ) {
            switch (e.type) {
                case SDL_QUIT:
                    return 0;
                case SDL_TEXTINPUT:
                    input += e.text.text;
                    break;
                case SDL_KEYDOWN:
                    printf("KEYDOWN %d\n", e.key.keysym.sym);

                    switch (e.key.keysym.sym) {
                        case 1073741906: *libfxcg_keypressed = KEY_CTRL_UP; break;
                        case 1073741905: *libfxcg_keypressed = KEY_CTRL_DOWN; break;
                        case 1073741904: *libfxcg_keypressed = KEY_CTRL_LEFT; break;
                        case 1073741903: *libfxcg_keypressed = KEY_CTRL_RIGHT; break;
                        case 13 :  *libfxcg_keypressed = KEY_CTRL_EXE; break;
                        case 27 :  *libfxcg_keypressed = KEY_CTRL_EXIT; break;
                        default: 
                            if (( e.key.keysym.sym > 27 ) && ( e.key.keysym.sym < 128 ) ) {
                                *libfxcg_keypressed = e.key.keysym.sym; 
                            }
                    }

                    if (e.key.keysym.sym == SDLK_BACKSPACE && input.size()) {
                        input.pop_back();
                    }
                    break;
            }
        }
        
        short* pixels_dst = nullptr;
        int pitch;
        SDL_LockTexture(texture, NULL, (void**)&pixels_dst, &pitch);
        memcpy( pixels_dst, libfxcg_vram, sizeof(short) * LCD_WIDTH_PX * LCD_HEIGHT_PX);
        SDL_UnlockTexture(texture);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        SDL_Delay(15);
    }

    SDL_FreeSurface(screen);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

