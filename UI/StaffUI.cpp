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

void StaffUI::Draw()
{
    DrawBackground();
    DrawStaticElement();
    DrawDropDownAccount();
    DrawDropDownSchoolYear();
}