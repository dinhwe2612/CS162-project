#ifndef app_hpp
#define app_hpp

#include "../external/raylib/src/raylib.h"
#include <iostream>

struct LoginUI
{
    int windowWidth;
    int windowHeight;
    Texture2D background;
    Texture2D logo;
    Font sans_serif_bold;
    void Construct(int windowWidth, int windowHeight);
    void Deconstruct();
    void Update();
    void Draw();
    void DrawBackground();
    void DrawLoginBox();
    void Tick();
};

#endif