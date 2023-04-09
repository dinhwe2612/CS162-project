#include "StaffUI_Course.hpp"

Course::Course(int windowWidth, int windowHeight)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    background = LoadTexture("UI/images/background9.png");

    PT_serif_bold = LoadFont("UI/font/PT_Serif/PTSerif-Bold.ttf");
    PT_serif_regular = LoadFont("UI/font/PT_Serif/PTSerif-Regular.ttf");

    back.SetRectangle(0.85*windowWidth, 0.17*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);
    back.SetTexture("UI/images/back.png");

    addCourse.SetRectangle(0.31*windowWidth, 0.24*windowHeight, 0.025*windowWidth, 0.025*windowWidth, LIGHTGRAY, WHITE);
    addCourse.SetTexture("UI/images/add.png");
}

Course::~Course()
{
    UnloadTexture(background);
    UnloadTexture(back.image);
    UnloadTexture(addCourse.image);

    UnloadFont(PT_serif_bold);
    UnloadFont(PT_serif_regular);
}

void Course::Draw(int& menuWindow)
{
    
    DrawBackground();
}

void Course::DrawBackground()
{
    // background
    Rectangle bsrc = {0, 0, background.width, background.height};
    Rectangle bdest = {0.12*windowWidth, 0.17*windowHeight, 0.76*windowWidth, 0.71*windowHeight};
    Vector2 origin = {0, 0};
    DrawTexturePro(background, bsrc, bdest, origin, 0, WHITE);

    // top bar
    Rectangle tdest = {0.12*windowWidth, 0.17*windowHeight, 0.76*windowWidth, 0.034*windowHeight};
    DrawRectangleRec(tdest, (Color){222, 215, 251, 255});

    // draw "Add new courses" text
    Vector2 textPos = {0.34*windowWidth, 0.24*windowHeight};
    DrawTextEx(PT_serif_bold, "Add new course", textPos, 0.02*windowWidth, 0.5, BLACK);
}