#ifndef button_hpp
#define button_hpp

#include "../external/raylib/src/raylib.h"
#include <iostream>
#include <string.h>

using namespace std;

struct Button {
    Rectangle buttonShape;
    Color inColor, outColor;

    Font font;
    string Text;
    Vector2 coordText;
    float fontSize;
    float spacing;
    Color textColor;
    

    void SetRectangle(float x, float y, float width, float height, Color In, Color Out);
    void SetText(Font _font, string _Text, float coordX, float coordY, float _fontSize, float _spacing, Color _textColor);
    void Draw();
    bool isPRESSED(int button);
};

#endif