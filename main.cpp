#include "UI/app.hpp"
#include "external/raylib/src/raylib.h"

int main()
{
    // init window
    const int WindowWidth = 1280;
    const int WindowHeight = 720;

    InitWindow(WindowWidth, WindowHeight, "You lazy ass, RUN!");

    SetTargetFPS(60);

    LoginUI Login;
    Login.Construct(WindowWidth, WindowHeight);

    while (!WindowShouldClose())
    {
        Login.Tick();
    }
    Login.Deconstruct();
    CloseWindow();
}