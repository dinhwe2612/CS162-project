#ifndef StaffUI_hpp
#define StaffUI_hpp

#include "../external/raylib/src/raylib.h"
#include <iostream>
#include "Button.hpp"
#include "InputBar.hpp"
#include "StaffUI_Class.hpp"
#include "StaffUI_Semester.hpp"
#include "StaffUI_Course.hpp"
#include <array>
#include <vector>
#include <algorithm>
#include "../Header/login.h"
#include "../Header/view.h"
#include "../Header/schoolYear.h"


struct StaffUI 
{
    float windowWidth;
    float windowHeight;

//---------------------------------------------------------------------------------------------//
//                                      SCHOOL YEAR SECTION
//---------------------------------------------------------------------------------------------//

    Texture2D background;
    
    Font PT_serif_regular;
    Font PT_serif_bold;

    Button dropDown;
    Button signOut;
    Button ChangePassWord;
    Button ViewProfile;
    Button cornerStripes; 
    Button addSchoolYear;
    Button Close;

    // keep track of semester button
    std::vector<Button> ListOfSchoolYearButtons;

    InputBar oldPassword;
    InputBar newPassword;
    InputBar confirmPassword;
    InputBar enterSchoolYear;

    bool *BUTTON_SchoolYear_isCLICKED;

    string username;

    // for testing only, need backend to pull info from
    // add school year section in AddschoolYear() function is also a test. Need backend to modify input system
    // also DrawSchoolYear() is adjusted to work with ListSize
    string *ListOfSchoolYear;
    int ListSize = 12;


//---------------------------------------------------------------------------------------------//
//                               SEMESTER, CLASS & COURSE DECLARATION
//---------------------------------------------------------------------------------------------//

    Class _Class;

    SemesterUI _Semester;

    Course course = Course(windowWidth, windowHeight);




//---------------------------------------------------------------------------------------------//
//                               FUNCTIONS AND MENU CONTROL 
//---------------------------------------------------------------------------------------------//
    const int DEFAULT = -1;

    int menuStaff = DEFAULT;
    int previousmenuStaff = DEFAULT;
    enum windowStaff {
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
    void AddSchoolYear(); // return whether add school year window is on
    void Draw(int &menuLogin);
        void DrawBackground();
        void DrawStaticElement();
        void DrawDropDownAccount(int &menuLogin);
        void DrawDropDownSchoolYear();
        void DrawSchoolYear();
        void DrawChangePassword();
        void DrawViewProfile();
        // void DrawSchoolYearMenu();
        void DrawCurrentWindow();
};

#endif