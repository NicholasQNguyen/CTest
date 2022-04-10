#include "raylib.h"
#include <stdio.h>
#include <math.h>

const bool True = 1;
const bool False = 0;
const float pi = 3.14159;

// Dimensions in pixels
const int screenWidth = 800;
const int screenHeight = 450;

const float gravity = 2.0;

typedef struct Arrow
{
    Vector2 position;
    Rectangle image;
    float hVelocity;
    float vVelocity;
} Arrow;

void applyGravity(Arrow *arrow)
{
    arrow->position.y += gravity;
}

float findAngle(Vector2 origin, Vector2 target)
{
    float xDifference = origin.x - target.x;
    float yDifference = origin.y - target.y;
    float slope = xDifference/yDifference;
    return atan(slope) * (180/pi);
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
