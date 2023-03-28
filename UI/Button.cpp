#include "Button.hpp"

void Button::SetRectangle(float x, float y, float width, float height, Color In, Color Out) {
    buttonShape = {x, y, width, height};
    inColor = In;
    outColor = Out;
}

void Button::SetText(Font _font, string _Text, float coordX, float coordY, float _fontSize, float _spacing, Color _textColor) {
    font = _font;
    Text = _Text;
    coordText = {coordX, coordY};
    fontSize = _fontSize;
    spacing = _spacing;
    textColor = _textColor;  
}

void Button::Draw() {
    Color curColor;
    if (CheckCollisionPointRec(GetMousePosition(), buttonShape)) {
        curColor = inColor;
    } else {
        curColor = outColor;
    }

    DrawRectangleRec(buttonShape, curColor);
    DrawTextEx(font, Text.c_str(), coordText, fontSize, spacing, textColor);
}

bool Button::isPRESSED(int button) {
    if (CheckCollisionPointRec(GetMousePosition(), buttonShape)) {
        if (IsMouseButtonPressed(button)) return true;
    }
    return false;
}