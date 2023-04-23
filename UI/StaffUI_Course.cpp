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

    Create.SetText(PT_serif_bold, "Done", 0.48*windowWidth, 0.76*windowHeight, 0.018*windowWidth, 0.5, RAYWHITE);
    Create.SetRectangle(0.35*windowWidth, 0.75*windowHeight, 0.3*windowWidth, 0.06*windowHeight, BLACK, DARKBLUE);

    addCourse.SetRectangle(0.31*windowWidth, 0.24*windowHeight, 0.025*windowWidth, 0.025*windowWidth, LIGHTGRAY, WHITE);
    addCourse.SetTexture("UI/images/add.png");

    viewGPA.SetRectangle(0.52*windowWidth, 0.24*windowHeight, 0.025*windowWidth, 0.025*windowWidth, LIGHTGRAY, WHITE);
    viewGPA.SetTexture("UI/images/statistic.png");

    del.SetRectangle(0.79*windowWidth, 0.17*windowHeight, 0.09*windowWidth, 0.05*windowHeight, LIGHTGRAY, RAYWHITE);
    del.SetText(PT_serif_bold, "Delete course", 0.8*windowWidth, 0.18*windowHeight, 0.015*windowWidth, 0.5, RED);

    back.SetRectangle(0.12*windowWidth, 0.17*windowHeight, 0.06*windowWidth, 0.05*windowHeight, LIGHTGRAY, RAYWHITE);
    back.SetText(PT_serif_bold, "Back", 0.135*windowWidth, 0.18*windowHeight, 0.015*windowWidth, 0.5, BLACK);

    add.SetRectangle(0.52*windowWidth, 0.17*windowHeight, 0.09*windowWidth, 0.05*windowHeight, LIGHTGRAY, RAYWHITE);
    add.SetText(PT_serif_bold, "Add Student", 0.53*windowWidth, 0.18*windowHeight, 0.015*windowWidth, 0.5, BLACK);

    studentConfig.SetRectangle(0.61*windowWidth, 0.17*windowHeight, 0.09*windowWidth, 0.05*windowHeight, LIGHTGRAY, RAYWHITE);
    studentConfig.SetText(PT_serif_bold, "Update student", 0.613*windowWidth, 0.18*windowHeight, 0.015*windowWidth, 0.5, BLACK);

    drop.SetRectangle(0.34*windowWidth, 0.17*windowHeight, 0.09*windowWidth, 0.05*windowHeight, LIGHTGRAY, RAYWHITE);
    drop.SetText(PT_serif_bold, "Import file", 0.355*windowWidth, 0.18*windowHeight, 0.015*windowWidth, 0.5, BLACK);

    info.SetRectangle(0.25*windowWidth, 0.17*windowHeight, 0.09*windowWidth, 0.05*windowHeight, LIGHTGRAY, RAYWHITE);
    info.SetText(PT_serif_bold, "Course info", 0.263*windowWidth, 0.18*windowHeight, 0.015*windowWidth, 0.5, BLACK);

    exportStudent.SetRectangle(0.43*windowWidth, 0.17*windowHeight, 0.09*windowWidth, 0.05*windowHeight, LIGHTGRAY, RAYWHITE);
    exportStudent.SetText(PT_serif_bold, "Export file", 0.447*windowWidth, 0.18*windowHeight, 0.015*windowWidth, 0.5, BLACK);
    
    delStudent.SetRectangle(0.7*windowWidth, 0.17*windowHeight, 0.09*windowWidth, 0.05*windowHeight, LIGHTGRAY, RAYWHITE);
    delStudent.SetText(PT_serif_bold, "Delete student", 0.701*windowWidth + 6, 0.18*windowHeight, 0.015*windowWidth, 0.5, BLACK);

    addCourseClose.image = close.image;
    addCourseClose.bsrc = (Rectangle){0, 0, float(addCourse.image.width), float(addCourse.image.height)};
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
    maxStudents.currentInput = "50";

    enterClass.Construct(0.425*windowWidth, 0.45*windowHeight, 0.15*windowWidth, 0.05*windowHeight, 0.43*windowWidth, 0.46*windowHeight, 0.018*windowWidth, 0.5, 10, "");
    enterClass.SetColorBox(WHITE, WHITE);
}

void Course::Deconstruct()
{
    UnloadTexture(background);
    UnloadTexture(close.image);
    UnloadTexture(addCourse.image);
    UnloadTexture(viewGPA.image);

    UnloadFont(PT_serif_bold);
    UnloadFont(PT_serif_regular);
}

void Course::Draw()
{
    DrawTextEx(PT_serif_bold, (">  " + schoolYear + "  >  " + semester).c_str(), (Vector2){float(0.25*windowWidth), float(0.01*windowHeight)}, 0.015*windowWidth, 0.5, WHITE);
    DrawBackground();
    if (menuCourse == CREATECOURSE) {
        DrawCreateCourse(); 
    } else if (menuCourse == VIEWCOURSE) {
        DrawViewCourse();
    } else if (menuCourse == VIEWGPA) {
        ChooseViewClass();
    } else if (menuCourse == MODIFYCOURSE) {
        DrawViewCourse();
        DrawModifyCourse();
    } else if (menuCourse == ADDSTUDENT) {
        DrawViewCourse();
        DrawAddStudent();
    } else if (menuCourse == IMPORTSTUDENTLIST) {
        DrawImportStudentList();
    } else if (menuCourse == EXPORTSTUDENTLIST) {
        DrawViewCourse();
        DrawExportStudentList();
    } else if (menuCourse == DELETESTUDENT) {
        DrawViewCourse();
        DrawDeleteStudent();
    } else if (menuCourse == DELETECOURSE) {
        DrawViewCourse();
        DrawDeleteCourse();
    } else {
        DrawCourseList();
    }
}

