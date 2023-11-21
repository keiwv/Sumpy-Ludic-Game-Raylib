#include "raylib.h"
#include <math.h>

typedef enum
{
    START,
    SELECTGAME,
    OPTIONS,
    CUSTOME,
    EXIT
} GameScene;

GameScene currentScene = START;
Vector2 mousePosition = {0};
bool waiting = true;

/********************************** PROTOTIPO DE FUNCIONES ************************************/
bool CheckMouseOnOption(const char *optionText, float fontSize, float position);
void generate_dinos(int frame, float runningTime, float frameTime, Texture2D dinosaurio, Texture2D sombra, float posX, float posY, int maxFrames);
void generate_dino_noAnimated(Texture2D dinosaurio, int maxFrames, Texture2D sombra, float posX, float posY);
void generte_rec(void);
/************************************************************************************************/
void UpdateMenu()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckMouseOnOption("Seleccionar nivel", 70, 0.532))
        {
            currentScene = SELECTGAME;
        }
        if (CheckMouseOnOption("Opciones", 70, 0.697))
        {
            currentScene = OPTIONS;
        }
        if (CheckMouseOnOption("Personaje", 70, 0.615))
        {
            currentScene = CUSTOME;
        }
        if (CheckMouseOnOption("Salir", 70, 0.78))
        {
            currentScene = EXIT;
        }
    }
}

void DrawMenu(Texture2D dinosaurio, int frame, float runningTime, float frameTime, Texture2D sombra)
{
    /**************************************** DISEñO DE MENU ********************************************/
    BeginDrawing();
    ClearBackground(BLACK);
    float fontSize = 80.0f + 10.0f * sinf(GetTime() * 8.0f);
    /*****************************************  RECTANGULO TRANSPARENTE ***********************************/
    Color select = {255, 200, 0, 255};
    generte_rec();
    /****************************************** DINOSAURIO  **********************************************/
    int maxFrames = 24;
    generate_dinos(frame, runningTime, frameTime, dinosaurio, sombra, 170.f, 600.f, maxFrames);
    /*****************************************************************************************************/
    if (CheckMouseOnOption("Selecciona un nivel", 70, 0.532))
    {
        DrawText("Selecciona un nivel", GetScreenWidth() / 2 - MeasureText("Selecciona un nivel", fontSize) / 2, GetScreenHeight() / 2, fontSize, select);
    }
    else
    {
        DrawText("Selecciona un nivel", GetScreenWidth() / 2 - MeasureText("Selecciona un nivel", 70) / 2, GetScreenHeight() / 2, 70, WHITE);
    }

    if (CheckMouseOnOption("Personaje", 70, 0.615))
    {
        DrawText("Personaje", GetScreenWidth() / 2 - MeasureText("Personaje", fontSize) / 2, GetScreenHeight() * 0.5905, fontSize, select);
    }
    else
    {
        DrawText("Personaje", GetScreenWidth() / 2 - MeasureText("Personaje", 70) / 2, GetScreenHeight() * 0.5905, 70, WHITE);
    }

    if (CheckMouseOnOption("Opciones", 70, 0.697))
    {
        DrawText("Opciones", GetScreenWidth() / 2 - MeasureText("Opciones", fontSize) / 2, GetScreenHeight() * 0.67545, fontSize, select);
    }
    else
    {
        DrawText("Opciones", GetScreenWidth() / 2 - MeasureText("Opciones", 70) / 2, GetScreenHeight() * 0.67545, 70, WHITE);
    }

    if (CheckMouseOnOption("Salir", 70, 0.78))
    {
        DrawText("Salir", GetScreenWidth() / 2 - MeasureText("Salir", fontSize) / 2, GetScreenHeight() * 0.755, fontSize, select);
    }
    else
    {
        DrawText("Salir", GetScreenWidth() / 2 - MeasureText("Salir", 70) / 2, GetScreenHeight() * 0.755, 70, WHITE);
    }
    EndDrawing();
}

