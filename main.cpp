#include "UI/LoginUI.hpp"
#include "UI/InputBar.hpp"
#include "UI/StaffUI.hpp"
#include "UI/Button.hpp"

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
        BeginDrawing();

            Login.Draw();
        
        EndDrawing();
        
    }
    Login.Deconstruct();
    
    CloseWindow();
}