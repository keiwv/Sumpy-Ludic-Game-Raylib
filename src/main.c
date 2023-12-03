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
/********************  Variables y constantes globales *************************/
bool waiting = true;
int selectDino = 0;
const int screenWidth = 1920;
const int screenHeight = 1080;
/********************************** PROTOTIPO DE FUNCIONES ************************************/
bool CheckMouseOnOptionY(const char *optionText, float fontSize, float position);
void generate_dinos(int frame, float runningTime, float frameTime, Texture2D dinosaurio, Texture2D sombra, float posX, float posY, int maxFrames);
void generate_dino_noAnimated(Texture2D dinosaurio, int maxFrames, Texture2D sombra, float posX, float posY);
void generte_rec(void);
bool CheckMouseOnOptionXandY(const char *optionText, float fontSize, float positionX, float positionY);
/************************************************************************************************/
void UpdateMenu()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckMouseOnOptionY("Seleccionar nivel", 70, 0.532))
        {
            currentScene = SELECTGAME;
        }
        if (CheckMouseOnOptionY("Opciones", 70, 0.697))
        {
            currentScene = OPTIONS;
        }
        if (CheckMouseOnOptionY("Personaje", 70, 0.615))
        {
            currentScene = CUSTOME;
        }
        if (CheckMouseOnOptionY("Salir", 70, 0.78))
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
    generate_dinos(frame, runningTime, frameTime, dinosaurio, sombra, (float)screenWidth / 8, (float)screenHeight / 1.6, maxFrames);
    /*****************************************************************************************************/
    if (CheckMouseOnOptionY("Selecciona un nivel", 70, 0.532))
    {
        DrawText("Selecciona un nivel", screenWidth / 2 - MeasureText("Selecciona un nivel", fontSize) / 2, screenHeight / 2, fontSize, select);
    }
    else
    {
        DrawText("Selecciona un nivel", screenWidth / 2 - MeasureText("Selecciona un nivel", 70) / 2, screenHeight / 2, 70, WHITE);
    }

    if (CheckMouseOnOptionY("Personajes", 70, 0.615))
    {
        DrawText("Personajes", screenWidth / 2 - MeasureText("Personajes", fontSize) / 2, screenHeight * 0.5905, fontSize, select);
    }
    else
    {
        DrawText("Personajes", screenWidth / 2 - MeasureText("Personajes", 70) / 2, screenHeight * 0.5905, 70, WHITE);
    }

    if (CheckMouseOnOptionY("Opciones", 70, 0.697))
    {
        DrawText("Opciones", screenWidth / 2 - MeasureText("Opciones", fontSize) / 2, screenHeight * 0.67545, fontSize, select);
    }
    else
    {
        DrawText("Opciones", screenWidth / 2 - MeasureText("Opciones", 70) / 2, screenHeight * 0.67545, 70, WHITE);
    }

    if (CheckMouseOnOptionY("Salir", 70, 0.78))
    {
        DrawText("Salir", screenWidth / 2 - MeasureText("Salir", fontSize) / 2, screenHeight * 0.755, fontSize, select);
    }
    else
    {
        DrawText("Salir", screenWidth / 2 - MeasureText("Salir", 70) / 2, screenHeight * 0.755, 70, WHITE);
    }
    EndDrawing();
}

