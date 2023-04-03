#include "InputBar.hpp"

void InputBar::Construct(float x, float y, float width, float height, float cX, float cY, int _szText, float _spacing, int _MAX_SIZE, string Starting) {
    inputShape = (Rectangle){x, y, width, height};
    coordText = (Vector2){cX, cY};
    szText = _szText;
    spacing = _spacing;
    MAX_SIZE = _MAX_SIZE;
    startingInput = Starting;
    origin = (Vector2){0, 0};
    font = LoadFont("UI/font/DM_Serif_Display/DMSerifDisplay-Regular.ttf");
}

void InputBar::Draw() {
    SetInputText();
    DrawRectanglePro(inputShape, origin, 0, colorBox);
    DrawTextEx(font, (startingInput + (isPassword ? password : currentInput) + (OnText ? "_" : "")).c_str(), coordText, szText, spacing, colorText);
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
        colorBox = colorBox2;
        int key = GetCharPressed();
        while(key > 0) {
            if (currentInput.size() <= MAX_SIZE) {
                currentInput.push_back(key);
                password.push_back('*');
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !currentInput.empty()) {
            currentInput.pop_back();
            password.pop_back();
        }

    } else {
        colorBox = colorBox1;
    }
} 

string InputBar::GetInput() {
    return currentInput;
}