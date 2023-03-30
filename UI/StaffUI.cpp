#include "StaffUI.hpp"

void StaffUI::Construct(float windowWidth, float windowHeight)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    background = LoadTexture("UI/images/background5.png");
    PT_serif_regular = LoadFont("UI/font/PT_Serif/PTSerif-Regular.ttf");

    dropDown.SetTexture("UI/images/down-arrow-3.png");
    dropDown.SetRectangle(0.97*windowWidth, 0.005*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);

    cornerStripes.SetTexture("UI/images/stripes.png");
    cornerStripes.SetRectangle(0.01*windowWidth, 0.005*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);

    oldPassword.Construct(windowWidth/2 + 2 - 11, 0.2*windowHeight + 93 + 2, 200 - 4, 32 - 4, windowWidth/2 - 50 + 3, 0.2*windowHeight + 93, 0.022*windowWidth, 0.5, 8, "");
    oldPassword.colorBox1 = WHITE;

    newPassword.Construct(windowWidth/2 + 2 - 11, 0.2*windowHeight + 153 + 2, 200 - 4, 32 - 4, windowWidth/2 - 50 + 3, 0.2*windowHeight + 153, 0.022*windowWidth, 0.5, 8, "");
    newPassword.colorBox1 = WHITE;

    confirmPassword.Construct(windowWidth/2 + 2 - 11, 0.2*windowHeight + 213 + 2, 200 - 4, 32 - 4, windowWidth/2 - 50 + 3, 0.2*windowHeight + 213, 0.022*windowWidth, 0.5, 8, "");
    confirmPassword.colorBox1 = WHITE;
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

void StaffUI::DrawDropDownAccount()
{
    // check if down arrow is clicked
    static bool IS_DROPDOWN_CLICKED = false;
    
    if (dropDown.isPRESSED(MOUSE_BUTTON_LEFT))
        IS_DROPDOWN_CLICKED = true;
    else if (!CheckCollisionPointRec(GetMousePosition(), (Rectangle){0.86*windowWidth, 0, 0.14*windowWidth, 0.15*windowHeight}))
        IS_DROPDOWN_CLICKED = false;

    // draw features accordingly
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

void StaffUI::DrawDropDownSchoolYear(int numberOfCreatedSchoolYear)
{
    // check if stripes icon is clicked
    static bool IS_DROPDOWN_CLICKED = false;

    if (cornerStripes.isPRESSED(MOUSE_BUTTON_LEFT))
        IS_DROPDOWN_CLICKED = true;
    else if (!CheckCollisionPointRec(GetMousePosition(), (Rectangle){0, 0.05*windowHeight, 0.2*windowWidth, windowWidth}) 
                && !cornerStripes.isPRESSED(MOUSE_BUTTON_LEFT) 
                && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        IS_DROPDOWN_CLICKED = false;

    if (IS_DROPDOWN_CLICKED)
    {
        DrawRectangle(0, 0.05*windowHeight, 0.2*windowWidth, windowWidth, RAYWHITE);
        DrawLine(0.2*windowWidth, 0.05*windowHeight, 0.2*windowWidth, windowHeight, LIGHTGRAY);
    }


   
}

void StaffUI::DrawChangePassword() {
    DrawBackground();
    // draw top bar
    Rectangle bar = {0, 0, windowWidth, 0.05*windowHeight};
    DrawRectangleRec(bar, DARKBLUE);

    // draw outer box border
    Rectangle borders = {windowWidth/2, windowHeight/2, 0.31*windowWidth, 0.31*windowWidth};
    Vector2 bordersOrigin = {borders.width/2, borders.height/2};
    DrawRectanglePro(borders, bordersOrigin, 0, LIGHTGRAY);

    // draw outer box
    Rectangle rec = {windowWidth/2, windowHeight/2, 0.3*windowWidth, 0.3*windowWidth};
    Vector2 recOrigin = {rec.width/2, rec.height/2};
    DrawRectanglePro(rec, recOrigin, 0, RAYWHITE);

    // draw "Change password" text
    Vector2 changePasswordPos = {windowWidth/2 - 110, 0.2*windowHeight + 33};
    DrawTextEx(PT_serif_regular, "Change password", changePasswordPos, 0.03*windowWidth, 0.5, BLACK);

    // draw "Old password" box
    Vector2 oldPasswordPos = {windowWidth/2 - 188, 0.2*windowHeight + 93};
    DrawTextEx(PT_serif_regular, "Old password", oldPasswordPos, 0.022*windowWidth, 0.5, BLACK);
    Rectangle newPasswordBox = (Rectangle){windowWidth/2 - 11, 0.2*windowHeight + 93, 200, 32};
    DrawRectangleRec(newPasswordBox, BLACK);
    oldPassword.Draw();

    // draw "New password" box
    Vector2 newPasswordPos = {windowWidth/2 - 188, 0.2*windowHeight + 153};
    DrawTextEx(PT_serif_regular, "New password", newPasswordPos, 0.022*windowWidth, 0.5, BLACK);
    Rectangle oldPasswordBox = (Rectangle){windowWidth/2 - 11, 0.2*windowHeight + 153, 200, 32};
    DrawRectangleRec(oldPasswordBox, BLACK);
    newPassword.Draw();

    // draw "Confirm password" box
    Vector2 confirmPasswordPos = {windowWidth/2 - 188, 0.2*windowHeight + 213};
    DrawTextEx(PT_serif_regular, "Confirm password", confirmPasswordPos, 0.022*windowWidth, 0.5, BLACK);
    Rectangle confirmPasswordBox = (Rectangle){windowWidth/2 - 11, 0.2*windowHeight + 213, 200, 32};
    DrawRectangleRec(confirmPasswordBox, BLACK);
    confirmPassword.Draw();
}

// void StaffUI::DrawSchoolYear(bool isDroppedDown, )
// {
//     if (isDroppedDown)
//     {
//         DrawRectangle(0, 0.05*windowHeight, 0.2*windowWidth, windowWidth, RAYWHITE);
//         DrawLine(0.2*windowWidth, 0.05*windowHeight, 0.2*windowWidth, windowHeight, LIGHTGRAY);
//     }
//     else
//     {
        
//     }
// }

void StaffUI::Draw()
{
    switch (menuStaff) {
    default:
        DrawBackground();
        DrawStaticElement();
        dropDown.DrawTexture();
        signOut.DrawText();
            DrawDropDownAccount();
        cornerStripes.DrawTexture();
        DrawDropDownSchoolYear(5);
        ChangePassWord.DrawText();
        if (ChangePassWord.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuStaff = CHANGE_PASSWORD;
        }
        break;
    case CHANGE_PASSWORD:
        DrawChangePassword();
        break;
    }
}