#include "input.h"

void KeyPressed(unsigned char key, int x, int y);

        void KeyUp(unsigned char key, int x, int y);

        void KeySpecial(int key, int x, int y);

class GlutInput: public Input
{
    public:
        GlutInput();
        ~GlutInput();

        void KeyPressed(unsigned char key, int x, int y);

        void KeyUp(unsigned char key, int x, int y);

        void KeySpecial(int key, int x, int y);
};
