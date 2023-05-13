#include "StaffUI_Class.hpp"

void Class::Construct(int windowWidth, int windowHeight)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    background = LoadTexture("UI/images/background9.png");

    PT_serif_bold = LoadFont("UI/font/PT_Serif/PTSerif-Bold.ttf");
    PT_serif_regular = LoadFont("UI/font/PT_Serif/PTSerif-Regular.ttf");

    close.SetTexture("UI/images/close.png");
    close.SetRectangle(0.85*windowWidth, 0.17*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);

    addClass.SetTexture("UI/images/add.png");
    addClass.SetRectangle(0.31*windowWidth, 0.24*windowHeight, 0.025*windowWidth, 0.025*windowWidth, LIGHTGRAY, WHITE);

    drop.SetRectangle(0.8*windowWidth, 0.17*windowHeight, 0.08*windowWidth, 0.05*windowHeight, LIGHTGRAY, RAYWHITE);
    drop.SetText(PT_serif_bold, "Drop file", 0.815*windowWidth, 0.18*windowHeight, 0.015*windowWidth, 0.5, BLACK);

    back.SetRectangle(0.12*windowWidth, 0.17*windowHeight, 0.06*windowWidth, 0.05*windowHeight, LIGHTGRAY, RAYWHITE);
    back.SetText(PT_serif_bold, "Back", 0.135*windowWidth, 0.18*windowHeight, 0.015*windowWidth, 0.5, BLACK);

    add.SetRectangle(0.71*windowWidth, 0.17*windowHeight, 0.09*windowWidth, 0.05*windowHeight, LIGHTGRAY, RAYWHITE);
    add.SetText(PT_serif_bold, "Add Student", 0.72*windowWidth + 6, 0.18*windowHeight, 0.015*windowWidth, 0.5, BLACK);

    inputClass.Construct(0.425*windowWidth, 0.48*windowHeight, 0.15*windowWidth, 0.05*windowHeight, 0.43*windowWidth, 0.49*windowHeight, 0.018*windowWidth, 0.5, 10, "");
    inputClass.SetColorBox(WHITE, WHITE);

    StudentID.Construct(0.4*windowWidth, 0.3*windowHeight, 0.25*windowWidth, 0.05*windowHeight, 0.4*windowWidth, 0.31*windowHeight - 10, 0.03*windowWidth, 0.5, 7, "");
    StudentID.SetColorBox(WHITE, WHITE);
    StudentID.onlyNum = true;

    firstName.Construct(0.4*windowWidth, 0.37*windowHeight, 0.25*windowWidth, 0.05*windowHeight, 0.4*windowWidth, 0.38*windowHeight - 10, 0.03*windowWidth, 0.5, 10, "");
    firstName.SetColorBox(WHITE, WHITE);
    firstName.onlyWord = true;

    lastName.Construct(0.4*windowWidth, 0.44*windowHeight, 0.25*windowWidth, 0.05*windowHeight, 0.4*windowWidth, 0.45*windowHeight - 10, 0.03*windowWidth, 0.5, 10, "");
    lastName.SetColorBox(WHITE, WHITE);
    lastName.onlyWord = true;

    Male.SetRectangle(0.4*windowWidth + 60, 0.51*windowHeight, 35, 0.05*windowHeight, LIGHTGRAY, WHITE);
    Female.SetRectangle(0.5*windowWidth + 85 - 10, 0.51*windowHeight, 35, 0.05*windowHeight, LIGHTGRAY, WHITE);
    Other.SetRectangle(0.6*windowWidth + 70, 0.51*windowHeight, 35, 0.05*windowHeight, LIGHTGRAY, WHITE);
    Tick = LoadTexture("UI/images/tick.png");
    TickRec = (Rectangle){0, 0, float(Tick.width), float(Tick.height)};

    day.Construct(0.4*windowWidth, 0.58*windowHeight, 0.05*windowHeight, 0.05*windowHeight, 0.4*windowWidth + 4, 0.59*windowHeight - 10, 0.03*windowWidth, 0.5, 1, "");
    day.SetColorBox(WHITE, WHITE);
    day.onlyNum = true;
    month.Construct(0.4*windowWidth + 0.05*windowHeight + 35, 0.58*windowHeight, 0.05*windowHeight, 0.05*windowHeight, 0.4*windowWidth + 0.05*windowHeight + 39, 0.59*windowHeight - 10, 0.03*windowWidth, 0.5, 1, "");
    month.SetColorBox(WHITE, WHITE);
    month.onlyNum = true;
    year.Construct(0.4*windowWidth + 0.05*windowHeight + 35 + 0.05*windowHeight + 35, 0.58*windowHeight, 0.1*windowHeight, 0.05*windowHeight, 0.4*windowWidth + 0.05*windowHeight + 35 + 0.05*windowHeight + 39, 0.59*windowHeight - 10, 0.03*windowWidth, 0.5, 3, "");
    year.SetColorBox(WHITE, WHITE);
    year.onlyNum = true;

    socialID.Construct(0.4*windowWidth, 0.65*windowHeight, 0.25*windowWidth, 0.05*windowHeight, 0.4*windowWidth, 0.66*windowHeight - 10, 0.03*windowWidth, 0.5, 11, "");
    socialID.SetColorBox(WHITE, WHITE);
    socialID.onlyNum = true;

    viewGPA.SetRectangle(0.52*windowWidth, 0.24*windowHeight, 0.025*windowWidth, 0.025*windowWidth, LIGHTGRAY, WHITE);
    viewGPA.SetTexture("UI/images/statistic.png");
}

void Class::Deconstruct()
{
    UnloadTexture(background);
    UnloadTexture(close.image);
    UnloadTexture(addClass.image);
    UnloadTexture(Tick);
    UnloadTexture(viewGPA.image);
    UnloadFont(PT_serif_bold);
}

