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

    
}

void Class::Deconstruct()
{
    UnloadTexture(background);
    UnloadTexture(close.image);
    UnloadTexture(addClass.image);

    UnloadFont(PT_serif_bold);
}

void Class::Draw()
{
    DrawBackground();
    close.DrawTexture();
    addClass.DrawTexture();
    DrawClassList();
    DrawCreateClass();
    

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
            
            // createClass(ListOfClasses, listSize, inputClass.GetInput(), SchoolYear);
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

    static bool classClicked;

    posY += GetMouseWheelMove() * 30;
    if (posY > 0) posY = 0;

    //int szList = ListOfSchoolYear.size();
    // replace szList with Listsize from here
    if (0.3*windowHeight + (1 + listSize) * 0.1*windowHeight + posY <= 720)
        posY = 720 - (0.3*windowHeight + (1 + listSize) * 0.1*windowHeight);

    
    for (int i = 0; i < listSize; ++i)
    {
        Button _class;

        if (0.3*windowHeight + i * 0.1*windowHeight + posY <= 0.05*windowHeight) continue;

        static std::string classDir;
        
        _class.SetRectangle(0.31*windowWidth, 0.3*windowHeight + i * 0.1*windowHeight + posY, 0.4*windowWidth, 0.08*windowHeight, LIGHTGRAY, (Color){251, 244, 226, 255});
        _class.SetText(PT_serif_bold, ListOfClasses[i], 0.33*windowWidth, 0.32*windowHeight + i * 0.1*windowHeight + posY, 0.02*windowWidth, 0.5, BLACK);
        
        if (_class.buttonShape.y >= 0.26*windowHeight && _class.buttonShape.y + _class.buttonShape.height <= 0.88*windowHeight)
            _class.DrawText();

        if (_class.isPRESSED(MOUSE_BUTTON_LEFT))
        {
            classDir = ListOfClasses[i];
            classClicked = true;
        }

        if (classClicked && isAddClass)
            DrawViewClass();
        
        if (back.isPRESSED(MOUSE_BUTTON_LEFT))
            classClicked = false;

        DrawTextEx(PT_serif_bold, classDir.c_str(), (Vector2){0.33*windowWidth, 0.01*windowHeight}, 0.015*windowWidth, 0.5, WHITE);
    }
}

void Class::DrawViewClass()
{
    Rectangle box = {0.12*windowWidth, 0.17*windowHeight, 0.76*windowWidth, 0.71*windowHeight};
    DrawRectangleRec(box, RAYWHITE);
    
    drop.DrawText();
    back.DrawText();
    add.DrawText();

    static bool isDropClicked;
    
    if (drop.isPRESSED(MOUSE_BUTTON_LEFT))
        isDropClicked = true;

    if (isDropClicked)
    {
        std::string dir = LoadDroppedFile();

        DrawTextEx(PT_serif_bold, dir.c_str(), (Vector2){0.43*windowWidth, 0.5*windowHeight}, 0.015*windowWidth, 0.5, BLACK);
    }
}

std::string Class::LoadDroppedFile()
{
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




