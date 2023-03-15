#include "external/raylib/src/raylib.h"

int main()
{
    const int WindowWidth = 1280;
    const int WindowHeight = 720;

    InitWindow(WindowWidth, WindowHeight, "Fuck");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawRectangle(100, 100, 100 , 300, RED);
            DrawRectangleV((Vector2){300, 200}, (Vector2){100, 30}, BLUE);
            DrawRectangleRec((Rectangle){200, 200, 100, 100}, GREEN);

        EndDrawing();
    }
    
}