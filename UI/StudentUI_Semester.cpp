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
        DrawTextEx(PT_serif_bold, (">  " + SchoolYear).c_str(), (Vector2){float(0.25*windowWidth), float(0.01*windowHeight)}, 0.015*windowWidth, 0.5, WHITE);
        close.DrawTexture();
        DrawSemesterList();
        if (close.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuWindow = -1;//default
        }
    } else if (menuSemester == 1) {//scoreboard

        // if (course.close.isPRESSED(MOUSE_BUTTON_LEFT) && course.menuCourse == -1) {
        //     menuSemester = 0;
        // }
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

    // draw "Choose a semester" text
    Vector2 textPos = {float(0.34*windowWidth), float(0.24*windowHeight)};
    DrawTextEx(PT_serif_bold, "Choose a semester", textPos, 0.02*windowWidth, 0.5, BLACK);

    Rectangle wsrc = {0, 0, float(world.width), float(world.height)};
    Rectangle wdest = {float(0.31*windowWidth), float(0.23*windowHeight), float(0.027*windowWidth), float(0.027*windowWidth)};
    DrawTexturePro(world, wsrc, wdest, (Vector2){0, 0}, 0, WHITE);
}

void StudentSemesterUI::DrawSemesterList()
{
    static bool SemesterClicked = false;
    
    for (int i = 0; i < listSize; ++i)
    {
        Button _Semester;
        
        _Semester.SetRectangle(0.31*windowWidth, 0.3*windowHeight + i * 0.18*windowHeight, 0.4*windowWidth, 0.16*windowHeight, LIGHTGRAY, (Color){251, 244, 226, 255});
        _Semester.SetText(PT_serif_bold, ListOfSemesters[i], 0.33*windowWidth, 0.32*windowHeight + i * 0.18*windowHeight, 0.02*windowWidth, 0.5, BLACK);
        
        _Semester.DrawText();
    }
}




