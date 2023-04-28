#include "StudentUI.hpp"

void StudentUI::Construct(float windowWidth, float windowHeight)
{
    this-> windowWidth = windowWidth;
    this-> windowHeight = windowHeight;

    background = LoadTexture("UI/images/background5.png");
    calendar = LoadTexture("UI/images/calendar (2).png");

    PT_serif_regular = LoadFont("UI/font/PT_Serif/PTSerif-Regular.ttf");
    PT_serif_bold = LoadFont("UI/font/PT_Serif/PTSerif-Bold.ttf");

    dropdownButton.SetTexture("UI/images/down-arrow-3.png");
    dropdownButton.SetRectangle(0.97*windowWidth, 0.005*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);

    cornerStripes.SetTexture("UI/images/stripes.png");
    cornerStripes.SetRectangle(0.01*windowWidth, 0.005*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);

    signOut.SetRectangle(0.86*windowWidth, 0.15*windowHeight, 0.14*windowWidth, 0.05*windowHeight, GRAY, LIGHTGRAY);
    signOut.SetText(PT_serif_regular, ">    Sign out", 0.88*windowWidth, 0.16*windowHeight, 0.015*windowWidth, 0.5, BLACK);

    ChangePassWord.SetRectangle(0.86*windowWidth, 0.1*windowHeight, 0.14*windowWidth, 0.05*windowHeight, GRAY, LIGHTGRAY);
    ChangePassWord.SetText(PT_serif_regular, ">    Change password", 0.88*windowWidth, 0.11*windowHeight, 0.015*windowWidth, 0.5, BLACK);

    ViewProfile.SetRectangle(0.86*windowWidth, 0.05*windowHeight, 0.14*windowWidth, 0.05*windowHeight, GRAY, LIGHTGRAY);
    ViewProfile.SetText(PT_serif_regular, ">    View profile", 0.88*windowWidth, 0.06*windowHeight, 0.015*windowWidth, 0.5, BLACK);

    oldPassword.Construct(windowWidth/2 + 2 - 11, 0.2*windowHeight + 93 + 2 + 4, 200 - 4, 32 - 4, windowWidth/2 - 11 + 4, 0.2*windowHeight + 93 + 4, 0.022*windowWidth, 0.5, 8, "");
    oldPassword.colorBox1 = WHITE;
    oldPassword.isPassword = true;

    newPassword.Construct(windowWidth/2 + 2 - 11, 0.2*windowHeight + 153 + 2 + 4 * 2, 200 - 4, 32 - 4, windowWidth/2 - 11 + 4, 0.2*windowHeight + 153 + 4 * 2, 0.022*windowWidth, 0.5, 8, "");
    newPassword.colorBox1 = WHITE;
    newPassword.isPassword = true;

    confirmPassword.Construct(windowWidth/2 + 2 - 11, 0.2*windowHeight + 213 + 2 + 4 * 3, 200 - 4, 32 - 4, windowWidth/2 - 11 + 4, 0.2*windowHeight + 213 + 4 * 3, 0.022*windowWidth, 0.5, 8, "");
    confirmPassword.colorBox1 = WHITE;
    confirmPassword.isPassword = true;

    BUTTON_SchoolYear_isCLICKED = new bool[101];
    memset(BUTTON_SchoolYear_isCLICKED, 0, sizeof BUTTON_SchoolYear_isCLICKED);

    // Semester initialisation
}

void StudentUI::Deconstruct()
{
    UnloadTexture(background);
    UnloadTexture(dropdownButton.image);
    UnloadTexture(cornerStripes.image);
}

void StudentUI::Draw(int& menuLogin)
{
    switch (menuStudent)
    {
    default:
        DrawBackground();
        DrawStaticElements();
        DrawDropDownAccount(menuLogin);//for signout button
        DrawDropDownSchoolYear();
        DrawCurrentWindow();
        break;
    case CHANGE_PASSWORD:
        DrawChangePassword();
        break;
    }
}

void StudentUI::DrawCurrentWindow() {
    switch (menuWindow) {
    default:
        break;
    case SEMESTER:
        _Semester.Draw(menuWindow);
        break;
    }
}

void StudentUI::DrawBackground()
{
    // draw background 
    Vector2 origin = {0, 0};
    Rectangle bsrc = {0, 0, float(background.width), float(background.height)};
    Rectangle bdest = {0, 0, float(windowWidth), float(windowHeight)};
    DrawTexturePro(background, bsrc, bdest, origin, 0, WHITE);

   
}

