#ifndef StaffUI_Class_hpp
#define StaffUI_Class_hpp

#include "../external/raylib/src/raylib.h"
#include "Button.hpp"
#include "InputBar.hpp"
#include <iostream>
#include <array>
#include <algorithm>
#include "../Header/view.h"
#include "../Header/schoolYear.h"
#include "../Header/StudentStruct.h"
#include "../Header/score.h"
#include "../Header/StudentFunc.h"

using namespace std;

struct Class
{
    int windowWidth;
    int windowHeight;

    string SchoolYear;

    Texture2D background;

    Font PT_serif_bold;
    Font PT_serif_regular;

    Button addClass;
    Button close;
    Button view, drop, add, back;
    Button viewGPA;

    InputBar inputClass;
    InputBar StudentID, firstName, lastName, day, month, year, socialID;
    Button Male, Female, Other;
    Texture2D Tick;
    Rectangle TickRec;
    Student addedStudent;

    string *ListOfClasses; 
    int listSize = 0;

    int classIndex = 0;

    Student *ListOfStudent;
    int listStuSize = 0;

    int stuIndex = 0;

    bool isAddClass = false;
    bool isDropClicked = false;
    bool classClicked = false;

    Student *studentListOfClass;
    int studentListOfClassSize = 0;
    ScoreBoard **scoreBoardOfClass;
    ACourse **courseOfClass;
    int *scoreBoardOfClassSize = 0;

    string *listOfSemester;
    int semesterSize = 0;

    string curClass;

    int DEFAULT = -1;
    int menuClass = DEFAULT;
    enum windowCLass {
        VIEW_CLASS,
        VIEW_STUDENT,
        DROP_FILE,
        ADD_STUDENT,
        CHOOSEVIEWCLASS,
        VIEWGPA
    };

    // std::array<std::string, 100> ListOfClasses = {"22TT1", "22TT2", "21TT1", "21TT2", "20TT1", "20TT2", "19TT1", "19TT2", "18TT1", "18TT2"}; 
    // int listSize = 10;
    
    void Construct(int windowWidth, int windowHeight);
    void Deconstruct();

    Vector2 GetCenterPos(float x, float y, float width, float height, string text, Font font, float fontSize, float spacing);
    string convertFloatToString(float x);

    void Draw(int &menuWindow);
        void DrawBackground();
        void DrawCreateClass();
        void DrawClassList();
        void DrawViewClass();
        void DrawStudentList();
        void DrawAddStudent();
        void DrawSchoolYearMenu();
        void LoadDroppedFile();
        void ChooseViewClass();
        void DrawViewGPA();
};

#endif