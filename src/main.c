#include "raylib.h"
#include <math.h>

typedef enum
{
    LOGO,
    MENU,
    SELECTGAME,
    OPTIONS,
    CREDITS,
    EXIT
} GameScene;

typedef enum
{
    WAITING,
    LEVEL1,
    LEVEL2,
} GameLevel;

GameScene currentScene = MENU;
GameLevel currentGameLevel = WAITING;

Vector2 mousePosition = {0};
bool waiting = true;

#define MATRIX_WIDTH 6
#define MATRIX_HEIGHT 7
#define RECTANGLE_SIZE 100

int screenWidth = 1920;
int screenHeight = 1080;

//****** PROTOTYPE FUNCTIONS *********************
void logoLoading(Texture2D logoTexture, int frameCounter);

void UpdateMenu();
void DrawMenu();

void UpdateSelectGame();
void MainSelectGame();
void DrawSelectGame();

void UpdateGame();
void DrawGame();

bool CheckMouseOnOption(const char *optionText, float fontSize, float position);

int main()
{
    InitWindow(screenWidth, screenHeight, "Sumpy");
    bool exitProgram = false;
    int frameCounter = 0;
    Texture2D logoTexture = LoadTexture("resources/logo2.png");
    Image icon = LoadImage("resources/icon.png");
    SetWindowIcon(icon);
    while (!WindowShouldClose() && !exitProgram)
    {
        mousePosition = GetMousePosition();

        switch (currentScene)
        {
        case LOGO:
            frameCounter++;
            logoLoading(logoTexture, frameCounter);
            break;
        case MENU:
            UpdateMenu();
            DrawMenu();
            break;
        case SELECTGAME:
            MainSelectGame();
            break;
        case OPTIONS:
            break;
        case CREDITS:
            break;
        case EXIT:
            break;
        }
    }
    UnloadTexture(logoTexture);
    UnloadImage(icon);
    CloseWindow();
    return 0;
}
//************ LOGO LOADING ********
void logoLoading(Texture2D logoTexture, int frameCounter)
{
    float logoOpacity = 0.0f;

    if (frameCounter <= 500)
    {

        logoOpacity += 1.0f / 60.0f;
    }

    if (frameCounter > 60 && frameCounter <= 120)
    {
        logoOpacity = 1.0f;
    }

    if (frameCounter > 120 && frameCounter <= 180)
    {

        logoOpacity -= 1.0f / 60.0f;
    }

    if (frameCounter > 2000)
    {

        currentScene = MENU;
    }

    BeginDrawing();
    ClearBackground(GREEN);
    DrawTexturePro(logoTexture, (Rectangle){0, 0, logoTexture.width, logoTexture.height},
                   (Rectangle){screenWidth / 2 - logoTexture.width / 2, screenHeight / 2 - logoTexture.height / 2,
                               logoTexture.width, logoTexture.height},
                   (Vector2){0, 0}, 0.0f, Fade(WHITE, logoOpacity));
    EndDrawing();
}

//************ START FUNCTIONS *************
void UpdateMenu()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckMouseOnOption("Seleccionar nivel", 70, 0.532))
        {
            currentScene = SELECTGAME;
        }
        if (CheckMouseOnOption("Opciones", 70, 0.615))
        {
            currentScene = OPTIONS;
        }
        if (CheckMouseOnOption("Créditos", 70, 0.697))
        {
            currentScene = CREDITS;
        }
        if (CheckMouseOnOption("Salir", 70, 0.78))
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
        DrawText("Selecciona un nivel", screenWidth / 2 - MeasureText("Selecciona un nivel", fontSize) / 2, screenHeight / 2, fontSize, YELLOW);
    }
    else
    {
        DrawText("Selecciona un nivel", screenWidth / 2 - MeasureText("Selecciona un nivel", 70) / 2, screenHeight / 2, 70, WHITE);
    }

    if (CheckMouseOnOption("Opciones", 70, 0.615))
    {
        DrawText("Opciones", screenWidth / 2 - MeasureText("Opciones", fontSize) / 2, screenHeight * 0.5905, fontSize, YELLOW);
    }
    else
    {
        DrawText("Opciones", screenWidth / 2 - MeasureText("Opciones", 70) / 2, screenHeight * 0.5905, 70, WHITE);
    }

    if (CheckMouseOnOption("Créditos", 70, 0.697))
    {
        DrawText("Créditos", screenWidth / 2 - MeasureText("Créditos", fontSize) / 2, screenHeight * 0.67545, fontSize, YELLOW);
    }
    else
    {
        DrawText("Créditos", screenWidth / 2 - MeasureText("Créditos", 70) / 2, screenHeight * 0.67545, 70, WHITE);
    }
    if (CheckMouseOnOption("Salir", 70, 0.78))
    {
        DrawText("Salir", screenWidth / 2 - MeasureText("Salir", fontSize) / 2, screenHeight * 0.755, fontSize, YELLOW);
    }
    else
    {
        DrawText("Salir", screenWidth / 2 - MeasureText("Salir", 70) / 2, screenHeight * 0.755, 70, WHITE);
    }

    EndDrawing();
}

