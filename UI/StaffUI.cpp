#include "StaffUI.hpp"

void StaffUI::Construct(float windowWidth, float windowHeight)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    background = LoadTexture("UI/images/background5.png");
    PT_serif_regular = LoadFont("UI/font/PT_Serif/PTSerif-Regular.ttf");

    dropDown.SetTexture("UI/images/down-arrow-3.png");
    dropDown.SetRectangle(0.97*windowWidth, 0.005*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);
}

void StaffUI::Deconstruct()
{
    UnloadTexture(background);
    UnloadTexture(dropDown.image);

    UnloadFont(PT_serif_regular);
}

void StaffUI::DrawBackground()
{
    Vector2 origin = {0, 0};
    Rectangle bsrc = {0, 0, background.width, background.height};
    Rectangle bdest = {0, 0, windowWidth, windowHeight};
    DrawTexturePro(background, bsrc, bdest, origin, 0, WHITE);
}

void StaffUI::DrawStaticElement()
{
    // draw top bar
    Rectangle bar = {0, 0, windowWidth, 0.05*windowHeight};
    DrawRectangleRec(bar, DARKBLUE);

    // draw "hello <username>" text
    Vector2 loginStatusPos = {0.86*windowWidth, 0.01*windowHeight};
    DrawTextEx(PT_serif_regular, "Hello <username>", loginStatusPos, 0.015*windowWidth, 0.5, RAYWHITE);
}

void StaffUI::updateDropDownBox()
{
    static bool IS_DROPDOWN_CLICKED = false;
    if (dropDown.isPRESSED(MOUSE_BUTTON_LEFT))
        IS_DROPDOWN_CLICKED = true;
    else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !dropDown.isPRESSED(MOUSE_BUTTON_LEFT))
        IS_DROPDOWN_CLICKED = false;

    if (IS_DROPDOWN_CLICKED)
    {
        signOut.SetRectangle(0.86*windowWidth, 0.05*windowHeight, 0.14*windowWidth, 0.05*windowHeight, GRAY, LIGHTGRAY);
        ChangePassWord.SetRectangle(0.86*windowWidth, 0.1*windowHeight, 0.14*windowWidth, 0.05*windowHeight, GRAY, LIGHTGRAY);
        signOut.SetText(PT_serif_regular, ">    Sign out", 0.88*windowWidth, 0.06*windowHeight, 0.015*windowWidth, 0.5, BLACK);
        ChangePassWord.SetText(PT_serif_regular, ">    Change password", 0.88*windowWidth, 0.11*windowHeight, 0.015*windowWidth, 0.5, BLACK);
    }
    else
    {
        signOut.SetRectangle(1*windowWidth, 0.05*windowHeight, 0.14*windowWidth, 0.05*windowHeight, GRAY, LIGHTGRAY);
        ChangePassWord.SetRectangle(1*windowWidth, 0.1*windowHeight, 0.14*windowWidth, 0.05*windowHeight, GRAY, LIGHTGRAY);
        signOut.SetText(PT_serif_regular, ">    Sign out", 1*windowWidth, 0.06*windowHeight, 0.015*windowWidth, 0.5, BLACK);
        ChangePassWord.SetText(PT_serif_regular, ">    Change password", 1*windowWidth, 0.11*windowHeight, 0.015*windowWidth, 0.5, BLACK);
    }

}



void StaffUI::Draw()
{
    DrawBackground();
    DrawStaticElement();
    dropDown.DrawTexture();
    signOut.DrawText();
        updateDropDownBox();

    ChangePassWord.DrawText();
}