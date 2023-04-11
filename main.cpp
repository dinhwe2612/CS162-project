#include "UI/LoginUI.hpp"
#include "UI/InputBar.hpp"
#include "UI/StaffUI.hpp"
#include "UI/Button.hpp"

int main()
{
    // init window
    const int WindowWidth = 1280;
    const int WindowHeight = 720;

    InitWindow(WindowWidth, WindowHeight, "annyeonghaseyo");

    SetTargetFPS(60);

    LoginUI Login;
    Login.Construct(WindowWidth, WindowHeight);
    StaffUI Staff;
    Staff.Construct(WindowWidth, WindowHeight);
    
    const int DEFAULT = -1;

    int menuLogin = DEFAULT;
    enum WindowLogin{
        STAFF,
        STUDENT
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
            switch (menuLogin) {
            default:
                Login.Draw(menuLogin);
                if (Login.isLoginSuccess) {
                    menuLogin = STAFF;

                    Staff.username = Login.inputUsername.GetInput();
                    Login.inputUsername.currentInput = "";
                    Login.inputPassword.currentInput = "";
                    Login.isLoginSuccess = false;
                }
                break;
            case STAFF:
                Staff.Draw(menuLogin);
                break;
            }
        EndDrawing();
        
    }
    Login.Deconstruct();
    Staff.Deconstruct();
    
    CloseWindow();
}