#include "raylib.h"
#include <math.h>

typedef enum
{
    START,
    SELECTGAME,
    OPTIONS,
    CREDITS,
    EXIT
} GameScene;

GameScene currentScene = START;
Vector2 mousePosition = {0};
bool waiting = true;

bool CheckMouseOnOption(const char *optionText, float fontSize, float position);

void UpdateGame()
{

}
void DrawGame()
{

}

void UpdateMenu()
{
    // Lógica de actualización del menú
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckMouseOnOption("Seleccionar nivel", 70, 0.5))
        {
            currentScene = SELECTGAME;
        }
        if (CheckMouseOnOption("Opciones", 70, 0.65))
        {
            currentScene = OPTIONS;
        }
        if (CheckMouseOnOption("Créditos", 70, 0.8))
        {
            currentScene = CREDITS;
        }
        if (CheckMouseOnOption("Salir", 70, 0.9))
        {
            currentScene = EXIT;
        }
    }
}

void DrawMenu()
{
    // Lógica de dibujo del menú
    BeginDrawing();
    ClearBackground(BLACK);

    float fontSize = 80.0f + 10.0f * sinf(GetTime() * 8.0f);
    if (CheckMouseOnOption("Selecciona un nivel", 70, 0.532))
    {
        DrawText("Selecciona un nivel", GetScreenWidth() / 2 - MeasureText("Selecciona un nivel", fontSize) / 2, GetScreenHeight() / 2, fontSize, YELLOW);
    }
    else
    {
        DrawText("Selecciona un nivel", GetScreenWidth() / 2 - MeasureText("Selecciona un nivel", 70) / 2, GetScreenHeight()/2, 70, WHITE);
    }

    if (CheckMouseOnOption("Opciones", 70, 0.7))
    {
        DrawText("Opciones", GetScreenWidth() / 2 - MeasureText("Opciones", fontSize) / 2, GetScreenHeight() * 0.7, fontSize, YELLOW);
    }
    else
    {
        DrawText("Opciones", GetScreenWidth() / 2 - MeasureText("Opciones", 70) / 2, GetScreenHeight() * 0.7, 70, WHITE);
    }

    if (CheckMouseOnOption("Créditos", 70, 0.8))
    {
        DrawText("Créditos", GetScreenWidth() / 2 - MeasureText("Créditos", fontSize) / 2, GetScreenHeight() * 0.8, fontSize, YELLOW);
    }
    else
    {
        DrawText("Créditos", GetScreenWidth() / 2 - MeasureText("Créditos", 70) / 2, GetScreenHeight() * 0.8, 70, WHITE);
    }
    if (CheckMouseOnOption("Salir", 70, 0.9))
    {
        DrawText("Salir", GetScreenWidth() / 2 - MeasureText("Salir", fontSize) / 2, GetScreenHeight() * 0.9, fontSize, YELLOW);
    }
    else
    {
        DrawText("Salir", GetScreenWidth() / 2 - MeasureText("Salir", 70) / 2, GetScreenHeight() * 0.9, 70, WHITE);
    }

    EndDrawing();
}

void UpdateOptions()
{
    // Lógica de actualización de opciones
}

void DrawOptions()
{
    // Lógica de dibujo de opciones
}

void UpdateCredits()
{
    // Lógica de actualización de créditos
}

void DrawCredits()
{
    // Lógica de dibujo de créditos
}

int main()
{
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Sumpy");
    
    while (!WindowShouldClose())
    {
        mousePosition = GetMousePosition();

        switch (currentScene)
        {
        case START:
            UpdateMenu();
            DrawMenu();
            break;
        case SELECTGAME:
            UpdateGame();
            DrawGame();
            break;
        case OPTIONS:
            UpdateOptions();
            DrawOptions();
            break;
        case CREDITS:
            UpdateCredits();
            DrawCredits();
            break;
        case EXIT:
            // Lógica para salir del programa
            break;
        }
    }

    CloseWindow();
    return 0;
}

bool CheckMouseOnOption(const char *optionText, float fontSize, float position)
{
    Vector2 textSize = MeasureTextEx(GetFontDefault(), optionText, fontSize, 0);

    float centerX = GetScreenWidth() / 2 - textSize.x / 2;
    float centerY = GetScreenHeight() * position - textSize.y / 2;

    Rectangle optionBounds = {centerX, centerY, textSize.x, textSize.y};
    DrawRectangle(centerX, centerY, textSize.x, textSize.y, GREEN);
    return CheckCollisionPointRec(mousePosition, optionBounds);
}
