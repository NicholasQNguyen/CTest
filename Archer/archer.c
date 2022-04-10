#include "raylib.h"
#include <stdio.h>
#include <math.h>

// Coding constants
const bool True = 1;
const bool False = 0;
const float pi = 3.14159;

// Dimensions in pixels
const int screenWidth = 800;
const int screenHeight = 450;

// Initial speed values
const float hSpeed = 10.0;
const float vSpeed = 10.0;
const float gravity = 0.1;

typedef struct Arrow
{
    Vector2 position;
    Rectangle image;
    float hVelocity;
    float vVelocity;
} Arrow;

float findAngle(Vector2 origin, Vector2 target)
{
    float xDifference = origin.x - target.x;
    float yDifference = origin.y - target.y;
    float slope = yDifference/xDifference;
    return atan(slope);
}

void move(Arrow *arrow)
{
    arrow->image.x += arrow->hVelocity;
    arrow->image.y -= arrow->vVelocity;
}

void setVelocity(Arrow *arrow, float angle)
{
    arrow->hVelocity = hSpeed * cos(angle);
    arrow->vVelocity = fabs(vSpeed * sin(angle));
    printf("hVelocity: %f\n", arrow->hVelocity);
    printf("vVelocity: %f\n", arrow->vVelocity);
}

void applyGravity(Arrow *arrow)
{
    arrow->vVelocity -= gravity;
}


int main()
{
    bool velocitySet = False;
    bool arrowGenerated = False;
    float angle = 0.0;
    // make a square to represent the arrow
    Rectangle arrowSquare = {0, screenHeight - 20, 20, 20};
    Arrow arrow = {(Vector2){arrowSquare.x, arrowSquare.y}, arrowSquare, 0, 0};
    Arrow arrowList[10];


    // raylib window boilerplate
    InitWindow(screenWidth, screenHeight, "Archer");
    SetTargetFPS(60);

    // exit on esc or click the x
    while (!WindowShouldClose())
    {
        // Get mouse position on left click
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();
            // Convert from screen to World coordinates
            angle = findAngle((Vector2){arrowSquare.x, arrowSquare.y}, mousePosition); 
            arrowGenerated = True;
        }
        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Hello world!", 190, 200, 20, RED);
            if (arrowGenerated)
            {
                if (!velocitySet)
                {
                    setVelocity(&arrow, angle);
                    velocitySet = True;
                }
                DrawRectangleRec(arrow.image, BLUE); 
                move(&arrow);
                applyGravity(&arrow);
            }
        EndDrawing();
    }

    return 0;
}
