#include "raylib.h"
#include <math.h>

typedef enum
{
    MENU,
    OPTIONS,
    CREDITS,
    EXIT
} GameScene;

GameScene currentScene = MENU;
Vector2 mousePosition = {0};
bool waiting = true;

bool CheckMouseOnOption(const char *optionText, float fontSize);

void UpdateMenu() {
    // Lógica de actualización del menú
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckMouseOnOption("Opciones", 70)) {
            currentScene = OPTIONS;
        } else if (CheckMouseOnOption("Créditos", 70)) {
            currentScene = CREDITS;
        } else if (CheckMouseOnOption("Salir", 70)) {
            currentScene = EXIT;
        } else {
            waiting = false;
        }
    }
}

void DrawMenu() {
    // Lógica de dibujo del menú
    BeginDrawing();
    ClearBackground(BLACK);

    float fontSize = 80.0f + 10.0f * sinf(GetTime() * 8.0f);
    DrawText("Selecciona un nivel", GetScreenWidth() / 2 - MeasureText("Selecciona un nivel", fontSize) / 2, GetScreenHeight() / 2, fontSize, WHITE);
    DrawText("Opciones", GetScreenWidth() / 2 - MeasureText("Opciones", 70) / 2, GetScreenHeight() * 0.6, 70, WHITE);
    DrawText("Créditos", GetScreenWidth() / 2 - MeasureText("Créditos", 70) / 2, GetScreenHeight() * 0.7, 70, WHITE);
    DrawText("Salir", GetScreenWidth() / 2 - MeasureText("Salir", 70) / 2, GetScreenHeight() * 0.8, 70, WHITE);

    EndDrawing();
}

void UpdateOptions() {
    // Lógica de actualización de opciones
}

void DrawOptions() {
    // Lógica de dibujo de opciones
}

void UpdateCredits() {
    // Lógica de actualización de créditos
}

void DrawCredits() {
    // Lógica de dibujo de créditos
}

int main() {
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Sumpy");

    while (!WindowShouldClose()) {
        mousePosition = GetMousePosition();

        switch (currentScene) {
        case MENU:
            UpdateMenu();
            DrawMenu();
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


bool CheckMouseOnOption(const char *optionText, float fontSize) {

    Rectangle optionBounds = MeasureTextEx(GetFontDefault(),optionText, fontSize,0);


    optionBounds.x = GetScreenWidth() / 2 - optionBounds.width / 2;
    optionBounds.y = GetScreenHeight() * 0.6;

    return CheckCollisionPointRec(mousePosition, optionBounds);
}