//************* SELECT GAME FUNCTIONS ********************
void UpdateSelectGame()
{
    Rectangle LEVEL1_RECT = {10, 10, 20, 20};
    Rectangle LEVEL2_RECT = {300, 300, 300, 300};
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointRec(mousePosition, LEVEL1_RECT))
        {
            currentGameLevel = LEVEL1;
        }
        if (CheckCollisionPointRec(mousePosition, LEVEL2_RECT))
        {
            currentGameLevel = LEVEL2;
        }
    }
}

void MainSelectGame()
{
    switch (currentGameLevel)
    {
    case WAITING:
        UpdateSelectGame();
        DrawSelectGame();
        break;
    case LEVEL1:
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
        break;
    case LEVEL2:
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
        break;
    }
}

void DrawSelectGame()
{
    Rectangle LEVEL1_RECT = {10, 10, 20, 20};
    Rectangle LEVEL2_RECT = {300, 300, 300, 300};
    BeginDrawing();
    ClearBackground(PURPLE);
    DrawRectangleRec(LEVEL1_RECT, WHITE);
    DrawRectangleRec(LEVEL2_RECT, BLACK);
    EndDrawing();
}

//************* GAME *******************
void UpdateGame()
{
    DrawGame();
}

void DrawGame()
{
    BeginDrawing();
    ClearBackground(BLACK);

    int matrixX = 600 + (screenWidth - MATRIX_WIDTH * (RECTANGLE_SIZE + 10)) / 2;
    int matrixY = (screenHeight - MATRIX_HEIGHT * (RECTANGLE_SIZE + 10)) / 2;

    Rectangle rectangulo;
    for (int i = 0; i < MATRIX_HEIGHT; i++)
    {
        for (int j = 0; j < MATRIX_WIDTH; j++)
        {
            rectangulo.height = RECTANGLE_SIZE;
            rectangulo.width = RECTANGLE_SIZE;
            rectangulo.x = matrixX + j * (RECTANGLE_SIZE + 10);
            rectangulo.y = matrixY + i * (RECTANGLE_SIZE + 10);
            DrawRectangleRounded(rectangulo, 0.4, 0, RED);
            DrawRectangleRoundedLines(rectangulo, 0.4, 20, 2, WHITE);
        }
    }

    DrawRectangleLines(screenHeight / 10, screenWidth / 2, 300, 200, RED);
    DrawRectangleLines(50, 50, 1200, 200, BLUE);
    EndDrawing();
}
//************* USEFUL FUNCTIONS ****************************
bool CheckMouseOnOption(const char *optionText, float fontSize, float position)
{
    Vector2 textSize = MeasureTextEx(GetFontDefault(), optionText, fontSize, 0);
    float centerX = screenWidth / 2 - textSize.x / 2;
    float centerY = screenHeight * position - textSize.y / 2;

    Rectangle optionBounds = {centerX, centerY, textSize.x, textSize.y};
    return CheckCollisionPointRec(mousePosition, optionBounds);
}
