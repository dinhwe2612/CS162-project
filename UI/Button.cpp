#include "Button.hpp"

void Button::SetRectangle(float x, float y, float width, float height, Color In, Color Out) {
    buttonShape = (Rectangle){x, y, width, height};
    inColor = In;
    outColor = Out;
}

void Button::SetText(Font _font, string _Text, float coordX, float coordY, float _fontSize, float _spacing, Color _textColor) {
    font = _font;
    Text = _Text;
    coordText = (Vector2){coordX, coordY};
    fontSize = _fontSize;
    spacing = _spacing;
    textColor = _textColor;  
}

void Button::SetTexture(string path) {
    image = LoadTexture(path.c_str());
    bsrc = (Rectangle){0, 0, image.width, image.height};
    origin = (Vector2){0, 0};
}

void Button::DrawText() {
    Color curColor;
    if (CheckCollisionPointRec(GetMousePosition(), buttonShape)) {
        curColor = inColor;
    } else {
        curColor = outColor;
    }

    DrawRectangleRec(buttonShape, curColor);
    DrawTextEx(font, Text.c_str(), coordText, fontSize, spacing, textColor);
}

void Button::DrawTexture() {
    Color curColor;
    if (CheckCollisionPointRec(GetMousePosition(), buttonShape)) {
        curColor = inColor;
    } else {
        curColor = outColor;
    }

    DrawTexturePro(image, bsrc, buttonShape, origin, 0, curColor);
}

bool Button::isPRESSED(int button) {
    if (CheckCollisionPointRec(GetMousePosition(), buttonShape)) {
        if (IsMouseButtonPressed(button)) return true;
    }
    return false;
}