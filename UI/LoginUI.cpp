#include "LoginUI.hpp"
#include "StaffUI.hpp"

//---------------------------------------------------------------------------------------------//
//                                  Construct / Deconstruct
//---------------------------------------------------------------------------------------------//

void LoginUI::Construct(float windowWidth, float windowHeight)
{
    // window size init

    this->windowHeight = windowHeight;
    this->windowWidth = windowWidth;
    
    // load texture

    logo = LoadTexture("UI/images/logo.png");
    background = LoadTexture("UI/images/background5.png");
    usrIcon = LoadTexture("UI/images/profile.png");
    passwordIcon = LoadTexture("UI/images/padlock-2.png");
    staffIcon = LoadTexture("UI/images/people.png");
    studentIcon = LoadTexture("UI/images/students.png");
    
    // load font

    PT_serif_bold = LoadFont("UI/font/PT_Serif/PTSerif-Bold.ttf");
    PT_serif_regular = LoadFont("UI/font/PT_Serif/PTSerif-Regular.ttf");
    
    //InputBar

    // float x, float y, float width, float height, float cX, float cY, int _szText, int _spacing, int _MAX_SIZE, string Starting
    inputUsername.Construct(486, 295.5, 305, 45, 490, 300, 30, 0.5, 11, "       ");
    inputPassword.Construct(486, 369, 305, 45, 490, 373, 30, 0.5, 11, "       ");
    inputPassword.isPassword = true;

    //Button 

    signInButton.SetRectangle(0.379*windowWidth, 0.64*windowHeight, 0.24*windowWidth, 0.08*logo.height, BLACK, DARKBLUE);
    signInButton.SetText(PT_serif_regular, "Sign in", 0.475*windowWidth, 0.655*windowHeight, 0.02*windowWidth, 0.5, RAYWHITE);
}

void LoginUI::Deconstruct()
{
    UnloadTexture(background);
    UnloadTexture(logo);
    UnloadTexture(usrIcon);
    UnloadTexture(passwordIcon);
    UnloadTexture(staffIcon);
    UnloadTexture(studentIcon);

    UnloadFont(PT_serif_bold);
    UnloadFont(PT_serif_regular);
    UnloadFont(inputUsername.font);
    UnloadFont(inputPassword.font);
}

//---------------------------------------------------------------------------------------------//
//                              All static elements drawn here
//---------------------------------------------------------------------------------------------//

void LoginUI::DrawBackground()
{
    Vector2 origin = {0, 0};
    Rectangle bsrc = {0, 0, background.width, background.height};
    Rectangle bdest = {0, 0, windowWidth, windowHeight};
    DrawTexturePro(background, bsrc, bdest, origin, 0, WHITE);
}

void LoginUI::DrawLoginBox()
{
    // draw top bar

    Rectangle bar = {0, 0, windowWidth, 0.05*windowHeight};
    DrawRectangleRec(bar, DARKBLUE);

    // draw "You are not login" text

    Vector2 loginStatusPos = {0.88*windowWidth, 0.01*windowHeight};
    DrawTextEx(PT_serif_regular, "You are not logged in", loginStatusPos, 0.015*windowWidth, 0.5, RAYWHITE);

    // draw outer box border

    Rectangle borders = {windowWidth/2, windowHeight/2, 0.31*windowWidth, 0.31*windowWidth};
    Vector2 bordersOrigin = {borders.width/2, borders.height/2};
    DrawRectanglePro(borders, bordersOrigin, 0, LIGHTGRAY);

    // draw outer box

    Rectangle rec = {windowWidth/2, windowHeight/2, 0.3*windowWidth, 0.3*windowWidth};
    Vector2 recOrigin = {rec.width/2, rec.height/2};
    DrawRectanglePro(rec, recOrigin, 0, RAYWHITE);

    // draw logo

    Rectangle logoSrc = {0, 0, logo.width, logo.height};
    Rectangle logoDest = {0.75*windowWidth/2, 0.55*windowHeight/2, 0.07*logo.width, 0.07*logo.height};
    Vector2 logoOrigin = {0, 0};
    DrawTexturePro(logo, logoSrc, logoDest, logoOrigin, 0, RAYWHITE);

    // draw "SIGN IN" text

    Vector2 signInPos = {0.379 * windowWidth, 0.336*windowHeight};
    DrawTextEx(PT_serif_bold, "Sign in", signInPos, 0.02*windowWidth, 0.5, BLACK);

    // draw "Are you staff or student?" text

    Vector2 statusChoicePos = {0.383*windowWidth, 0.376*windowHeight};
    DrawTextEx(PT_serif_regular, "Are you staff or student?", statusChoicePos, 0.012*windowWidth, 0.5, BLACK);

    // draw username box

    Rectangle usrBox = {0.379*windowWidth, 0.409*windowHeight, 0.24*windowWidth, 0.08*logo.height};
    DrawRectangleLinesEx(usrBox, 1, BLACK);

    // draw password box

    Rectangle passBox = {0.379*windowWidth, 0.511*windowHeight, 0.24*windowWidth, 0.08*logo.height};
    DrawRectangleLinesEx(passBox, 1, BLACK);    
}

