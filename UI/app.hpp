#ifndef app_hpp
#define app_hpp

#include "../external/raylib/src/raylib.h"
#include <iostream>

struct LoginUI
{
    int windowWidth;
    int windowHeight;
    void Construct(int windowWidth, int windowHeight);
    void Update();
    void Draw(Texture2D& logo, Texture2D& loginBox, Texture2D& topBar);
    void DrawTopbar(Texture2D& topbar);
    void DrawLogo(Texture2D& logo);
    void DrawLoginBox(Texture2D& loginBox);
    void Tick(Texture2D& logo, Texture2D& loginBox, Texture2D& topBar);
};

#endif