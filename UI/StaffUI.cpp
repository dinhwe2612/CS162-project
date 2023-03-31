#include "StaffUI.hpp"

//---------------------------------------------------------------------------------------------//
//                                  Construct / Deconstruct
//---------------------------------------------------------------------------------------------//

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


    oldPassword.Construct(windowWidth/2 + 2 - 11, 0.2*windowHeight + 93 + 2 + 4, 200 - 4, 32 - 4, windowWidth/2 - 11 + 4, 0.2*windowHeight + 93 + 4, 0.022*windowWidth, 0.5, 8, "");
    oldPassword.colorBox1 = WHITE;

    newPassword.Construct(windowWidth/2 + 2 - 11, 0.2*windowHeight + 153 + 2 + 4 * 2, 200 - 4, 32 - 4, windowWidth/2 - 11 + 4, 0.2*windowHeight + 153 + 4 * 2, 0.022*windowWidth, 0.5, 8, "");
    newPassword.colorBox1 = WHITE;

    confirmPassword.Construct(windowWidth/2 + 2 - 11, 0.2*windowHeight + 213 + 2 + 4 * 3, 200 - 4, 32 - 4, windowWidth/2 - 11 + 4, 0.2*windowHeight + 213 + 4 * 3, 0.022*windowWidth, 0.5, 8, "");
    confirmPassword.colorBox1 = WHITE;

    BUTTON_SchoolYear_isCLICKED = new bool[101];
    memset(BUTTON_SchoolYear_isCLICKED, 0, sizeof BUTTON_SchoolYear_isCLICKED);
}

void StaffUI::Deconstruct()
{
    UnloadTexture(background);
    UnloadTexture(dropDown.image);
    UnloadTexture(addSchoolYear.image);

    UnloadFont(PT_serif_regular);
    UnloadFont(PT_serif_bold);

    delete []BUTTON_SchoolYear_isCLICKED;
}

//---------------------------------------------------------------------------------------------//
//                              All static elements drawn here
//---------------------------------------------------------------------------------------------//

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

