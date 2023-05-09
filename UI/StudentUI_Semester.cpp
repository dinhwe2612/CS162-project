#include "StudentUI_Semester.hpp"

void StudentSemesterUI::Construct(int windowWidth, int windowHeight)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    background = LoadTexture("UI/images/background9.png");
    world = LoadTexture("UI/images/world.png");

    PT_serif_bold = LoadFont("UI/font/PT_Serif/PTSerif-Bold.ttf");
    PT_serif_regular = LoadFont("UI/font/PT_Serif/PTSerif-Regular.ttf");

    close.SetTexture("UI/images/close.png");
    close.SetRectangle(0.85*windowWidth, 0.17*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);
}

void StudentSemesterUI::Deconstruct()
{
    UnloadTexture(background);
    UnloadTexture(world);
    UnloadTexture(close.image);

    UnloadFont(PT_serif_bold);
}

void StudentSemesterUI::Draw(int &menuWindow)
{
    DrawBackground();
    if (menuSemester == 0) {//default
        DrawTextEx(PT_serif_bold, (">  " + schoolYear).c_str(), (Vector2){float(0.25*windowWidth), float(0.01*windowHeight)}, 0.015*windowWidth, 0.5, WHITE);
        close.DrawTexture();
        DrawSemesterList();
        if (close.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuWindow = -1;//default
        }
    } else if (menuSemester == 1) {//scoreboard
        DrawTextEx(PT_serif_bold, (">  " + schoolYear + "  >  " + semester).c_str(), (Vector2){float(0.25*windowWidth), float(0.01*windowHeight)}, 0.015*windowWidth, 0.5, WHITE);
        DrawCourseList();
        if (close.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuSemester = 0;
        }
    } else if (menuSemester == 2) {
        DrawScoreBoard();
    }
}

void StudentSemesterUI::DrawBackground()
{
    // background
    Rectangle bsrc = {0, 0, float(background.width), float(background.height)};
    Rectangle bdest = {float(0.12*windowWidth), float(0.17*windowHeight), float(0.76*windowWidth), float(0.71*windowHeight)};
    Vector2 origin = {0, 0};
    DrawTexturePro(background, bsrc, bdest, origin, 0, WHITE);

    // top bar
    Rectangle tdest = {float(0.12*windowWidth), float(0.17*windowHeight), float(0.76*windowWidth), float(0.034*windowHeight)};
    DrawRectangleRec(tdest, (Color){222, 215, 251, 255});

    Rectangle wsrc = {0, 0, float(world.width), float(world.height)};
    Rectangle wdest = {float(0.31*windowWidth), float(0.23*windowHeight), float(0.027*windowWidth), float(0.027*windowWidth)};
    DrawTexturePro(world, wsrc, wdest, (Vector2){0, 0}, 0, WHITE);
}

void StudentSemesterUI::DrawSemesterList()
{
    // draw "Choose a semester" text
    Vector2 textPos = {float(0.34*windowWidth), float(0.24*windowHeight)};
    DrawTextEx(PT_serif_bold, "Choose a semester", textPos, 0.02*windowWidth, 0.5, BLACK);

    //
    static bool SemesterClicked = false;
    
    for (int i = 0; i < listSize; ++i)
    {
        Button _Semester;
        
        _Semester.SetRectangle(0.31*windowWidth, 0.3*windowHeight + i * 0.18*windowHeight, 0.4*windowWidth, 0.16*windowHeight, LIGHTGRAY, (Color){251, 244, 226, 255});
        _Semester.SetText(PT_serif_bold, ListOfSemesters[i], 0.33*windowWidth, 0.32*windowHeight + i * 0.18*windowHeight, 0.02*windowWidth, 0.5, BLACK);
        
        _Semester.DrawText();
        DrawRectangleLinesEx(_Semester.buttonShape, 0.5, BLACK);

        if (_Semester.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuSemester = 1;
            semester = ListOfSemesters[i];
            if (!ViewCoursesStudent(schoolYear, semester, studentID, ListOfCourses, ListOfScores, listCourseSize)) cerr << "Error: ViewCoursesStudent" << endl;
        }
    }
}

