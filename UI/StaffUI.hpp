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
    Font PT_serif_bold;

    Button dropDown;
    Button signOut;
    Button ChangePassWord;
    Button cornerStripes; 
    Button addSchoolYear;


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
        void DrawDropDownSchoolYear();
        void DrawSchoolYear();

};

#endif