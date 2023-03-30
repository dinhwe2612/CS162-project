#include "StaffUI.hpp"
#include <array>
#include <iostream>

void StaffUI::Construct(float windowWidth, float windowHeight)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    // texture

    background = LoadTexture("UI/images/background5.png");
    
    // font

    PT_serif_regular = LoadFont("UI/font/PT_Serif/PTSerif-Regular.ttf");
    PT_serif_bold = LoadFont("UI/font/PT_Serif/PTSerif-Bold.ttf");

    // button

    dropDown.SetTexture("UI/images/down-arrow-3.png");
    dropDown.SetRectangle(0.97*windowWidth, 0.005*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);

    cornerStripes.SetTexture("UI/images/stripes.png");
    cornerStripes.SetRectangle(0.01*windowWidth, 0.005*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);

    signOut.SetRectangle(0.86*windowWidth, 0.05*windowHeight, 0.14*windowWidth, 0.05*windowHeight, GRAY, LIGHTGRAY);
    signOut.SetText(PT_serif_regular, ">    Sign out", 0.88*windowWidth, 0.06*windowHeight, 0.015*windowWidth, 0.5, BLACK);

    ChangePassWord.SetRectangle(0.86*windowWidth, 0.1*windowHeight, 0.14*windowWidth, 0.05*windowHeight, GRAY, LIGHTGRAY);
    ChangePassWord.SetText(PT_serif_regular, ">    Change password", 0.88*windowWidth, 0.11*windowHeight, 0.015*windowWidth, 0.5, BLACK);

    addSchoolYear.SetTexture("UI/images/add.png");
    addSchoolYear.SetRectangle(0.01*windowWidth, 0.12*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);


    oldPassword.Construct(windowWidth/2 + 2 - 11, 0.2*windowHeight + 93 + 2, 200 - 4, 32 - 4, windowWidth/2 - 11 + 4, 0.2*windowHeight + 93, 0.022*windowWidth, 0.5, 8, "");
    oldPassword.colorBox1 = WHITE;

    newPassword.Construct(windowWidth/2 + 2 - 11, 0.2*windowHeight + 153 + 2, 200 - 4, 32 - 4, windowWidth/2 - 11 + 4, 0.2*windowHeight + 153, 0.022*windowWidth, 0.5, 8, "");
    newPassword.colorBox1 = WHITE;

    confirmPassword.Construct(windowWidth/2 + 2 - 11, 0.2*windowHeight + 213 + 2, 200 - 4, 32 - 4, windowWidth/2 - 11 + 4, 0.2*windowHeight + 213, 0.022*windowWidth, 0.5, 8, "");
    confirmPassword.colorBox1 = WHITE;
}

void StaffUI::Deconstruct()
{
    UnloadTexture(background);
    UnloadTexture(dropDown.image);
    UnloadTexture(addSchoolYear.image);

    UnloadFont(PT_serif_regular);
    UnloadFont(PT_serif_bold);
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

    // draw corner stripes in top left corner

    cornerStripes.DrawTexture();

    // draw down arrow in top right corner

    dropDown.DrawTexture();
}

void StaffUI::DrawDropDownAccount()
{
    // check if down arrow is clicked

    static bool IS_DROPDOWN_CLICKED = false;
    
    if (dropDown.isPRESSED(MOUSE_BUTTON_LEFT))
        IS_DROPDOWN_CLICKED = true;
    else if (!CheckCollisionPointRec(GetMousePosition(), (Rectangle){0.86*windowWidth, 0, 0.14*windowWidth, 0.15*windowHeight}))
        IS_DROPDOWN_CLICKED = false;

    // draw sign out and drop down

    if (IS_DROPDOWN_CLICKED)
    {
        signOut.DrawText();
        ChangePassWord.DrawText();
    }
}

void StaffUI::DrawDropDownSchoolYear()
{
    // check if stripes icon is clicked

    static bool IS_DROPDOWN_CLICKED = false;

    if (cornerStripes.isPRESSED(MOUSE_BUTTON_LEFT))
        IS_DROPDOWN_CLICKED = true;
    else if (!CheckCollisionPointRec(GetMousePosition(), (Rectangle){0, 0.05*windowHeight, 0.2*windowWidth, windowWidth}) 
                && !cornerStripes.isPRESSED(MOUSE_BUTTON_LEFT) 
                && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        IS_DROPDOWN_CLICKED = false;

    // draw school year, number of school year needed here

    if (IS_DROPDOWN_CLICKED)
        DrawSchoolYear();
}

void StaffUI::DrawSchoolYear()
{
        // draw pop-up box

        DrawRectangle(0, 0.05*windowHeight, 0.2*windowWidth, windowHeight, RAYWHITE);
        DrawLine(0.2*windowWidth, 0.05*windowHeight, 0.2*windowWidth, windowHeight, LIGHTGRAY);

        // draw School year text

        Vector2 syTextOrigin = {0.01*windowWidth, 0.06*windowHeight};
        DrawTextEx(PT_serif_bold, "School Year", syTextOrigin, 0.025*windowWidth, 0.5, DARKBLUE);

        // draw add school year button

        addSchoolYear.DrawTexture();
        Vector2 addTextOrigin = {0.035*windowWidth, 0.12*windowHeight};
        DrawTextEx(PT_serif_bold, "Add a school year", addTextOrigin, 0.018*windowWidth, 0.5, DARKBLUE);
        
        // array of school year will be inserted here
        
        std::array<std::string, 7> ListOfSchoolYear = {"2021 - 2022", "2020 - 2021", "2019 - 2020", "2018 - 2019", "2017 - 2018", "2016 - 2017", "2015 - 2016"};
        
        for (int i = 0; i < ListOfSchoolYear.size(); ++i)
        {
            Button schoolYear;
            schoolYear.SetRectangle(0, 0.18*windowHeight + i * 0.1*windowHeight, 0.2*windowWidth, 0.08*windowHeight, LIGHTGRAY, RAYWHITE);
            schoolYear.SetText(PT_serif_bold, ">   " + ListOfSchoolYear[i], 0.01*windowWidth, 0.2*windowHeight + i * 0.1*windowHeight, 0.02*windowWidth, 0.5, DARKBLUE);
            schoolYear.DrawText();
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

    // draw "Back" button
    Button Back;
    Back.SetRectangle(0, 0, 0.1*windowHeight, 0.05*windowHeight, BLUE, DARKBLUE);
    Back.SetText(PT_serif_bold, "Back", 0.01*windowWidth, 0.01*windowHeight, 0.02*windowWidth, 0.5, WHITE);
    Back.DrawText();
    if (Back.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuStaff = 0;
    }
}

void StaffUI::Draw()
{
    
        switch (menuStaff) {
    default:
        DrawBackground();
        DrawStaticElement();
        DrawDropDownAccount();
        DrawDropDownSchoolYear();
        if (ChangePassWord.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuStaff = CHANGE_PASSWORD;
        }
        break;
    case CHANGE_PASSWORD:
        DrawChangePassword();
        break;
    }

}