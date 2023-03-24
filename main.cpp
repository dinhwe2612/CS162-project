#include "UI/app.hpp"
#include "external/raylib/src/raylib.h"

int main()
{
    // init window
    const int WindowWidth = 1280;
    const int WindowHeight = 720;
    
    LoginUI Login;
    Login.Construct(WindowWidth, WindowHeight);

    InitWindow(WindowWidth, WindowHeight, "You lazy ass, RUN!");
    SetTargetFPS(60);

    Texture2D logo = LoadTexture("UI/images/full-logo.png");
    Texture2D topbar = LoadTexture("UI/images/topbar.png");
    Texture2D dummy = LoadTexture("UI/images/short-logo.png");

    while (!WindowShouldClose())
    {
        Login.Tick(logo, dummy, topbar);
    }
    UnloadTexture(logo);
    UnloadTexture(topbar);
    UnloadTexture(dummy);
}