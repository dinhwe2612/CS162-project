#include "StaffUI_Semester.hpp"

void SemesterUI::Construct(int windowWidth, int windowHeight)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    background = LoadTexture("UI/images/background9.png");

    PT_serif_bold = LoadFont("UI/font/PT_Serif/PTSerif-Bold.ttf");
    PT_serif_regular = LoadFont("UI/font/PT_Serif/PTSerif-Regular.ttf");

    close.SetTexture("UI/images/close.png");
    close.SetRectangle(0.85*windowWidth, 0.17*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);

    addSemesterClose = close;
    addSemesterClose.SetRectangle(0.565*windowWidth, 0.30*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);

    addSemester.SetTexture("UI/images/add.png");
    addSemester.SetRectangle(0.31*windowWidth, 0.24*windowHeight, 0.025*windowWidth, 0.025*windowWidth, LIGHTGRAY, WHITE);

    inputSemester.Construct(0.425*windowWidth, 0.36*windowHeight, 0.15*windowWidth, 0.05*windowHeight, 0.43*windowWidth, 0.365*windowHeight, 0.018*windowWidth, 0.5, 10, "");
    inputSemester.SetColorBox(WHITE, WHITE);

    SemesterStartDate.Construct(0.425*windowWidth, 0.46*windowHeight, 0.15*windowWidth, 0.05*windowHeight, 0.43*windowWidth, 0.465*windowHeight, 0.018*windowWidth, 0.5, 8, "");
    SemesterStartDate.SetColorBox(WHITE, WHITE);

    SemesterEndDate.Construct(0.425*windowWidth, 0.56*windowHeight, 0.15*windowWidth, 0.05*windowHeight, 0.43*windowWidth, 0.565*windowHeight, 0.018*windowWidth, 0.5, 8, "");
    SemesterEndDate.SetColorBox(WHITE, WHITE);
}

void SemesterUI::Deconstruct()
{
    UnloadTexture(background);
    UnloadTexture(close.image);
    UnloadTexture(addSemester.image);

    UnloadFont(PT_serif_bold);
}

void SemesterUI::Draw()
{
    DrawBackground();
    close.DrawTexture();
    addSemester.DrawTexture();
    DrawSemesterList();
    DrawCreateSemester();

}

void SemesterUI::DrawBackground()
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

void SemesterUI::DrawCreateSemester()
{
    static bool isAddSemester;
    
    if (addSemester.isPRESSED(MOUSE_BUTTON_LEFT))
        isAddSemester = true;

    if (isAddSemester)
    {
        // draw outer box border
        Rectangle borders = {windowWidth/2, windowHeight/2, 0.18*windowWidth, 0.23*windowWidth};
        Vector2 bordersOrigin = {borders.width/2, borders.height/2};
        DrawRectanglePro(borders, bordersOrigin, 0, LIGHTGRAY);

        // draw outer box
        Rectangle rec = {windowWidth/2, windowHeight/2, 0.17*windowWidth, 0.22*windowWidth};
        Vector2 recOrigin = {rec.width/2, rec.height/2};
        DrawRectanglePro(rec, recOrigin, 0, RAYWHITE);

        // draw create school year button and its function
        Button Create;
        Create.SetText(PT_serif_bold, "Create", 0.48*windowWidth, 0.64*windowHeight, 0.018*windowWidth, 0.5, RAYWHITE);
        Create.SetRectangle(0.425*windowWidth, 0.63*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK, DARKBLUE);
        Create.DrawText();

        if (Create.isPRESSED(MOUSE_BUTTON_LEFT) && listSize <= 2)
        {
            ListOfSemesters[listSize++] = inputSemester.GetInput();
        }
        else if (listSize >= 3)
        {
            DrawTextEx(PT_serif_regular, "Max number of semester is 3", (Vector2){0.425*windowWidth, 0.608*windowHeight}, 0.015*windowWidth, 0.5, RED);
        }
        

        // draw enter school year box
        inputSemester.Draw();
        DrawRectangleLines(0.425*windowWidth, 0.36*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK);
        DrawTextEx(PT_serif_bold, "Enter Semester name", (Vector2){0.425*windowWidth, 0.33*windowHeight}, 0.015*windowWidth, 0.5, BLACK);

        // draw semester start date
        SemesterStartDate.Draw();
        DrawRectangleLines(0.425*windowWidth, 0.46*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK);
        DrawTextEx(PT_serif_bold, "Enter start date", (Vector2){0.425*windowWidth, 0.43*windowHeight}, 0.015*windowWidth, 0.5, BLACK);
        
        // draw semester end date
        SemesterEndDate.Draw();
        DrawRectangleLines(0.425*windowWidth, 0.56*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK);
        DrawTextEx(PT_serif_bold, "Enter end date", (Vector2){0.425*windowWidth, 0.53*windowHeight}, 0.015*windowWidth, 0.5, BLACK);

        // draw close button and its function
        addSemesterClose.DrawTexture();

        if (addSemesterClose.isPRESSED(MOUSE_BUTTON_LEFT)) {
            isAddSemester = false;
            inputSemester.currentInput = "";
        }
    }
}

void SemesterUI::DrawSemesterList()
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
            SemesterDir = "  >  " + ListOfSemesters[i];
            SemesterClicked = true;
        }
        
        DrawTextEx(PT_serif_bold, SemesterDir.c_str(), (Vector2){0.33*windowWidth, 0.01*windowHeight}, 0.015*windowWidth, 0.5, WHITE);
    }
}