//---------------------------------------------------------------------------------------------//
//                              All non-static elements drawn here
//---------------------------------------------------------------------------------------------//

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

    if (cornerStripes.isPRESSED(MOUSE_BUTTON_LEFT)) {
        IS_DROPDOWN_CLICKED = true;
        for(int i = 0; i < 50; ++i) {
            BUTTON_SchoolYear_isCLICKED[i] = false;
        }
    }
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

    // array of school year will be inserted here
    
    std::array<std::string, 12> ListOfSchoolYear = {"2021 - 2022", "2020 - 2021", "2019 - 2020", "2018 - 2019", "2017 - 2018", "2016 - 2017", "2015 - 2016", "2014 - 2015", "2013 - 2014", "2012 - 2013", "2011 - 2012", "2010 - 2011"};
    
    float static posY = 0;
    float static totalAccumulativeHeight = 0;
    float accumulativeHeight = 0;

    posY += GetMouseWheelMove() * 30;
    if (posY > 0) posY = 0;
    int szList = ListOfSchoolYear.size();
    if (0.18*windowHeight + szList * 0.1*windowHeight + posY + totalAccumulativeHeight <= 720)
            posY = 720 - (0.18*windowHeight + szList * 0.1*windowHeight + totalAccumulativeHeight);
    
    
    // draw and store school year buttons

    for (int i = 0; i < szList; ++i)
    {
        // if (0.18*windowHeight + i * 0.1*windowHeight + posY + accumulativeHeight <= 0.05*windowHeight) continue;

        Button schoolYear;
        schoolYear.SetRectangle(0, 0.18*windowHeight + i * 0.1*windowHeight + posY + accumulativeHeight, 0.2*windowWidth, 0.08*windowHeight, LIGHTGRAY, RAYWHITE);
        if (GetMouseY() >= 0.18*windowHeight && schoolYear.isPRESSED(MOUSE_BUTTON_LEFT))
            BUTTON_SchoolYear_isCLICKED[i] ^= 1;

        if (BUTTON_SchoolYear_isCLICKED[i]) {
            schoolYear.SetText(PT_serif_bold, "v   " + ListOfSchoolYear[i], 0.01*windowWidth, 0.2*windowHeight + i * 0.1*windowHeight + posY + accumulativeHeight, 0.02*windowWidth, 0.5, DARKBLUE);
            DrawSchoolYearMenu();
        }
        //     // Draw 3 buttons for semester in rectangle
        //     Button Semester1;
        //     Semester1.SetRectangle(0, 0.18*windowHeight + i * 0.1*windowHeight + posY + 0.08*windowHeight + accumulativeHeight, 0.2*windowWidth, 0.1*windowHeight, LIGHTGRAY, RAYWHITE);
        //     Semester1.SetText(PT_serif_bold, "Semester 1", 0.04*windowWidth, 0.2*windowHeight + i * 0.1*windowHeight + posY + 0.08*windowHeight + accumulativeHeight, 0.02*windowWidth, 0.5, DARKBLUE);
        //     Semester1.DrawText();
        //     Button Semester2;
        //     Semester2.SetRectangle(0, 0.18*windowHeight + i * 0.1*windowHeight + posY + 0.18*windowHeight + accumulativeHeight, 0.2*windowWidth, 0.1*windowHeight, LIGHTGRAY, RAYWHITE);
        //     Semester2.SetText(PT_serif_bold, "Semester 2", 0.04*windowWidth, 0.2*windowHeight + i * 0.1*windowHeight + posY + 0.18*windowHeight + accumulativeHeight, 0.02*windowWidth, 0.5, DARKBLUE);
        //     Semester2.DrawText();
        //     Button Semester3;
        //     Semester3.SetRectangle(0, 0.18*windowHeight + i * 0.1*windowHeight + posY + 0.28*windowHeight + accumulativeHeight, 0.2*windowWidth, 0.1*windowHeight, LIGHTGRAY, RAYWHITE);
        //     Semester3.SetText(PT_serif_bold, "Semester 3", 0.04*windowWidth, 0.2*windowHeight + i * 0.1*windowHeight + posY + 0.28*windowHeight + accumulativeHeight, 0.02*windowWidth, 0.5, DARKBLUE);
        //     Semester3.DrawText();

        //     accumulativeHeight += 0.3*windowHeight;
        // }
        else schoolYear.SetText(PT_serif_bold, ">   " + ListOfSchoolYear[i], 0.01*windowWidth, 0.2*windowHeight + i * 0.1*windowHeight + posY + accumulativeHeight, 0.02*windowWidth, 0.5, DARKBLUE);
        
        schoolYear.DrawText();

        ListOfSchoolYearButtons.push_back(schoolYear);
    }
    totalAccumulativeHeight = accumulativeHeight;

    // draw a rectangle to hide scroll up contents

    DrawRectangle(0, 0.05*windowHeight, 0.2*windowWidth, 0.13*windowHeight, RAYWHITE);
    DrawLine(0, 0.18*windowHeight, 0.2*windowWidth, 0.18*windowHeight, BLUE);

    // draw School year text

    Vector2 syTextOrigin = {0.01*windowWidth, 0.06*windowHeight};
    DrawTextEx(PT_serif_bold, "School Year", syTextOrigin, 0.025*windowWidth, 0.5, DARKBLUE);

    // draw add school year button

    addSchoolYear.DrawTexture();
    Vector2 addTextOrigin = {0.035*windowWidth, 0.12*windowHeight};
    DrawTextEx(PT_serif_bold, "Add a school year", addTextOrigin, 0.018*windowWidth, 0.5, DARKBLUE);

    DrawStaticElement();
}

