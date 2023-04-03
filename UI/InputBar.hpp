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
    Color colorBox = RAYWHITE, colorBox1 = RAYWHITE, colorBox2 = RAYWHITE, colorText = BLACK;
    int MAX_SIZE = 0;
    bool OnText = false;
    bool isPassword = false;
    string password = "";

    void Construct(float x, float y, float width, float height, float cX, float cY, int _szText, float _spacing, int _MAX_SIZE, string Starting);
    void SetInputText();
    void SetColorBox(Color color1, Color color2) { colorBox1 = color1; colorBox2 = color2; }
    void Draw();
    string GetInput();  
};

#endif