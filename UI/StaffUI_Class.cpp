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
    add.SetText(PT_serif_bold, "Add Student", 0.72*windowWidth, 0.18*windowHeight, 0.015*windowWidth, 0.5, BLACK);

    inputClass.Construct(0.425*windowWidth, 0.48*windowHeight, 0.15*windowWidth, 0.05*windowHeight, 0.43*windowWidth, 0.49*windowHeight, 0.018*windowWidth, 0.5, 10, "");
    inputClass.SetColorBox(WHITE, WHITE);

    StudentID.Construct(0.4*windowWidth, 0.3*windowHeight, 0.25*windowWidth, 0.05*windowHeight, 0.4*windowWidth, 0.31*windowHeight - 10, 0.03*windowWidth, 0.5, 10, "");
    StudentID.SetColorBox(WHITE, WHITE);

    firstName.Construct(0.4*windowWidth, 0.37*windowHeight, 0.25*windowWidth, 0.05*windowHeight, 0.4*windowWidth, 0.38*windowHeight - 10, 0.03*windowWidth, 0.5, 10, "");
    firstName.SetColorBox(WHITE, WHITE);

    lastName.Construct(0.4*windowWidth, 0.44*windowHeight, 0.25*windowWidth, 0.05*windowHeight, 0.4*windowWidth, 0.45*windowHeight - 10, 0.03*windowWidth, 0.5, 10, "");
    lastName.SetColorBox(WHITE, WHITE);

    Male.SetRectangle(0.4*windowWidth + 60, 0.51*windowHeight, 35, 0.05*windowHeight, LIGHTGRAY, WHITE);
    Female.SetRectangle(0.5*windowWidth + 85 - 10, 0.51*windowHeight, 35, 0.05*windowHeight, LIGHTGRAY, WHITE);
    Other.SetRectangle(0.6*windowWidth + 70, 0.51*windowHeight, 35, 0.05*windowHeight, LIGHTGRAY, WHITE);
    Tick = LoadTexture("UI/images/down.png");
    TickRec = {0, 0, Tick.width, Tick.height};

    DOB.Construct(0.4*windowWidth, 0.58*windowHeight, 0.25*windowWidth, 0.05*windowHeight, 0.4*windowWidth, 0.59*windowHeight - 10, 0.03*windowWidth, 0.5, 10, "");
    DOB.SetColorBox(WHITE, WHITE);

    socialID.Construct(0.4*windowWidth, 0.65*windowHeight, 0.25*windowWidth, 0.05*windowHeight, 0.4*windowWidth, 0.66*windowHeight - 10, 0.03*windowWidth, 0.5, 10, "");
    socialID.SetColorBox(WHITE, WHITE);
}

void Class::Deconstruct()
{
    UnloadTexture(background);
    UnloadTexture(close.image);
    UnloadTexture(addClass.image);

    UnloadFont(PT_serif_bold);
}

void Class::Draw(int &menuWindow)
{
    DrawBackground();

    if (menuClass == VIEW_CLASS) {
        DrawViewClass();
    } else if (menuClass == VIEW_STUDENT) {
        DrawViewStudent();
    } else if (menuClass == DROP_FILE) {
        std::string dir = LoadDroppedFile();
        DrawTextEx(PT_serif_bold, dir.c_str(), (Vector2){0.43*windowWidth, 0.5*windowHeight}, 0.015*windowWidth, 0.5, BLACK);
        Button UploadFile;
        UploadFile.SetRectangle(0.7*windowWidth, 0.7*windowHeight, 95, 50, LIGHTGRAY, BLUE);
        UploadFile.SetText(PT_serif_bold, "Upload", 0.7*windowWidth + 5, 0.7*windowHeight + 10, 0.025*windowWidth, 0.5, BLACK);
        UploadFile.DrawText();
        if (UploadFile.isPRESSED(MOUSE_BUTTON_LEFT) && dir != "Drop file into this window") {
            importStudent(ListOfStudent, listStuSize, dir, SchoolYear, ListOfClasses[classIndex]);
        }
    } else if (menuClass == ADD_STUDENT) {
        DrawAddStudent();
    } else {
        close.DrawTexture();
        addClass.DrawTexture();
        DrawClassList();
        DrawCreateClass();
        if (close.isPRESSED(MOUSE_BUTTON_LEFT)) {
            menuWindow = DEFAULT;
            isAddClass = false;
        }
    }
}

void Class::DrawBackground()
{
    // background
    Rectangle bsrc = {0, 0, background.width, background.height};
    Rectangle bdest = {0.12*windowWidth, 0.17*windowHeight, 0.76*windowWidth, 0.71*windowHeight};
    Vector2 origin = {0, 0};
    DrawTexturePro(background, bsrc, bdest, origin, 0, WHITE);

    // top bar
    Rectangle tdest = {0.12*windowWidth, 0.17*windowHeight, 0.76*windowWidth, 0.034*windowHeight};
    DrawRectangleRec(tdest, (Color){222, 215, 251, 255});

    // draw "Add new class" text
    Vector2 textPos = {0.34*windowWidth, 0.24*windowHeight};
    DrawTextEx(PT_serif_bold, "Add new class", textPos, 0.02*windowWidth, 0.5, BLACK);
}

