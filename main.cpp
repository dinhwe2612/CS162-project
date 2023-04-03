#include "UI/LoginUI.hpp"
#include "UI/InputBar.hpp"
#include "UI/StaffUI.hpp"
#include "UI/Button.hpp"

int main()
{
    // validateAccount("SSSS", "SSSS", true);
    // changePassword("22125016", "SSSS", false);
    // init window
    const int WindowWidth = 1280;
    const int WindowHeight = 720;

    InitWindow(WindowWidth, WindowHeight, "annyeonghaseyo");

    SetTargetFPS(60);

    LoginUI Login;
    Login.Construct(WindowWidth, WindowHeight);
    StaffUI Staff;
    Staff.Construct(WindowWidth, WindowHeight);
    
    int menuLogin = 0;
    enum WindowLogin{
        LOGIN,
        STAFF,
        STUDENT
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();

            switch (menuLogin) {
            default:
                Login.Draw();
                if (Login.isLoginSuccess) {
                    menuLogin = STAFF;

                    Staff.username = Login.inputUsername.GetInput();
                    Login.isLoginSuccess = false;
                    Login.inputUsername.currentInput = "";
                    Login.inputPassword.currentInput = "";
                }
                break;
            case STAFF:
                Staff.Draw();
                if (Staff.signOut.isPRESSED(MOUSE_BUTTON_LEFT)) {
                    menuLogin = LOGIN;

                    Staff.menuStaff = 0;
                }
                break;
            }
        EndDrawing();
        
    }
    Login.Deconstruct();
    Staff.Deconstruct();
    
    CloseWindow();
}