#include "app.hpp"

void LoginUI::Construct(int windowWidth, int windowHeight)
{
    this->windowHeight = windowHeight;
    this->windowWidth = windowWidth;
}

void LoginUI::Draw(Texture2D& logo, Texture2D& loginBox, Texture2D& topBar)
{
    BeginDrawing();
        DrawTopbar(topBar);
        DrawLogo(logo);
    // DrawLoginBox(loginBox);
    EndDrawing();
}

void LoginUI::DrawTopbar(Texture2D& topbar)
{
    Rectangle src = {0, 0, topbar.width, topbar.height};
    Rectangle dest = {0, 0, windowWidth, 0.05 * windowHeight};
    Vector2 origin = {0, 0};
    DrawTexturePro(topbar, src, dest, origin, 0, WHITE);
}

void LoginUI::DrawLogo(Texture2D& logo)
{
    Rectangle logoSrc = {0, 0, logo.width, logo.height};
    Rectangle logoDest = {windowWidth/2, windowHeight/2 + 0.2*windowHeight, logo.width, logo.height};
    Vector2 LogoOrigin = {logo.width/2, logo.height/2};
    DrawTexturePro(logo, logoSrc, logoDest, LogoOrigin, 0, WHITE);
}

void LoginUI::Update()
{
    ClearBackground(RAYWHITE);
}

void LoginUI::Tick(Texture2D& logo, Texture2D& loginBox, Texture2D& topBar)
{
    Draw(logo, loginBox, topBar);
    Update();
}