void Class::Draw(int &menuWindow)
{
    DrawSchoolYearMenu();

    if (menuClass == VIEW_CLASS) {
        DrawViewClass();
    } else if (menuClass == DROP_FILE) {
        LoadDroppedFile();
    } else if (menuClass == ADD_STUDENT) {
        DrawAddStudent();
    } else if (menuClass == VIEWGPA) {
        DrawViewGPA();
    } else {
        DrawBackground();
        close.DrawTexture();
        addClass.DrawTexture();
        DrawClassList();
        DrawCreateClass();
        if (menuClass == CHOOSEVIEWCLASS)
            ChooseViewClass();
        if (menuClass == -1 && viewGPA.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuClass = CHOOSEVIEWCLASS;
            viewClasses(ListOfClasses, listSize, SchoolYear);
        }
        if (close.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuWindow = DEFAULT;
            isAddClass = false;
        }
    }
}

void Class::DrawBackground()
{
    // background
    Rectangle bsrc = {0, 0, float(background.width), float(background.height)};
    Rectangle bdest = {float(0.12*windowWidth), float(0.17*windowHeight), float(0.76*windowWidth), float(0.71*windowHeight)};
    Vector2 origin = {0, 0};
    DrawTexturePro(background, bsrc, bdest, origin, 0, WHITE);

    // top bar
    Rectangle tdest = {float(0.12*windowWidth), float(0.17*windowHeight), float(0.76*windowWidth), float(0.034*windowHeight)};
    DrawRectangleRec(tdest, (Color){222, 215, 251, 255});

    // draw "Add new class" text
    Vector2 textPos = {float(0.34*windowWidth), float(0.24*windowHeight)};
    DrawTextEx(PT_serif_bold, "Add new class", textPos, 0.02*windowWidth, 0.5, BLACK);

    DrawTextEx(PT_serif_bold, "View semester result", (Vector2){float(0.55*windowWidth), float(0.24*windowHeight)}, 0.02*windowWidth, 0.5, BLACK);
    viewGPA.DrawTexture();
}

bool greater_string1 (std::string& a, std::string& b)
{
    return (a > b);
}

void Class::DrawCreateClass()
{    
    if (menuClass == -1 && addClass.isPRESSED(MOUSE_BUTTON_LEFT))
        isAddClass = true;

    if (isAddClass)
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
        Button Create;
        Create.SetText(PT_serif_bold, "Create", 0.48*windowWidth, 0.56*windowHeight, 0.018*windowWidth, 0.5, RAYWHITE);
        Create.SetRectangle(0.425*windowWidth, 0.55*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK, DARKBLUE);
        Create.DrawText();

        if (Create.isPRESSED(MOUSE_BUTTON_LEFT))
        {
            // ListOfClasses[ListOfClasses.size()-1] = inputClass.GetInput();
            // std::sort(ListOfClasses.begin(), ListOfClasses.end(), greater_string1);
            // ++listSize;
            
            createClass(ListOfClasses, listSize, inputClass.GetInput(), SchoolYear);
            isAddClass = false;
            inputClass.currentInput = "";
        }

        // draw enter school year box
        inputClass.Draw();
        DrawRectangleLines(0.425*windowWidth, 0.48*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK);

        // draw enter school year text
        Vector2 enterText = {float(0.425*windowWidth), float(0.44*windowHeight)};
        DrawTextEx(PT_serif_bold, "Enter class name", enterText, 0.015*windowWidth, 0.5, BLACK);

        // draw close button and its function
        Button addClassClose;
        addClassClose = close;
        addClassClose.SetRectangle(0.57*windowWidth, 0.39*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);
        addClassClose.DrawTexture();

        if (addClassClose.isPRESSED(MOUSE_BUTTON_LEFT)) {
            isAddClass = false;
            inputClass.currentInput = "";
        }
    }
}

void Class::DrawClassList()
{
    float static posY = 0;

    posY += GetMouseWheelMove() * 30;
    
    //int szList = ListOfSchoolYear.size();
    // replace szList with Listsize from here
    if (0.3*windowHeight + (1 + listSize) * 0.1*windowHeight + posY <= 720)
        posY = 720 - (0.3*windowHeight + (1 + listSize) * 0.1*windowHeight);
    if (posY > 0) posY = 0;

    
    for (int i = 0; i < listSize; ++i)
    {
        Button _class;

        if (0.3*windowHeight + i * 0.1*windowHeight + posY <= 0.05*windowHeight) continue;
        
        _class.SetRectangle(0.31*windowWidth, 0.3*windowHeight + i * 0.1*windowHeight + posY, 0.4*windowWidth, 0.08*windowHeight, LIGHTGRAY, (Color){251, 244, 226, 255});
        _class.SetText(PT_serif_bold, ListOfClasses[i], 0.33*windowWidth, 0.32*windowHeight + i * 0.1*windowHeight + posY, 0.02*windowWidth, 0.5, BLACK);
        
        if (_class.buttonShape.y >= 0.26*windowHeight && _class.buttonShape.y + _class.buttonShape.height <= 0.88*windowHeight)
        {
            _class.DrawText();
            DrawRectangleLinesEx(_class.buttonShape, 0.5, BLACK);
        }

        if (menuClass == -1 && _class.isPRESSED(MOUSE_BUTTON_LEFT) && !isAddClass)
        {
            static std::string classDir;

            classDir = "  >  " + ListOfClasses[i];
            classClicked = true;
            viewStudentInClass(ListOfClasses[i], SchoolYear, ListOfStudent, listStuSize);
            classIndex = i;
        }

        if (classClicked)
            menuClass = VIEW_CLASS;
    }
}

void Class::DrawViewClass()
{
    Rectangle box = {float(0.12*windowWidth), float(0.17*windowHeight), float(0.76*windowWidth), float(0.71*windowHeight)};
    DrawRectangleRec(box, RAYWHITE);
    DrawRectangleLinesEx((Rectangle){float(box.x - 2), float(box.y - 2), float(box.width + 4), float(box.height + 4)}, 1, BLACK);
    DrawTextEx(PT_serif_bold, (">  " + ListOfClasses[classIndex]).c_str(), (Vector2){float(0.33*windowWidth), float(0.01*windowHeight)}, 0.015*windowWidth, 0.5, WHITE);

    drop.DrawText();
    back.DrawText();
    add.DrawText();
    if (drop.isPRESSED(MOUSE_BUTTON_LEFT))
        isDropClicked = true;
    if (back.isPRESSED(MOUSE_BUTTON_LEFT))
            classClicked = false,
            menuClass = DEFAULT;
    if (isDropClicked)
    {
        menuClass = DROP_FILE;
    }
    if (add.isPRESSED(MOUSE_BUTTON_LEFT))
        menuClass = ADD_STUDENT;
    
    DrawStudentList();
}

