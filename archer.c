#include "raylib.h"
#include <stdio.h>

const bool True = 1;
const bool False = 0;

// Dimensions in pixels
const int screenWidth = 800;
const int screenHeight = 450;

typedef struct Arrow
{
    Vector2 position;
    float hVelocity;
    float vVelocity;
} Arrow;

void shoot()
{
    
}

int main()
{
    Vector2 position = (Vector2){0.0, 0.0};
    bool arrowGenerated = False;
    Rectangle arrow = {};

    InitWindow(screenWidth, screenHeight, "Archer");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Get mouse position on left click
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            position = GetMousePosition();
            arrow.x = position.x;
            arrow.y = position.y;
            arrow.width = 20;
            arrow.height = 20;
            arrowGenerated = True;
        }
        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Hello world!", 190, 200, 20, RED);
            if (arrowGenerated)
            {
                DrawRectangleRec(arrow, BLUE);
            }
        EndDrawing();
    }

    return 0;
}