void UpdateOptions(Music music)
{
    // Lógica de actualización de opciones
    bool stopMusic = false;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckMouseOnOptionY("Regresar", 70, 0.78))
        {
            currentScene = START;
        }
        if (CheckMouseOnOptionY("Silenciar musica", 70, 0.615))
        {
            if (!stopMusic)
            {
                PauseMusicStream(music);
            }
        }
        if (CheckMouseOnOptionY("Personaje", 70, 0.697))
        {
            ResumeMusicStream(music);
            stopMusic = true;
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
    generate_dinos(frame, runningTime, frameTime, dinosaurio, sombra, screenWidth / 1.35, screenHeight / 2, 24);
    /********************************************************************************/
    if (CheckMouseOnOptionY("Efectos de sonido", 70, 0.532))
    {
        DrawText("Efectos de sonido", screenWidth / 2 - MeasureText("Efectos de sonido", fontSize) / 2, screenHeight / 2, fontSize, select);
    }
    else
    {
        DrawText("Efectos de sonido", screenWidth / 2 - MeasureText("Efectos de sonido", 70) / 2, screenHeight / 2, 70, WHITE);
    }

    if (CheckMouseOnOptionY("Silenciar musica", 70, 0.615))
    {
        DrawText("Silenciar musica", screenWidth / 2 - MeasureText("Silenciar musica", fontSize) / 2, screenHeight * 0.5905, fontSize, WHITE);
    }
    else
    {
        DrawText("Silenciar musica", screenWidth / 2 - MeasureText("Silenciar musica", 70) / 2, screenHeight * 0.5905, 70, WHITE);
    }

    if (CheckMouseOnOptionY("Activar musica", 70, 0.697))
    {
        DrawText("Activar musica", screenWidth / 2 - MeasureText("Activar musica", fontSize) / 2, screenHeight * 0.67545, fontSize, select);
    }
    else
    {
        DrawText("Activar musica", screenWidth / 2 - MeasureText("Activar musica", 70) / 2, screenHeight * 0.67545, 70, WHITE);
    }
    if (CheckMouseOnOptionY("Regresar", 70, 0.78))
    {
        DrawText("Regresar", screenWidth / 2 - MeasureText("Regresar", fontSize) / 2, screenHeight * 0.755, fontSize, select);
    }
    else
    {
        DrawText("Regresar", screenWidth / 2 - MeasureText("Regresar", 70) / 2, screenHeight * 0.755, 70, WHITE);
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
    float fontSize = 80.0f + 10.0f * sinf(GetTime() * 8.0f);

    static bool mostrarMensaje = false;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckMouseOnOptionY("Regresar", 70, 0.84))
        {
            currentScene = START;
            mostrarMensaje = false;
        }
        if (/* condition */)
        {
            /* code */
        }
        else
        {
            if (CheckMouseOnOptionXandY("Espy", 70, 0.5, 0.43)) // verifica que dinosaurio escogio
            {
                selectDino = 1;
                mostrarMensaje = true;
            }
            if (CheckMouseOnOptionXandY("Nacky", 70, 1, 0.43))
            {
                selectDino = 2;
                mostrarMensaje = true;
            }
            if (CheckMouseOnOptionXandY("Juan", 80, 1.4, 0.43))
            {
                selectDino = 3;
                mostrarMensaje = true;
            }
        }
    }

    if (mostrarMensaje)
    {
        DrawText("LISTO", screenWidth / 2.35 - MeasureText("LISTO", fontSize) / 2, screenHeight / 4, fontSize * 2.0f, BLACK);
    }
}

