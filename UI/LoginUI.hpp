#ifndef loginui_hpp
#define loginui_hpp

#include "../external/raylib/src/raylib.h"
#include <iostream>
#include "InputBar.hpp"
#include "Button.hpp"

struct LoginUI
{
    // window size
    float windowWidth;
    float windowHeight;

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
    
    // InputBar
    InputBar inputUsername;
    InputBar inputPassword;
    
    // Button sign in
    Button signInButton;

    // check whether staff or student is clicked and respond
    bool STAFF_IS_CLICKED = true;
    bool STUDENT_IS_CLICKED = false;
    bool status = true;

    // struct constructor / deconstructor
    void Construct(float windowWidth, float windowHeight);
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