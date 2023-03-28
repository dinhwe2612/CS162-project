#include "StaffUI.hpp"

void StaffUI::Construct(float windowWidth, float windowHeight) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    background = LoadTexture("UI/images/background5.png");
    PT_serif_regular = LoadFont("UI/font/PT_Serif/PTSerif-Regular.ttf");
    
    Back.SetRectangle(0, 0, 100, 100, GRAY, WHITE);
    Back.SetTexture("UI/images/backButton.png");

    float tmpX = (windowWidth - 100) / 2 - 100;
    float tmpY = 150;
    ViewProfile.SetRectangle(tmpX, tmpY, 250, 70, WHITE, GRAY);
    ViewProfile.SetText(PT_serif_regular, "View Profile", tmpX + 2, tmpY + 2, 60, 0.5, BLACK);

    SignOut.SetRectangle(tmpX, tmpY + 200, 250, 70, WHITE, GRAY);
    SignOut.SetText(PT_serif_regular, "Sign Out", tmpX + 2, tmpY + 200, 60, 0.5, BLACK);
}

void StaffUI::Deconstruct() {
    UnloadTexture(background);
    UnloadFont(PT_serif_regular);
}

void StaffUI::DrawBackground() {
    Vector2 origin = {0, 0};
    Rectangle bsrc = {0, 0, background.width, background.height};
    Rectangle bdest = {0, 0, windowWidth, windowHeight};
    DrawTexturePro(background, bsrc, bdest, origin, 0, WHITE);

    DrawRectangle(100, 100, windowWidth - 200, 600, GRAY);
}

void StaffUI::DrawButton() {
    
    
}

void StaffUI::Draw() {
    switch (menuStaff) {
    default:
        DrawBackground();
        ViewProfile.DrawText();
        if (ViewProfile.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuStaff = VIEWPROFILE;
        }
        break;
    case VIEWPROFILE:
        DrawBackground();
        Back.DrawTexture();
        SignOut.DrawText();
        if (Back.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuStaff = STAFF;
        }
        break;
    }
}