#include "StudentUI.hpp"

void StudentUI::Construct(float windowWidth, float windowHeight)
{
    this-> windowWidth = windowWidth;
    this-> windowHeight = windowHeight;

    background = LoadTexture("UI/images/background5.png");
    calendar = LoadTexture("UI/images/calendar (2).png");
    profile = LoadTexture("UI/images/user.png");
    gender = LoadTexture("UI/images/followers (1).png");
    DOB = LoadTexture("UI/images/calendar-silhouette (1).png");
    socialID = LoadTexture("UI/images/social_id.png");
    Class = LoadTexture("UI/images/mortarboard.png");
    studentID = LoadTexture("UI/images/id-card (1).png");

    PT_serif_regular = LoadFont("UI/font/PT_Serif/PTSerif-Regular.ttf");
    PT_serif_bold = LoadFont("UI/font/PT_Serif/PTSerif-Bold.ttf");

    dropdownButton.SetTexture("UI/images/down-arrow-3.png");
    dropdownButton.SetRectangle(0.97*windowWidth, 0.005*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);

    cornerStripes.SetTexture("UI/images/stripes.png");
    cornerStripes.SetRectangle(0.01*windowWidth, 0.005*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);

    signOut.SetRectangle(0.8*windowWidth, 0.67*windowHeight, 0.18*windowWidth, 0.05*windowHeight, BLACK, DARKBLUE);
    signOut.SetText(PT_serif_bold, "Sign out", 0.865*windowWidth, 0.68*windowHeight, 0.015*windowWidth, 0.5, WHITE);

    ChangePassWord.SetRectangle(0.8*windowWidth, 0.6*windowHeight, 0.18*windowWidth, 0.05*windowHeight, BLACK, DARKBLUE);
    ChangePassWord.SetText(PT_serif_bold, "Change password", 0.842*windowWidth, 0.61*windowHeight, 0.015*windowWidth, 0.5, WHITE);

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
    _Semester.Construct(windowWidth, windowHeight);
}

