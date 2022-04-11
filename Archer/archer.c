#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Coding constants
const bool True = 1;
const bool False = 0;

// Dimensions in pixels
const int screenWidth = 500;
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
    float angle;
    bool hit;
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
}

void applyGravity(Arrow *arrow)
{
    arrow->vVelocity -= gravity;
}

int main()
{   
    bool velocityNeedsSetting = False;
    bool arrowGenerated = False;
    float angle = 0.0;

    int index = 0;
    Arrow arrowList[100];

    Rectangle target = {screenWidth - 20, 0, 20, screenHeight};
    int score = 0;

    // raylib window boilerplate
    InitWindow(screenWidth, screenHeight, "Archer");
    SetTargetFPS(60);

    // exit on esc or click the x
    while (!WindowShouldClose())
    {
        // Get mouse position on left click
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Rectangle arrowSquare = {0, screenHeight - 20, 20, 20};
            Arrow arrow = {(Vector2){arrowSquare.x, arrowSquare.y}, arrowSquare, 0, 0};
            arrowList[index] = arrow;
            Vector2 mousePosition = GetMousePosition();
            angle = findAngle((Vector2){0, screenHeight}, mousePosition); 
            arrowList[index].angle = angle;
            velocityNeedsSetting = True;
        }
        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Hello world!", 190, 200, 20, RED);
            // Draw the target
            DrawRectangleRec(target, RED);

            // Apply velocity to the most recent square
            if (velocityNeedsSetting)
            {
                setVelocity(&arrowList[index], arrowList[index].angle);
                index++;
                velocityNeedsSetting = False;
            }

            // move and apply gravity to all of the squares and draw them
            for (int i=0; i<=index; i++)
            {
                move(&arrowList[i]);
                applyGravity(&arrowList[i]);
                DrawRectangleRec(arrowList[i].image, BLUE); 
            }
            // Check for collision between the arrows and the target
            for (int i=0; i<=index; i++)
            {
                if (CheckCollisionRecs(arrowList[i].image, target) && !arrowList[i].hit)
                {
                    // Change a bool to make it hit only once
                    arrowList[i].hit = True;
                    if (arrowList[i].image.y < screenHeight / 3)
                    {
                        score = score + 30;
                    }
                    else if (arrowList[i].image.y > screenHeight / 3 + screenHeight / 3)
                    {
                        score = score + 20;
                    }
                    else if (arrowList[i].image.y > screenHeight / 3)
                    {
                        score = score + 10;
                    }
                    printf("%d\n", score);
                }
            }
            
        EndDrawing();
    }

    return 0;
}
