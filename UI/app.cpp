#include "../external/raylib/src/raylib.h"
#include "app.hpp"
#include <assert.h>
#include <iostream>

// Constructor to init window
App::App(int windowWidth, int windowHeight, int fps, std::string title)
{
    this->windowHeight = windowHeight;
    this->windowWidth = windowWidth;
    assert(!GetWindowHandle() && "Window already opened.");
    InitWindow(windowWidth, windowHeight, title.c_str());
    SetTargetFPS(fps);
}

// Destructor
App:: ~App() 
{
    assert(GetWindowHandle() && "Window already closed.");
    CloseWindow();
}

// bool return if window should close
bool App::AppShouldClose() const
{
    return WindowShouldClose();
}

// draw and update
void App::Tick()
{
    BeginDrawing();
    Update();
    Draw();
    EndDrawing();
}

void App::Draw ()
{
    Image logopng = LoadImage("images/fit-logo-eng--V5.png");
    Texture2D logo = LoadTextureFromImage(logopng);
    Vector2 logoPos = {windowWidth / 2, windowHeight / 2};
    DrawTexture(logo, logoPos.x, logoPos.y, WHITE);
}

void App::Update ()
{
    ClearBackground(BLACK);
   

}


