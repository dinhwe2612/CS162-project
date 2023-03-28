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
                if (Login.signInButton.isPRESSED(MOUSE_BUTTON_LEFT)) {
                    if (Login.status == Login.STAFF_IS_CLICKED) {
                        menuLogin = STAFF;
                        Staff.menuStaff = 0;
                    }
                    if (Login.status == Login.STUDENT_IS_CLICKED) {
                        menuLogin = STUDENT;
                    }
                }
                break;
            case STAFF:
                Staff.Draw();
                if (Staff.SignOut.isPRESSED(MOUSE_BUTTON_LEFT)) {
                    menuLogin = LOGIN;
                }
                break;
            }
        
        EndDrawing();
        
    }
    Login.Deconstruct();
    Staff.Deconstruct();
    
    CloseWindow();
}