void StudentUI::DrawStaticElements()
{
    // draw top bar
    Rectangle bar = {0, 0, float(windowWidth), float(0.05*windowHeight)};
    DrawRectangleRec(bar, DARKBLUE);

    // draw "hello <username>" text
    Vector2 loginStatusPos = {float(0.97*windowWidth - 63 - 7 * username.size()), float(0.01*windowHeight)};
    DrawTextEx(PT_serif_regular, ("Hello <" + username + ">").c_str(), loginStatusPos, 0.015*windowWidth, 0.5, RAYWHITE);
    
    // draw corner stripes in top left corner

    cornerStripes.DrawTexture();

    // draw down arrow in top right corner
    dropdownButton.DrawTexture();
}

void StudentUI::DrawChangePassword() 
{
    static int statusChangePassword = 0;

    DrawBackground();
    // draw top bar
    Rectangle bar = {0, 0, float(windowWidth), float(0.05*windowHeight)};
    DrawRectangleRec(bar, DARKBLUE);

    // draw outer box border
    Rectangle borders = {float(windowWidth/2), float(windowHeight/2), float(0.31*windowWidth), float(0.31*windowWidth)};
    Vector2 bordersOrigin = {float(borders.width/2), float(borders.height/2)};
    DrawRectanglePro(borders, bordersOrigin, 0, LIGHTGRAY);

    // draw outer box
    Rectangle rec = {float(windowWidth/2), float(windowHeight/2), float(0.3*windowWidth), float(0.3*windowWidth)};
    Vector2 recOrigin = {float(rec.width/2), float(rec.height/2)};
    DrawRectanglePro(rec, recOrigin, 0, RAYWHITE);

    // draw "Change password" text
    Vector2 changePasswordPos = {float(windowWidth/2 - 110), float(0.2*windowHeight + 33)};
    DrawTextEx(PT_serif_regular, "Change password", changePasswordPos, 0.03*windowWidth, 0.5, BLACK);

    // draw "Old password" box
    Vector2 oldPasswordPos = {float(windowWidth/2 - 176), float(0.2*windowHeight + 93 + 4)};
    DrawTextEx(PT_serif_regular, "Old password", oldPasswordPos, 0.022*windowWidth, 0.5, BLACK);
    Rectangle newPasswordBox = (Rectangle){float(windowWidth/2 - 11), float(0.2*windowHeight + 93 + 4), 200, 32};
    DrawRectangleRec(newPasswordBox, BLACK);
    oldPassword.Draw();

    // draw "New password" box
    Vector2 newPasswordPos = {float(windowWidth/2 - 176), float(0.2*windowHeight + 153 + 4 * 2)};
    DrawTextEx(PT_serif_regular, "New password", newPasswordPos, 0.022*windowWidth, 0.5, BLACK);
    Rectangle oldPasswordBox = (Rectangle){float(windowWidth/2 - 11), float(0.2*windowHeight + 153 + 4 * 2), 200, 32};
    DrawRectangleRec(oldPasswordBox, BLACK);
    newPassword.Draw();

    // draw "Confirm password" box
    Vector2 confirmPasswordPos = {float(windowWidth/2 - 188), float(0.2*windowHeight + 213 + 4 * 3)};
    DrawTextEx(PT_serif_regular, "Confirm password", confirmPasswordPos, 0.022*windowWidth, 0.5, BLACK);
    Rectangle confirmPasswordBox = (Rectangle){float(windowWidth/2 - 11), float(0.2*windowHeight + 213 + 4 * 3), 200, 32};
    DrawRectangleRec(confirmPasswordBox, BLACK);
    confirmPassword.Draw();

    // draw "Back" button
    Button Back;
    Back.SetRectangle(0, 0, 0.1*windowHeight, 0.05*windowHeight, BLUE, DARKBLUE);
    Back.SetText(PT_serif_bold, "Back", 0.01*windowWidth, 0.01*windowHeight, 0.02*windowWidth, 0.5, WHITE);
    Back.DrawText();
    if (Back.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuStudent = DEFAULT;
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
        OLD_PASSWORD_IS_NOT_CORRECT,
        NEW_PASSWORD_IS_OLD_PASSWORD,
        NEW_PASSWORD_IS_NOT_CONFIRM_PASSWORD
    };

    if (Change.isPRESSED(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_ENTER)) {
        int validate = validateAccount(username, oldPassword.GetInput(), false);
        if (validate == 1) {
            if (newPassword.GetInput() == oldPassword.GetInput()) {
                statusChangePassword = NEW_PASSWORD_IS_OLD_PASSWORD;
            } else {
                if (newPassword.GetInput() != confirmPassword.GetInput()) {
                    statusChangePassword = NEW_PASSWORD_IS_NOT_CONFIRM_PASSWORD;
                } else {
                    statusChangePassword = CHANGE_PASSWORD_SUCCESS;
                    changePassword(username, newPassword.GetInput(), false);
                    oldPassword.currentInput = "";
                    oldPassword.password = "";
                    newPassword.currentInput = "";
                    newPassword.password = "";
                    confirmPassword.currentInput = "";
                    confirmPassword.password = "";
                }
            }
        }
        else statusChangePassword = OLD_PASSWORD_IS_NOT_CORRECT;
    }

    if (statusChangePassword == CHANGE_PASSWORD_SUCCESS) {
        Vector2 changedPos = {float(windowWidth/2 - 158), float(0.2*windowHeight + 273)};
        DrawTextEx(PT_serif_regular, "Your password has been changed!", changedPos, 0.022*windowWidth, 0.5, BLUE);
    } 
    else if (statusChangePassword == OLD_PASSWORD_IS_NOT_CORRECT) {
        Vector2 failPos = {float(windowWidth/2 - 158), float(0.2*windowHeight + 273)};
        DrawTextEx(PT_serif_regular, "PLease correct your old password", failPos, 0.022*windowWidth, 0.5, RED);
    } 
    else if (statusChangePassword == NEW_PASSWORD_IS_OLD_PASSWORD){
        Vector2 failPos = {float(windowWidth/2 - 158), float(0.2*windowHeight + 273)};
        DrawTextEx(PT_serif_regular, "Please use another new password", failPos, 0.022*windowWidth, 0.5, RED);
    } 
    else if (statusChangePassword == NEW_PASSWORD_IS_NOT_CONFIRM_PASSWORD){
        Vector2 failPos = {float(windowWidth/2 - 158), float(0.2*windowHeight + 273)};
        DrawTextEx(PT_serif_regular, "Please correct confirm password", failPos, 0.022*windowWidth, 0.5, RED);
    }
}

