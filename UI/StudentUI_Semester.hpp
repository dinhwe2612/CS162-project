#ifndef StudentUI_Semester_hpp
#define StudentUI_Semester_hpp

#include "../external/raylib/src/raylib.h"
#include "Button.hpp"
#include "InputBar.hpp"
#include <array>
#include <iostream>
#include "../Header/view.h"
#include "../Header/SemesterCourse.h"
#include "StaffUI_Course.hpp"

struct StudentSemesterUI
{
    int windowWidth;
    int windowHeight;

    string SchoolYear;

    Texture2D background;

    Font PT_serif_bold;
    Font PT_serif_regular;

    Button addSemester;
    Button close;
    Button back;
    Button addSemesterClose;
        

    InputBar inputSemester;
    InputBar SemesterStartDate;
    InputBar SemesterEndDate;

    Course course;

    bool isAddSemester = false;

    string *ListOfSemesters;

    int indexSemester;

    int menuSemester = 0;

    // std::array<std::string, 3> ListOfSemesters = {"Semester 1", "Semester 2"}; 
    // std::array<std::array<int, 3>, 3> ListOfStartDates = {{{20, 1, 2022}, {20, 5, 2022}}};
    // std::array<std::array<int, 3>, 3> ListOfEndDates = {{{1, 5, 2022}, {1, 10, 2022}}};
    int listSize = 2;
    
    void Construct(int windowWidth, int windowHeight);
    void Deconstruct();

    std::string LoadDroppedFile();

    void Draw(int &menuWindow);
        void DrawBackground();
        void DrawCreateSemester();
        void DrawSemesterList();
        
};

#endif
