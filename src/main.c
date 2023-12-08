#include "raylib.h"
#include <math.h>
#include <stdio.h>

typedef enum
{
    LOGO,
    START,
    SELECTGAME,
    OPTIONS,
    CUSTOME,
    EXIT
} GameScene;

typedef enum
{
    WAITING,
    LEVEL1,
    LEVEL2,
} GameLevel;

GameLevel currentGameLevel = WAITING;
GameScene currentScene = START;
Vector2 mousePosition = {0};
/********************  Variables y constantes globales *************************/
Sound sound1;
Sound sound2;
bool waiting = true;
int selectDino = 0;
const int screenWidth = 1920;
const int screenHeight = 1080;
static bool musicPaused = false;
static bool soundPaused = true;

bool flagLoadTextures = false;
/********************************** PROTOTIPO DE FUNCIONES ************************************/
void logoLoading(Texture2D logoTexture, int frameCounter);
void UpdateSelectGame();
void MainSelectGame(Music menu);
void DrawSelectGame();
bool CheckMouseOnOptionY(const char *optionText, float fontSize, float position);
void generate_dinos(int frame, float runningTime, float frameTime, Texture2D dinosaurio, Texture2D sombra, float posX, float posY, int maxFrames, int op);
void generate_dino_noAnimated(Texture2D dinosaurio, int maxFrames, Texture2D sombra, float posX, float posY);
void generte_rec(void);
bool CheckMouseOnOptionXandY(const char *optionText, float fontSize, float positionX, float positionY);
void playsound(Sound sonido, bool flag);
/************************************************************************************************/
void UpdateMenu()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckMouseOnOptionY("Jugar", 70, 0.532))
        {
            playsound(sound1, soundPaused);
            currentScene = SELECTGAME;
        }
        if (CheckMouseOnOptionY("Opciones", 70, 0.697))
        {
            playsound(sound1, soundPaused);
            currentScene = OPTIONS;
        }
        if (CheckMouseOnOptionY("Personaje", 70, 0.615))
        {
            playsound(sound1, soundPaused);
            currentScene = CUSTOME;
        }
        if (CheckMouseOnOptionY("Salir", 70, 0.78))
        {
            playsound(sound1, soundPaused);
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
    generate_dinos(frame, runningTime, frameTime, dinosaurio, sombra, (float)screenWidth / 12, (float)screenHeight / 1.9, maxFrames, 1);
    /*****************************************************************************************************/
    if (CheckMouseOnOptionY("Jugar", 70, 0.532))
    {
        DrawText("Jugar", screenWidth / 2 - MeasureText("Jugar", fontSize) / 2, screenHeight / 2, fontSize, select);
    }
    else
    {
        DrawText("Jugar", screenWidth / 2 - MeasureText("Jugar", 70) / 2, screenHeight / 2, 70, WHITE);
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

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckMouseOnOptionY("Regresar", 70, 0.78))
        {
            playsound(sound1, soundPaused);
            currentScene = START;
        }
        if (CheckMouseOnOptionY("Musica", 70, 0.650))
        {
            playsound(sound1, soundPaused);
            if (musicPaused)
            {
                ResumeMusicStream(music);
                musicPaused = false;
            }
            else
            {
                PauseMusicStream(music);
                musicPaused = true;
            }
        }
        if (CheckMouseOnOptionY("Efectos", 70, 0.532))
        {
            if (soundPaused)
            {
                ResumeSound(sound1);
                soundPaused = false;
            }
            else
            {
                PauseSound(sound1);
                soundPaused = true;
                playsound(sound1, soundPaused);
            }
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
    generate_dinos(frame, runningTime, frameTime, dinosaurio, sombra, screenWidth / 1.35, screenHeight / 2, 24, 1);
    /********************************************************************************/
    if (CheckMouseOnOptionY("Efectos", 70, 0.532))
    {
        DrawText("Efectos", screenWidth / 2.099 - MeasureText("Efectos", fontSize) / 2, screenHeight / 2, fontSize, select);
    }
    else
    {
        DrawText("Efectos", screenWidth / 2.099 - MeasureText("Efectos", 70) / 2, screenHeight / 2, 70, WHITE);
    }
    if (soundPaused)
    {
        DrawText("ON", screenWidth / 1.559 - MeasureText("Efectos", 70) / 2, screenHeight / 2, 70, WHITE);
    }
    else
    {
        DrawText("OFF", screenWidth / 1.559 - MeasureText("Efectos", 70) / 2, screenHeight / 2, 70, select);
    }

    if (CheckMouseOnOptionY("Musica", 75, 0.655))
    {
        DrawText("Musica", screenWidth / 2.1 - MeasureText("Musica", fontSize) / 2, screenHeight * 0.630, fontSize, WHITE);
    }
    else
    {
        DrawText("Musica", screenWidth / 2.1 - MeasureText("Musica", 70) / 2, screenHeight * 0.630, 70, WHITE);
    }
    if (musicPaused)
    {
        DrawText("OFF", screenWidth / 1.6 - MeasureText("Musica", 70) / 2, screenHeight * 0.630, 70, select);
    }
    else
    {
        DrawText("ON", screenWidth / 1.6 - MeasureText("Musica", 70) / 2, screenHeight * 0.630, 70, WHITE);
    }

    // DrawText(musicPaused ? "OFF" : "ON", screenWidth / 1.6 - MeasureText("Musica", 70) / 2, screenHeight * 0.630, 70, select);

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
            playsound(sound1, soundPaused);
            currentScene = START;
            mostrarMensaje = false;
        }
        if (CheckMouseOnOptionXandY("Espy", 70, 0.5, 0.43)) // verifica que dinosaurio escogio
        {
            playsound(sound2, soundPaused);
            selectDino = 1;
            mostrarMensaje = true;
        }
        if (CheckMouseOnOptionXandY("Nacky", 70, 1, 0.43))
        {
            playsound(sound2, soundPaused);
            selectDino = 2;
            mostrarMensaje = true;
        }
        if (CheckMouseOnOptionXandY("Juan", 80, 1.4, 0.43))
        {
            playsound(sound2, soundPaused);
            selectDino = 3;
            mostrarMensaje = true;
        }
    }

    if (mostrarMensaje)
    {
        DrawText("LISTO", screenWidth / 2.35 - MeasureText("LISTO", fontSize) / 2, screenHeight / 4, fontSize * 2.0f, BLACK);
    }
    else
    {
        DrawText("SELECCIONA UN PERSONAJE", screenWidth / 2 - MeasureText("SELECCIONA UN PERSONAJE", 100) / 2, screenHeight * 0.150, 100, BLACK);
    }
}

