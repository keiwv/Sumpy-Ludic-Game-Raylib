/*

*/
#include "raylib.h"
#include <math.h>

int main(void)
{
    const int pantallaAncho = 1920;
    const int pantallaAlto = 1080;

    InitWindow(pantallaAncho, pantallaAlto, "Sumpy - Juego lúdico");

    SetTargetFPS(144);

    bool waiting = true;
    float fontSize = 80.0f;

    Texture2D texture = LoadTexture("C:\\sumpy-ludic-game-raylib\\build\\resources\\background.png");
    while (!WindowShouldClose())
    {
        ShowCursor();

        BeginDrawing();
        DrawTexture(texture, pantallaAncho / 2 - texture.width / 2, pantallaAlto / 2 - texture.height / 2, WHITE);
        if (waiting)
        {
            fontSize = 80.0f + 10.0f * sinf(GetTime() * 2.0f);
            DrawText("Selecciona un nivel", pantallaAncho / 2 - MeasureText("Selecciona un nivel", fontSize) / 2, pantallaAlto / 2, fontSize, WHITE);
        }
        else
        {
            DrawText("Selecciona un nivel", pantallaAncho / 2 - MeasureText("Selecciona un nivel", 70) / 2, pantallaAlto / 2, 70, WHITE);
        }

        DrawText("Opciones", pantallaAncho / 2 - MeasureText("Opciones", 70) / 2, pantallaAlto * 0.6, 70, WHITE);
        DrawText("Créditos", pantallaAncho / 2 - MeasureText("Créditos", 70) / 2, pantallaAlto * 0.7, 70, WHITE);
        DrawText("Salir", pantallaAncho / 2 - MeasureText("Salir", 70) / 2, pantallaAlto * 0.8, 70, WHITE);
        EndDrawing();
    }
    UnloadTexture(texture);
    CloseWindow();
    return 0;
}