void Class::LoadDroppedFile()
{
    static FilePathList droppedFiles;
    static string dir = "";
    Rectangle box = {float(0.12*windowWidth), float(0.17*windowHeight), float(0.76*windowWidth), float(0.71*windowHeight)};
    DrawRectangleRec(box, RAYWHITE);
    DrawRectangleLinesEx((Rectangle){float(box.x - 2), float(box.y - 2), float(box.width + 4), float(box.height + 4)}, 1, BLACK);
    back.DrawText();
    if (back.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuClass = VIEW_CLASS, 
        isDropClicked = false;
        if (IsFileDropped()) UnloadDroppedFiles(droppedFiles);
        dir = "";
        viewStudentInClass(ListOfClasses[classIndex], SchoolYear, ListOfStudent, listStuSize);
    }

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
        // cout << ListOfClasses[classIndex] << endl;
        importStudent(ListOfStudent, listStuSize, dir, SchoolYear, ListOfClasses[classIndex]);
        UnloadDroppedFiles(droppedFiles);
        dir = "";
        isDropClicked = false;
    }
    if (dir == "") DrawTextEx(PT_serif_bold, "Drop file into this window", (Vector2){float(0.43*windowWidth), float(0.5*windowHeight)}, 0.016*windowWidth, 0.5, BLACK);
    else DrawTextEx(PT_serif_bold, dir.c_str(), (Vector2){float(0.37*windowWidth), float(0.5*windowHeight)}, 0.016*windowWidth, 0.5, BLACK);
}

