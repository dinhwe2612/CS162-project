#ifndef StaffUI_Semester_hpp
#define StaffUI_Semester_hpp

#include "../external/raylib/src/raylib.h"
struct Staff_Semester
{
    Texture2D background;

    void Construct();
    void Deconstruct();

    void Draw();
        void DrawBackground();

};


#endif