void UpdateOptions()
{
    // Lógica de actualización de opciones
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckMouseOnOption("Regresar", 70, 0.78))
        {
            currentScene = START;
        }
    }
}

void DrawOptions(Texture2D dinosaurio, int frame, float runningTime, float frameTime, Texture2D sombra)
{
    // Lógica de dibujo de opciones
    BeginDrawing();
    ClearBackground(WHITE);
    Color select = {255, 200, 0, 255};
    float fontSize = 80.0f + 10.0f * sinf(GetTime() * 8.0f);
    /******************************* GENERAR RECTANGULO ******************************/
    generte_rec();
    /**************************** GENERAR DINOSAURIO  *******************************/
    generate_dinos(frame, runningTime, frameTime, dinosaurio, sombra, 1400.f, 580.f, 24);
    /********************************************************************************/
    if (CheckMouseOnOption("Pantalla completa", 70, 0.532))
    {
        DrawText("Pantalla completa", GetScreenWidth() / 2 - MeasureText("Pantalla completa", fontSize) / 2, GetScreenHeight() / 2, fontSize, select);
    }
    else
    {
        DrawText("Pantalla completa", GetScreenWidth() / 2 - MeasureText("Pantalla completa", 70) / 2, GetScreenHeight() / 2, 70, WHITE);
    }

    if (CheckMouseOnOption("Silenciar musica", 70, 0.615))
    {
        DrawText("Silenciar musica", GetScreenWidth() / 2 - MeasureText("Silenciar musica", fontSize) / 2, GetScreenHeight() * 0.5905, fontSize, WHITE);
    }
    else
    {
        DrawText("Silenciar musica", GetScreenWidth() / 2 - MeasureText("Silenciar musica", 70) / 2, GetScreenHeight() * 0.5905, 70, WHITE);
    }

    if (CheckMouseOnOption("Modo ventana", 70, 0.697))
    {
        DrawText("Modo ventana", GetScreenWidth() / 2 - MeasureText("Modo ventana", fontSize) / 2, GetScreenHeight() * 0.67545, fontSize, select);
    }
    else
    {
        DrawText("Modo ventana", GetScreenWidth() / 2 - MeasureText("Modo ventana", 70) / 2, GetScreenHeight() * 0.67545, 70, WHITE);
    }
    if (CheckMouseOnOption("Regresar", 70, 0.78))
    {
        DrawText("Regresar", GetScreenWidth() / 2 - MeasureText("Regresar", fontSize) / 2, GetScreenHeight() * 0.755, fontSize, select);
    }
    else
    {
        DrawText("Regresar", GetScreenWidth() / 2 - MeasureText("Regresar", 70) / 2, GetScreenHeight() * 0.755, 70, WHITE);
    }
    EndDrawing();
}

void UpdateGame()
{
}

void DrawGame()
{
}

void UpdateCustome()
{
    // Lógica de actualización de créditos
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckMouseOnOption("Regresar", 70, 0.85))
        {
            currentScene = START;
        }
    }
}