void Class::DrawStudentList() {
    float static posY = 0;

    posY += GetMouseWheelMove() * 30;
    
    int szButton = 0.08*windowHeight;
    int posX = -60;

    if (0.32*windowHeight + 5 + (listStuSize) * szButton + posY <= 0.8*windowHeight)
        posY = 0.8*windowHeight - (0.32*windowHeight + 5 + (listStuSize) * szButton);
    if (posY > 0) posY = 0;

    Rectangle BoxStuList = {float(0.26*windowWidth + posX), float(0.27*windowHeight), float(0.58*windowWidth + 20), float(0.53*windowHeight)};
    for (int i = 0; i < listStuSize; ++i)
    {
        if (0.32*windowHeight + 5 + (i + 1) * szButton + posY <= 0.32*windowHeight + 5) continue;
        if (0.32*windowHeight + 5 + i * szButton + posY >= 0.8*windowHeight) break;
        Button No;
        No.SetRectangle(BoxStuList.x, 0.32*windowHeight + 5 + i * szButton + posY, BoxStuList.width, szButton, (Color){210, 195, 195, 255}, LIGHTGRAY);
        No.DrawText();
        DrawLine(BoxStuList.x, 0.32*windowHeight + 5 + i * szButton + posY + szButton, BoxStuList.x + BoxStuList.width, 0.32*windowHeight + 5 + i * szButton + posY + szButton, BLACK);

        DrawTextEx(PT_serif_regular, to_string(i + 1).c_str(), GetCenterPos(BoxStuList.x, 0.32*windowHeight + 5 + i * szButton + posY, 0.31*windowWidth + posX - BoxStuList.x, szButton, to_string(i + 1).c_str(), PT_serif_regular, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
        DrawTextEx(PT_serif_regular, ListOfStudent[i].firstName.c_str(), GetCenterPos(0.31*windowWidth + posX, 0.32*windowHeight + 5 + i * szButton + posY, 0.11*windowWidth, szButton, ListOfStudent[i].firstName.c_str(), PT_serif_regular, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
        DrawTextEx(PT_serif_regular, ListOfStudent[i].lastName.c_str(), GetCenterPos(0.42*windowWidth + posX, 0.32*windowHeight + 5 + i * szButton + posY, 0.11*windowWidth - 5, szButton, ListOfStudent[i].lastName.c_str(), PT_serif_regular, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
        DrawTextEx(PT_serif_regular, ListOfStudent[i].studentID.c_str(), GetCenterPos(0.53*windowWidth - 5 + posX, 0.32*windowHeight + 5 + i * szButton + posY, 0.11*windowWidth - 5, szButton, ListOfStudent[i].studentID.c_str(), PT_serif_regular, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
        DrawTextEx(PT_serif_regular, ListOfStudent[i].DOB.c_str(), GetCenterPos(0.64*windowWidth - 10 + posX, 0.32*windowHeight + 5 + i * szButton + posY, 0.12*windowWidth, szButton, ListOfStudent[i].DOB.c_str(), PT_serif_regular, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
        DrawTextEx(PT_serif_regular, ListOfStudent[i].socialID.c_str(), GetCenterPos(0.76*windowWidth - 10 + posX, 0.32*windowHeight + 5 + i * szButton + posY, BoxStuList.x + BoxStuList.width - (0.76*windowWidth - 10 + posX), szButton, ListOfStudent[i].socialID.c_str(), PT_serif_regular, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
    }
    Rectangle box1 = {float(BoxStuList.x), float(0.32*windowHeight + 5 - (szButton + 5)), float(BoxStuList.width), float(szButton + 5)};
    DrawRectanglePro(box1, (Vector2){0, 0}, 0, RAYWHITE);
    Rectangle box2 = {float(BoxStuList.x - 1), float(0.8*windowHeight), float(BoxStuList.width + 1), float(0.08*windowHeight)};
    DrawRectanglePro(box2, (Vector2){0, 0}, 0, RAYWHITE);

    DrawLine(BoxStuList.x, 0.32*windowHeight + 5, BoxStuList.x + BoxStuList.width, 0.32*windowHeight + 5, BLACK);

    DrawRectangleRoundedLines(BoxStuList, 0.05, 0.1, 2, BLACK);

    string title = "No.       First Name       Last Name       Student ID       Date of birth        Social ID";
    DrawTextEx(PT_serif_bold, title.c_str(), (Vector2){float(0.27*windowWidth + posX), float(0.28*windowHeight)}, 0.02*windowWidth, 0.5, BLACK);

    DrawTextEx(PT_serif_bold, ("List of students in " + ListOfClasses[classIndex]).c_str(), (Vector2){float(0.353*windowWidth), float(0.2*windowHeight)}, 0.035*windowWidth, 0.5, BLACK);

    DrawLine(0.31*windowWidth + posX, 0.27*windowHeight, 0.31*windowWidth + posX, 0.8*windowHeight, BLACK);
    DrawLine(0.42*windowWidth + posX, 0.27*windowHeight, 0.42*windowWidth + posX, 0.8*windowHeight, BLACK);
    DrawLine(0.53*windowWidth - 5 + posX, 0.27*windowHeight, 0.53*windowWidth - 5 + posX, 0.8*windowHeight, BLACK);
    DrawLine(0.64*windowWidth - 10 + posX, 0.27*windowHeight, 0.64*windowWidth - 10 + posX, 0.8*windowHeight, BLACK);
    DrawLine(0.76*windowWidth - 10 + posX, 0.27*windowHeight, 0.76*windowWidth - 10 + posX, 0.8*windowHeight, BLACK);
}

void Class::DrawAddStudent() {
    static int Gender = 0;
    
    Rectangle box = {float(0.12*windowWidth), float(0.17*windowHeight), float(0.76*windowWidth), float(0.71*windowHeight)};
    DrawRectangleRec(box, RAYWHITE);
    DrawRectangleLinesEx((Rectangle){float(box.x - 2), float(box.y - 2), float(box.width + 4), float(box.height + 4)}, 1, BLACK);
    DrawTextEx(PT_serif_bold, (">  " + ListOfClasses[classIndex]).c_str(), (Vector2){float(0.33*windowWidth), float(0.01*windowHeight)}, 0.015*windowWidth, 0.5, WHITE);
    DrawTextEx(PT_serif_bold, "Add student", (Vector2){float(0.4*windowWidth), float(0.17*windowHeight)}, 0.045*windowWidth, 0.5, BLACK);

    back.DrawText();

    //Draw student ID
    DrawTextEx(PT_serif_bold, "Student ID", (Vector2){float(0.25*windowWidth), float(0.3*windowHeight)}, 0.027*windowWidth, 0.5, BLACK);
    DrawRectangleLines(0.4*windowWidth - 2, 0.3*windowHeight - 2, 0.25*windowWidth + 3, 0.05*windowHeight + 3, BLACK);
    StudentID.Draw();
    //Draw first name
    DrawTextEx(PT_serif_bold, "First name", (Vector2){float(0.25*windowWidth), float(0.37*windowHeight)}, 0.027*windowWidth, 0.5, BLACK);
    DrawRectangleLines(0.4*windowWidth - 2, 0.37*windowHeight - 2, 0.25*windowWidth + 3, 0.05*windowHeight + 3, BLACK);
    firstName.Draw();
    //Draw last name
    DrawTextEx(PT_serif_bold, "Last name", (Vector2){float(0.25*windowWidth), float(0.44*windowHeight)}, 0.027*windowWidth, 0.5, BLACK);
    DrawRectangleLines(0.4*windowWidth - 2, 0.44*windowHeight - 2, 0.25*windowWidth + 3.5, 0.05*windowHeight + 4, BLACK);
    lastName.Draw();
    //Draw gender
    DrawTextEx(PT_serif_bold, "Gender", (Vector2){float(0.25*windowWidth), float(0.51*windowHeight)}, 0.027*windowWidth, 0.5, BLACK);
    DrawTextEx(PT_serif_bold, "Male", (Vector2){float(0.4*windowWidth), float(0.51*windowHeight)}, 0.025*windowWidth, 0.5, BLACK);
    DrawTextEx(PT_serif_bold, "Female", (Vector2){float(0.5*windowWidth - 10), float(0.51*windowHeight)}, 0.025*windowWidth, 0.5, BLACK);
    DrawTextEx(PT_serif_bold, "Other",(Vector2){float(0.6*windowWidth), float(0.51*windowHeight)}, 0.025*windowWidth, 0.5, BLACK);
    if (Male.isPRESSED(MOUSE_BUTTON_LEFT)) Gender = 0;
    if (Female.isPRESSED(MOUSE_BUTTON_LEFT)) Gender = 1;
    if (Other.isPRESSED(MOUSE_BUTTON_LEFT)) Gender = 2;
    // if (Gender == 0) DrawTexturePro(Tick, TickRec, Male.buttonShape, (Vector2){0, 0}, 0, BLACK);
    // else Male.DrawText();
    // if (Gender == 1) DrawTexturePro(Tick, TickRec, Female.buttonShape, (Vector2){0, 0}, 0, WHITE);
    // else Female.DrawText();
    // if (Gender == 2) DrawTexturePro(Tick, TickRec, Other.buttonShape, (Vector2){0, 0}, 0, WHITE);
    // else Other.DrawText();
    Male.DrawText();
    Female.DrawText();
    Other.DrawText();
    if (Gender == 0) DrawRectangle(Male.buttonShape.x, Male.buttonShape.y, Male.buttonShape.height, Male.buttonShape.width, BLACK);
    else if (Gender == 1) DrawRectangle(Female.buttonShape.x, Female.buttonShape.y, Female.buttonShape.height, Female.buttonShape.width, BLACK);
    else DrawRectangle(Other.buttonShape.x, Other.buttonShape.y, Other.buttonShape.height, Other.buttonShape.width, BLACK);
    DrawRectangleLines(0.4*windowWidth + 60 - 1, 0.51*windowHeight - 1, 35 + 1, 0.05*windowHeight + 1, BLACK);
    DrawRectangleLines(0.5*windowWidth + 85 - 10 - 1, 0.51*windowHeight - 1, 35 + 1, 0.05*windowHeight + 1, BLACK);
    DrawRectangleLines(0.6*windowWidth + 70 - 1, 0.51*windowHeight - 1, 35 + 1, 0.05*windowHeight + 1, BLACK);
    //Draw DOB
    DrawTextEx(PT_serif_bold, "Date of birth", (Vector2){float(0.25*windowWidth), float(0.58*windowHeight)}, 0.027*windowWidth, 0.5, BLACK);
    DrawRectangleLines(0.4*windowWidth - 2, 0.58*windowHeight - 2, 0.05*windowHeight + 4, 0.05*windowHeight + 4, BLACK);
    day.Draw();
    DrawText("-", 0.4*windowWidth + 0.05*windowHeight + 10, 0.58*windowHeight, 0.05*windowHeight, BLACK);
    DrawRectangleLines(0.4*windowWidth + 0.05*windowHeight + 33, 0.58*windowHeight - 2, 0.05*windowHeight + 4, 0.05*windowHeight + 4, BLACK);
    month.Draw();
    DrawText("-", 0.4*windowWidth + 0.05*windowHeight + 33 + 0.05*windowHeight + 10, 0.58*windowHeight, 0.05*windowHeight, BLACK);
    DrawRectangleLines(0.4*windowWidth + 0.05*windowHeight + 33 + 0.05*windowHeight + 33, 0.58*windowHeight - 2, 0.1*windowHeight + 5, 0.05*windowHeight + 4, BLACK);
    year.Draw();
    //Draw socialID
    DrawTextEx(PT_serif_bold, "Social ID", (Vector2){float(0.25*windowWidth), float(0.65*windowHeight)}, 0.027*windowWidth, 0.5, BLACK);
    DrawRectangleLines(0.4*windowWidth - 2, 0.65*windowHeight - 2, 0.25*windowWidth + 3.5, 0.05*windowHeight + 3.5, BLACK);
    socialID.Draw();

    Button AddStudentButton;
    AddStudentButton.SetRectangle(0.61*windowWidth - 8, 0.77*windowHeight, 72, 0.05*windowHeight, LIGHTGRAY, BLUE);
    AddStudentButton.SetText(PT_serif_bold, "ADD", 0.61*windowWidth - 4, 0.77*windowHeight, 0.03*windowWidth, 0.5, BLACK);
    AddStudentButton.DrawText();

    if (AddStudentButton.isPRESSED(MOUSE_BUTTON_LEFT)) {
        Student newStudent;
        newStudent.Class = ListOfClasses[classIndex];
        newStudent.studentID = StudentID.GetInput();
        newStudent.firstName = firstName.GetInput();
        newStudent.lastName = lastName.GetInput();
        newStudent.gender = Gender;
        newStudent.DOB = day.GetInput() + "/" + month.GetInput() + "/" + year.GetInput();
        newStudent.socialID = socialID.GetInput();
        newStudent.Class = ListOfClasses[classIndex];
        Gender = 0;
        StudentID.currentInput = "";
        firstName.currentInput = "";
        lastName.currentInput = "";
        day.currentInput = "";
        month.currentInput = "";
        year.currentInput = "";
        socialID.currentInput = "";
        addStudentToClass(ListOfStudent, listStuSize, newStudent, SchoolYear, ListOfClasses[classIndex]);
    }
    if (back.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuClass = VIEW_CLASS;
        Gender = 0;
        StudentID.currentInput = "";
        firstName.currentInput = "";
        lastName.currentInput = "";
        day.currentInput = "";
        month.currentInput = "";
        year.currentInput = "";
        socialID.currentInput = "";
    }
}

void Class::DrawSchoolYearMenu() {
    DrawTextEx(PT_serif_bold, (">  " + SchoolYear).c_str(), (Vector2){float(0.25*windowWidth), float(0.01*windowHeight)}, 0.015*windowWidth, 0.5, WHITE);
}

Vector2 Class::GetCenterPos(float x, float y, float width, float height, string text, Font font, float fontSize, float spacing) {
    Vector2 size = MeasureTextEx(font, text.c_str(), fontSize, spacing);
    return (Vector2){x + width/2 - size.x/2, y + height/2 - size.y/2};
}

void Class::ChooseViewClass()
{
    static bool isError = false;
        
    // draw outer box border
    DrawRectangle(0.35*windowWidth, 0.33*windowHeight, 0.32*windowWidth, 0.34*windowHeight, LIGHTGRAY);

    // draw outer box
    DrawRectangle(0.355*windowWidth, 0.33*windowHeight + 0.005*windowWidth, 0.31*windowWidth, 0.34*windowHeight - 0.012*windowWidth, RAYWHITE);

    // draw create school year button and its function
    Button Done;
    Vector2 posDone = MeasureTextEx(PT_serif_bold, "Done", 0.02*windowWidth, 0.5);
    posDone.x = 0.425*windowWidth + (0.17*windowWidth - posDone.x) / 2;
    posDone.y = 0.6*windowHeight + (0.05*windowHeight - posDone.y) / 2;
    Done.SetText(PT_serif_bold, "Done", posDone.x, posDone.y, 0.018*windowWidth, 0.5, RAYWHITE);
    Done.SetRectangle(0.425*windowWidth, 0.6*windowHeight, 0.17*windowWidth, 0.05*windowHeight, BLACK, DARKBLUE);
    Done.DrawText();

    // draw Choose a class to view text
    float posXenterText = 0.425*windowWidth + (0.15*windowWidth - MeasureTextEx(PT_serif_bold, "Choose a class to view", 0.02*windowWidth, 0.5).x) / 2;
    Vector2 enterText = {posXenterText, float(0.345*windowHeight)};
    DrawTextEx(PT_serif_bold, "Choose a class to view", enterText, 0.02*windowWidth, 0.5, BLACK);

    // draw class list
    static int curIndex = 0;
    static int indexChosen = -1;

    if (GetMouseWheelMove() > 0) curIndex = max(0, curIndex - 1);
    if (GetMouseWheelMove() < 0) curIndex = min(listSize - 3, curIndex + 1);
    for(int i = curIndex, cnt = 0; i < listSize && cnt < 3; ++i, ++cnt) {

        Button viewClass;
        Vector2 posTextClass = MeasureTextEx(PT_serif_bold, ListOfClasses[i].c_str(), 0.016*windowWidth, 0.5);
        posTextClass.x = 0.41*windowWidth + (0.2*windowWidth - posTextClass.x) / 2;
        posTextClass.y = 0.39*windowHeight + 0.07*windowHeight*cnt + (0.05*windowHeight - posTextClass.y) / 2;

        viewClass.SetText(PT_serif_bold, ListOfClasses[i].c_str(), posTextClass.x, posTextClass.y, 0.016*windowWidth, 0.5, BLACK);
        viewClass.SetRectangle(0.41*windowWidth, 0.39*windowHeight + 0.07*windowHeight*cnt, 0.2*windowWidth, 0.05*windowHeight, LIGHTGRAY, (Color){251, 244, 226, 255});
        viewClass.DrawText();
        if (i == indexChosen) {
            DrawRectangleRounded((Rectangle){0.413*windowWidth, 0.395*windowHeight + 0.07*windowHeight*cnt, 0.005*windowWidth, 0.04*windowHeight}, 0.005*windowWidth, 12, BLUE);
        }

        DrawLine(0.41*windowWidth, 0.44*windowHeight + 0.07*windowHeight*cnt, 0.61*windowWidth, 0.44*windowHeight + 0.07*windowHeight*cnt, BLACK);
        DrawLine(0.61*windowWidth, 0.39*windowHeight + 0.07*windowHeight*cnt, 0.61*windowWidth, 0.44*windowHeight + 0.07*windowHeight*cnt, BLACK);
        
        if (!isError && viewClass.isPRESSED(MOUSE_BUTTON_LEFT)) {
            indexChosen = i;
        }
    }

    // draw close button and its function
    Button viewGPAClose;
    viewGPAClose.image = close.image;
    viewGPAClose.bsrc = (Rectangle){0, 0, float(close.image.width), float(close.image.height)};
    viewGPAClose.origin = (Vector2){0, 0};
    viewGPAClose.SetRectangle(0.644*windowWidth, 0.34*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);
    viewGPAClose.DrawTexture();

    if (!isError && viewGPAClose.isPRESSED(MOUSE_BUTTON_LEFT)) {
        curIndex = 0;
        indexChosen = -1;
        menuClass = -1;
    }

    if (!isError && Done.isPRESSED(MOUSE_BUTTON_LEFT))
    {
        if (indexChosen == -1) {
            isError = true;
        } else {
            curIndex = 0;
            curClass = ListOfClasses[indexChosen];
            indexChosen = -1;
            menuClass = VIEWGPA;
            if (!viewClassScoreBoardAllSemester(listOfSemester, semesterSize, studentListOfClass, studentListOfClassSize, courseOfClass, scoreBoardOfClass, scoreBoardOfClassSize, curClass)) cerr << "Can't viewClassScoreBoardAllSemester" << endl;
        }
    }
    if (isError) {
        // draw outer box border
        Rectangle borders = {float(windowWidth/2), float(windowHeight/2), float(0.19*windowWidth), float(0.14*windowWidth)};
        Vector2 bordersOrigin = {float(borders.width/2), float(borders.height/2)};
        DrawRectanglePro(borders, bordersOrigin, 0, LIGHTGRAY);

        // draw outer box
        Rectangle rec = {float(windowWidth/2), float(windowHeight/2), float(0.18*windowWidth), float(0.13*windowWidth)};
        Vector2 recOrigin = {float(rec.width/2), float(rec.height/2)};
        DrawRectanglePro(rec, recOrigin, 0, RAYWHITE);

        // draw error message
        enterText = (Vector2){float(0.425*windowWidth), float(0.43*windowHeight)};
        DrawTextEx(PT_serif_bold, "Please select a class", enterText, 0.015*windowWidth, 0.5, BLACK);
        DrawTextEx(PT_serif_bold, "to view!", (Vector2){float(0.425*windowWidth), float(0.455*windowHeight)}, 0.015*windowWidth, 0.5, BLACK);

        Button addStudentClose;
        addStudentClose.image = close.image;
        addStudentClose.bsrc = (Rectangle){0, 0, float(close.image.width), float(close.image.height)};
        addStudentClose.origin = (Vector2){0, 0};
        addStudentClose.SetRectangle(0.57*windowWidth, 0.39*windowHeight, 0.02*windowWidth, 0.02*windowWidth, LIGHTGRAY, WHITE);
        addStudentClose.DrawTexture();

        // draw create school year button and its function

        Done.SetText(PT_serif_bold, "OK", 0.49*windowWidth, 0.55*windowHeight, 0.018*windowWidth, 0.5, RAYWHITE);
        Done.SetRectangle(0.425*windowWidth, 0.54*windowHeight, 0.15*windowWidth, 0.05*windowHeight, BLACK, DARKBLUE);
        Done.DrawText();

        if (Done.isPRESSED(MOUSE_BUTTON_LEFT)) {
            isError = false;
        }

        if (addStudentClose.isPRESSED(MOUSE_BUTTON_LEFT)) {
            isError = false;
        }
    }
}

void Class::DrawViewGPA()
{
    Rectangle box = {float(0), float(0.053*windowHeight), float(windowWidth), float(windowHeight)};
    DrawRectangleRec(box, (Color){150, 190, 200, 255});
    DrawRectangleLinesEx((Rectangle){float(box.x - 2), float(box.y - 2), float(box.width + 4), float(box.height + 4)}, 1, DARKBLUE);
    DrawTextEx(PT_serif_bold, (">  " + ListOfClasses[classIndex]).c_str(), (Vector2){float(0.33*windowWidth), float(0.01*windowHeight)}, 0.015*windowWidth, 0.5, WHITE);

    static int posY = 0;
    static float lastPosY = 0;

    posY += GetMouseWheelMove() * 30;
    if (posY > 0) posY = 0;
    if (lastPosY + 0.02*windowHeight < windowHeight) posY = 0;

    // draw back button
    Button viewGPAback;
    viewGPAback.SetRectangle(0, 0.053*windowHeight + posY, 0.1*windowWidth, 0.05*windowHeight, DARKBLUE, BLUE);
    Vector2 posBack = GetCenterPos(0, 0.053*windowHeight + posY, 0.1*windowWidth, 0.05*windowHeight, "BACK", PT_serif_bold, 0.02*windowWidth, 0.5);
    viewGPAback.SetText(PT_serif_bold, "BACK", posBack.x, posBack.y, 0.02*windowWidth, 0.5, BLACK);
    viewGPAback.DrawText();
    DrawRectangleLines(0, 0.053*windowHeight + posY, 0.1*windowWidth, 0.05*windowHeight, BLACK);

    // draw Scoreboard of class text
    Vector2 posTittle = GetCenterPos(0, 0.07*windowHeight + posY, windowWidth, 0.05*windowHeight, "Scoreboard of " + curClass, PT_serif_bold, 0.04*windowWidth, 0.5);
    DrawTextEx(PT_serif_bold, ("Scoreboard of " + curClass).c_str(), posTittle, 0.04*windowWidth, 0.5, RED);

    // draw table
        // draw table header includes No., student id, Full name of student, name of course, total mark, GPA
    float posX1 = 0.05*windowWidth;
    float posX2 = 0.08*windowWidth;
    float posX3 = 0.2*windowWidth;
    float posX4 = 0.4*windowWidth;
    float posX5 = 0.8*windowWidth;
    float posX6 = 0.9*windowWidth;
    float posX7 = 0.95*windowWidth;
    float sizeY = 0.05*windowHeight;
    float curPosY = 0.2*windowHeight + posY;
    DrawRectangle(posX1, curPosY, posX7 - posX1, sizeY, DARKBLUE);
    DrawLine(posX1, curPosY, posX7, curPosY, DARKBLUE);

    DrawTextEx(PT_serif_bold, "No.", GetCenterPos(posX1, curPosY, posX2 - posX1, 0.05*windowHeight, "No.", PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, WHITE);
    DrawTextEx(PT_serif_bold, "Student ID", GetCenterPos(posX2, curPosY, posX3 - posX2, 0.05*windowHeight, "Student ID", PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, WHITE);
    DrawTextEx(PT_serif_bold, "Full name of student", GetCenterPos(posX3, curPosY, posX4 - posX3, 0.05*windowHeight, "Full name of student", PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, WHITE);
    DrawTextEx(PT_serif_bold, "Name of course", GetCenterPos(posX4, curPosY, posX5 - posX4, 0.05*windowHeight, "Name of course", PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, WHITE);
    DrawTextEx(PT_serif_bold, "Total mark", GetCenterPos(posX5, curPosY, posX6 - posX5, 0.05*windowHeight, "Total mark", PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, WHITE);
    DrawTextEx(PT_serif_bold, "GPA", GetCenterPos(posX6, curPosY, posX7 - posX6, 0.05*windowHeight, "GPA", PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, WHITE);

    curPosY += 0.05*windowHeight;
    DrawLine(posX1, curPosY, posX7, curPosY, DARKBLUE);
        // draw table content
    float totalGPA = 0;
    for(int i = 0; i < studentListOfClassSize; ++i) {
        float lengthY = sizeY * max(1, scoreBoardOfClassSize[i]);

        Button box;
        if (i % 2) box.SetRectangle(posX1, curPosY, posX7 - posX1, lengthY, LIGHTGRAY, (Color){245, 230, 255, 255});
        else box.SetRectangle(posX1, curPosY, posX7 - posX1, lengthY, LIGHTGRAY, WHITE);
        box.DrawText();

        DrawLine(posX1, curPosY, posX7, curPosY, DARKBLUE); 
        DrawTextEx(PT_serif_bold, to_string(i + 1).c_str(), GetCenterPos(posX1, curPosY, posX2 - posX1, lengthY, to_string(i + 1), PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
        DrawTextEx(PT_serif_bold, studentListOfClass[i].studentID.c_str(), GetCenterPos(posX2, curPosY, posX3 - posX2, lengthY, studentListOfClass[i].studentID, PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
        DrawTextEx(PT_serif_bold, (studentListOfClass[i].lastName + " " + studentListOfClass[i].firstName).c_str(), GetCenterPos(posX3, curPosY, posX4 - posX3, lengthY, studentListOfClass[i].lastName + studentListOfClass[i].firstName, PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);

        float totalScore = 0, totalCredit = 0;
        for(int j = 0; j < scoreBoardOfClassSize[i]; ++j) {
            DrawTextEx(PT_serif_bold, courseOfClass[i][j].name.c_str(), GetCenterPos(posX4, curPosY, posX5 - posX4, sizeY, courseOfClass[i][j].name, PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
            if (scoreBoardOfClass[i][j].total != -1) {
                DrawTextEx(PT_serif_bold, convertFloatToString(scoreBoardOfClass[i][j].total).c_str(), GetCenterPos(posX5, curPosY, posX6 - posX5, sizeY, convertFloatToString(scoreBoardOfClass[i][j].total), PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
                float score = 0;
                if (scoreBoardOfClass[i][j].total > 8.4) score = 4;
                else if (scoreBoardOfClass[i][j].total > 7.9) score = 3.5;
                else if (scoreBoardOfClass[i][j].total > 6.9) score = 3;
                else if (scoreBoardOfClass[i][j].total > 6.4) score = 2.5;
                else if (scoreBoardOfClass[i][j].total > 5.4) score = 2;
                else if (scoreBoardOfClass[i][j].total > 4.9) score = 1.5;
                else if (scoreBoardOfClass[i][j].total > 3.9) score = 1;
                else score = 0;
                totalScore += score * courseOfClass[i][j].credit;
                totalCredit += courseOfClass[i][j].credit;
            }
            curPosY += sizeY;

            DrawLine(posX4, curPosY, posX6, curPosY, DARKBLUE);
        }
        if (scoreBoardOfClassSize[i] == 0) curPosY += sizeY;

        if (totalCredit != 0) {
            DrawTextEx(PT_serif_bold, convertFloatToString(totalScore / totalCredit).c_str(), GetCenterPos(posX6, curPosY - lengthY, posX7 - posX6, lengthY, convertFloatToString(totalScore / totalCredit), PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, BLACK);
            totalGPA += totalScore / totalCredit;
        }
        DrawLine(posX1, curPosY, posX7, curPosY, DARKBLUE);
    }
    lastPosY = curPosY;

    if (studentListOfClassSize != 0) totalGPA /= studentListOfClassSize;

    DrawLine(posX1, 0.2*windowHeight + posY, posX1, curPosY, DARKBLUE);
    DrawLine(posX2, 0.2*windowHeight + posY, posX2, curPosY, DARKBLUE);
    DrawLine(posX3, 0.2*windowHeight + posY, posX3, curPosY, DARKBLUE);
    DrawLine(posX4, 0.2*windowHeight + posY, posX4, curPosY, DARKBLUE);
    DrawLine(posX5, 0.2*windowHeight + posY, posX5, curPosY, DARKBLUE);
    DrawLine(posX6, 0.2*windowHeight + posY, posX6, curPosY, DARKBLUE);
    DrawLine(posX7, 0.2*windowHeight + posY, posX7, curPosY, DARKBLUE);

    DrawRectangle(0.8*windowWidth, 0.14*windowHeight, 0.07*windowWidth, 0.04*windowHeight, DARKGREEN);
    DrawTextEx(PT_serif_bold, ("GPA: " + convertFloatToString(totalGPA)).c_str(), GetCenterPos(0.8*windowWidth, 0.14*windowHeight, 0.07*windowWidth, 0.04*windowHeight, ("GPA: " + convertFloatToString(totalGPA)).c_str(), PT_serif_bold, 0.02*windowWidth, 0.5), 0.02*windowWidth, 0.5, WHITE);

    //draw drop down semester list
    static int indexSemester = -1;
    static bool isShowSemesterList = false;
    float coordY = 0.139*windowHeight + posY;
    Button isSelect;
    isSelect.SetRectangle(posX1, coordY, 0.145*windowWidth, 0.04*windowHeight, LIGHTGRAY, WHITE);
    Vector2 posText;
    if (indexSemester == -1) {
        posText = GetCenterPos(posX1, coordY, 0.145*windowWidth, 0.04*windowHeight, "All Semester", PT_serif_bold, 0.02*windowWidth, 0.5);
        isSelect.SetText(PT_serif_bold, "All Semester", posText.x, posText.y, 0.02*windowWidth, 0.5, BLACK);
    } else {
        posText = GetCenterPos(posX1, coordY, 0.145*windowWidth, 0.04*windowHeight, listOfSemester[indexSemester], PT_serif_bold, 0.02*windowWidth, 0.5);
        isSelect.SetText(PT_serif_bold, listOfSemester[indexSemester], posText.x, posText.y, 0.02*windowWidth, 0.5, BLACK);
    }
    isSelect.DrawText();
    if (isShowSemesterList) DrawRectangleLines(posX1, coordY, 0.1454*windowWidth, 0.042*windowHeight, BLUE);
    else DrawRectangleLines(posX1, coordY, 0.1454*windowWidth, 0.042*windowHeight, BLACK);

    if (isShowSemesterList) {
        // cout << semesterSize << '\n';
        coordY -= 0.003*windowHeight;
        for(int i = -1, cnt = 0; i < semesterSize; ++i) {
            if (i == indexSemester) continue;
            Button semester;
            semester.SetRectangle(posX1, coordY + 0.045*windowHeight + cnt * 0.04*windowHeight, 0.145*windowWidth, 0.04*windowHeight, BLUE, WHITE);
            
            if (i != -1) {
                posText = GetCenterPos(posX1, coordY + 0.045*windowHeight + cnt * 0.04*windowHeight, 0.145*windowWidth, 0.04*windowHeight, listOfSemester[i], PT_serif_bold, 0.02*windowWidth, 0.5);
                semester.SetText(PT_serif_bold, listOfSemester[i], posX1 + 0.0025*windowWidth, posText.y, 0.02*windowWidth, 0.5, BLACK);
            } else {
                posText = GetCenterPos(posX1, coordY + 0.045*windowHeight + cnt * 0.04*windowHeight, 0.145*windowWidth, 0.04*windowHeight, "All Semester", PT_serif_bold, 0.02*windowWidth, 0.5);
                semester.SetText(PT_serif_bold, "All Semester", posText.x, posText.y, 0.02*windowWidth, 0.5, BLACK);
            }
            semester.DrawText();
            DrawRectangleLines(posX1, coordY + 0.045*windowHeight + cnt * 0.04*windowHeight, 0.1454*windowWidth, 0.042*windowHeight, BLACK);
            if (semester.isPRESSED(MOUSE_BUTTON_LEFT)) {
                indexSemester = i;
                isShowSemesterList = false;
                if (indexSemester == -1) {
                    if (!viewClassScoreBoardAllSemester(listOfSemester, semesterSize, studentListOfClass, studentListOfClassSize, courseOfClass, scoreBoardOfClass, scoreBoardOfClassSize, curClass)) cerr << "Can't viewClassScoreBoardAllSemester" << endl;
                } else {
                    string semester;
                    int j = listOfSemester[i].find(' ');
                    semester = listOfSemester[i].substr(j + 1, (int)listOfSemester[i].size() - j - 1);
                    if (!viewClassScoreBoardInSemester(studentListOfClass, studentListOfClassSize, courseOfClass, scoreBoardOfClass, scoreBoardOfClassSize, SchoolYear, semester, curClass)) cerr << "Can't viewClassScoreBoardInSemester" << endl;
                }
            }
            ++cnt;
        }
    }

    if (isSelect.isPRESSED(MOUSE_BUTTON_LEFT)) {
        isShowSemesterList ^= 1;
    } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        isShowSemesterList = false;
    }

    if (viewGPAback.isPRESSED(MOUSE_BUTTON_LEFT)) {
        isShowSemesterList = false;
        menuClass = CHOOSEVIEWCLASS;
    }
}

string Class::convertFloatToString(float x) {
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