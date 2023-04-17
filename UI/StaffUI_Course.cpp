#include "StaffUI_Course.hpp"

void Course::Construct(int windowWidth, int windowHeight)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    background = LoadTexture("UI/images/background9.png");

    PT_serif_bold = LoadFont("UI/font/PT_Serif/PTSerif-Bold.ttf");
    PT_serif_regular = LoadFont("UI/font/PT_Serif/PTSerif-Regular.ttf");

    close.SetRectangle(0.85*windowWidth, 0.17*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);
    close.SetTexture("UI/images/close.png");

    Create.SetText(PT_serif_bold, "Create", 0.48*windowWidth, 0.76*windowHeight, 0.018*windowWidth, 0.5, RAYWHITE);
    Create.SetRectangle(0.35*windowWidth, 0.75*windowHeight, 0.3*windowWidth, 0.06*windowHeight, BLACK, DARKBLUE);

    addCourse.SetRectangle(0.31*windowWidth, 0.24*windowHeight, 0.025*windowWidth, 0.025*windowWidth, LIGHTGRAY, WHITE);
    addCourse.SetTexture("UI/images/add.png");

    addCourseClose.image = close.image;
    addCourseClose.bsrc = (Rectangle){0, 0, addCourse.image.width, addCourse.image.height};
    addCourseClose.origin = (Vector2){0, 0};
    addCourseClose.SetRectangle(0.655*windowWidth, 0.16*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);

    courseName.Construct(0.35*windowWidth, 0.22*windowHeight, 0.3*windowWidth, 0.05*windowHeight, 0.355*windowWidth, 0.225*windowHeight, 0.018*windowWidth, 0.5, 24, "");
    courseName.SetColorBox(WHITE, WHITE);

    courseID.Construct(0.35*windowWidth, 0.31*windowHeight, 0.14*windowWidth, 0.05*windowHeight, 0.355*windowWidth, 0.315*windowHeight, 0.018*windowWidth, 0.5, 10, "");
    courseID.SetColorBox(WHITE, WHITE);

    className.Construct(0.51*windowWidth, 0.31*windowHeight, 0.14*windowWidth, 0.05*windowHeight, 0.515*windowWidth, 0.315*windowHeight, 0.018*windowWidth, 0.5, 10, "");
    className.SetColorBox(WHITE, WHITE);

    teacherName.Construct(0.35*windowWidth, 0.4*windowHeight, 0.3*windowWidth, 0.05*windowHeight, 0.355*windowWidth, 0.405*windowHeight, 0.018*windowWidth, 0.5, 30, "");
    teacherName.SetColorBox(WHITE, WHITE);

    numberOfCredits.Construct(0.35*windowWidth, 0.49*windowHeight, 0.14*windowWidth, 0.05*windowHeight, 0.355*windowWidth, 0.495*windowHeight, 0.018*windowWidth, 0.5, 10, "");
    numberOfCredits.SetColorBox(WHITE, WHITE);

    maxStudents.Construct(0.51*windowWidth, 0.49*windowHeight, 0.14*windowWidth, 0.05*windowHeight, 0.515*windowWidth, 0.495*windowHeight, 0.018*windowWidth, 0.5, 10, "");
    maxStudents.SetColorBox(WHITE, WHITE);
}

void Course::Deconstruct()
{
    UnloadTexture(background);
    UnloadTexture(close.image);
    UnloadTexture(addCourse.image);

    UnloadFont(PT_serif_bold);
    UnloadFont(PT_serif_regular);
}

void Course::Draw()
{
    DrawTextEx(PT_serif_bold, (">  " + schoolYear + "  >  " + semester).c_str(), (Vector2){0.25*windowWidth, 0.01*windowHeight}, 0.015*windowWidth, 0.5, WHITE);
    DrawBackground();
    DrawCourseList();
    DrawCreateCourse();
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

    addCourse.DrawTexture();

    close.DrawTexture();
}

