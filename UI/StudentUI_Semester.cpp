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
            viewCourses(schoolYear, semester, ListOfCourses, listCourseSize);
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
}

