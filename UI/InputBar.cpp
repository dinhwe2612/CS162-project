#include "InputBar.hpp"

void InputBar::Construct(float x, float y, float width, float height, float cX, float cY, int _szText, int _spacing, int _MAX_SIZE, string Starting) {
    inputShape = {x, y, width, height};
    coordText = {cX, cY};
    szText = _szText;
    spacing = _spacing;
    MAX_SIZE = _MAX_SIZE;
    startingInput = Starting;
    origin = {0, 0};
    font = LoadFont("UI/font/PT_Serif/PTSerif-Bold.ttf");
}

void InputBar::Draw() {
    SetInputText();
    DrawRectanglePro(inputShape, origin, 0, colorBox);
    DrawTextEx(font, (startingInput + currentInput + (OnText ? "_" : "")).c_str(), coordText, szText, spacing, colorText);
}

void InputBar::SetInputText() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(GetMousePosition(), inputShape)) {
            OnText = true;
        } else {
            OnText = false;
        }
    }
    if (OnText) {
        colorBox = GRAY;
        int key = GetCharPressed();
        while(key > 0) {
            if (currentInput.size() <= MAX_SIZE) {
                currentInput.push_back(key);
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !currentInput.empty()) {
            currentInput.pop_back();
        }
    } else {
        colorBox = WHITE;
    }
} 

string InputBar::GetInput() {
    return currentInput;
}