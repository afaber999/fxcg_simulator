// #include <stdio.h>
// #include <fxcg/display.h>
// #include <fxcg/keyboard.h>
// #include <fxcg/system.h>

// //void OS_InnerWait_ms(int wait_ms);

// int main_() {

//     int key;
//     int loop = 0;
//     color_t bg = COLOR_AZURE;

//     Bdisp_EnableColor(1);
//     Bdisp_AllClr_VRAM();

//     auto vram = (short*)GetVRAMAddress();
     
//     for (;;) {
//         switch (loop) {
//             case 0:
//                 bg  = COLOR_AZURE;
//                 break;
//             case 1:
//                 bg  = COLOR_BEIGE;
//                 break;
//             default:
//                 bg  = COLOR_RED;
//                 loop = 0;
//                 break;
//         }

//         for ( int y = 0; y< LCD_HEIGHT_PX; y++ ) {
//             for ( int x = 0; x< LCD_WIDTH_PX / 3; x++ ) {
//                 vram[ y * LCD_WIDTH_PX + x] = bg;
//             }
//         }
//         // GetKey(&key);
//         //OS_InnerWait_ms(1000);
//         OS_InnerWait_ms(100);
//         loop++;
//     }
//     return 0;
// }