void Course::DrawBackground()
{
    // background
    Rectangle bsrc = {0, 0, float(background.width), float(background.height)};
    Rectangle bdest = {float(0.12*windowWidth), float(0.17*windowHeight), float(0.76*windowWidth), float(0.71*windowHeight)};
    Vector2 origin = {0, 0};
    DrawTexturePro(background, bsrc, bdest, origin, 0, WHITE);

    // top bar
    Rectangle tdest = {float(0.12*windowWidth), float(0.17*windowHeight), float(0.76*windowWidth), float(0.034*windowHeight)};
    DrawRectangleRec(tdest, (Color){222, 215, 251, 255});

    // draw "Add new courses" text
    DrawTextEx(PT_serif_bold, "Add new course", (Vector2){float(0.34*windowWidth),float(0.24*windowHeight)}, 0.02*windowWidth, 0.5, BLACK);
    addCourse.DrawTexture();

    // draw "View semester result"
    DrawTextEx(PT_serif_bold, "View semester result", (Vector2){float(0.55*windowWidth), float(0.24*windowHeight)}, 0.02*windowWidth, 0.5, BLACK);
    viewGPA.DrawTexture();
    
    close.DrawTexture();
}

void Course::DrawCourseList()
{
    if (addCourse.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuCourse = CREATECOURSE;
    }

    if (viewGPA.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuCourse = VIEWGPA;
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
            course.DrawText();

        if (course.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuCourse = VIEWCOURSE;
            curCourse = ListOfCourses[i];
            indexCourse = i;
            viewStudentInCourse(schoolYear, semester, curCourse, ListOfStudents, listStudentSize);
        }
    }
}

