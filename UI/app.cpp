#include "../external/raylib/src/raylib.h"
#include "app.hpp"
#include <assert.h>
#include <iostream>

App::App(int windowWidth, int windowHeight, int fps, std::string title)
{
    assert(!GetWindowHandle() && "Window already opened.");
    InitWindow(windowWidth, windowHeight, title.c_str());
    SetTargetFPS(fps);
}

App:: ~App() 
{
    assert(GetWindowHandle() && "Window already closed.");
    CloseWindow();
}

bool App::AppShouldClose() const
{
    return WindowShouldClose();
}

void App::Tick()
{
    BeginDrawing();
    Update();
    Draw();
    EndDrawing();
}

void App::Draw ()
{

}

void App::Update ()
{
    ClearBackground(RAYWHITE);
}


