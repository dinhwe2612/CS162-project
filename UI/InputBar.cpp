#include "InputBar.hpp"

void InputBar::draw() {
    // BeginDrawing();
        SetInputText();
        DrawRectanglePro(inputShape, origin, 0, colorBox);
        DrawTextEx(font, (startingInput + currentInput).c_str(), coordText, szText, spacing, colorText);
    // EndDrawing();
}

bool check(Vector2 pos, Rectangle shape) {
    if (pos.x < shape.x || shape.x + shape.width <= pos.x) return false;
    if (pos.y < shape.y || shape.y + shape.height <= pos.y) return false;
    return true;
}

void InputBar::SetInputText() {
    if (CheckCollisionPointRec(GetMousePosition(), inputShape)) {
        colorBox = GRAY;
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
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
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
} 

string InputBar::GetInput() {
    return currentInput;
}