void DrawCustome(Texture2D dino, Texture2D dino2, Texture2D dino3, Texture2D sombra, int frame, float runningTime, float frameTime)
{
    BeginDrawing();
    ClearBackground(WHITE);
    Color select = {255, 200, 0, 255};
    float fontSize = 80.0f + 10.0f * sinf(GetTime() * 8.0f);
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
        DrawText("Espy", screenWidth / 2 - MeasureText("Espy", 70) / 0.3, screenHeight / 2.5, 70, select);
        generate_dinos(frame, runningTime, frameTime, dino, sombra, (screenWidth / 2 - MeasureText("Regresar", 90) / 2) - 400, 500.f, 24, 0);
    }
    else
    {
        DrawText("Espy", screenWidth / 2 - MeasureText("Espy", 70) / 0.3, screenHeight / 2.5, 70, WHITE);
        generate_dino_noAnimated(dino, 24, sombra, (screenWidth / 2 - MeasureText("Regresar", 90) / 2) - 400, 500.f);
    }

    if (CheckMouseOnOptionXandY("Nacky", 70, 1, 0.43))
    {
        DrawText("Nacky", screenWidth / 2 - MeasureText("Nacky", 70) / 2, screenHeight / 2.5, 70, select);
        generate_dinos(frame, runningTime, frameTime, dino2, sombra, screenWidth / 2 - MeasureText("Regresar", 90) / 2, 500.f, 24, 0);
    }
    else
    {
        DrawText("Nacky", screenWidth / 2 - MeasureText("Nacky", 70) / 2, screenHeight / 2.5, 70, WHITE);
        generate_dino_noAnimated(dino2, 24, sombra, screenWidth / 2 - MeasureText("Regresar", 90) / 2, 500.f);
    }
    if (CheckMouseOnOptionXandY("Juan", 80, 1.4, 0.43))
    {
        DrawText("Juan", screenWidth / 1.4 - MeasureText("Juan", 70) / 2, screenHeight / 2.5, 70, select);
        generate_dinos(frame, runningTime, frameTime, dino3, sombra, (screenWidth / 2 - MeasureText("Regresar", 90) / 2) + 400, 500, 24, 0);
    }
    else
    {
        DrawText("Juan", screenWidth / 1.4 - MeasureText("Juan", 70) / 2, screenHeight / 2.5, 70, WHITE);
        generate_dino_noAnimated(dino3, 24, sombra, (screenWidth / 2 - MeasureText("Regresar", 90) / 2) + 400, 500.f);
    }
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
    /*********************************** SONIDOS ***********************************/
    sound1 = LoadSound("audios_danna\\sonido-menu.wav");
    sound2 = LoadSound("audios_danna\\selectDino.mp3");
    /**************************** Background OPTIONS  ******************************/
    Image background_options = LoadImage("imagenes_danna\\background_options.png");
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
    int frameCounter = 0;
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
        case LOGO:
            frameCounter++;
            logoLoading(texture_logo, frameCounter); // NO MODIFICAR ESTA FUNCIÓN, SOLUCIONARÉ ALGUNOS PROBLEMAS.
            break;
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
            DrawCustome(dino1, dino4, dino3, sombra, frame, runningTime, frameTime);
            break;
        case SELECTGAME:
            PauseMusicStream(music);
            MainSelectGame(level1);
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

    UnloadSound(sound1);
    UnloadMusicStream(level1);
    UnloadMusicStream(music);
    CloseAudioDevice();

    CloseWindow();

    return 0;
}
/********************************** DESARROLLO DE FUNCIONES ************************************/