void DrawCustome(Texture2D dino, Texture2D dino2, Texture2D dino3, Texture2D sombra)
{
    BeginDrawing();
    ClearBackground(WHITE);
    Color select = {255, 200, 0, 255};
    float fontSize = 80.0f + 10.0f * sinf(GetTime() * 8.0f);
    DrawText("SELECCIONA UN PERSONAJE", screenWidth / 2 - MeasureText("SELECCIONA UN PERSONAJE", 100) / 2, screenHeight * 0.150, 100, BLACK);
    /******************************   rectangulo negro   **********************************/
    Rectangle rec = {(float)screenWidth / 2 - MeasureText("Regresar", 87) / 2, screenHeight * 0.79, 400, 100};
    Color rectangleColor = {0, 0, 0, 128};
    Color borde = {0, 0, 0, 220};
    DrawRectangleRoundedLines(rec, .30, .20, 13.f, borde);
    DrawRectangleRounded(rec, .30, .50, rectangleColor);
    /***************************     animar texto      ***************************/
    if (CheckMouseOnOptionY("Regresar", 70, 0.84))
    {
        DrawText("Regresar", screenWidth / 2 - MeasureText("Regresar", fontSize) / 2, screenHeight * 0.800, fontSize, select);
    }
    else
    {
        DrawText("Regresar", screenWidth / 2 - MeasureText("Regresar", 70) / 2, screenHeight * 0.800, 70, WHITE);
    }
    /**********************************  nombres de dinosaurios  ****************************************/
    // X    Y
    if (CheckMouseOnOptionXandY("Espy", 70, 0.5, 0.43))
    {
        DrawText("Espy", screenWidth / 2 - MeasureText("Espy", 70) / 0.3, screenHeight / 2.5, fontSize, select);
    }
    else
    {
        DrawText("Espy", screenWidth / 2 - MeasureText("Espy", 70) / 0.3, screenHeight / 2.5, 70, WHITE);
    }

    if (CheckMouseOnOptionXandY("Nacky", 70, 1, 0.43))
    {
        DrawText("Nacky", screenWidth / 2 - MeasureText("Nacky", 70) / 2, screenHeight / 2.5, fontSize, select);
    }
    else
    {
        DrawText("Nacky", screenWidth / 2 - MeasureText("Nacky", 70) / 2, screenHeight / 2.5, 70, WHITE);
    }
    if (CheckMouseOnOptionXandY("Juan", 80, 1.4, 0.43))
    {
        DrawText("Juan", screenWidth / 1.4 - MeasureText("Juan", 70) / 2, screenHeight / 2.5, fontSize, select);
    }
    else
    {
        DrawText("Juan", screenWidth / 1.4 - MeasureText("Juan", 70) / 2, screenHeight / 2.5, 70, WHITE);
    }
    /***********************  Dibujar dinosaurios  ***************************/
    generate_dino_noAnimated(dino, 24, sombra, (screenWidth / 2 - MeasureText("Regresar", 90) / 2) - 400, 500.f);
    generate_dino_noAnimated(dino2, 24, sombra, screenWidth / 2 - MeasureText("Regresar", 90) / 2, 500.f);
    generate_dino_noAnimated(dino3, 24, sombra, (screenWidth / 2 - MeasureText("Regresar", 90) / 2) + 400, 500.f);
    /************************************************************************/
    EndDrawing();
}

/***************************************** FUNCION PRINCIPAL *****************************************/

