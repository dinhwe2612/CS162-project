#ifndef StaffUI_hpp
#define StaffUI_hpp

#include "../external/raylib/src/raylib.h"
#include <iostream>
#include "Button.hpp"

struct StaffUI {
    float windowWidth;
    float windowHeight;

    Texture2D background;
    Texture2D backButtonImage;
    Font PT_serif_regular;

    Button Back;
    Button ViewProfile;
    Button SignOut;

    int menuStaff = 0;
    enum windowStaff {
        STAFF,
        VIEWPROFILE
    };

    void Construct(float windowWidth, float windowHeight);
    void Deconstruct();
    void Draw();
    void DrawBackground();
    void DrawButton();
};

#endif