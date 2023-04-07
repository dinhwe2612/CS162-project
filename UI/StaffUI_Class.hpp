#ifndef StaffUI_Class_hpp
#define StaffUI_Class_hpp

#include "../external/raylib/src/raylib.h"
#include "Button.hpp"
#include "InputBar.hpp"
#include <iostream>
#include <array>
#include <algorithm>

struct Class
{
    int windowWidth;
    int windowHeight;

    Texture2D background;

    Font PT_serif_bold;
    Font PT_serif_regular;

    Button addClass;
    Button close;
    Button view, drop, add, back;

    InputBar inputClass;

    std::array<std::string, 100> ListOfClasses = {"22TT1", "22TT2", "21TT1", "21TT2", "20TT1", "20TT2", "19TT1", "19TT2", "18TT1", "18TT2"}; 
    int listSize = 10;

    std::string classDir;


    void Construct(int windowWidth, int windowHeight);
    void Deconstruct();

    std::string LoadDroppedFile();

    void Draw();
        void DrawBackground();
        void DrawCreateClass();
        void DrawClassList();
        void DrawViewClass();
};

#endif