#ifndef StaffUI_Course_hpp
#define StaffUI_Course_hpp

#include "../external/raylib/src/raylib.h"
#include "Button.hpp"
#include "InputBar.hpp"
#include <array>

struct Course 
{
    int windowWidth, windowHeight;

    Texture2D background;
    
    Button back;
    Button addCourse;

    Font PT_serif_bold;
    Font PT_serif_regular;

    std::array <std::string, 10> ListOfCourses = {"CS161", "PH211", "MTH251", "CS162", "PH212", "MTH252"};
    int listCourseSize = 6;

    Course(int windowWidth, int windowHeight);
    ~Course();

    void Draw(int& menuWindow);
        void DrawBackground();

};

#endif