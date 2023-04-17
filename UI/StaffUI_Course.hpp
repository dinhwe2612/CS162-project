#ifndef StaffUI_Course_hpp
#define StaffUI_Course_hpp

#include "../external/raylib/src/raylib.h"
#include "Button.hpp"
#include "InputBar.hpp"
#include <array>
#include "../Header/view.h"
#include "../Header/SemesterCourse.h"

struct Course 
{
    int windowWidth, windowHeight;

    Texture2D background;
    
    Button close;
    Button addCourse;
    Button addCourseClose;
    Button Create;

    Font PT_serif_bold;
    Font PT_serif_regular;

    InputBar courseName;
    InputBar courseID;
    InputBar className;
    InputBar teacherName;
    InputBar numberOfCredits;
    InputBar maxStudents;

    bool isAddCourse = false;

    // std::array <std::string, 10> ListOfCourses = {"CS161", "PH211", "MTH251", "CS162", "PH212", "MTH252", "CM101"};
    ACourse *ListOfCourses;
    int listCourseSize = 7;

    int menuCourse = 0;

    string schoolYear;
    string semester;

    void Construct(int windowwidth, int windowHeight);
    void Deconstruct();

    std::string buttonChosen(float x, float y, float width, float height, std::string* labels, bool* isButtonPressed, int size);

    void Draw();
        void DrawBackground();
        void DrawCourseList();
        void DrawCreateCourse();

};

#endif