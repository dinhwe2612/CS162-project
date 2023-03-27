#ifndef InputBar_hpp
#define InputBar_hpp

#include "../external/raylib/src/raylib.h"
#include <iostream>
#include <string.h>
using namespace std;

struct InputBar {
    string startingInput, currentInput;
    Texture inputText;
    Font font;
    Rectangle inputShape;
    Vector2 origin, coordText;
    float szText, spacing;
    Color colorBox = WHITE, colorText = BLACK;
    int MAX_SIZE = 5;

    InputBar(float _left, float _top, float _right, float _bottom, float cX, float cY, int _szText, int _spacing, int _MAX_SIZE, string Starting) {
        szText = _szText;
        spacing = _spacing;
        startingInput = Starting;
        MAX_SIZE = _MAX_SIZE;
        origin = {0, 0};
        inputShape = {_left, _top, _right, _bottom};
        font = LoadFont("UI/font/PT_Serif/PTSerif-Bold.ttf");
        coordText = {cX, cY};
    }
    void draw();
    void SetInputText();
    string GetInput();
};

#endif