void StudentSemesterUI::DrawCourseList() {
    
    close.DrawTexture();
    //
    Vector2 textPos = {float(0.34*windowWidth), float(0.24*windowHeight)};
    DrawTextEx(PT_serif_bold, "List of course", textPos, 0.02*windowWidth, 0.5, BLACK);
    //draw button view scoreboard
    Button viewScoreboard;
    viewScoreboard.SetRectangle(0.495*windowWidth, 0.24*windowHeight, 0.135*windowWidth, 0.04*windowHeight, LIGHTGRAY, {255, 20, 194, 80});
    viewScoreboard.SetText(PT_serif_bold, "View Scoreboard", 0.5*windowWidth, 0.24*windowHeight, 0.02*windowWidth, 0.5, BLACK);
    viewScoreboard.DrawText();
    DrawRectangleLinesEx((Rectangle){0.495*windowWidth, 0.24*windowHeight, 0.135*windowWidth, 0.04*windowHeight}, 1, BLACK);
    if (viewScoreboard.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuSemester = 2;
    }

    float static posY = 0;

    // static bool courseClicked = false;

    posY += GetMouseWheelMove() * 30;
    

    //int szList = ListOfSchoolYear.size();
    // replace szList with listCourseSize from here
    if (0.3*windowHeight + (1 + listCourseSize) * 0.1*windowHeight + posY <= 720)
        posY = 720 - (0.3*windowHeight + (1 + listCourseSize) * 0.1*windowHeight);
    if (posY > 0) posY = 0;
    
    for (int i = 0; i < listCourseSize; ++i)
    {
        Button course;

        if (0.3*windowHeight + i * 0.1*windowHeight + posY <= 0.05*windowHeight) continue;
        
        course.SetRectangle(0.31*windowWidth, 0.3*windowHeight + i * 0.1*windowHeight + posY, 0.4*windowWidth, 0.08*windowHeight, LIGHTGRAY, (Color){251, 244, 226, 255});
        course.SetText(PT_serif_bold, ListOfCourses[i].name + " - " + ListOfCourses[i].Class, 0.33*windowWidth, 0.32*windowHeight + i * 0.1*windowHeight + posY, 0.02*windowWidth, 0.5, BLACK);
        
        if (course.buttonShape.y >= 0.26*windowHeight && course.buttonShape.y + course.buttonShape.height <= 0.88*windowHeight)
        {
            course.DrawText();
            DrawRectangleLinesEx(course.buttonShape, 0.5, BLACK);
        }
    }
}

Vector2 Centered(float x, float y, float width, float height, string Text, Font font, float fontSize, float spacing) {
    Vector2 size = MeasureTextEx(font, Text.c_str(), fontSize, spacing);
    return (Vector2){x + (width - size.x) / 2, y + (height - size.y) / 2};
}

string convertFloatToString2(float x) {
    string ans = to_string(x);
    int i, sz = ans.size();
    for(i = 0; i < sz && ans[i] != '.'; ++i);
    int sur = 0;
    while(sz - i > 2) {
        if (sz - i == 3) {
            if (ans.back() >= '5') sur = 1;
        }
        ans.pop_back(), --sz;
    }
    for(int i = sz - 1; i >= 0; --i) {
        if (ans[i] == '.') continue;
        if (sur) {
            if (ans[i] == '9') ans[i] = '0';
            else {
                ++ans[i];
                sur = 0;
            }
        }
    }
    return ans;
}

