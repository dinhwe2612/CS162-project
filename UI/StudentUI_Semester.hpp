#ifndef StudentUI_Semester_hpp
#define StudentUI_Semester_hpp

#include "../external/raylib/src/raylib.h"
#include "Button.hpp"
#include "InputBar.hpp"
#include <array>
#include <iostream>
#include "../Header/view.h"
#include "../Header/SemesterCourse.h"
#include "../Header/StudentFunc.h"
#include "StaffUI_Course.hpp"

struct StudentSemesterUI
{
    int windowWidth;
    int windowHeight;

    string schoolYear;
    string semester;
    string studentID;

    Texture2D background;
    Texture2D world;

    Font PT_serif_bold;
    Font PT_serif_regular;

    Button close;

    string *ListOfSemesters;

    int indexSemester;

    int menuSemester = 0;
    
    int listSize = 0;
    int listCourseSize = 0;
    ACourse *ListOfCourses;
    ScoreBoard *ListOfScores;
    
    void Construct(int windowWidth, int windowHeight);
    void Deconstruct();

    void Draw(int &menuWindow);
        void DrawBackground();
        void DrawSemesterList();
        void DrawCourseList();
        void DrawScoreBoard();
};

#endif
