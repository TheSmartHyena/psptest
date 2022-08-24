#include "headers/screen.hpp"
#include <array>
#include <pspge.h>
#include <pspdisplay.h>
#include <psputils.h>

using namespace std;

void Screen::init() {
    Screen::draw_buffer = static_cast<uint32_t*>(sceGeEdramGetAddr());
    Screen::disp_buffer = static_cast<uint32_t*>(sceGeEdramGetAddr()) + (272 * 512 * 4);

    sceDisplaySetMode(0, 480, 272);
    sceDisplaySetFrameBuf(disp_buffer, 512, PSP_DISPLAY_PIXEL_FORMAT_8888, 1);
}

void Screen::swapBuffers () {
    uint32_t* temp = disp_buffer;
    disp_buffer = draw_buffer;
    draw_buffer = temp;

    sceKernelDcacheWritebackInvalidateAll();
    sceDisplaySetFrameBuf(disp_buffer, 512, PSP_DISPLAY_PIXEL_FORMAT_8888, PSP_DISPLAY_SETBUF_NEXTFRAME);

}

void Screen::setPixel (int i, int j, uint32_t color) {
    int off = i + (j * 512);
    draw_buffer[1 + off + 1 * 512] = color;
}

void Screen::render (uint32_t screenPixels[480][272]) {
    for (int i = 0; i <= 50; ++i) {
        for (int j = 0; j <= 50; ++j) {
            // setPixel(i, j, screenPixels[i][j]);
            setPixel(i, j, 0xFFFFFF);
        }
    }
}

void Screen::clear (uint32_t color) {
    for (int i = 0; i <= 480; i++) {
        for (int j = 0; j <= 272; i++) {
            setPixel(i, j, color);
        }
    }
}