void DrawCustome(Texture2D dino, Texture2D dino2, Texture2D dino3, Texture2D sombra)
{
    BeginDrawing();
    ClearBackground(WHITE);
    Color select = {255, 200, 0, 255};
    float fontSize = 80.0f + 10.0f * sinf(GetTime() * 8.0f);
    DrawText("SELECCIONA UN PERSONAJE", GetScreenWidth() / 2 - MeasureText("SELECCIONA UN PERSONAJE", 100) / 2, GetScreenHeight() * 0.150, 100, BLACK);

    Rectangle rec = {(float)GetScreenWidth() / 2 - MeasureText("Regresar", 87) / 2, 850.f, 400, 100};
    Color rectangleColor = {0, 0, 0, 128};
    Color borde = {0, 0, 0, 220};
    DrawRectangleRoundedLines(rec, .30, .20, 13.f, borde);
    DrawRectangleRounded(rec, .30, .50, rectangleColor);
    if (CheckMouseOnOption("Regresar", 70, .85))
    {
        DrawText("Regresar", GetScreenWidth() / 2 - MeasureText("Regresar", fontSize) / 2, GetScreenHeight() * 0.800, fontSize, select);
    }
    else
    {
        DrawText("Regresar", GetScreenWidth() / 2 - MeasureText("Regresar", 70) / 2, GetScreenHeight() * 0.800, 70, WHITE);
    }
    /***********************  Dibujar dinosaurios  ***************************/
    generate_dino_noAnimated(dino, 24, sombra, (GetScreenWidth() / 2 - MeasureText("Regresar", 90) / 2) - 400, 500.f);
    generate_dino_noAnimated(dino2, 24, sombra, GetScreenWidth() / 2 - MeasureText("Regresar", 90) / 2, 500.f);
    generate_dino_noAnimated(dino3, 24, sombra, (GetScreenWidth() / 2 - MeasureText("Regresar", 90) / 2) + 400, 500.f);
    /************************************************************************/
    EndDrawing();
}

/***************************************** FUNCION PRINCIPAL *****************************************/