//---------------------------------------------------------------------------------------------//
//                              All non-static elements drawn here
//---------------------------------------------------------------------------------------------//

void LoginUI::DrawStatusButtons()
{
    // draw staff icon

    Rectangle staffIconSrc = {0, 0, staffIcon.width, staffIcon.height};
    Rectangle staffIconDest = {0.512*windowWidth, 0.336*windowHeight, 0.029*windowWidth, 0.029*windowWidth};
    Vector2 staffIconOrigin = {0, 0};

    // draw student icon

    Rectangle studentIconSrc = {0, 0, studentIcon.width, studentIcon.height};
    Rectangle studentIconDest = {0.58*windowWidth , 0.336*windowHeight, 0.029*windowWidth, 0.029*windowWidth};
    Vector2 studentIconPos = {0, 0};

    if (CheckCollisionPointRec(GetMousePosition(), staffIconDest) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        status = STAFF_IS_CLICKED;
    }
    if (CheckCollisionPointRec(GetMousePosition(), studentIconDest) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        status = STUDENT_IS_CLICKED;
    }

    if (status == STAFF_IS_CLICKED)
    {
        DrawTexturePro(staffIcon, staffIconSrc, staffIconDest, staffIconOrigin, 0, WHITE);
        DrawTexturePro(studentIcon, studentIconSrc, studentIconDest, studentIconPos, 0, GRAY);
    }
    else if (status == STUDENT_IS_CLICKED)
    {
        DrawTexturePro(staffIcon, staffIconSrc, staffIconDest, staffIconOrigin, 0, GRAY);
        DrawTexturePro(studentIcon, studentIconSrc, studentIconDest, studentIconPos, 0, WHITE);
    }
}

void LoginUI::DrawLoginIcon() 
{
    // draw username icon

    Rectangle usrIconSrc = {0, 0, usrIcon.width, usrIcon.height};
    Rectangle usrIconDest = {0.381*windowWidth, 0.420*windowHeight, 0.024*windowWidth, 0.024*windowWidth};
    Vector2 usrIconOrigin = {0, 0};
    DrawTexturePro(usrIcon, usrIconSrc, usrIconDest, usrIconOrigin, 0, WHITE);

    // draw password icon

    Rectangle passIconSrc = {0, 0, passwordIcon.width, passwordIcon.height};
    Rectangle passIconDest = {0.381*windowWidth, 0.525*windowHeight, 0.024*windowWidth, 0.024*windowWidth};
    Vector2 passOrigin = {0, 0};
    DrawTexturePro(passwordIcon, passIconSrc, passIconDest, passOrigin, 0, WHITE);
}

void LoginUI::DrawRetry() 
{
    Vector2 retryPos = {0.37*windowWidth, 0.61*windowHeight};
    DrawTextEx(PT_serif_regular, "Incorrect username or password. Please try again!", retryPos, 0.015*windowWidth, 0.5, RED);
}

//---------------------------------------------------------------------------------------------//
//                              All objects drawn managed here
//---------------------------------------------------------------------------------------------//

void LoginUI::Draw(int &menuLogin)
{
    DrawBackground();
    DrawLoginBox();
    inputUsername.Draw();
    inputPassword.Draw();
    DrawLoginIcon();
    signInButton.DrawText();
    DrawStatusButtons();
    if (signInButton.isPRESSED(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_ENTER)) {
        int loginState = validateAccount(inputUsername.GetInput(), inputPassword.GetInput(), status);
        if (loginState == 1) {
            isLoginSuccess = true;
            isLoginFail = false;
            inputPassword.password = "";
        } else if (loginState == -1 || loginState == -2) {
            isLoginFail = true;
        }
    }
    if (inputUsername.OnText && IsKeyPressed(KEY_TAB)) {
        inputUsername.OnText = false;
        inputPassword.OnText = true;
    }
    if (isLoginFail) {
        DrawRetry();
    }
}