void Course::DrawCourseList()
{
    float static posY = 0;

    static bool courseClicked = false;

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
        course.SetText(PT_serif_bold, ListOfCourses[i].id + " - " + ListOfCourses[i].name, 0.33*windowWidth, 0.32*windowHeight + i * 0.1*windowHeight + posY, 0.02*windowWidth, 0.5, BLACK);
        
        if (course.buttonShape.y >= 0.26*windowHeight && course.buttonShape.y + course.buttonShape.height <= 0.88*windowHeight)
            course.DrawText();

        if (!isAddCourse && course.isPRESSED(MOUSE_BUTTON_LEFT))
        {
            courseClicked = true;
        }

        // if (courseClicked && isAddCourse)
        //     DrawViewClass();
        
        if (close.isPRESSED(MOUSE_BUTTON_LEFT))
            courseClicked = false;

    }
}

void Course::DrawCreateCourse()
{
    
    if (addCourse.isPRESSED(MOUSE_BUTTON_LEFT))
        isAddCourse = true;

    if (isAddCourse)
    {
        // draw outer box border
        Rectangle borders = {windowWidth/2, windowHeight/2, 0.36*windowWidth, 0.39*windowWidth};
        Vector2 bordersOrigin = {borders.width/2, borders.height/2};
        DrawRectanglePro(borders, bordersOrigin, 0, LIGHTGRAY);

        // draw outer box
        Rectangle rec = {windowWidth/2, windowHeight/2, 0.35*windowWidth, 0.38*windowWidth};
        Vector2 recOrigin = {rec.width/2, rec.height/2};
        DrawRectanglePro(rec, recOrigin, 0, RAYWHITE);

        

        // draw create school year button and its function
        Create.DrawText();
        

        // draw course name
        courseName.Draw();
        DrawRectangleLines(0.35*windowWidth, 0.22*windowHeight, 0.3*windowWidth, 0.05*windowHeight, BLACK);
        DrawTextEx(PT_serif_bold, "Enter course name", (Vector2){0.35*windowWidth, 0.19*windowHeight}, 0.015*windowWidth, 0.5, BLACK);

        // draw course id
        courseID.Draw();
        DrawRectangleLines(0.35*windowWidth, 0.31*windowHeight, 0.14*windowWidth, 0.05*windowHeight, BLACK);
        DrawTextEx(PT_serif_bold, "Enter course ID", (Vector2){0.35*windowWidth, 0.28*windowHeight}, 0.015*windowWidth, 0.5, BLACK);
        
        // draw class name
        className.Draw();
        DrawRectangleLines(0.51*windowWidth, 0.31*windowHeight, 0.14*windowWidth, 0.05*windowHeight, BLACK);
        DrawTextEx(PT_serif_bold, "Enter class name", (Vector2){0.51*windowWidth, 0.28*windowHeight}, 0.015*windowWidth, 0.5, BLACK);
        
        // draw teacher name
        teacherName.Draw();
        DrawRectangleLines(0.35*windowWidth, 0.4*windowHeight, 0.3*windowWidth, 0.05*windowHeight, BLACK);
        DrawTextEx(PT_serif_bold, "Enter teacher name", (Vector2){0.35*windowWidth, 0.37*windowHeight}, 0.015*windowWidth, 0.5, BLACK);

        // draw number of credits
        numberOfCredits.Draw();
        DrawRectangleLines(0.35*windowWidth, 0.49*windowHeight, 0.14*windowWidth, 0.05*windowHeight, BLACK);
        DrawTextEx(PT_serif_bold, "Number of credits", (Vector2){0.35*windowWidth, 0.46*windowHeight}, 0.015*windowWidth, 0.5, BLACK);

        // draw max number of students
        maxStudents.Draw();
        DrawRectangleLines(0.51*windowWidth, 0.49*windowHeight, 0.14*windowWidth, 0.05*windowHeight, BLACK);
        DrawTextEx(PT_serif_bold, "Max No. of students", (Vector2){0.51*windowWidth, 0.46*windowHeight}, 0.015*windowWidth, 0.5, BLACK);

        // draw days of week buttons
        std::string dayLabel[10] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
        static bool isDayChosen[10] = {true, false, false, false, false, false, false};
        std::string chosenDay = buttonChosen(0.35*windowWidth, 0.58*windowHeight, 0.37*windowHeight, 0.05*windowHeight, dayLabel, isDayChosen, 7);
        DrawTextEx(PT_serif_bold, "Select date of course", (Vector2){0.35*windowWidth, 0.55*windowHeight}, 0.015*windowWidth, 0.5, BLACK);
        
        // draw session
        std::string sessionLabel[10] = {"S1", "S2", "S3", "S4"};
        static bool isSessionChosen[10] = {true, false, false, false};
        std::string chosenSession = buttonChosen(0.35*windowWidth, 0.67*windowHeight, 0.22*windowHeight, 0.05*windowHeight, sessionLabel, isSessionChosen, 4);
        DrawTextEx(PT_serif_bold, "Select session", (Vector2){0.35*windowWidth, 0.64*windowHeight}, 0.015*windowWidth, 0.5, BLACK);

        // draw close button
        addCourseClose.DrawTexture();

        if (addCourseClose.isPRESSED(MOUSE_BUTTON_LEFT)) {
            isAddCourse = false;
            // inputSemester.currentInput = "";
        }
        if (Create.isPRESSED(MOUSE_BUTTON_LEFT)) {
            ACourse newCourse;
            newCourse.name = courseName.GetInput();
            newCourse.id = courseID.GetInput();
            newCourse.Class = className.GetInput();
            newCourse.teacher = teacherName.GetInput();
            newCourse.credit = stoi(numberOfCredits.GetInput());
            newCourse.maxStudent = stoi(maxStudents.GetInput());
            int tmp = 0;
            for(int i = 0; i < 7; ++i) if (isDayChosen[i]) tmp = i, isDayChosen[i] = false;
            isDayChosen[0] = true;
            newCourse.dayOfWeek = dayLabel[tmp];
            for(int i = 0; i < 4; ++i) if (isSessionChosen[i]) tmp = i, isSessionChosen[i] = false;
            isSessionChosen[0] = true;
            newCourse.session = sessionLabel[tmp];
            AddCourse(schoolYear, semester, newCourse, ListOfCourses, listCourseSize);
            courseName.currentInput = "";
            courseID.currentInput = "";
            className.currentInput = "";
            teacherName.currentInput = "";
            numberOfCredits.currentInput = "";
            maxStudents.currentInput = "";
            isAddCourse = false;
        }
    }
}

std::string Course::buttonChosen(float x, float y, float width, float height, std::string* labels, bool* isButtonPressed, int size)
{
    std::string labelPressed;

    float buttonWidth = width / size;

    for (int i = 0; i < size; ++i)
    {
        float buttonX = x + i* (buttonWidth + 0.005*windowWidth);
        Button choice;
        
        if (!isButtonPressed[i])
            choice.SetRectangle(buttonX, y, buttonWidth, height, WHITE, WHITE);
        else
            choice.SetRectangle(buttonX, y, buttonWidth, height, LIGHTGRAY, LIGHTGRAY);

        if (choice.isPRESSED(MOUSE_BUTTON_LEFT))
        {
            labelPressed = labels[i];

            for (int j = 0; j < size; ++j)
            {
                if (j == i)
                    isButtonPressed[j] = true;
                else
                    isButtonPressed[j] = false;
            }
        }

        choice.SetText(PT_serif_regular, labels[i], buttonX+0.0002*windowWidth, y+0.002*windowHeight, 0.018*windowWidth, 0.01, BLACK);

        choice.DrawText();
        DrawRectangleLines(buttonX, y, buttonWidth, height, BLACK);
    }

    return labelPressed;
}