void Course::DrawCreateCourse()
{
    // draw outer box border
    Rectangle borders = {float(windowWidth/2), float(windowHeight/2), float(0.36*windowWidth), float(0.39*windowWidth)};
    Vector2 bordersOrigin = {float(borders.width/2), float(borders.height/2)};
    DrawRectanglePro(borders, bordersOrigin, 0, LIGHTGRAY);

    // draw outer box
    Rectangle rec = {float(windowWidth/2), float(windowHeight/2), float(0.35*windowWidth), float(0.38*windowWidth)};
    Vector2 recOrigin = {float(rec.width/2), float(rec.height/2)};
    DrawRectanglePro(rec, recOrigin, 0, RAYWHITE);

    // draw create school year button and its function
    Create.DrawText();

    // draw course name
    courseName.Draw();
    DrawRectangleLines(0.35*windowWidth, 0.22*windowHeight, 0.3*windowWidth, 0.05*windowHeight, BLACK);
    DrawTextEx(PT_serif_bold, "Enter course name", (Vector2){float(0.35*windowWidth), float(0.19*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);

    // draw course id
    courseID.Draw();
    DrawRectangleLines(0.35*windowWidth, 0.31*windowHeight, 0.14*windowWidth, 0.05*windowHeight, BLACK);
    DrawTextEx(PT_serif_bold, "Enter course ID", (Vector2){float(0.35*windowWidth), float(0.28*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);
    
    // draw class name
    className.Draw();
    DrawRectangleLines(0.51*windowWidth, 0.31*windowHeight, 0.14*windowWidth, 0.05*windowHeight, BLACK);
    DrawTextEx(PT_serif_bold, "Enter class name", (Vector2){float(0.51*windowWidth), float(0.28*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);
    
    // draw teacher name
    teacherName.Draw();
    DrawRectangleLines(0.35*windowWidth, 0.4*windowHeight, 0.3*windowWidth, 0.05*windowHeight, BLACK);
    DrawTextEx(PT_serif_bold, "Enter teacher name", (Vector2){float(0.35*windowWidth), float(0.37*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);

    // draw number of credits
    numberOfCredits.Draw();
    DrawRectangleLines(0.35*windowWidth, 0.49*windowHeight, 0.14*windowWidth, 0.05*windowHeight, BLACK);
    DrawTextEx(PT_serif_bold, "Number of credits", (Vector2){float(0.35*windowWidth), float(0.46*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);

    // draw max number of students
    maxStudents.Draw();
    DrawRectangleLines(0.51*windowWidth, 0.49*windowHeight, 0.14*windowWidth, 0.05*windowHeight, BLACK);
    DrawTextEx(PT_serif_bold, "Max No. of students", (Vector2){float(0.51*windowWidth), float(0.46*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);

    // draw days of week buttons
    std::string chosenDay = buttonChosen(0.35*windowWidth, 0.58*windowHeight, 0.37*windowHeight, 0.05*windowHeight, dayLabel, isDayChosen, 7);
    DrawTextEx(PT_serif_bold, "Select date of course", (Vector2){float(0.35*windowWidth), float(0.55*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);
    
    // draw session
    std::string chosenSession = buttonChosen(0.35*windowWidth, 0.67*windowHeight, 0.22*windowHeight, 0.05*windowHeight, sessionLabel, isSessionChosen, 4);
    DrawTextEx(PT_serif_bold, "Select session", (Vector2){float(0.35*windowWidth), float(0.64*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);

    // draw close button
    addCourseClose.DrawTexture();

    if (addCourseClose.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuCourse = -1;
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
        maxStudents.currentInput = "50";
        menuCourse = -1;
    }
}

void Course::DrawModifyCourse() {
    
    del.DrawText();
    back.DrawText();
    add.DrawText();
    drop.DrawText();
    info.DrawText();
    delStudent.DrawText();
    exportStudent.DrawText();
    studentConfig.DrawText();

    // draw outer box border
    Rectangle borders = {float(windowWidth/2), float(windowHeight/2), float(0.36*windowWidth), float(0.39*windowWidth)};
    Vector2 bordersOrigin = {float(borders.width/2), float(borders.height/2)};
    DrawRectanglePro(borders, bordersOrigin, 0, LIGHTGRAY);

    // draw outer box
    Rectangle rec = {float(windowWidth/2), float(windowHeight/2), float(0.35*windowWidth), float(0.38*windowWidth)};
    Vector2 recOrigin = {float(rec.width/2), float(rec.height/2)};
    DrawRectanglePro(rec, recOrigin, 0, RAYWHITE);

    // draw create school year button and its function
    Create.DrawText();

    // draw course name
    courseName.Draw();
    DrawRectangleLines(0.35*windowWidth, 0.22*windowHeight, 0.3*windowWidth, 0.05*windowHeight, BLACK);
    DrawTextEx(PT_serif_bold, "Enter course name", (Vector2){float(0.35*windowWidth), float(0.19*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);

    // draw course id
    DrawTextEx(PT_serif_bold, courseID.GetInput().c_str(), {0.355*windowWidth, 0.315*windowHeight}, 0.018*windowWidth, 0.5, BLACK);
    DrawRectangleLines(0.35*windowWidth, 0.31*windowHeight, 0.14*windowWidth, 0.05*windowHeight, BLACK);
    DrawTextEx(PT_serif_bold, "Enter course ID", (Vector2){float(0.35*windowWidth), float(0.28*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);
    
    // draw class name
    DrawTextEx(PT_serif_bold, className.GetInput().c_str(), {0.515*windowWidth, 0.315*windowHeight}, 0.018*windowWidth, 0.5, BLACK);
    DrawRectangleLines(0.51*windowWidth, 0.31*windowHeight, 0.14*windowWidth, 0.05*windowHeight, BLACK);
    DrawTextEx(PT_serif_bold, "Enter class name", (Vector2){float(0.51*windowWidth), float(0.28*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);
    
    // draw teacher name
    teacherName.Draw();
    DrawRectangleLines(0.35*windowWidth, 0.4*windowHeight, 0.3*windowWidth, 0.05*windowHeight, BLACK);
    DrawTextEx(PT_serif_bold, "Enter teacher name", (Vector2){float(0.35*windowWidth), float(0.37*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);

    // draw number of credits
    numberOfCredits.Draw();
    DrawRectangleLines(0.35*windowWidth, 0.49*windowHeight, 0.14*windowWidth, 0.05*windowHeight, BLACK);
    DrawTextEx(PT_serif_bold, "Number of credits", (Vector2){float(0.35*windowWidth), float(0.46*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);

    // draw max number of students
    maxStudents.Draw();
    DrawRectangleLines(0.51*windowWidth, 0.49*windowHeight, 0.14*windowWidth, 0.05*windowHeight, BLACK);
    DrawTextEx(PT_serif_bold, "Max No. of students", (Vector2){float(0.51*windowWidth), float(0.46*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);

    // draw days of week buttons
    std::string chosenDay = buttonChosen(0.35*windowWidth, 0.58*windowHeight, 0.37*windowHeight, 0.05*windowHeight, dayLabel, isDayChosen, 7);
    DrawTextEx(PT_serif_bold, "Select date of course", (Vector2){float(0.35*windowWidth), float(0.55*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);
    
    // draw session
    std::string chosenSession = buttonChosen(0.35*windowWidth, 0.67*windowHeight, 0.22*windowHeight, 0.05*windowHeight, sessionLabel, isSessionChosen, 4);
    DrawTextEx(PT_serif_bold, "Select session", (Vector2){float(0.35*windowWidth), float(0.64*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);

    // draw close button
    addCourseClose.DrawTexture();
    
    if (addCourseClose.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuCourse = VIEWCOURSE;
        courseName.currentInput = "";
        courseID.currentInput = "";
        className.currentInput = "";
        teacherName.currentInput = "";
        numberOfCredits.currentInput = "";
        maxStudents.currentInput = "";
    }
    if (Create.isPRESSED(MOUSE_BUTTON_LEFT)) {
        curCourse.name = courseName.GetInput();
        curCourse.id = courseID.GetInput();
        curCourse.Class = className.GetInput();
        curCourse.teacher = teacherName.GetInput();
        curCourse.credit = stoi(numberOfCredits.GetInput());
        curCourse.maxStudent = stoi(maxStudents.GetInput());
        int tmp = 0;
        for(int i = 0; i < 7; ++i) if (isDayChosen[i]) tmp = i, isDayChosen[i] = false;
        isDayChosen[0] = true;
        curCourse.dayOfWeek = dayLabel[tmp];
        for(int i = 0; i < 4; ++i) if (isSessionChosen[i]) tmp = i, isSessionChosen[i] = false;
        isSessionChosen[0] = true;
        curCourse.session = sessionLabel[tmp];
        AddCourse(schoolYear, semester, curCourse, ListOfCourses, listCourseSize);
        menuCourse = VIEWCOURSE;
        Update_CourseInformation(curCourse, schoolYear, semester);
        courseName.currentInput = "";
        courseID.currentInput = "";
        className.currentInput = "";
        teacherName.currentInput = "";
        numberOfCredits.currentInput = "";
        maxStudents.currentInput = "";
        ListOfCourses[indexCourse] = curCourse;
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

void Course::DrawViewCourse()
{
    DrawTextEx(PT_serif_bold, (">  " + schoolYear + "  >  " + semester + "  >  " + curCourse.name + " - " + curCourse.Class).c_str(), (Vector2){float(0.25*windowWidth), float(0.01*windowHeight)}, 0.015*windowWidth, 0.5, WHITE);
    Rectangle box = {float(0.12*windowWidth), float(0.17*windowHeight), float(0.76*windowWidth), float(0.71*windowHeight)};
    DrawRectangleRec(box, RAYWHITE);
    DrawRectangleLinesEx((Rectangle){float(box.x - 2), float(box.y - 2), float(box.width + 4), float(box.height + 4)}, 1, BLACK);
    

    del.DrawText();
    back.DrawText();
    add.DrawText();
    drop.DrawText();
    info.DrawText();
    delStudent.DrawText();
    exportStudent.DrawText();
    studentConfig.DrawText();

    DrawStudentList();

    if (menuCourse != VIEWCOURSE) return;
    
    if (del.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuCourse = DELETECOURSE;
    }
    if (delStudent.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuCourse = DELETESTUDENT;
    }
    if (exportStudent.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuCourse = EXPORTSTUDENTLIST;
    }
    if (drop.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuCourse = IMPORTSTUDENTLIST;
    }
    if (add.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuCourse = ADDSTUDENT;
    }
    if (back.isPRESSED(MOUSE_BUTTON_LEFT))
        menuCourse = -1;

    if (info.isPRESSED(MOUSE_BUTTON_LEFT))
    {
        menuCourse = MODIFYCOURSE;
        for(int i = 0; i < 4; ++i) 
            if (curCourse.session == sessionLabel[i]) isSessionChosen[i] = true; 
            else isSessionChosen[i] = false;
        for(int i = 0; i < 7; ++i) 
            if (curCourse.dayOfWeek == dayLabel[i]) isDayChosen[i] = true; 
            else isDayChosen[i] = false;
        courseName.currentInput = curCourse.name;
        courseID.currentInput = curCourse.id;
        className.currentInput = curCourse.Class;
        teacherName.currentInput = curCourse.teacher;
        numberOfCredits.currentInput = to_string(curCourse.credit);
        maxStudents.currentInput = to_string(curCourse.maxStudent);
    }
}

void Course::ChooseViewClass()
{
    // draw outer box border
    Rectangle borders = {float(windowWidth/2), float(windowHeight/2), float(0.19*windowWidth), float(0.14*windowWidth)};
    Vector2 bordersOrigin = {float(borders.width/2), float(borders.height/2)};
    DrawRectanglePro(borders, bordersOrigin, 0, LIGHTGRAY);

    // draw outer box
    Rectangle rec = {float(windowWidth/2), float(windowHeight/2), float(0.18*windowWidth), float(0.13*windowWidth)};
    Vector2 recOrigin = {float(rec.width/2), float(rec.height/2)};
    DrawRectanglePro(rec, recOrigin, 0, RAYWHITE);

    // draw create school year button and its function
    Button Done;
    Done.SetText(PT_serif_bold, "Done", 0.48*windowWidth, 0.56*windowHeight, 0.018*windowWidth, 0.5, RAYWHITE);
    Done.SetRectangle(0.425*windowWidth, 0.55*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK, DARKBLUE);
    Done.DrawText();
    
    if (Done.isPRESSED(MOUSE_BUTTON_LEFT))
    {
        // createSchoolYear(ListOfSchoolYear, ListSize, enterSchoolYear.GetInput());
        // menuStaff = previousmenuStaff;
        menuCourse = -1;
        enterClass.currentInput = "";
    }

    DrawTextEx(PT_serif_regular, "Class not found", (Vector2){float(0.46*windowWidth), float(0.52*windowHeight)}, 0.015*windowWidth, 0.5, RED);

    // draw enter class box
    enterClass.Draw();
    DrawRectangleLines(0.425*windowWidth, 0.45*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK);

    // draw enter school year text
    Vector2 enterText = {float(0.425*windowWidth), float(0.41*windowHeight)};
    DrawTextEx(PT_serif_bold, "Enter a class to view", enterText, 0.015*windowWidth, 0.5, BLACK);

    // draw close button and its function
    Button viewGPAClose;
    viewGPAClose.image = close.image;
    viewGPAClose.bsrc = (Rectangle){0, 0, float(close.image.width), float(close.image.height)};
    viewGPAClose.origin = (Vector2){0, 0};
    viewGPAClose.SetRectangle(0.57*windowWidth, 0.39*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);
    viewGPAClose.DrawTexture();

    if (viewGPAClose.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuCourse = -1;
        enterClass.currentInput = "";
    }
}

void Course::DrawViewGPA()
{
    // if (class is chosen and class is in database)
    Rectangle box = {float(0.12*windowWidth), float(0.17*windowHeight), float(0.76*windowWidth), float(0.71*windowHeight)};
    DrawRectangleRec(box, RAYWHITE);
    DrawRectangleLinesEx((Rectangle){float(box.x - 2), float(box.y - 2), float(box.width + 4), float(box.height + 4)}, 1, BLACK);

    // draw scoreboard

    back.DrawText();
}

void Course::DrawStudentList() {
    float static posY = 0;

    posY += GetMouseWheelMove() * 30;
    posY += (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) * 30;
    posY -= (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) * 30;
    
    int szButton = 0.08*windowHeight;

    float static posX = - 0.046875*windowWidth;

    posX += (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) * 70;
    posX -= (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) * 70;


    if (0.32*windowHeight + 5 + (listStudentSize) * szButton + posY <= 0.8*windowHeight)
        posY = 0.8*windowHeight - (0.32*windowHeight + 5 + (listStudentSize) * szButton);
    if (posY > 0) posY = 0;

    // auto checkCollisionX = [](float x, float windowWidth) {
    //     return (0.84*windowWidth - 0.046875*windowWidth + 20 <= x && x <= - 0.046875*windowWidth);
    // };
    if (1.07*windowWidth + posX < 0.84*windowWidth - 0.046875*windowWidth + 20) posX = 0.84*windowWidth - 0.046875*windowWidth + 20 - 1.07*windowWidth;
    if (posX > - 0.046875*windowWidth) posX = - 0.046875*windowWidth;

    Rectangle BoxStuList = {float(0.26*windowWidth - 0.046875*windowWidth), float(0.27*windowHeight), float(0.58*windowWidth + 20), float(0.53*windowHeight)};
    for (int i = 0; i < listStudentSize; ++i)
    {
        if (0.32*windowHeight + 5 + (i + 1) * szButton + posY <= 0.32*windowHeight + 5) continue;
        if (0.32*windowHeight + 5 + i * szButton + posY >= 0.8*windowHeight) break;
        Button No;
        if (indexStudent != i)
            No.SetRectangle(BoxStuList.x, 0.32*windowHeight + 5 + i * szButton + posY, BoxStuList.width, szButton - 1, (Color){210, 195, 195, 255}, LIGHTGRAY);
        else No.SetRectangle(BoxStuList.x, 0.32*windowHeight + 5 + i * szButton + posY, BoxStuList.width, szButton - 1, BLUE, BLUE);
        No.DrawText();
        DrawLine(BoxStuList.x, 0.32*windowHeight + 5 + i * szButton + posY + szButton, BoxStuList.x + BoxStuList.width, 0.32*windowHeight + 5 + i * szButton + posY + szButton, BLACK);
        // Draw No
        if (posX >= - 0.046875*windowWidth - 1)
            DrawTextEx(PT_serif_regular, to_string(i + 1).c_str(), (Vector2){float(0.27*windowWidth + posX), float(0.34*windowHeight + i * szButton + posY)}, 0.02*windowWidth, 0.5, BLACK);
        // Draw Student ID
        if (posX >= - 0.046875*windowWidth - 1 - 70 * 2)
            DrawTextEx(PT_serif_regular, ListOfStudents[i].studentID.c_str(), (Vector2){float(0.32*windowWidth + posX), float(0.34*windowHeight + i * szButton + posY)}, 0.02*windowWidth, 0.5, BLACK);
        // Draw Student Name
        DrawTextEx(PT_serif_regular, (ListOfStudents[i].lastName + " " + ListOfStudents[i].firstName).c_str(), (Vector2){float(0.43*windowWidth + posX), float(0.34*windowHeight + i * szButton + posY)}, 0.02*windowWidth, 0.5, BLACK);
        // Draw Student GPA

        if (menuCourse == VIEWCOURSE && No.isPRESSED(MOUSE_BUTTON_LEFT)) {
            if (indexStudent == i) indexStudent = -1;
            else indexStudent = i;
        }
    }
    Rectangle boxUp = {float(BoxStuList.x), float(0.32*windowHeight + 5 - (szButton + 5)), float(BoxStuList.width), float(szButton + 5)};
    DrawRectanglePro(boxUp, (Vector2){0, 0}, 0, RAYWHITE);
    Rectangle boxDown = {float(BoxStuList.x - 1), float(0.8*windowHeight), float(BoxStuList.width + 1), float(0.08*windowHeight)};
    DrawRectanglePro(boxDown, (Vector2){0, 0}, 0, RAYWHITE);

    DrawLine(BoxStuList.x, 0.32*windowHeight + 5, BoxStuList.x + BoxStuList.width, 0.32*windowHeight + 5, BLACK);

    DrawRectangleRoundedLines(BoxStuList, 0.05, 0.1, 2, BLACK);

    if (posX >= - 0.046875*windowWidth - 1)
        DrawLine(0.31*windowWidth + posX, 0.27*windowHeight, 0.31*windowWidth + posX, 0.8*windowHeight, BLACK);
    if (posX >= - 0.046875*windowWidth - 1 - 70 * 3)
        DrawLine(0.42*windowWidth + posX, 0.27*windowHeight, 0.42*windowWidth + posX, 0.8*windowHeight, BLACK);
    DrawLine(0.585*windowWidth + posX, 0.27*windowHeight, 0.585*windowWidth + posX, 0.8*windowHeight, BLACK);
    DrawLine(0.7*windowWidth + posX, 0.27*windowHeight, 0.7*windowWidth + posX, 0.8*windowHeight, BLACK);
    DrawLine(0.837*windowWidth + posX, 0.27*windowHeight, 0.837*windowWidth + posX, 0.8*windowHeight, BLACK);
    if (posX <= - 0.046875*windowWidth - 1)
        DrawLine(0.95*windowWidth + posX, 0.27*windowHeight, 0.95*windowWidth + posX, 0.8*windowHeight, BLACK);

    // title
    if (posX >= - 0.046875*windowWidth - 1)
        DrawTextEx(PT_serif_bold, "No.", (Vector2){float(0.27*windowWidth + posX), float(0.28*windowHeight)}, 0.02*windowWidth, 0.5, BLACK);
    if (posX > - 0.046875*windowWidth - 1 - 70 * 2)
        DrawTextEx(PT_serif_bold, "Student ID", (Vector2){float(0.32*windowWidth + posX), float(0.28*windowHeight)}, 0.02*windowWidth, 0.5, BLACK);
    DrawTextEx(PT_serif_bold, "Student Full Name", (Vector2){float(0.43*windowWidth + posX), float(0.28*windowHeight)}, 0.02*windowWidth, 0.5, BLACK);
    DrawTextEx(PT_serif_bold, "Other Mark", (Vector2){float(0.6*windowWidth + posX), float(0.28*windowHeight)}, 0.02*windowWidth, 0.5, BLACK);
    DrawTextEx(PT_serif_bold, "Midterm Mark", (Vector2){float(0.715*windowWidth + posX), float(0.28*windowHeight)}, 0.02*windowWidth, 0.5, BLACK);
    if (posX <= - 0.046875*windowWidth - 1)
        DrawTextEx(PT_serif_bold, "Final Mark", (Vector2){float(0.853*windowWidth + posX), float(0.28*windowHeight)}, 0.02*windowWidth, 0.5, BLACK);
    if (posX <= - 0.046875*windowWidth - 70 * 2 - 1)
        DrawTextEx(PT_serif_bold, "Total Mark", (Vector2){float(0.965*windowWidth + posX), float(0.28*windowHeight)}, 0.02*windowWidth, 0.5, BLACK);

    // DrawTextEx(PT_serif_bold, ("List of students in " + curCourse.name).c_str(), (Vector2){float(0.353*windowWidth), float(0.2*windowHeight)}, 0.035*windowWidth, 0.5, BLACK);

    Rectangle boxLeft = {float(0.12*windowWidth), BoxStuList.y, float(BoxStuList.x - 0.12*windowWidth - 2), BoxStuList.height};
    DrawRectanglePro(boxLeft, (Vector2){0, 0}, 0, RAYWHITE);
    Rectangle boxRight = {float(BoxStuList.x + BoxStuList.width + 2), BoxStuList.y, float(0.88*windowWidth - (BoxStuList.x + BoxStuList.width) - 2), BoxStuList.height};
    DrawRectanglePro(boxRight, (Vector2){0, 0}, 0, RAYWHITE);
}

void Course::DrawAddStudent() {
    static bool canAdd = true;

    del.DrawText();
    back.DrawText();
    add.DrawText();
    drop.DrawText();
    info.DrawText();
    delStudent.DrawText();
    exportStudent.DrawText();
    studentConfig.DrawText();

    // draw outer box border
    Rectangle borders = {float(windowWidth/2), float(windowHeight/2), float(0.19*windowWidth), float(0.14*windowWidth)};
    Vector2 bordersOrigin = {float(borders.width/2), float(borders.height/2)};
    DrawRectanglePro(borders, bordersOrigin, 0, LIGHTGRAY);

    // draw outer box
    Rectangle rec = {float(windowWidth/2), float(windowHeight/2), float(0.18*windowWidth), float(0.13*windowWidth)};
    Vector2 recOrigin = {float(rec.width/2), float(rec.height/2)};
    DrawRectanglePro(rec, recOrigin, 0, RAYWHITE);

    // draw create school year button and its function
    Button Done;
    Done.SetText(PT_serif_bold, "Done", 0.48*windowWidth, 0.56*windowHeight, 0.018*windowWidth, 0.5, RAYWHITE);
    Done.SetRectangle(0.425*windowWidth, 0.55*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK, DARKBLUE);
    Done.DrawText();
    
    if (Done.isPRESSED(MOUSE_BUTTON_LEFT))
    {
        canAdd = Add1StudenttoCourse(enterClass.GetInput(), curCourse, schoolYear, semester);
        enterClass.currentInput = "";
        viewStudentInCourse(schoolYear, semester, curCourse, ListOfStudents, listStudentSize);
        if (canAdd) menuCourse = VIEWCOURSE;
    }

    if (!canAdd)
        DrawTextEx(PT_serif_regular, "Student ID is not found", (Vector2){float(0.44*windowWidth), float(0.52*windowHeight)}, 0.015*windowWidth, 0.5, RED);

    // draw enter class box
    enterClass.Draw();
    DrawRectangleLines(0.425*windowWidth, 0.45*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK);

    // draw enter school year text
    Vector2 enterText = {float(0.425*windowWidth), float(0.41*windowHeight)};
    DrawTextEx(PT_serif_bold, "Enter a Student ID to add", enterText, 0.015*windowWidth, 0.5, BLACK);

    // draw close button and its function
    Button addStudentClose;
    addStudentClose.image = close.image;
    addStudentClose.bsrc = (Rectangle){0, 0, float(close.image.width), float(close.image.height)};
    addStudentClose.origin = (Vector2){0, 0};
    addStudentClose.SetRectangle(0.57*windowWidth, 0.39*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);
    addStudentClose.DrawTexture();

    if (addStudentClose.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuCourse = VIEWCOURSE;
        enterClass.currentInput = "";
        canAdd = true;
    }
}

void Course::DrawImportStudentList() {
    DrawTextEx(PT_serif_bold, (">  " + schoolYear + "  >  " + semester + "  >  " + curCourse.name + " - " + curCourse.Class).c_str(), (Vector2){float(0.25*windowWidth), float(0.01*windowHeight)}, 0.015*windowWidth, 0.5, WHITE);
    static FilePathList droppedFiles;
    static string dir = "";
    Rectangle box = {float(0.12*windowWidth), float(0.17*windowHeight), float(0.76*windowWidth), float(0.71*windowHeight)};
    DrawRectangleRec(box, RAYWHITE);
    DrawRectangleLinesEx((Rectangle){float(box.x - 2), float(box.y - 2), float(box.width + 4), float(box.height + 4)}, 1, BLACK);
    back.DrawText();
    if (back.isPRESSED(MOUSE_BUTTON_LEFT))
        menuCourse = VIEWCOURSE, 
        UnloadDroppedFiles(droppedFiles),
        dir = "";

    Rectangle dropInBox = {float(windowWidth/2), float(windowHeight/2), float(0.3*windowWidth), float(0.3*windowHeight)};
    Vector2 dropInOrigin = {float(dropInBox.width/2), float(dropInBox.height/2)};
    DrawRectanglePro(dropInBox, dropInOrigin, 0, (Color){234, 227, 210, 255});

    if (IsFileDropped())
    {
        droppedFiles = LoadDroppedFiles();
        if (IsFileExtension(droppedFiles.paths[0], ".csv"))
        {
            dir = droppedFiles.paths[0];
        }
    }
    Button UploadFile;
    UploadFile.SetRectangle(0.7*windowWidth, 0.7*windowHeight, 95, 50, LIGHTGRAY, BLUE);
    UploadFile.SetText(PT_serif_bold, "Upload", 0.7*windowWidth + 5, 0.7*windowHeight + 10, 0.025*windowWidth, 0.5, BLACK);
    UploadFile.DrawText();
    if (UploadFile.isPRESSED(MOUSE_BUTTON_LEFT) && dir != "") {
        // importStudent(ListOfStudent, listStuSize, dir, SchoolYear, ListOfClasses[classIndex]);
        UnloadDroppedFiles(droppedFiles);
        dir = "";
    }
    if (dir == "") DrawTextEx(PT_serif_bold, "Drop file into this window", (Vector2){float(0.43*windowWidth), float(0.5*windowHeight)}, 0.016*windowWidth, 0.5, BLACK);
    else DrawTextEx(PT_serif_bold, dir.c_str(), (Vector2){float(0.37*windowWidth), float(0.5*windowHeight)}, 0.016*windowWidth, 0.5, BLACK);
}

void Course::DrawExportStudentList() {
    
    del.DrawText();
    back.DrawText();
    add.DrawText();
    drop.DrawText();
    info.DrawText();
    delStudent.DrawText();
    exportStudent.DrawText();
    studentConfig.DrawText();

    // draw outer box border
    Rectangle borders = {float(windowWidth/2), float(windowHeight/2), float(0.19*windowWidth), float(0.14*windowWidth)};
    Vector2 bordersOrigin = {float(borders.width/2), float(borders.height/2)};
    DrawRectanglePro(borders, bordersOrigin, 0, LIGHTGRAY);

    // draw outer box
    Rectangle rec = {float(windowWidth/2), float(windowHeight/2), float(0.18*windowWidth), float(0.13*windowWidth)};
    Vector2 recOrigin = {float(rec.width/2), float(rec.height/2)};
    DrawRectanglePro(rec, recOrigin, 0, RAYWHITE);

    // draw create school year button and its function
    Button Done;
    Done.SetText(PT_serif_bold, "Done", 0.48*windowWidth, 0.56*windowHeight, 0.018*windowWidth, 0.5, RAYWHITE);
    Done.SetRectangle(0.425*windowWidth, 0.55*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK, DARKBLUE);
    Done.DrawText();
    
    if (Done.isPRESSED(MOUSE_BUTTON_LEFT))
    {
        menuCourse = VIEWCOURSE;
        enterClass.currentInput = "";
    }

    DrawTextEx(PT_serif_regular, "Invalid path", (Vector2){float(0.463*windowWidth), float(0.52*windowHeight)}, 0.015*windowWidth, 0.5, RED);

    // draw enter class box
    enterClass.Draw();
    DrawRectangleLines(0.425*windowWidth, 0.45*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK);

    // draw enter school year text
    Vector2 enterText = {float(0.425*windowWidth), float(0.41*windowHeight)};
    DrawTextEx(PT_serif_bold, "Enter a path to export to", enterText, 0.015*windowWidth, 0.5, BLACK);

    // draw close button and its function
    Button addStudentClose;
    addStudentClose.image = close.image;
    addStudentClose.bsrc = (Rectangle){0, 0, float(close.image.width), float(close.image.height)};
    addStudentClose.origin = (Vector2){0, 0};
    addStudentClose.SetRectangle(0.57*windowWidth, 0.39*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);
    addStudentClose.DrawTexture();

    if (addStudentClose.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuCourse = VIEWCOURSE;
        enterClass.currentInput = "";
    }
}

void Course::DrawDeleteStudent() {
    
    del.DrawText();
    back.DrawText();
    add.DrawText();
    drop.DrawText();
    info.DrawText();
    delStudent.DrawText();
    exportStudent.DrawText();
    studentConfig.DrawText();

    // draw outer box border
    Rectangle borders = {float(windowWidth/2), float(windowHeight/2), float(0.19*windowWidth), float(0.14*windowWidth)};
    Vector2 bordersOrigin = {float(borders.width/2), float(borders.height/2)};
    DrawRectanglePro(borders, bordersOrigin, 0, LIGHTGRAY);

    // draw outer box
    Rectangle rec = {float(windowWidth/2), float(windowHeight/2), float(0.18*windowWidth), float(0.13*windowWidth)};
    Vector2 recOrigin = {float(rec.width/2), float(rec.height/2)};
    DrawRectanglePro(rec, recOrigin, 0, RAYWHITE);

    // draw create school year button and its function
    Button Done;
    Done.SetText(PT_serif_bold, "Yes", 0.484*windowWidth, 0.55*windowHeight, 0.018*windowWidth, 0.5, RAYWHITE);
    Done.SetRectangle(0.425*windowWidth, 0.54*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK, DARKBLUE);
    Done.DrawText();
    
    if (Done.isPRESSED(MOUSE_BUTTON_LEFT))
    {
        menuCourse = VIEWCOURSE;
        enterClass.currentInput = "";
        Remove1StudentfromCourse(ListOfStudents[indexStudent].studentID, curCourse, schoolYear, semester);
        viewStudentInCourse(schoolYear, semester, curCourse, ListOfStudents, listStudentSize);
    }

    // draw enter school year text
    Vector2 enterText = {float(0.425*windowWidth), float(0.43*windowHeight)};
    if (indexStudent != -1) {
        DrawTextEx(PT_serif_bold, "Do you want to delete", enterText, 0.015*windowWidth, 0.5, BLACK);
        DrawTextEx(PT_serif_bold, "this student?", (Vector2){float(0.425*windowWidth), float(0.455*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);
    } else {
        DrawTextEx(PT_serif_bold, "Please select a student", enterText, 0.015*windowWidth, 0.5, BLACK);
        DrawTextEx(PT_serif_bold, "to delete!", (Vector2){float(0.425*windowWidth), float(0.455*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);
    }

    // draw close button and its function
    Button addStudentClose;
    addStudentClose.image = close.image;
    addStudentClose.bsrc = (Rectangle){0, 0, float(close.image.width), float(close.image.height)};
    addStudentClose.origin = (Vector2){0, 0};
    addStudentClose.SetRectangle(0.57*windowWidth, 0.39*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);
    addStudentClose.DrawTexture();

    if (addStudentClose.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuCourse = VIEWCOURSE;
        enterClass.currentInput = "";
    }
}

void Course::DrawDeleteCourse() {

    del.DrawText();
    back.DrawText();
    add.DrawText();
    drop.DrawText();
    info.DrawText();
    delStudent.DrawText();
    exportStudent.DrawText();
    studentConfig.DrawText();

    // draw outer box border
    Rectangle borders = {float(windowWidth/2), float(windowHeight/2), float(0.19*windowWidth), float(0.14*windowWidth)};
    Vector2 bordersOrigin = {float(borders.width/2), float(borders.height/2)};
    DrawRectanglePro(borders, bordersOrigin, 0, LIGHTGRAY);

    // draw outer box
    Rectangle rec = {float(windowWidth/2), float(windowHeight/2), float(0.18*windowWidth), float(0.13*windowWidth)};
    Vector2 recOrigin = {float(rec.width/2), float(rec.height/2)};
    DrawRectanglePro(rec, recOrigin, 0, RAYWHITE);

    // draw create school year button and its function
    Button Done;
    Done.SetText(PT_serif_bold, "Yes", 0.484*windowWidth, 0.55*windowHeight, 0.018*windowWidth, 0.5, RAYWHITE);
    Done.SetRectangle(0.425*windowWidth, 0.54*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK, DARKBLUE);
    Done.DrawText();
    
    if (Done.isPRESSED(MOUSE_BUTTON_LEFT))
    {
        menuCourse = -1;
        enterClass.currentInput = "";
        DeleteACourse(schoolYear, semester, curCourse, ListOfCourses, listCourseSize);
    }

    // draw enter school year text
    Vector2 enterText = {float(0.425*windowWidth), float(0.43*windowHeight)};
    DrawTextEx(PT_serif_bold, "Do you want to delete", enterText, 0.015*windowWidth, 0.5, BLACK);
    DrawTextEx(PT_serif_bold, "this course?", (Vector2){float(0.425*windowWidth), float(0.455*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);

    // draw close button and its function
    Button addStudentClose;
    addStudentClose.image = close.image;
    addStudentClose.bsrc = (Rectangle){0, 0, float(close.image.width), float(close.image.height)};
    addStudentClose.origin = (Vector2){0, 0};
    addStudentClose.SetRectangle(0.57*windowWidth, 0.39*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);
    addStudentClose.DrawTexture();

    if (addStudentClose.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuCourse = VIEWCOURSE;
        enterClass.currentInput = "";
    }
}

