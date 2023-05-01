#ifndef StudentUI_hpp
#define StudentUI_hpp

#include "StaffUI_Class.hpp"
#include "StudentUI_Semester.hpp"
#include "../external/raylib/src/raylib.h"
#include "../Header/login.h"
#include "../Header/view.h"
#include <iostream>
#include <vector>
#include "Button.hpp"
#include "InputBar.hpp"

struct StudentUI
{
    float windowWidth, windowHeight;
    string username;
    string *ListOfSchoolYear;
    int ListSize = 0;
    bool *BUTTON_SchoolYear_isCLICKED;
    std::vector<Button> ListOfSchoolYearButtons;

    StudentSemesterUI _Semester;   

    Texture2D background;
    Texture2D calendar;
    Texture2D profile;
    Texture2D gender;
    Texture2D DOB;
    Texture2D socialID;
    Texture2D Class;
    Texture2D studentID;

    Button cornerStripes; 
    Button dropdownButton;
    Button signOut;
    Button ChangePassWord;

    Font PT_serif_bold;
    Font PT_serif_regular;
    
    InputBar oldPassword;
    InputBar newPassword;
    InputBar confirmPassword;

    const int DEFAULT = -1;
    int menuStudent = DEFAULT;
    int previousmenuStudent = DEFAULT;
    enum windowStudent {
        CHANGE_PASSWORD,
        VIEW_PROFILE,
        CREATE_SCHOOLYEAR
    };

    int menuWindow = DEFAULT;
    enum window {
        SEMESTER,
        CLASS,
        COURSE
    };

    void Construct(float windowWidth, float windowHeight);
    void Deconstruct();

    void Draw(int& menuLogin);
        void DrawBackground();
        void DrawChangePassword();
        void DrawDropDownAccount(int& menuWindow);
        void DrawDropDownSchoolYear();
        void DrawSchoolYear();
        void DrawStaticElements();
        void DrawCurrentWindow();

};

#endif
