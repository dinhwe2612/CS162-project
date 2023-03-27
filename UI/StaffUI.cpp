#include "StaffUI.hpp"
#include "InputBar.hpp"

void StaffUI::Construct(int windowWidth, int windowHeight)
{
    this->windowHeight = windowHeight;
    this->windowWidth = windowWidth;
    logo = LoadTexture("UI/images/logo.png");
    background = LoadTexture("UI/images/background5.png");
    sans_serif_bold = LoadFont("UI/font/PT_Serif/PTSerif-Bold.ttf");
}

void StaffUI::Deconstruct()
{
    UnloadTexture(background);
    UnloadTexture(logo);
    UnloadFont(sans_serif_bold);
}

void StaffUI::Draw()
{
    // BeginDrawing();
        DrawBackground();
        DrawLoginBox();

    // EndDrawing();
}

void StaffUI::DrawBackground()
{
    Vector2 origin = {0, 0};
    Rectangle bsrc = {0, 0, background.width, background.height};
    Rectangle bdest = {0, 0, windowWidth, windowHeight};
    DrawTexturePro(background, bsrc, bdest, origin, 0, WHITE);
}

void StaffUI::DrawLoginBox()
{
    // draw outer box border
    Rectangle borders = {windowWidth/2, windowHeight/2, 0.31*windowWidth, 0.31*windowWidth};
    Vector2 bordersOrigin = {borders.width/2, borders.height/2};
    DrawRectanglePro(borders, bordersOrigin, 0, LIGHTGRAY);

    // draw outer box
    Rectangle rec = {windowWidth/2, windowHeight/2, 0.3*windowWidth, 0.3*windowWidth};
    Vector2 recOrigin = {rec.width/2, rec.height/2};
    DrawRectanglePro(rec, recOrigin, 0, RAYWHITE);

    // draw logo
    Rectangle logoSrc = {0, 0, logo.width, logo.height};
    Rectangle logoDest = {0.75*rec.x, 0.55*rec.y, 0.07*logo.width, 0.07*logo.height};
    Vector2 logoOrigin = {0, 0};
    DrawTexturePro(logo, logoSrc, logoDest, logoOrigin, 0, RAYWHITE);

    // draw "SIGN IN" text
    Vector2 signInPos = {1.01*logoDest.x, 1.22*logoDest.y};
    DrawTextEx(sans_serif_bold, "Sign in", signInPos, 0.02*windowWidth, 0.5, BLACK);

    // draw username box
    Rectangle usrBox = {signInPos.x, 1.22*signInPos.y, 0.8*rec.width, 0.08*logo.height};
    DrawRectangleLinesEx(usrBox, 1, BLACK);
    
    // draw password box
    Rectangle passBox = {signInPos.x, 1.25*usrBox.y, 0.8*rec.width, 0.08*logo.height};
    DrawRectangleLinesEx(passBox, 1, BLACK);
}

void StaffUI::Update()
{
    ClearBackground(RAYWHITE);
}

void StaffUI::Tick()
{
    Draw();
    Update();
}