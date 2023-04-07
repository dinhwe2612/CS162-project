#include "StaffUI_Semester.hpp"

void Semester::Construct(int windowWidth, int windowHeight)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    background = LoadTexture("UI/images/background9.png");

    PT_serif_bold = LoadFont("UI/font/PT_Serif/PTSerif-Bold.ttf");
    PT_serif_regular = LoadFont("UI/font/PT_Serif/PTSerif-Regular.ttf");

    close.SetTexture("UI/images/close.png");
    close.SetRectangle(0.85*windowWidth, 0.17*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);

    addSemester.SetTexture("UI/images/add.png");
    addSemester.SetRectangle(0.31*windowWidth, 0.24*windowHeight, 0.025*windowWidth, 0.025*windowWidth, LIGHTGRAY, WHITE);

    inputSemester.Construct(0.425*windowWidth, 0.46*windowHeight, 0.15*windowWidth, 0.05*windowHeight, 0.43*windowWidth, 0.47*windowHeight, 0.018*windowWidth, 0.5, 10, "");
    inputSemester.SetColorBox(WHITE, WHITE);

    
}

void Semester::Deconstruct()
{
    UnloadTexture(background);
    UnloadTexture(close.image);
    UnloadTexture(addSemester.image);

    UnloadFont(PT_serif_bold);
}

void Semester::Draw()
{
    DrawBackground();
    close.DrawTexture();
    addSemester.DrawTexture();
    DrawSemesterList();
    DrawCreateSemester();

}

void Semester::DrawBackground()
{
    // background
    Rectangle bsrc = {0, 0, background.width, background.height};
    Rectangle bdest = {0.12*windowWidth, 0.17*windowHeight, 0.76*windowWidth, 0.71*windowHeight};
    Vector2 origin = {0, 0};
    DrawTexturePro(background, bsrc, bdest, origin, 0, WHITE);

    // top bar
    Rectangle tdest = {0.12*windowWidth, 0.17*windowHeight, 0.76*windowWidth, 0.034*windowHeight};
    DrawRectangleRec(tdest, (Color){222, 215, 251, 255});

    // draw "Add new Semester" text
    Vector2 textPos = {0.34*windowWidth, 0.24*windowHeight};
    DrawTextEx(PT_serif_bold, "Add new Semester", textPos, 0.02*windowWidth, 0.5, BLACK);
}

void Semester::DrawCreateSemester()
{
    static bool isAddSemester;
    
    if (addSemester.isPRESSED(MOUSE_BUTTON_LEFT))
        isAddSemester = true;

    if (isAddSemester)
    {
        // draw outer box border
        Rectangle borders = {windowWidth/2, windowHeight/2, 0.19*windowWidth, 0.14*windowWidth};
        Vector2 bordersOrigin = {borders.width/2, borders.height/2};
        DrawRectanglePro(borders, bordersOrigin, 0, LIGHTGRAY);

        // draw outer box
        Rectangle rec = {windowWidth/2, windowHeight/2, 0.18*windowWidth, 0.13*windowWidth};
        Vector2 recOrigin = {rec.width/2, rec.height/2};
        DrawRectanglePro(rec, recOrigin, 0, RAYWHITE);

        // draw create school year button and its function
        Button Create;
        Create.SetText(PT_serif_bold, "Create", 0.48*windowWidth, 0.56*windowHeight, 0.018*windowWidth, 0.5, RAYWHITE);
        Create.SetRectangle(0.425*windowWidth, 0.55*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK, DARKBLUE);
        Create.DrawText();

        if (Create.isPRESSED(MOUSE_BUTTON_LEFT) && listSize <= 2)
        {
            ListOfSemesters[listSize++] = inputSemester.GetInput();
        }
        else if (listSize >= 3)
        {
            DrawTextEx(PT_serif_regular, "Max number of semester is 3", (Vector2){0.425*windowWidth, 0.52*windowHeight}, 0.015*windowWidth, 0.5, RED);
        }
        

        // draw enter school year box
        inputSemester.Draw();
        DrawRectangleLines(0.425*windowWidth, 0.46*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK);

        // draw enter school year text
        Vector2 enterText = {0.425*windowWidth, 0.42*windowHeight};
        DrawTextEx(PT_serif_bold, "Enter Semester name", enterText, 0.015*windowWidth, 0.5, BLACK);

        // draw close button and its function
        Button addSemesterClose;
        addSemesterClose = close;
        addSemesterClose.SetRectangle(0.57*windowWidth, 0.39*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);
        addSemesterClose.DrawTexture();

        if (addSemesterClose.isPRESSED(MOUSE_BUTTON_LEFT)) {
            isAddSemester = false;
            inputSemester.currentInput = "";
        }
    }
}

void Semester::DrawSemesterList()
{
    static bool SemesterClicked;
    
    for (int i = 0; i < listSize; ++i)
    {
        Button _Semester;

        static std::string SemesterDir;
        
        _Semester.SetRectangle(0.31*windowWidth, 0.3*windowHeight + i * 0.18*windowHeight, 0.4*windowWidth, 0.16*windowHeight, LIGHTGRAY, (Color){251, 244, 226, 255});
        _Semester.SetText(PT_serif_bold, ListOfSemesters[i], 0.33*windowWidth, 0.32*windowHeight + i * 0.18*windowHeight, 0.02*windowWidth, 0.5, BLACK);
        
        _Semester.DrawText();

        if (_Semester.isPRESSED(MOUSE_BUTTON_LEFT))
        {
            SemesterDir = ListOfSemesters[i];
            SemesterClicked = true;
        }
        
        DrawTextEx(PT_serif_bold, SemesterDir.c_str(), (Vector2){0.33*windowWidth, 0.01*windowHeight}, 0.015*windowWidth, 0.5, WHITE);
    }
}