void StudentUI::DrawDropDownAccount(int &menuLogin)
{
    // check if down arrow is clicked

    static bool IS_DROPDOWN_CLICKED = false;
    
    if (dropdownButton.isPRESSED(MOUSE_BUTTON_LEFT))
        IS_DROPDOWN_CLICKED ^= 1;
    else if (!CheckCollisionPointRec(GetMousePosition(), (Rectangle){float(0.86*windowWidth), 0, float(0.14*windowWidth), float(0.2*windowHeight)}))
        IS_DROPDOWN_CLICKED = false;

    // draw sign out and drop down

    if (IS_DROPDOWN_CLICKED)
    {
        signOut.DrawText();
        ChangePassWord.DrawText();
        ViewProfile.DrawText();

        if (signOut.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuStudent = DEFAULT;
            menuLogin = DEFAULT;
            menuWindow = DEFAULT;
        }
        if (ChangePassWord.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuStudent = CHANGE_PASSWORD;
        }
        if (ViewProfile.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuStudent = VIEW_PROFILE;
        }
    }
}

void StudentUI::DrawDropDownSchoolYear()
{
    // check if stripes icon is clicked

    static bool IS_DROPDOWN_CLICKED = false;

    if (cornerStripes.isPRESSED(MOUSE_BUTTON_LEFT))
    {
        IS_DROPDOWN_CLICKED ^= 1;
        if (IS_DROPDOWN_CLICKED) {
            viewSchoolYear(ListOfSchoolYear, ListSize);
            for(int i = 0; i < ListSize; ++i) {
                BUTTON_SchoolYear_isCLICKED[i] = false;
            }
        }
    }
    else if (!CheckCollisionPointRec(GetMousePosition(), (Rectangle){0, float(0.05*windowHeight), float(0.2*windowWidth), float(windowWidth)}) 
                && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
                && !CheckCollisionPointRec(GetMousePosition(), (Rectangle){float(0.41*windowWidth), float(0.38*windowHeight), float(0.19*windowWidth), float(0.14*windowWidth)}))
        IS_DROPDOWN_CLICKED = false;

    // draw school year, number of school year needed here

    if (IS_DROPDOWN_CLICKED)
    {
        DrawSchoolYear();
    }
    else
    {
        // move invisible buttons out of the screen
        for (auto& schoolYearButton : ListOfSchoolYearButtons)
        {
            schoolYearButton.SetRectangle(windowWidth, 0.18*windowHeight, 0.2*windowWidth, 0.08*windowHeight, LIGHTGRAY, RAYWHITE);
        }
    }
}