int main()
{
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Sumpy");
    /*******************************    MUSICA    **********************************/
    InitAudioDevice();
    Music music = LoadMusicStream("audios_danna\\menu_musica.mp3");
    Music level1 = LoadMusicStream("audios_danna\\LEVEL_.mp3");
    PlayMusicStream(music);
    PlayMusicStream(level1);
    /**************************** Background OPTIONS  ******************************/
    Image background_options = LoadImage("imagenes_danna\\background_verde.png");
    ImageResize(&background_options, GetScreenWidth(), GetScreenHeight());
    Texture2D texture_options = LoadTextureFromImage(background_options);
    UnloadImage(background_options);
    /**************************** Background START  ********************************/
    Image som = LoadImage("imagenes_danna\\sheets\\shadow_2.png");
    ImageResize(&som, 200, 200);
    Texture2D sombra = LoadTextureFromImage(som);
    Texture2D texture_logo = LoadTexture("imagenes_danna\\logo.png");
    Image background_start = LoadImage("imagenes_danna\\background_menu.png");
    ImageResize(&background_start, GetScreenWidth(), GetScreenHeight());
    Texture2D texture_start = LoadTextureFromImage(background_start);
    UnloadImage(som);
    UnloadImage(background_start);
    /***************************** Background CUSTOME **********************************/
    Image background_custome = LoadImage("imagenes_danna\\background_level2.png");
    ImageResize(&background_custome, GetScreenWidth(), GetScreenHeight());
    Texture2D texture_custome = LoadTextureFromImage(background_custome);
    UnloadImage(background_custome);
    /********************************** Dinosaurios ***********************************/
    Texture2D dino1 = LoadTexture("imagenes_danna\\sheets\\DinoSprites - doux.png");
    Texture2D dino2 = LoadTexture("imagenes_danna\\sheets\\DinoSprites - vita.png");
    Texture2D dino3 = LoadTexture("imagenes_danna\\sheets\\DinoSprites - mort.png");
    Texture2D dino4 = LoadTexture("imagenes_danna\\sheets\\DinoSprites - tard.png");
    /****************************  Movimiento dinosaurio ****************************/
    int frame{};
    float runningTime{};
    const float frameTime{1.f / 10.f};
    /*********************************************************************************/
    bool exitProgram = false;

    while (!WindowShouldClose() && !exitProgram)
    {
        mousePosition = GetMousePosition();
        /***************************************************** MOVIMIENTO ****************************************************/
        float dT = GetFrameTime();
        runningTime += dT;
        if (runningTime >= frameTime)
        {
            runningTime = 0.f;
            frame++;
            if (frame > 24)
            {
                frame = 0;
            }
        }
        /**********************************************************************************************************************/
        switch (currentScene)
        {
        case START:
            UpdateMusicStream(music);
            DrawTextureEx(texture_start, Vector2{(float)GetScreenWidth() / 2 - (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 - (float)GetScreenHeight() / 2}, 0, 1.0f, WHITE);
            DrawTextureEx(texture_logo, Vector2{0, 0}, 0, 1.0f, WHITE);
            UpdateMenu();
            DrawMenu(dino1, frame, runningTime, frameTime, sombra);
            break;
        case SELECTGAME:
            UpdateMusicStream(level1);
            UpdateGame();
            DrawGame();
            break;
        case OPTIONS:
            UpdateMusicStream(music);
            DrawTextureEx(texture_options, Vector2{(float)GetScreenWidth() / 2 - (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 - (float)GetScreenHeight() / 2}, 0, 1.0f, WHITE);
            UpdateOptions();
            DrawOptions(dino2, frame, runningTime, frameTime, sombra);
            break;
        case CUSTOME:
            UpdateMusicStream(music);
            DrawTextureEx(texture_custome, Vector2{(float)GetScreenWidth() / 2 - (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 - (float)GetScreenHeight() / 2}, 0, 1.0f, WHITE);
            UpdateCustome();
            DrawCustome(dino1, dino4, dino3, sombra);
            break;
        case EXIT:
            exitProgram = true;
            break;
        }
    }
    UnloadTexture(texture_custome);
    UnloadTexture(sombra);
    UnloadTexture(dino1);
    UnloadTexture(dino2);
    UnloadTexture(dino3);
    UnloadTexture(dino4);
    UnloadTexture(texture_logo);
    UnloadTexture(texture_start);
    UnloadTexture(texture_options);

    UnloadMusicStream(level1);
    UnloadMusicStream(music);
    CloseAudioDevice();

    CloseWindow();

    return 0;
}

/********************************** DESARROLLO DE FUNCIONES ************************************/

bool CheckMouseOnOption(const char *optionText, float fontSize, float position)
{
    Vector2 textSize = MeasureTextEx(GetFontDefault(), optionText, fontSize, 0);

    float centerX = GetScreenWidth() / 2 - textSize.x / 2;
    float centerY = GetScreenHeight() * position - textSize.y / 2;

    Rectangle optionBounds = {centerX, centerY, textSize.x, textSize.y};

    return CheckCollisionPointRec(mousePosition, optionBounds);
}

void generate_dino_noAnimated(Texture2D dinosaurio, int maxFrames, Texture2D sombra, float posX, float posY)
{
    Rectangle source = {0.f, 0.f, (float)dinosaurio.width / maxFrames, (float)dinosaurio.height};
    Rectangle dest = {posX, posY, 15 * (float)dinosaurio.width / maxFrames, 15 * (float)dinosaurio.height};
    Vector2 origin = {0.f, 0.f};
    DrawTexture(sombra, posX + 30, 640, WHITE);
    DrawTexturePro(dinosaurio, source, dest, origin, 0.f, WHITE);
}

void generate_dinos(int frame, float runningTime, float frameTime, Texture2D dinosaurio, Texture2D sombra, float posX, float posY, int maxFrames)
{
    Rectangle dest = {posX, posY, 10 * (float)dinosaurio.width / maxFrames, 10 * (float)dinosaurio.height};
    Rectangle source = {frame * (float)dinosaurio.width / maxFrames, 0.f, (float)dinosaurio.width / maxFrames, (float)dinosaurio.height};
    Vector2 origin = {0.f, 0.f};
    DrawTexture(sombra, posX, 640, WHITE);
    DrawTexturePro(dinosaurio, source, dest, origin, 0.f, WHITE);
}

void generte_rec()
{
    Rectangle rec = {(float)GetScreenWidth() / 2 - 390, (float)GetScreenHeight() / 2 - 40, 769, 399};
    Color rectangleColor = {0, 0, 0, 128};
    Color borde = {0, 0, 0, 220};
    DrawRectangleRoundedLines(rec, .30, .20, 13.f, borde);
    DrawRectangleRounded(rec, .30, .50, rectangleColor);
}