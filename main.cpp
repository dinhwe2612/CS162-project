#include "UI/app.hpp"

int main()
{
    // init window
    const int WindowWidth = 1280;
    const int WindowHeight = 720;
    
    App app(WindowWidth, WindowHeight, 60, "Hello!");

    while (!app.AppShouldClose())
    {
        app.Tick();
    }
}