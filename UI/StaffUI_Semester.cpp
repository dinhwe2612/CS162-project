#include "StaffUI_Semester.hpp"

void StaffSemesterUI::Construct(int windowWidth, int windowHeight)
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

    SemesterStartDate.Construct(0.425*windowWidth, 0.46*windowHeight, 0.15*windowWidth, 0.05*windowHeight, 0.43*windowWidth, 0.465*windowHeight, 0.018*windowWidth, 0.5, 10, "");
    SemesterStartDate.SetColorBox(WHITE, WHITE);

    SemesterEndDate.Construct(0.425*windowWidth, 0.56*windowHeight, 0.15*windowWidth, 0.05*windowHeight, 0.43*windowWidth, 0.565*windowHeight, 0.018*windowWidth, 0.5, 10, "");
    SemesterEndDate.SetColorBox(WHITE, WHITE);

    // Course initialisation
    course.Construct(windowWidth, windowHeight);
}

void StaffSemesterUI::Deconstruct()
{
    UnloadTexture(background);
    UnloadTexture(close.image);
    UnloadTexture(addSemester.image);

    UnloadFont(PT_serif_bold);
    course.Deconstruct();
}

void StaffSemesterUI::Draw(int &menuWindow)
{
    DrawBackground();
    if (menuSemester == 0) {//default
        DrawTextEx(PT_serif_bold, (">  " + SchoolYear).c_str(), (Vector2){float(0.25*windowWidth), float(0.01*windowHeight)}, 0.015*windowWidth, 0.5, WHITE);
        close.DrawTexture();
        addSemester.DrawTexture();
        DrawSemesterList();
        DrawCreateSemester();
        if (close.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuWindow = -1;//default
        }
    } else if (menuSemester == 1) {//course
        course.Draw();
        if (course.close.isPRESSED(MOUSE_BUTTON_LEFT) && course.menuCourse == -1) {
            menuSemester = 0;
        }
    }
}

void StaffSemesterUI::DrawBackground()
{
    // background
    Rectangle bsrc = {0, 0, float(background.width), float(background.height)};
    Rectangle bdest = {float(0.12*windowWidth), float(0.17*windowHeight), float(0.76*windowWidth), float(0.71*windowHeight)};
    Vector2 origin = {0, 0};
    DrawTexturePro(background, bsrc, bdest, origin, 0, WHITE);

    // top bar
    Rectangle tdest = {float(0.12*windowWidth), float(0.17*windowHeight), float(0.76*windowWidth), float(0.034*windowHeight)};
    DrawRectangleRec(tdest, (Color){222, 215, 251, 255});

    // draw "Add new Semester" text
    Vector2 textPos = {float(0.34*windowWidth), float(0.24*windowHeight)};
    DrawTextEx(PT_serif_bold, "Add new Semester", textPos, 0.02*windowWidth, 0.5, BLACK);
}

void StaffSemesterUI::DrawCreateSemester()
{
    
    if (addSemester.isPRESSED(MOUSE_BUTTON_LEFT))
        isAddSemester = true;

    if (isAddSemester)
    {
        // draw outer box border
        Rectangle borders = {float(windowWidth/2),float( windowHeight/2), float(0.18*windowWidth), float(0.23*windowWidth)};
        Vector2 bordersOrigin = {float(borders.width/2), float(borders.height/2)};
        DrawRectanglePro(borders, bordersOrigin, 0, LIGHTGRAY);

        // draw outer box
        Rectangle rec = {float(windowWidth/2), float(windowHeight/2), float(0.17*windowWidth), float(0.22*windowWidth)};
        Vector2 recOrigin = {float(rec.width/2), float(rec.height/2)};
        DrawRectanglePro(rec, recOrigin, 0, RAYWHITE);

        // draw create school year button and its function
        Button Create;
        Create.SetText(PT_serif_bold, "Create", 0.48*windowWidth, 0.64*windowHeight, 0.018*windowWidth, 0.5, RAYWHITE);
        Create.SetRectangle(0.425*windowWidth, 0.63*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK, DARKBLUE);
        Create.DrawText();

        if (Create.isPRESSED(MOUSE_BUTTON_LEFT) && listSize <= 2)
        {
            ASemester newSemester;
            newSemester.semester = inputSemester.GetInput();
            newSemester.startDate = SemesterStartDate.GetInput();
            newSemester.endDate = SemesterEndDate.GetInput();
            newSemester.schoolYear = SchoolYear;
            CreateSemester(newSemester, ListOfSemesters, listSize);
            isAddSemester = false;
        }
        else if (listSize >= 3)
        {
            DrawTextEx(PT_serif_regular, "Max number of semester is 3", (Vector2){float(0.425*windowWidth), float(0.608*windowHeight)}, 0.015*windowWidth, 0.5, RED);
        }
        

        // draw enter school year box
        inputSemester.Draw();
        DrawRectangleLines(0.425*windowWidth, 0.36*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK);
        DrawTextEx(PT_serif_bold, "Enter Semester name", (Vector2){float(0.425*windowWidth), float(0.33*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);

        // draw semester start date
        SemesterStartDate.Draw();
        DrawRectangleLines(0.425*windowWidth, 0.46*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK);
        DrawTextEx(PT_serif_bold, "Enter start date", (Vector2){float(0.425*windowWidth), float(0.43*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);
        
        // draw semester end date
        SemesterEndDate.Draw();
        DrawRectangleLines(0.425*windowWidth, 0.56*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK);
        DrawTextEx(PT_serif_bold, "Enter end date", (Vector2){float(0.425*windowWidth), float(0.53*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);

        // draw close button and its function
        addSemesterClose.DrawTexture();

        if (addSemesterClose.isPRESSED(MOUSE_BUTTON_LEFT)) {
            isAddSemester = false;
            inputSemester.currentInput = "";
        }
    }
}

void StaffSemesterUI::DrawSemesterList()
{
    static bool SemesterClicked = false;
    
    for (int i = 0; i < listSize; ++i)
    {
        Button _Semester;
        
        _Semester.SetRectangle(0.31*windowWidth, 0.3*windowHeight + i * 0.18*windowHeight, 0.4*windowWidth, 0.16*windowHeight, LIGHTGRAY, (Color){251, 244, 226, 255});
        _Semester.SetText(PT_serif_bold, ListOfSemesters[i], 0.33*windowWidth, 0.32*windowHeight + i * 0.18*windowHeight, 0.02*windowWidth, 0.5, BLACK);
        
        _Semester.DrawText();
        DrawRectangleLinesEx(_Semester.buttonShape, 0.5, BLACK);

        if (!isAddSemester && _Semester.isPRESSED(MOUSE_BUTTON_LEFT))
        {
            SemesterClicked = true;
            menuSemester = 1;// menuSemester = SEMESTER
            course.schoolYear = SchoolYear;
            course.semester = ListOfSemesters[i];
            viewCourses(SchoolYear, ListOfSemesters[i], course.ListOfCourses, course.listCourseSize);
        }
    }
}