void StudentSemesterUI::DrawScoreBoard() {
    DrawTextEx(PT_serif_bold, (">  " + schoolYear + "  >  " + semester).c_str(), (Vector2){float(0.25*windowWidth), float(0.01*windowHeight)}, 0.015*windowWidth, 0.5, WHITE);
    Rectangle box = {float(0), float(0.053*windowHeight), float(windowWidth), float(windowHeight)};
    DrawRectangleRec(box, RAYWHITE);
    DrawRectangleLinesEx((Rectangle){float(box.x - 2), float(box.y - 2), float(box.width + 4), float(box.height + 4)}, 1, BLACK);

    // draw back button
    Button BackScoreBoard;
    BackScoreBoard.SetRectangle(float(0), float(0.052*windowHeight), float(0.05*windowWidth), float(0.04*windowHeight), LIGHTGRAY, RAYWHITE);
    BackScoreBoard.SetText(PT_serif_bold, "Back", float(0.005*windowWidth), float(0.053*windowHeight), 0.02*windowWidth, 0.5, BLACK);
    BackScoreBoard.DrawText();
    if (BackScoreBoard.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuSemester = 1;
    }

    int dx = 0.03*windowWidth, dy = 0.1*windowHeight;
    // draw table
    DrawLine(float(0.03*windowWidth + dx), float(0.1*windowHeight + dy), float(0.9*windowWidth + dx), float(0.1*windowHeight + dy), BLACK);
    DrawLine(float(0.03*windowWidth + dx), float(0.14*windowHeight + dy), float(0.9*windowWidth + dx), float(0.14*windowHeight + dy), BLACK);
    // draw No., course id, course name, credit, other, midterm, final, total
    DrawTextEx(PT_serif_bold, "No.", Centered(0.03*windowWidth + dx, 0.1*windowHeight + dy, 0.05*windowWidth, 0.04*windowHeight, "No.", PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
    DrawTextEx(PT_serif_bold, "Course ID", Centered(0.08*windowWidth + dx, 0.1*windowHeight + dy, 0.13*windowWidth, 0.04*windowHeight, "Course ID", PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
    DrawTextEx(PT_serif_bold, "Course name", Centered(0.21*windowWidth + dx, 0.1*windowHeight + dy, 0.29*windowWidth, 0.04*windowHeight, "Course name", PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
    DrawTextEx(PT_serif_bold, "Credit", Centered(0.5*windowWidth + dx, 0.1*windowHeight + dy, 0.08*windowWidth, 0.04*windowHeight, "Credit", PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
    DrawTextEx(PT_serif_bold, "Other", Centered(0.58*windowWidth + dx, 0.1*windowHeight + dy, 0.08*windowWidth, 0.04*windowHeight, "Other", PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
    DrawTextEx(PT_serif_bold, "Midterm", Centered(0.66*windowWidth + dx, 0.1*windowHeight + dy, 0.08*windowWidth, 0.04*windowHeight, "Midterm", PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
    DrawTextEx(PT_serif_bold, "Final", Centered(0.74*windowWidth + dx, 0.1*windowHeight + dy, 0.08*windowWidth, 0.04*windowHeight, "Final", PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
    DrawTextEx(PT_serif_bold, "Total", Centered(0.82*windowWidth + dx, 0.1*windowHeight + dy, 0.08*windowWidth, 0.04*windowHeight, "Total", PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
    // draw line between each column
    DrawLine(float(0.03*windowWidth + dx), float(0.1*windowHeight + dy), float(0.03*windowWidth + dx), float(0.14*windowHeight + 0.05*windowHeight*listCourseSize + dy), BLACK);
    DrawLine(float(0.08*windowWidth + dx), float(0.1*windowHeight + dy), float(0.08*windowWidth + dx), float(0.14*windowHeight + 0.05*windowHeight*listCourseSize + dy), BLACK);
    DrawLine(float(0.21*windowWidth + dx), float(0.1*windowHeight + dy), float(0.21*windowWidth + dx), float(0.14*windowHeight + 0.05*windowHeight*listCourseSize + dy), BLACK);
    DrawLine(float(0.5*windowWidth + dx), float(0.1*windowHeight + dy), float(0.5*windowWidth + dx), float(0.14*windowHeight + 0.05*windowHeight*listCourseSize + dy), BLACK);
    DrawLine(float(0.58*windowWidth + dx), float(0.1*windowHeight + dy), float(0.58*windowWidth + dx), float(0.14*windowHeight + 0.05*windowHeight*listCourseSize + dy), BLACK);
    DrawLine(float(0.66*windowWidth + dx), float(0.1*windowHeight + dy), float(0.66*windowWidth + dx), float(0.14*windowHeight + 0.05*windowHeight*listCourseSize + dy), BLACK);
    DrawLine(float(0.74*windowWidth + dx), float(0.1*windowHeight + dy), float(0.74*windowWidth + dx), float(0.14*windowHeight + 0.05*windowHeight*listCourseSize + dy), BLACK);
    DrawLine(float(0.82*windowWidth + dx), float(0.1*windowHeight + dy), float(0.82*windowWidth + dx), float(0.14*windowHeight + 0.05*windowHeight*listCourseSize + dy), BLACK);
    DrawLine(float(0.9*windowWidth + dx), float(0.1*windowHeight + dy), float(0.9*windowWidth + dx), float(0.14*windowHeight + 0.05*windowHeight*listCourseSize + dy), BLACK);
    // draw each course
    for(int i = 0; i < listCourseSize; ++i) {
        // draw line between each row
        DrawLine(float(0.03*windowWidth + dx), float(0.14*windowHeight + 0.05*windowHeight*(i+1) + dy), float(0.9*windowWidth + dx), float(0.14*windowHeight + 0.05*windowHeight*(i+1) + dy), BLACK);
        // draw text of each column 
        DrawTextEx(PT_serif_regular, to_string(i+1).c_str(), Centered(0.03*windowWidth + dx, 0.14*windowHeight + 0.05*windowHeight*i + dy, 0.05*windowWidth, 0.05*windowHeight, to_string(i+1), PT_serif_regular, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
        DrawTextEx(PT_serif_regular, ListOfCourses[i].id.c_str(), Centered(0.08*windowWidth + dx, 0.14*windowHeight + 0.05*windowHeight*i + dy, 0.13*windowWidth, 0.05*windowHeight, ListOfCourses[i].id, PT_serif_regular, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
        DrawTextEx(PT_serif_regular, ListOfCourses[i].name.c_str(), Centered(0.21*windowWidth + dx, 0.14*windowHeight + 0.05*windowHeight*i + dy, 0.29*windowWidth, 0.05*windowHeight, ListOfCourses[i].name, PT_serif_regular, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
        DrawTextEx(PT_serif_regular, to_string(ListOfCourses[i].credit).c_str(), Centered(0.5*windowWidth + dx, 0.14*windowHeight + 0.05*windowHeight*i + dy, 0.08*windowWidth, 0.05*windowHeight, to_string(ListOfCourses[i].credit), PT_serif_regular, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
        string otherScore = convertFloatToString2(ListOfScores[i].other);
        DrawTextEx(PT_serif_regular, otherScore.c_str(), Centered(0.58*windowWidth + dx, 0.14*windowHeight + 0.05*windowHeight*i + dy, 0.08*windowWidth, 0.05*windowHeight, otherScore, PT_serif_regular, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
        string midtermScore = convertFloatToString2(ListOfScores[i].midterm);
        DrawTextEx(PT_serif_regular, midtermScore.c_str(), Centered(0.66*windowWidth + dx, 0.14*windowHeight + 0.05*windowHeight*i + dy, 0.08*windowWidth, 0.05*windowHeight, midtermScore, PT_serif_regular, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
        string finalScore = convertFloatToString2(ListOfScores[i].finals);
        DrawTextEx(PT_serif_regular, finalScore.c_str(), Centered(0.74*windowWidth + dx, 0.14*windowHeight + 0.05*windowHeight*i + dy, 0.08*windowWidth, 0.05*windowHeight, finalScore, PT_serif_regular, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
        string totalScore = convertFloatToString2(ListOfScores[i].total);
        DrawTextEx(PT_serif_regular, totalScore.c_str(), Centered(0.82*windowWidth + dx, 0.14*windowHeight + 0.05*windowHeight*i + dy, 0.08*windowWidth, 0.05*windowHeight, totalScore, PT_serif_regular, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
    }
}

