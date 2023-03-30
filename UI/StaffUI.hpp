#ifndef StaffUI_hpp
#define StaffUI_hpp

#include "../external/raylib/src/raylib.h"
#include <iostream>
#include "Button.hpp"

struct StaffUI 
{
    float windowWidth;
    float windowHeight;

    Texture2D background;
    Font PT_serif_regular;

    Button dropDown;
    Button signOut;
    Button ChangePassWord;
    Button cornerStripes; 

    int menuStaff;
    enum windowStaff {
        SCHOOL_YEAR,
        SEMESTER,
        CLASS,
        COURSE
    };

    void Construct(float windowWidth, float windowHeight);
    void Deconstruct();
    void Draw();
        void DrawBackground();
        void DrawStaticElement();
        void DrawDropDownAccount();
        void DrawDropDownSchoolYear(int numberOfCreatedSchoolYear);
        void DrawSchoolYear(bool isDroppedDown);

};

#endif