void StaffUI::DrawChangePassword() 
{
    static int statusChangePassword = 0;

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
    Vector2 oldPasswordPos = {windowWidth/2 - 176, 0.2*windowHeight + 93 + 4};
    DrawTextEx(PT_serif_regular, "Old password", oldPasswordPos, 0.022*windowWidth, 0.5, BLACK);
    Rectangle newPasswordBox = (Rectangle){windowWidth/2 - 11, 0.2*windowHeight + 93 + 4, 200, 32};
    DrawRectangleRec(newPasswordBox, BLACK);
    oldPassword.Draw();

    // draw "New password" box
    Vector2 newPasswordPos = {windowWidth/2 - 176, 0.2*windowHeight + 153 + 4 * 2};
    DrawTextEx(PT_serif_regular, "New password", newPasswordPos, 0.022*windowWidth, 0.5, BLACK);
    Rectangle oldPasswordBox = (Rectangle){windowWidth/2 - 11, 0.2*windowHeight + 153 + 4 * 2, 200, 32};
    DrawRectangleRec(oldPasswordBox, BLACK);
    newPassword.Draw();

    // draw "Confirm password" box
    Vector2 confirmPasswordPos = {windowWidth/2 - 188, 0.2*windowHeight + 213 + 4 * 3};
    DrawTextEx(PT_serif_regular, "Confirm password", confirmPasswordPos, 0.022*windowWidth, 0.5, BLACK);
    Rectangle confirmPasswordBox = (Rectangle){windowWidth/2 - 11, 0.2*windowHeight + 213 + 4 * 3, 200, 32};
    DrawRectangleRec(confirmPasswordBox, BLACK);
    confirmPassword.Draw();

    // draw "Back" button
    Button Back;
    Back.SetRectangle(0, 0, 0.1*windowHeight, 0.05*windowHeight, BLUE, DARKBLUE);
    Back.SetText(PT_serif_bold, "Back", 0.01*windowWidth, 0.01*windowHeight, 0.02*windowWidth, 0.5, WHITE);
    Back.DrawText();
    if (Back.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuStaff = 0;
        statusChangePassword = 0;
    }

    // draw "Change" button
    Button Change;
    Change.SetRectangle(0.379*windowWidth, 0.64*windowHeight, 0.24*windowWidth, 46.72, BLUE, DARKBLUE);
    Change.SetText(PT_serif_bold, "Change", 0.475*windowWidth, 0.655*windowHeight, 0.02*windowWidth, 0.5, RAYWHITE);
    Change.DrawText();

    // draw "Your password has been changed" text
    enum STATUS_CHANGE_PASSWORD {
        DEFAULT,
        CHANGE_PASSWORD_SUCCESS,
        CHANGE_PASSWORD_FAIL
    };

    if (Change.isPRESSED(MOUSE_BUTTON_LEFT)) {
        statusChangePassword = CHANGE_PASSWORD_SUCCESS;
    }
    if (statusChangePassword == CHANGE_PASSWORD_SUCCESS) {
        Vector2 changedPos = {windowWidth/2 - 158, 0.2*windowHeight + 273};
        DrawTextEx(PT_serif_regular, "Your password has been changed", changedPos, 0.022*windowWidth, 0.5, BLUE);
    } else if (statusChangePassword == CHANGE_PASSWORD_FAIL) {
        Vector2 failPos = {windowWidth/2 - 158, 0.2*windowHeight + 273};
        DrawTextEx(PT_serif_regular, "Your old password is not correct", failPos, 0.022*windowWidth, 0.5, RED);
    } else {

    }
}

void StaffUI::DrawSchoolYearMenu()
{
    static Button SchoolYear;
    
    Vector2 accessDir = {0.25*windowWidth, 0.01*windowHeight};
    
}
//---------------------------------------------------------------------------------------------//
//                              All objects drawn managed here
//---------------------------------------------------------------------------------------------//

void StaffUI::Draw()
{
    switch (menuStaff) {
    default:
        DrawBackground();
        DrawStaticElement();
        DrawDropDownAccount();
        DrawDropDownSchoolYear();
        DrawSchoolYearMenu();
        if (ChangePassWord.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuStaff = CHANGE_PASSWORD;
        }
        break;
    case CHANGE_PASSWORD:
        DrawChangePassword();
        break;
    }

}