#include "raylib.h"
#include <stdio.h>

const bool True = 1;
const bool False = 0;

// Dimensions in pixels
const int screenWidth = 800;
const int screenHeight = 450;

const float moveSpeed = 2.0;
const float jumpHeight = 4.0;
const float gravity = 2.0;
const float jumpTime = 1.0;
const int listSize = 3;

typedef struct Player 
{
    Vector2 position;
    float hSpeed;
    float vSpeed;
    float jumpTimer;
} Player;

// Function called every frame to check for movement
void update(Player *player)
{
    if (IsKeyDown(KEY_RIGHT))
    {   
        player->position.x += player->hSpeed;
    }
    if (IsKeyDown(KEY_LEFT)) 
    {
        player->position.x -= player->hSpeed;
    }
    // Jump
    if (IsKeyDown(KEY_UP) && player->jumpTimer > 0)
    { 
        player->position.y -= player->vSpeed;
        player->jumpTimer = player->jumpTimer - GetFrameTime();
    }
}

void applyGravity(Player *player)
{
    player->position.y += gravity;
}

void antiGravity(Player *player)
{
    player->position.y -= gravity;
}

int main()
{
    Rectangle ground = 
    {
        0, screenHeight - 20, screenWidth, 20
    };
    Rectangle platform1 = 
    {
        screenWidth / 2, screenHeight / 2 + 100, 100, 20
    };
    Rectangle platform2 = 
    {
        screenWidth / 2 - 80, screenHeight / 2 + 30, 100, 20
    };

    Rectangle rectangleList[listSize];
    rectangleList[0] = ground;
    rectangleList[1] = platform1;
    rectangleList[2] = platform2;

    Player player = { 0 };
    player.position = (Vector2){0, screenHeight - ground.height - 40};
    player.hSpeed = moveSpeed;
    player.vSpeed = jumpHeight;
    player.jumpTimer = jumpTime;

    InitWindow(screenWidth, screenHeight, "Test");

    Rectangle playerSquare =
    {
    // x
    player.position.x,
    // y
    player.position.y,
    // width
    20,
    // height
    40
    };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        update(&player);
        playerSquare.x = player.position.x;
        playerSquare.y = player.position.y;

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Hello world!", 190, 200, 20, RED);
            // Draw the squares representing the ground and platforms
            for (int i = 0; i < listSize; i++)
            {
                DrawRectangleRec(rectangleList[i], BLUE);
            }
            DrawRectangleRec(playerSquare, MAROON);

        EndDrawing();

        applyGravity(&player);

        if (CheckCollisionRecs(playerSquare, ground) ||
            CheckCollisionRecs(playerSquare, platform1) ||
            CheckCollisionRecs(playerSquare, platform2))
        {
            player.jumpTimer = 1;
            antiGravity(&player);
        }
    }

    CloseWindow();

    return 0;
}
