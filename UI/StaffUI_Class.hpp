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

    InputBar inputClass;

    string *ListOfClasses; 
    int listSize = 0;
    
    void Construct(int windowWidth, int windowHeight);
    void Deconstruct();

    void Draw();
        void DrawBackground();
        void DrawCreateClass();
        void DrawClassList();
};

#endif