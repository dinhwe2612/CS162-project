<<<<<<< Updated upstream
#include "UI/LoginUI.hpp"
=======
#include "UI/app.hpp"
#include "UI/StaffUI.hpp"
#include "UI/InputBar.hpp"
>>>>>>> Stashed changes
#include "external/raylib/src/raylib.h"

int main()
{
    // init window
    const int WindowWidth = 1280;
    const int WindowHeight = 720;

    InitWindow(WindowWidth, WindowHeight, "You lazy ass, RUN!");

    SetTargetFPS(60);

    // LoginUI Login;
    // Login.Construct(WindowWidth, WindowHeight);
    StaffUI Staff;
    Staff.Construct(WindowWidth, WindowHeight);
    InputBar inputUsername(486, 296, 305, 44, 486 + 4, 296, 40, 2, 15, "");
    InputBar inputPassword(486, 369, 305, 45, 486 + 4, 369, 40, 2, 15, "");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        Staff.Draw();
        inputUsername.draw();
        inputPassword.draw();
        EndDrawing();
    }
    // Login.Deconstruct();
    Staff.Deconstruct();
    CloseWindow();
}