#include "app.hpp"

void LoginUI::Construct(int windowWidth, int windowHeight)
{
    this->windowHeight = windowHeight;
    this->windowWidth = windowWidth;
    cat = LoadTexture("UI/images/cat.png");
    poppins = LoadFont("UI/font/PTSerif-Bold.ttf");
    background = LoadTexture("UI/images/background.png");

}

void LoginUI::Deconstruct()
{
    UnloadTexture(cat);
    UnloadFont(poppins);
}

void LoginUI::Draw()
{
    BeginDrawing();
        DrawBackground();
        DrawLoginBox();

    EndDrawing();
}

void LoginUI::DrawBackground()
{
    Vector2 origin = {0, 0};

    // background
    Rectangle bsrc = {0, 0, background.width, background.height};
    Rectangle bdest = {0, 0, windowWidth, windowHeight};
    DrawTexturePro(background, bsrc, bdest, origin, 0, WHITE);
    // focal cat
    Rectangle csrc = {0, 0, cat.width, cat.height};
    Rectangle cdst = {0.15*windowWidth, 0.1*windowHeight, 0.7*cat.width, 0.5*cat.height};
    DrawTexturePro(cat, csrc, cdst, origin, 0, WHITE);
}

void LoginUI::DrawLoginBox()
{
    // outer box
    Rectangle box = {0.15*windowWidth + 0.7*cat.width, 0.1*windowHeight, 0.7*cat.width, 0.5*cat.height};
    DrawRectangleRec(box, WHITE);

    // login text
    Vector2 txtPos = {1.26*box.x, 2*box.y};
    DrawTextEx(poppins, "Sign In", txtPos, 0.03*windowWidth, 1, BLACK);
}

void LoginUI::Update()
{
    ClearBackground(RAYWHITE);
}

void LoginUI::Tick()
{
    Draw();
    Update();
}