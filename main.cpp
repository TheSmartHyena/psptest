#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include "headers/screen.hpp"

PSP_MODULE_INFO("PROUTCUL", 0, 1, 0);
using namespace std;

int exit_callback(int arg1, int arg2, void* common) {
    sceKernelExitGame();
    return 0;
}

int callbackThread(SceSize args, void* argp) {
    int cbid = sceKernelCreateCallback("Exit callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);

    sceKernelSleepThread();
    return 0;
}

void setupCallbacks() {
    int thid = sceKernelCreateThread("update_thread", callbackThread, 0x11, 0xFA0, 0, NULL);
    if (thid >= 0) {
        sceKernelStartThread(thid, 0, NULL);
    }
}

auto main() -> int {
    setupCallbacks();

    uint32_t screenPixels[480][272] = {{0xFFFFFF, 0xFFFFFF}, {0xFFFFFF, 0xFFFFFF}};
    Screen screen;

    screen.init();
    screen.clear(0x18B30000);

    
    while (1) {
        screen.render(screenPixels);
        screen.swapBuffers();
        sceDisplayWaitVblankStart();
    }
}