bool greater_string1 (std::string& a, std::string& b)
{
    return (a > b);
}

void Class::DrawCreateClass()
{    
    if (addClass.isPRESSED(MOUSE_BUTTON_LEFT))
        isAddClass = true;

    if (isAddClass)
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
        Vector2 enterText = {0.425*windowWidth, 0.44*windowHeight};
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
            _class.DrawText();

        if (_class.isPRESSED(MOUSE_BUTTON_LEFT) && !isAddClass)
        {
            classClicked = true;
            viewStudentInClass(ListOfClasses[i], SchoolYear, ListOfStudent, listStuSize);
            classIndex = i;
            // cout << listStuSize << '\n';
            // ListOfStudent = new Student[2];
            // listStuSize = 2;
            // ListOfStudent[0].studentID = "1";
            // ListOfStudent[1].studentID = "2";
        }

        if (classClicked)
            menuClass = VIEW_CLASS;
    }
}

void Class::DrawViewClass()
{
    Rectangle box = {0.12*windowWidth, 0.17*windowHeight, 0.76*windowWidth, 0.71*windowHeight};
    DrawRectangleRec(box, RAYWHITE);
    DrawTextEx(PT_serif_bold, (">  " + ListOfClasses[classIndex]).c_str(), (Vector2){0.33*windowWidth, 0.01*windowHeight}, 0.015*windowWidth, 0.5, WHITE);
    
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

std::string Class::LoadDroppedFile()
{
    Rectangle box = {0.12*windowWidth, 0.17*windowHeight, 0.76*windowWidth, 0.71*windowHeight};
    DrawRectangleRec(box, RAYWHITE);
    back.DrawText();
    if (back.isPRESSED(MOUSE_BUTTON_LEFT))
        menuClass = VIEW_CLASS, 
        isDropClicked = false;

    Rectangle dropInBox = {windowWidth/2, windowHeight/2, 0.3*windowWidth, 0.3*windowHeight};
    Vector2 dropInOrigin = {dropInBox.width/2, dropInBox.height/2};
    DrawRectanglePro(dropInBox, dropInOrigin, 0, (Color){234, 227, 210, 255});
    
    if (IsFileDropped())
    {
        FilePathList droppedFiles = LoadDroppedFiles();
        
        if (IsFileExtension(droppedFiles.paths[0], ".csv"))
        {
            return droppedFiles.paths[0];
        }
    }
    return "Drop file into this window";
}

void Class::DrawStudentList() {
    float static posY = 0;

    posY += GetMouseWheelMove() * 30;
    
    if (0.3*windowHeight + (1 + listStuSize) * 0.1*windowHeight + posY <= 720)
        posY = 720 - (0.3*windowHeight + (1 + listStuSize) * 0.1*windowHeight);
    if (posY > 0) posY = 0;

    
    for (int i = 0; i < listStuSize; ++i)
    {
        Button StudentButton;

        if (0.3*windowHeight + i * 0.1*windowHeight + posY <= 0.05*windowHeight) continue;
        
        StudentButton.SetRectangle(0.31*windowWidth, 0.3*windowHeight + i * 0.1*windowHeight + posY, 0.4*windowWidth, 0.08*windowHeight, (Color){210, 195, 195, 255}, LIGHTGRAY);
        StudentButton.SetText(PT_serif_bold, ListOfStudent[i].studentID.c_str(), 0.33*windowWidth, 0.32*windowHeight + i * 0.1*windowHeight + posY, 0.02*windowWidth, 0.5, BLACK);
        
        if (StudentButton.buttonShape.y >= 0.26*windowHeight && StudentButton.buttonShape.y + StudentButton.buttonShape.height <= 0.88*windowHeight)
            StudentButton.DrawText();

        if (StudentButton.isPRESSED(MOUSE_BUTTON_LEFT))
        {
            
        }
    }
}

void Class::DrawViewStudent() {
    
}

void Class::DrawAddStudent() {
    static int Gender = 0;
    
    Rectangle box = {0.12*windowWidth, 0.17*windowHeight, 0.76*windowWidth, 0.71*windowHeight};
    DrawRectangleRec(box, RAYWHITE);
    DrawTextEx(PT_serif_bold, ("> " + ListOfClasses[classIndex]).c_str(), (Vector2){0.33*windowWidth, 0.01*windowHeight}, 0.015*windowWidth, 0.5, WHITE);
    DrawTextEx(PT_serif_bold, "Add student", (Vector2){0.4*windowWidth, 0.17*windowHeight}, 0.045*windowWidth, 0.5, BLACK);

    back.DrawText();

    //Draw student ID
    DrawTextEx(PT_serif_bold, "Student ID", {0.25*windowWidth, 0.3*windowHeight}, 0.027*windowWidth, 0.5, BLACK);
    DrawRectangleLines(0.4*windowWidth - 2, 0.3*windowHeight - 2, 0.25*windowWidth + 3, 0.05*windowHeight + 3, BLACK);
    StudentID.Draw();
    //Draw first name
    DrawTextEx(PT_serif_bold, "First name", (Vector2){0.25*windowWidth, 0.37*windowHeight}, 0.027*windowWidth, 0.5, BLACK);
    DrawRectangleLines(0.4*windowWidth - 2, 0.37*windowHeight - 2, 0.25*windowWidth + 3, 0.05*windowHeight + 3, BLACK);
    firstName.Draw();
    //Draw last name
    DrawTextEx(PT_serif_bold, "Last name", (Vector2){0.25*windowWidth, 0.44*windowHeight}, 0.027*windowWidth, 0.5, BLACK);
    DrawRectangleLines(0.4*windowWidth - 2, 0.44*windowHeight - 2, 0.25*windowWidth + 3.5, 0.05*windowHeight + 4, BLACK);
    lastName.Draw();
    //Draw gender
    DrawTextEx(PT_serif_bold, "Gender", (Vector2){0.25*windowWidth, 0.51*windowHeight}, 0.027*windowWidth, 0.5, BLACK);
    DrawTextEx(PT_serif_bold, "Male", (Vector2){0.4*windowWidth, 0.51*windowHeight}, 0.025*windowWidth, 0.5, BLACK);
    DrawTextEx(PT_serif_bold, "Female", (Vector2){0.5*windowWidth - 10, 0.51*windowHeight}, 0.025*windowWidth, 0.5, BLACK);
    DrawTextEx(PT_serif_bold, "Other",(Vector2){0.6*windowWidth, 0.51*windowHeight}, 0.025*windowWidth, 0.5, BLACK);
    if (Male.isPRESSED(MOUSE_BUTTON_LEFT)) Gender = -1;
    if (Female.isPRESSED(MOUSE_BUTTON_LEFT)) Gender = 0;
    if (Other.isPRESSED(MOUSE_BUTTON_LEFT)) Gender = 1;
    if (Gender == 0) DrawTexturePro(Tick, TickRec, Male.buttonShape, (Vector2){0, 0}, 0, WHITE);
    else Male.DrawText();
    if (Gender == 1) DrawTexturePro(Tick, TickRec, Female.buttonShape, (Vector2){0, 0}, 0, WHITE);
    else Female.DrawText();
    if (Gender == 2) DrawTexturePro(Tick, TickRec, Other.buttonShape, (Vector2){0, 0}, 0, WHITE);
    else Other.DrawText();
    DrawRectangleLines(0.4*windowWidth + 60 - 1, 0.51*windowHeight - 1, 35 + 1, 0.05*windowHeight + 1, BLACK);
    DrawRectangleLines(0.5*windowWidth + 85 - 10 - 1, 0.51*windowHeight - 1, 35 + 1, 0.05*windowHeight + 1, BLACK);
    DrawRectangleLines(0.6*windowWidth + 70 - 1, 0.51*windowHeight - 1, 35 + 1, 0.05*windowHeight + 1, BLACK);
    //Draw DOB
    DrawTextEx(PT_serif_bold, "Date of birth", (Vector2){0.25*windowWidth, 0.58*windowHeight}, 0.027*windowWidth, 0.5, BLACK);
    DrawRectangleLines(0.4*windowWidth - 2, 0.58*windowHeight - 2, 0.25*windowWidth + 3.5, 0.05*windowHeight + 4, BLACK);
    DOB.Draw();
    //Draw socialID
    DrawTextEx(PT_serif_bold, "Social ID", (Vector2){0.25*windowWidth, 0.65*windowHeight}, 0.027*windowWidth, 0.5, BLACK);
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
        newStudent.DOB = DOB.GetInput();
        newStudent.socialID = socialID.GetInput();
        Gender = -1;
        StudentID.currentInput = "";
        firstName.currentInput = "";
        lastName.currentInput = "";
        DOB.currentInput = "";
        socialID.currentInput = "";
        addStudentToClass(ListOfStudent, listStuSize, newStudent, SchoolYear, ListOfClasses[classIndex]);
    }
    if (back.isPRESSED(MOUSE_BUTTON_LEFT)) {
        menuClass = VIEW_CLASS;
        Gender = -1;
        StudentID.currentInput = "";
        firstName.currentInput = "";
        lastName.currentInput = "";
        DOB.currentInput = "";
        socialID.currentInput = "";
    }
}


