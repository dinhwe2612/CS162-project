#ifndef button_hpp
#define button_hpp

#include "../external/raylib/src/raylib.h"
#include <iostream>
#include <string.h>

using namespace std;

struct Button 
{
    Rectangle buttonShape;
    Color inColor, outColor;
    
    //Text
    Font font;
    string Text;
    Vector2 coordText;
    float fontSize;
    float spacing;
    Color textColor;
    
    //Texture
    Texture2D image;
    Rectangle bsrc;
    Vector2 origin;

    //
    void SetRectangle(float x, float y, float width, float height, Color In, Color Out);
    
    //For Button Text
    void SetText(Font _font, string _Text, float coordX, float coordY, float _fontSize, float _spacing, Color _textColor);
    void DrawText();
    
    //Fot Button Image
    void SetTexture(string path);
    void DrawTexture();

    bool isPRESSED(int button);
};

#endif