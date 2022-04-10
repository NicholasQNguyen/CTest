#include "raylib.h"
#include <stdio.h>

const bool True = 1;
const bool False = 0;

// Dimensions in pixels
const int screenWidth = 800;
const int screenHeight = 450;


int main()
{
    InitWindow(screenWidth, screenHeight, "Archer");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Hello world!", 190, 200, 20, RED);
        EndDrawing();
    }

    return 0;
}