void StudentUI::Deconstruct()
{
    UnloadTexture(background);
    UnloadTexture(dropdownButton.image);
    UnloadTexture(cornerStripes.image);
    UnloadTexture(profile);
    UnloadTexture(gender);
    UnloadTexture(DOB);
    UnloadTexture(socialID);
    UnloadTexture(Class);
    UnloadTexture(studentID);

    UnloadFont(PT_serif_bold);
    UnloadFont(PT_serif_regular);

    _Semester.Deconstruct();
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

void StudentUI::Draw(int& menuLogin)
{
    switch (menuStudent)
    {
    default:
        DrawBackground();
        DrawStaticElements();
        DrawCurrentWindow();
        DrawDropDownAccount(menuLogin);//for signout button
        DrawDropDownSchoolYear();
        break;
    case CHANGE_PASSWORD:
        DrawChangePassword();
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
     Rectangle box = {float(0.785*windowWidth), float(0.05*windowHeight), float(0.21*windowWidth), float(0.7*windowHeight)};

    // check if down arrow is clicked

    static bool IS_DROPDOWN_CLICKED = false;
    
    if (dropdownButton.isPRESSED(MOUSE_BUTTON_LEFT))
        IS_DROPDOWN_CLICKED ^= 1;
    else if (!CheckCollisionPointRec(GetMousePosition(), (Rectangle){float(0.79*windowWidth), 0, float(0.21*windowWidth), float(0.75*windowHeight)}))
        IS_DROPDOWN_CLICKED = false;

    // draw sign out and drop down

    if (IS_DROPDOWN_CLICKED)
    {
        // draw drop down box
        DrawRectangleRounded(box, 0.1, 0, WHITE);
        DrawRectangleRoundedLines(box, 0.1, 0, 0.5, BLACK);

        Rectangle psrc = {0, 0, float(profile.width), float(profile.height)};
        Rectangle pdst = {float(0.855*windowWidth), float(0.07*windowHeight), float(0.07*windowWidth), float(0.07*windowWidth)};
        DrawTexturePro(profile, psrc, pdst, (Vector2){0, 0}, 0, WHITE);

        // draw name in the middle of box
        Vector2 nameSize =  MeasureTextEx(PT_serif_bold, curStu.firstName.c_str(), 0.016*windowWidth, 0.5);
        float nameXCoordinate = (box.width - nameSize.x) / 2 + box.x;

        DrawTextEx(PT_serif_bold, curStu.firstName.c_str(), (Vector2){nameXCoordinate, float(0.07*windowWidth + 0.08*windowHeight)}, 0.016*windowWidth, 0.5, BLACK);
        DrawLineV((Vector2){box.x, float(0.24*windowHeight)}, (Vector2){box.x + box.width, float(0.24*windowHeight)}, LIGHTGRAY);

        DrawTexturePro(gender, (Rectangle){0, 0, float(gender.width), float(gender.height)}, (Rectangle){float(0.8*windowWidth), float(0.27*windowHeight), float(0.024*windowWidth), float(0.024*windowWidth)}, (Vector2){0, 0}, 0, WHITE);
        DrawTextEx(PT_serif_bold, "Gender", (Vector2){float(0.84*windowWidth), float(0.27*windowHeight)}, 0.013*windowWidth, 0.5, GRAY);
        string Gender;
        if (curStu.gender == 0) Gender = "Male";
        else if (curStu.gender == 1) Gender = "Female";
        else Gender = "Other";
        DrawTextEx(PT_serif_bold, Gender.c_str(), (Vector2){float(0.84*windowWidth), float(0.29*windowHeight)}, 0.013*windowWidth, 0.5, BLACK);

        DrawTexturePro(DOB, (Rectangle){0, 0, float(DOB.width), float(DOB.height)}, (Rectangle){float(0.8*windowWidth), float(0.33*windowHeight), float(0.024*windowWidth), float(0.024*windowWidth)}, (Vector2){0, 0}, 0, WHITE);
        DrawTextEx(PT_serif_bold, "Date of birth", (Vector2){float(0.84*windowWidth), float(0.33*windowHeight)}, 0.013*windowWidth, 0.5, GRAY);
        DrawTextEx(PT_serif_bold, curStu.DOB.c_str(), (Vector2){float(0.84*windowWidth), float(0.35*windowHeight)}, 0.013*windowWidth, 0.5, BLACK);
        DrawTexturePro(socialID, (Rectangle){0, 0, float(socialID.width), float(socialID.height)}, (Rectangle){float(0.8*windowWidth), float(0.39*windowHeight), float(0.024*windowWidth), float(0.024*windowWidth)}, (Vector2){0, 0}, 0, WHITE);
        DrawTextEx(PT_serif_bold, "Social ID", (Vector2){float(0.84*windowWidth), float(0.39*windowHeight)}, 0.013*windowWidth, 0.5, GRAY);
        DrawTextEx(PT_serif_bold, curStu.socialID.c_str(), (Vector2){float(0.84*windowWidth), float(0.41*windowHeight)}, 0.013*windowWidth, 0.5, BLACK);

        DrawTexturePro(Class, (Rectangle){0, 0, float(Class.width), float(Class.height)}, (Rectangle){float(0.8*windowWidth), float(0.45*windowHeight), float(0.024*windowWidth), float(0.024*windowWidth)}, (Vector2){0, 0}, 0, WHITE);
        DrawTextEx(PT_serif_bold, "Class", (Vector2){float(0.84*windowWidth), float(0.45*windowHeight)}, 0.013*windowWidth, 0.5, GRAY);
        DrawTextEx(PT_serif_bold, curStu.Class.c_str(), (Vector2){float(0.84*windowWidth), float(0.47*windowHeight)}, 0.013*windowWidth, 0.5, BLACK);

        DrawTexturePro(studentID, (Rectangle){0, 0, float(studentID.width), float(studentID.height)}, (Rectangle){float(0.797*windowWidth), float(0.5*windowHeight), float(0.032*windowWidth), float(0.034*windowWidth)}, (Vector2){0, 0}, 0, WHITE);
        DrawTextEx(PT_serif_bold, "Student ID", (Vector2){float(0.84*windowWidth), float(0.51*windowHeight)}, 0.013*windowWidth, 0.5, GRAY);
        DrawTextEx(PT_serif_bold, curStu.studentID.c_str(), (Vector2){float(0.84*windowWidth), float(0.53*windowHeight)}, 0.013*windowWidth, 0.5, BLACK);
        
        DrawLineV((Vector2){box.x, float(0.58*windowHeight)}, (Vector2){box.x + box.width, float(0.58*windowHeight)}, LIGHTGRAY);

        signOut.DrawText();
        DrawRectangleLinesEx(signOut.buttonShape, 0.5, BLACK);

        ChangePassWord.DrawText();
        DrawRectangleLinesEx(ChangePassWord.buttonShape, 0.5, BLACK);

        if (signOut.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuStudent = DEFAULT;
            menuLogin = DEFAULT;
            menuWindow = DEFAULT;
        }
        if (ChangePassWord.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuStudent = CHANGE_PASSWORD;
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
            ViewSchoolYearStudent(curStu, ListOfSchoolYear, ListSize);
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
        // if (0.18*windowHeight + i * 0.1*windowHeight + posY + accumulativeHeight <= 0.05*windowHeight) continue;

        Button schoolYear;
        schoolYear.SetRectangle(0, 0.18*windowHeight + i * 0.1*windowHeight + posY + accumulativeHeight, 0.2*windowWidth, 0.08*windowHeight, LIGHTGRAY, RAYWHITE);
        // if ()
        //     BUTTON_SchoolYear_isCLICKED[i] ^= 1;

        if (GetMouseY() >= 0.18*windowHeight && schoolYear.isPRESSED(MOUSE_BUTTON_LEFT)) {
            schoolYear.SetText(PT_serif_bold, ">   " + ListOfSchoolYear[i], 0.01*windowWidth, 0.2*windowHeight + i * 0.1*windowHeight + posY + accumulativeHeight, 0.02*windowWidth, 0.5, DARKBLUE);

            menuWindow = SEMESTER;
            _Semester.menuSemester = 0;
            _Semester.schoolYear = ListOfSchoolYear[i]; 
            viewSemester(_Semester.schoolYear, _Semester.ListOfSemesters, _Semester.listSize);
            _Semester.schoolYear = ListOfSchoolYear[i];
            _Semester.studentID = curStu.studentID;
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
    DrawLineEx((Vector2){float(0.2*windowWidth), float(0.05*windowHeight)}, (Vector2){float(0.2*windowWidth), float(windowHeight)}, 1, BLUE);
}