#include <array>
using namespace std;

class Screen
{
    public:
        uint32_t* draw_buffer;
        uint32_t* disp_buffer;

        void init();
        void clear(uint32_t color);
        void swapBuffers();
        void setPixel(int i, int j, uint32_t color);
        void render(uint32_t screenPixels[480][272]);
};
