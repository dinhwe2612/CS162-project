#ifndef InputBar_hpp
#define InputBar_hpp

#include "../external/raylib/src/raylib.h"
#include <iostream>
#include <string.h>
using namespace std;

struct InputBar {
    string startingInput, currentInput;
    Font font;
    Rectangle inputShape;
    Vector2 origin, coordText;
    float szText, spacing;
    Color colorBox = RAYWHITE, colorText = BLACK;
    int MAX_SIZE = 0;
    bool OnText = false;

    void Construct(float x, float y, float width, float height, float cX, float cY, int _szText, float _spacing, int _MAX_SIZE, string Starting);
    void SetInputText();
    void Draw();
    string GetInput();  
};

#endif