//***************************** LOGO LOADING *****************************
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

        currentScene = START;
    }

    BeginDrawing();
    ClearBackground(GREEN);
    DrawTexturePro(logoTexture, (Rectangle){0, 0, logoTexture.width, logoTexture.height},
                   (Rectangle){screenWidth / 2 - logoTexture.width / 2, screenHeight / 2 - logoTexture.height / 2,
                               logoTexture.width, logoTexture.height},
                   (Vector2){0, 0}, 0.0f, Fade(WHITE, logoOpacity));
    EndDrawing();
}

//********************************** SELECCIONAR NIVEL FUNCIONES ****************************************
void UpdateSelectGame()
{
    Rectangle LEVEL1_RECT = {screenWidth / 4, screenHeight / 2, 300, 300};
    Rectangle LEVEL2_RECT = {screenWidth / 1.79, screenHeight / 2, 300, 300};
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

void MainSelectGame(Music menu)
{
    // AQUI PUEDES MODIFICAR TODO LO RELACIONADO CON EL SELECCIONAR NIVEL (DECORARLO). LOS RENCTÁNGULOS SON GUÍAS. PARA MOPDIFICAR LA POSICIÓN, DEBEN COINCIDIR LOS VALORES
    // DEL RECTANGULO DE ESTA FUNCIÓN LAS DE RECTANGULO EN LA FUNCION "UpdateSelectGame()". RECUERDA VER QUE DATOS TIENE LA ESTRUCTURA RECTANGLE.
    /************************ Background SELECTGAME ******************************/
    Image background_selectgame = LoadImage("imagenes_danna\\background_selectgame.png");
    ImageResize(&background_selectgame, screenWidth, screenHeight);
    Texture2D texture_selectgame = LoadTextureFromImage(background_selectgame);
    UnloadImage(background_selectgame);
    Vector2 postionTexture = {(float)screenWidth / 2 - (float)screenWidth / 2, (float)screenHeight / 2 - (float)screenHeight / 2};
    /******* textura selecciona un nivel*******/
    Texture2D selecNivel = LoadTexture("imagenes_danna\\SELECCIONA_UN_NIVEL.png");
    Vector2 positionZero = {screenWidth / 2 - selecNivel.width / 2, screenHeight / 2 - selecNivel.height * 1.8};
    do
    {
        switch (currentGameLevel)
        {
        case WAITING:
            DrawTextureEx(texture_selectgame, postionTexture, 0, 1.0f, WHITE); // fondo
            DrawTextureEx(selecNivel, positionZero, 0, 1.0f, WHITE);           // imagen selecciona un nivel
            UpdateMusicStream(menu);
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
    } while (!WindowShouldClose());
    UnloadTexture(selecNivel);
    UnloadTexture(texture_selectgame);
}

void DrawSelectGame()
{
    Rectangle LEVEL1_RECT = {screenWidth / 4, screenHeight / 2, 300, 300};
    Rectangle LEVEL2_RECT = {screenWidth / 1.79, screenHeight / 2, 300, 300};
    BeginDrawing();
    ClearBackground(PURPLE);
    DrawRectangleRec(LEVEL1_RECT, WHITE);
    DrawRectangleRec(LEVEL2_RECT, BLACK);

    EndDrawing();
}

/********************************** FUNCIONES ************************************/

void playsound(Sound sonido, bool flag)
{
    if (flag)
    {
        PlaySound(sonido);
    }
}

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

void generate_dinos(int frame, float runningTime, float frameTime, Texture2D dinosaurio, Texture2D sombra, float posX, float posY, int maxFrames, int op)
{
    Rectangle dest = {posX, posY, 15 * (float)dinosaurio.width / maxFrames, 15 * (float)dinosaurio.height};
    Rectangle source = {frame * (float)dinosaurio.width / maxFrames, 0.f, (float)dinosaurio.width / maxFrames, (float)dinosaurio.height};
    Vector2 origin = {0.f, 0.f};
    if (op)
    {
        DrawTexture(sombra, posX + 115, posY / 0.800, WHITE);
    }
    else
    {
        DrawTexture(sombra, posX + 30, 640, WHITE);
    }
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