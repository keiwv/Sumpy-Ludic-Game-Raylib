#include "raylib.h"

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Testing window");
    Vector2 ballPosition = {-100.0f, -100.0f};
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Process window events and update ball position
        ballPosition = GetMousePosition();

        BeginDrawing();
        ClearBackground(GREEN);

        // Draw only if the cursor is on the screen
        if (IsCursorOnScreen())
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                DrawCircleV(ballPosition, 40, YELLOW);

                
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
