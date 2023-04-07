#ifndef StaffUI_Semester_hpp
#define StaffUI_Semester_hpp

#include "../external/raylib/src/raylib.h"
#include "Button.hpp"
#include "InputBar.hpp"
#include <array>
#include <iostream>

struct Semester
{
    int windowWidth;
    int windowHeight;

    string SchoolYear;

    Texture2D background;

    Font PT_serif_bold;
    Font PT_serif_regular;

    Button addSemester;
    Button close;

    InputBar inputSemester;

    // string *ListOfClasses; 
    // int listSize = 0;

    std::array<std::string, 4> ListOfSemesters = {"Semester 1", "Semester 2"}; 
    int listSize = 2;
    
    void Construct(int windowWidth, int windowHeight);
    void Deconstruct();

    std::string LoadDroppedFile();

    void Draw();
        void DrawBackground();
        void DrawCreateSemester();
        void DrawSemesterList();
        
};

#endif