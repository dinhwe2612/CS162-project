#ifndef StaffUI_Course_hpp
#define StaffUI_Course_hpp

#include "../external/raylib/src/raylib.h"
#include "Button.hpp"
#include "InputBar.hpp"

struct Course 
{
    int windowWidth, windowHeight;

    Texture2D background;
    
    Button back;
    Button addCourse;

    Font PT_serif_bold;
    Font PT_serif_regular;

    std::array <std::string, 10> ListOfCourses

    Course(int windowWidth, int windowHeight);
    ~Course();

    void Draw();
        void DrawBackground();

};

#endif