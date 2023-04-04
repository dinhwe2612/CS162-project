#ifndef StaffUI_hpp
#define StaffUI_hpp

#include "../external/raylib/src/raylib.h"
#include <iostream>
#include "Button.hpp"
#include "InputBar.hpp"
#include "StaffUI_Class.hpp"
#include <array>
#include <vector>
#include <algorithm>
#include "../Header/login.h"
#include "../Header/view.h"


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
    std::array<std::string, 100> ListOfSchoolYear = {"2021 - 2022", "2020 - 2021", "2019 - 2020", "2018 - 2019", "2017 - 2018", "2016 - 2017", "2015 - 2016", "2014 - 2015", "2013 - 2014", "2012 - 2013", "2011 - 2012", "2010 - 2011"};
    int ListSize = 12;


//---------------------------------------------------------------------------------------------//
//                                  SEMESTER SECTION
//---------------------------------------------------------------------------------------------//


//---------------------------------------------------------------------------------------------//
//                                  SEMESTER SECTION
//---------------------------------------------------------------------------------------------//


    Class _Class;

//---------------------------------------------------------------------------------------------//
//                               FUNCTIONS AND MENU CONTROL 
//---------------------------------------------------------------------------------------------//
    const int DEFAULT = -1;

    int menuStaff = DEFAULT;
    enum windowStaff {
        CHANGE_PASSWORD,
        VIEW_PROFILE
    };

    int menuWindow = DEFAULT;
    enum window {
        // SCHOOL_YEAR,
        // SEMESTER,
        CLASS
        // COURSE
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
        void DrawSchoolYearMenu();
        void DrawCurrentWindow();
};

#endif