void StudentUI::DrawSchoolYear()
{
    // draw pop-up box

    DrawRectangle(0, 0.05*windowHeight, 0.2*windowWidth, windowHeight, RAYWHITE);
    DrawLine(0.2*windowWidth, 0.05*windowHeight, 0.2*windowWidth, windowHeight, LIGHTGRAY);

    // array of school year will be inserted here
    
    float static posY = 0;
    float static totalAccumulativeHeight = 0;
    float accumulativeHeight = 0;

    posY += GetMouseWheelMove() * 30;
    
    // limit the range of SchoolYearButtons
    if (0.18*windowHeight + ListSize * 0.1*windowHeight + posY + totalAccumulativeHeight <= 720)
            posY = 720 - (0.18*windowHeight + ListSize * 0.1*windowHeight + totalAccumulativeHeight);
    if (posY > 0) posY = 0;
    
    // draw and store school year buttons

    for (int i = 0; i < ListSize; ++i)
    {
        //skip drawing if button is out of screen
        if (0.18*windowHeight + i * 0.1*windowHeight + posY + accumulativeHeight <= 0.05*windowHeight) continue;

        Button schoolYear;
        schoolYear.SetRectangle(0, 0.18*windowHeight + i * 0.1*windowHeight + posY + accumulativeHeight, 0.2*windowWidth, 0.08*windowHeight, LIGHTGRAY, RAYWHITE);
        if (GetMouseY() >= 0.18*windowHeight && schoolYear.isPRESSED(MOUSE_BUTTON_LEFT))
            BUTTON_SchoolYear_isCLICKED[i] ^= 1;

        if (BUTTON_SchoolYear_isCLICKED[i]) {
            schoolYear.SetText(PT_serif_bold, ">   " + ListOfSchoolYear[i], 0.01*windowWidth, 0.2*windowHeight + i * 0.1*windowHeight + posY + accumulativeHeight, 0.02*windowWidth, 0.5, DARKBLUE);

            menuWindow = SEMESTER;
            _Semester.menuSemester = 0;
            _Semester.SchoolYear = ListOfSchoolYear[i]; 
            viewSemester(_Semester.SchoolYear, _Semester.ListOfSemesters, _Semester.listSize);
        }

        else 
            schoolYear.SetText(PT_serif_bold, ">   " + ListOfSchoolYear[i], 0.01*windowWidth, 0.2*windowHeight + i * 0.1*windowHeight + posY + accumulativeHeight, 0.02*windowWidth, 0.5, DARKBLUE);
        
        schoolYear.DrawText();

        ListOfSchoolYearButtons.push_back(schoolYear);

    }
    totalAccumulativeHeight = accumulativeHeight;

    // draw a rectangle to hide scroll up contents

    DrawRectangle(0, 0.05*windowHeight, 0.2*windowWidth, 0.13*windowHeight, RAYWHITE);
    DrawLine(0, 0.18*windowHeight, 0.2*windowWidth, 0.18*windowHeight, BLUE);

    // draw School year text

    Vector2 syTextOrigin = {float(0.01*windowWidth), float(0.06*windowHeight)};
    DrawTextEx(PT_serif_bold, "School Year", syTextOrigin, 0.025*windowWidth, 0.5, DARKBLUE);

    // draw add school year button
    DrawTexturePro(calendar, (Rectangle){0, 0, float(calendar.width), float(calendar.height)}, (Rectangle){float(0.01*windowWidth), float(0.12*windowHeight), float(0.02*windowWidth), float(0.02*windowWidth)}, (Vector2){0, 0}, 0, WHITE);
    Vector2 addTextOrigin = {float(0.035*windowWidth), float(0.12*windowHeight)};
    DrawTextEx(PT_serif_bold, "Pick a school year", addTextOrigin, 0.018*windowWidth, 0.5, DARKBLUE);

    DrawStaticElements();
}