int main()
{
    InitWindow(screenWidth, screenHeight, "Sumpy");
    Image icon = LoadImage("imagenes_danna\\icon.png");
    SetWindowIcon(icon);
    /*******************************    MUSICA    **********************************/
    InitAudioDevice();
    Music music = LoadMusicStream("audios_danna\\menu_musica.mp3");
    Music level1 = LoadMusicStream("audios_danna\\LEVEL_.mp3");
    PlayMusicStream(music);
    PlayMusicStream(level1);
    /**************************** Background OPTIONS  ******************************/
    Image background_options = LoadImage("imagenes_danna\\background_verde.png");
    ImageResize(&background_options, screenWidth, screenHeight);
    Texture2D texture_options = LoadTextureFromImage(background_options);
    UnloadImage(background_options);
    /**************************** Background START  ********************************/
    Image som = LoadImage("imagenes_danna\\sheets\\shadow_2.png");
    ImageResize(&som, 200, 200);
    Texture2D sombra = LoadTextureFromImage(som);
    Texture2D texture_logo = LoadTexture("imagenes_danna\\logo.png");
    Image background_start = LoadImage("imagenes_danna\\background_menu.png");
    ImageResize(&background_start, screenWidth, screenHeight);
    Texture2D texture_start = LoadTextureFromImage(background_start);
    UnloadImage(som);
    UnloadImage(background_start);
    /***************************** Background CUSTOME **********************************/
    Image background_custome = LoadImage("imagenes_danna\\background_level2.png");
    ImageResize(&background_custome, screenWidth, screenHeight);
    Texture2D texture_custome = LoadTextureFromImage(background_custome);
    UnloadImage(background_custome);
    /********************************** Dinosaurios ***********************************/
    Texture2D dino1 = LoadTexture("imagenes_danna\\sheets\\DinoSprites - doux.png");
    Texture2D dino2 = LoadTexture("imagenes_danna\\sheets\\DinoSprites - vita.png");
    Texture2D dino3 = LoadTexture("imagenes_danna\\sheets\\DinoSprites - mort.png");
    Texture2D dino4 = LoadTexture("imagenes_danna\\sheets\\DinoSprites - tard.png");
    /****************************  Movimiento dinosaurio ****************************/
    int frame = 0;
    float runningTime = 0;
    const float frameTime = 1.0f / 10.0f;
    /*********************************************************************************/
    bool exitProgram = false;

    Vector2 postionTexture = {(float)screenWidth / 2 - (float)screenWidth / 2, (float)screenHeight / 2 - (float)screenHeight / 2};
    Vector2 positionZero = {screenWidth / 2 - texture_logo.width / 2, screenHeight / 2 - texture_logo.height * 1.4};
    float dT;

    while (!WindowShouldClose() && !exitProgram)
    {
        mousePosition = GetMousePosition();
        /***************************************************** MOVIMIENTO ****************************************************/
        dT = GetFrameTime();
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
            DrawTextureEx(texture_start, postionTexture, 0, 1.0f, WHITE);
            DrawTextureEx(texture_logo, positionZero, 0, 1.0f, WHITE);
            UpdateMenu();
            DrawMenu(dino1, frame, runningTime, frameTime, sombra);
            break;
        case OPTIONS:
            UpdateMusicStream(music);
            DrawTextureEx(texture_options, postionTexture, 0, 1.0f, WHITE);
            UpdateOptions(music);
            DrawOptions(dino2, frame, runningTime, frameTime, sombra);
            break;
        case CUSTOME:
            UpdateMusicStream(music);
            DrawTextureEx(texture_custome, postionTexture, 0, 1.0f, WHITE);
            UpdateCustome();
            DrawCustome(dino1, dino4, dino3, sombra);
        case SELECTGAME:
            UpdateMusicStream(level1);
            UpdateGame();
            DrawGame();
            break;
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

bool CheckMouseOnOptionY(const char *optionText, float fontSize, float position)
{
    Vector2 textSize = MeasureTextEx(GetFontDefault(), optionText, fontSize, 0);

    float centerX = screenWidth / 2 - textSize.x / 2;
    float centerY = screenHeight * position - textSize.y / 2;

    Rectangle optionBounds = {centerX, centerY, textSize.x, textSize.y};
    // DrawRectangle(centerX, centerY, textSize.x, textSize.y, GREEN);

    return CheckCollisionPointRec(mousePosition, optionBounds);
}

bool CheckMouseOnOptionXandY(const char *optionText, float fontSize, float positionX, float positionY)
{
    Vector2 textSize = MeasureTextEx(GetFontDefault(), optionText, fontSize, 0);

    float centerX = screenWidth * positionX / 2 - textSize.x / 2;
    float centerY = screenHeight * positionY - textSize.y / 2;

    Rectangle optionBounds = {centerX, centerY, textSize.x, textSize.y};
    // DrawRectangle(centerX, centerY, textSize.x, textSize.y, GREEN);

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
    DrawTexture(sombra, posX, posY / 0.950, WHITE);
    DrawTexturePro(dinosaurio, source, dest, origin, 0.f, WHITE);
}

void generte_rec()
{
    float centerX = screenWidth / 2.01f;
    float centerY = screenHeight / 1.516f;

    float rectWidth = screenWidth / 2.5f;
    float rectHeight = screenHeight / 2.89f;

    Rectangle rec = {centerX - rectWidth / 2.0f, centerY - rectHeight / 2.0f, rectWidth, rectHeight};
    Color rectangleColor = {0, 0, 0, 128};
    Color border = {0, 0, 0, 220};

    DrawRectangleRoundedLines(rec, .30, .20, 13.f, border);

    DrawRectangleRounded(rec, .30, .50, rectangleColor);
}