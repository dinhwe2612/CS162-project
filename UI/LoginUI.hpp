#ifndef loginui_hpp
#define loginui_hpp

#include "../external/raylib/src/raylib.h"
#include <iostream>

struct LoginUI
{
    // window size
    int windowWidth;
    int windowHeight;

    // resources
        // Textures
    Texture2D background;
    Texture2D logo;
    Texture2D usrIcon;
    Texture2D passwordIcon;
    Texture2D staffIcon;
    Texture2D studentIcon;
        // Fonts
    Font PT_serif_bold;
    Font PT_serif_regular;

    // struct constructor / deconstructor
    void Construct(int windowWidth, int windowHeight);
    void Deconstruct();

    // draw functions
    void Update();
    void Draw();
        void DrawBackground();
        void DrawLoginBox();
        void DrawSignInButton();
        void DrawStatusButtons();
    void Tick();
};

#endif