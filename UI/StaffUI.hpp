#ifndef StaffUI_hpp
#define StaffUI_hpp

#include "../external/raylib/src/raylib.h"
#include <iostream>
#include "Button.hpp"
#include "InputBar.hpp"
#include <array>
#include <vector>

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

    std::vector<Button> ListOfSchoolYearButtons;

    InputBar oldPassword;
    InputBar newPassword;
    InputBar confirmPassword;

    int menuStaff;
    enum windowStaff {
        SCHOOL_YEAR,
        SEMESTER,
        CLASS,
        COURSE, 
        CHANGE_PASSWORD
    };

    void Construct(float windowWidth, float windowHeight);
    void Deconstruct();
    void Draw();
        void DrawBackground();
        void DrawStaticElement();
        void DrawDropDownAccount();
        void DrawDropDownSchoolYear();
        void DrawSchoolYear();
        void DrawChangePassword();
};

#endif