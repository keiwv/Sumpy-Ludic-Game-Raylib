#include "raylib.h"
#include "math.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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
    LEAVE
} GameLevel;

GameLevel currentGameLevel = WAITING;
GameScene currentScene = START;
Vector2 mousePosition = {0};
/********************  VARIABLES Y CONSTANTES GLOBALES *************************/
Sound sound1;
Sound sound2;
Sound sound3;
bool waiting = true;
int selectDino = 0;
const int screenWidth = 1920;
const int screenHeight = 1080;
static bool musicPaused = false;
static bool soundPaused = true;
bool flagLoadTextures = false;
/*************** JUEGO GLOBALES IMPORTANTES**************************/
#define MATRIX_WIDTH 9
#define MATRIX_HEIGHT 7
#define RECTANGLE_SIZE 100
bool pressedButtonNo1Flag = 0;
bool pressedButtonNo2Flag = 0;
Vector2 getMouseCollision = {0};
Vector2 isMousePressedCollision[2] = {0};
bool guessedRight = false;
/********************************** PROTOTIPO DE FUNCIONES ************************************/
/*      ************************ MANEJO DE ESCENARIOS Y JUEGO ***********************/
void logoLoading(Texture2D logoTexture, int frameCounter);

void UpdateMenu();
void DrawMenu(Texture2D dinosaurio, int frame, float runningTime, float frameTime, Texture2D sombra, Music music, Font fuente);

void UpdateOptions(Music music, Music level1);
void DrawOptions(Texture2D dinosaurio, int frame, float runningTime, float frameTime, Texture2D sombra, Music music, Font fuente);

void UpdateSelectGame(Sound sonido, Sound sonido2);
void MainSelectGame(Music menu, Sound sonido, Sound sonido2, Texture2D espy, Texture2D nacky, Texture2D juan, Texture2D sombra);

void DrawSelectGame(Texture2D txt_leve1, Texture2D txt_level2, Music musica, Texture2D espy, Texture2D nacky, Texture2D juan, Texture2D sombra, int frame, float runningTime, float frameTime);

/*        ************************ NIVELES **************************************         */
void DrawGameLv1(int gameMatrix[][MATRIX_WIDTH], int squareMatrixColor[][MATRIX_WIDTH], Color preColors[]);
bool UpdateGameLv1(int gameMatrix[][MATRIX_WIDTH], Vector2 position[], int userInput);
//******************************   DINOSAURIOS   *************************************
void DrawCustome(Texture2D dino, Texture2D dino2, Texture2D dino3, Texture2D sombra, int frame, float runningTime, float frameTime, Music music, Font fuente);
void UpdateCustome(Texture2D selectPers);

void generate_dinos(int frame, float runningTime, float frameTime, Texture2D dinosaurio, Texture2D sombra, float posX, float posY, int maxFrames, int op);
void generate_dino_noAnimated(Texture2D dinosaurio, int maxFrames, Texture2D sombra, float posX, float posY);

//*************** FUNCIONES DE ANIMACION PARA EL JUEGO ******************************
void drawMatrixCollision(Rectangle enlargedRect, int gameMatrix[][MATRIX_WIDTH], int squareMatrixColor[][MATRIX_WIDTH], Color preColors[]);
void drawMatrixSelected(Rectangle number1, int gameMatrix[][MATRIX_WIDTH], int matrixX, int matrixY, int valueX, int valueY, char number[], Color preColors[], int colorNumber);
bool modifyMatrix(int gameMatrix[][MATRIX_WIDTH], int squareMatrixColor[][MATRIX_WIDTH], Color preColors[3]);
double easeInOutCirc(double x);

//**************************** FUNCIONES EXTRAS *************************
int getRandomNumber(int ri, int rf);
void texto_sencillo(char texto[], float posicion, float font, float x, float y, bool mult, Font fonT);
void playsound(Sound sonido, bool flag);
bool CheckMouseOnOptionXandY(const char *optionText, float fontSize, float positionX, float positionY);
bool CheckMouseOnOptionY(char optionText[], float fontSize, float position);
void generte_rec(void);

/************************************* FUNCIÓN PRINCIPAL *************************/
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
    sound3 = LoadSound("audios_danna\\selectLevel.mp3");
    /************************ FUENTES ****************************/
    Font fonT = LoadFont("fuentes_danna\\Pixellari.ttf");
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
    Texture2D selectPers = LoadTexture("imagenes_danna\\SELECCIONA UN PERSONAJE (1).png");
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

    srand(time(NULL));
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
            DrawTextureEx(texture_start, postionTexture, 0, 1.0f, WHITE);
            DrawTextureEx(texture_logo, positionZero, 0, 1.0f, WHITE);
            UpdateMenu();
            DrawMenu(dino1, frame, runningTime, frameTime, sombra, music, fonT);
            break;
        case OPTIONS:
            DrawTextureEx(texture_options, postionTexture, 0, 1.0f, WHITE);
            UpdateOptions(music, level1);
            DrawOptions(dino2, frame, runningTime, frameTime, sombra, music, fonT);
            break;
        case CUSTOME:
            DrawTextureEx(texture_custome, postionTexture, 0, 1.0f, WHITE);
            UpdateCustome(selectPers);
            DrawCustome(dino1, dino4, dino3, sombra, frame, runningTime, frameTime, music, fonT);
            break;
        case SELECTGAME:
            currentGameLevel = WAITING;
            MainSelectGame(level1, sound1, sound3, dino1, dino4, dino3, sombra);
            PlayMusicStream(music);
            currentScene = START;
            break;
        case EXIT:
            exitProgram = true;
            break;
        }
    }
    UnloadFont(fonT);
    UnloadTexture(selectPers);
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

/*      ************************ MANEJO DE ESCENARIOS ***********************/
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

void DrawMenu(Texture2D dinosaurio, int frame, float runningTime, float frameTime, Texture2D sombra, Music music, Font fuente)
{
    /**************************************** DISEñO DE MENU ********************************************/
    BeginDrawing();
    ClearBackground(BLACK);
    if (!musicPaused)
    {
        UpdateMusicStream(music);
    }
    /*****************************************  RECTANGULO TRANSPARENTE ***********************************/
    generte_rec();
    /****************************************** DINOSAURIO  **********************************************/
    int maxFrames = 24;
    generate_dinos(frame, runningTime, frameTime, dinosaurio, sombra, (float)screenWidth / 12, (float)screenHeight / 1.9, maxFrames, 1);
    /******************************************** Dibujar mensajes **************************************************/
    texto_sencillo("Jugar", 0.532, 70, 2, 2, false, fuente);
    texto_sencillo("Personajes", 0.615, 70, 2, 0.5905, true, fuente);
    texto_sencillo("Opciones", 0.697, 70, 2, 0.67545, true, fuente);
    texto_sencillo("Salir", 0.78, 70, 2, 0.755, true, fuente);
    EndDrawing();
}
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

void UpdateOptions(Music music, Music level1)
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
                ResumeMusicStream(level1);
                ResumeMusicStream(music);
                musicPaused = false;
            }
            else
            {
                PauseMusicStream(level1);
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
void DrawOptions(Texture2D dinosaurio, int frame, float runningTime, float frameTime, Texture2D sombra, Music music, Font fuente)
{
    // Lógica de dibujo de opciones
    Color colo1 = {207, 207, 207, 255};

    BeginDrawing();
    ClearBackground(WHITE);
    if (!musicPaused)
    {
        UpdateMusicStream(music);
    }
    Color select = {255, 200, 0, 255};
    /******************************* GENERAR RECTANGULO ******************************/
    generte_rec();
    /**************************** GENERAR DINOSAURIO  *******************************/
    generate_dinos(frame, runningTime, frameTime, dinosaurio, sombra, screenWidth / 1.35, screenHeight / 2, 24, 1);
    /********************************************************************************/
    texto_sencillo("Efectos", 0.532, 70, 2.1, 2, false, fuente);
    if (soundPaused)
    {
        DrawText("ON", screenWidth / 1.559 - MeasureText("Efectos", 70) / 2, screenHeight / 1.96, 60, colo1);
    }
    else
    {
        DrawText("OFF", screenWidth / 1.559 - MeasureText("Efectos", 70) / 2, screenHeight / 1.96, 60, select);
    }
    texto_sencillo("Musica", 0.655, 70, 2.1, 0.630, true, fuente);
    if (musicPaused)
    {
        DrawText("OFF", screenWidth / 1.6 - MeasureText("Musica", 70) / 2, screenHeight * 0.640, 60, select);
    }
    else
    {
        DrawText("ON", screenWidth / 1.6 - MeasureText("Musica", 70) / 2, screenHeight * 0.640, 60, colo1);
    }
    texto_sencillo("Regresar", 0.78, 70, 2, 0.755, true, fuente);

    EndDrawing();
}

void UpdateSelectGame(Sound sonido, Sound sonido2)
{
    Vector2 mousePosition = GetMousePosition();
    Rectangle LEVEL1_RECT = {screenWidth / 3.5, screenHeight / 2, 235, 250};
    Rectangle LEVEL2_RECT = {screenWidth / 1.75, screenHeight / 2, 225, 250};

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointRec(mousePosition, LEVEL1_RECT))
        {
            playsound(sonido2, soundPaused);
            currentGameLevel = LEVEL1;
        }
        if (CheckCollisionPointRec(mousePosition, LEVEL2_RECT))
        {
            playsound(sonido2, soundPaused);
            currentGameLevel = LEVEL2;
        }
        if (CheckMouseOnOptionY("Regresar", 75, 0.920))
        {
            playsound(sonido, soundPaused);
            currentGameLevel = LEAVE;
        }
    }
}
void MainSelectGame(Music menu, Sound sonido, Sound sonido2, Texture2D espy, Texture2D nacky, Texture2D juan, Texture2D sombra)
{
    bool salir = false;
    /************************ Background SELECTGAME ******************************/
    Image background_selectgame = LoadImage("imagenes_danna\\background_selectgame.png");
    ImageResize(&background_selectgame, screenWidth, screenHeight);
    Texture2D texture_selectgame = LoadTextureFromImage(background_selectgame);
    UnloadImage(background_selectgame);
    /***************************  Imagenes de niveles *******************************/
    Texture2D level1 = LoadTexture("imagenes_danna\\selectLevel1-removebg-preview.png");
    Texture2D level2 = LoadTexture("imagenes_danna\\selectLevel2-removebg-preview.png");
    Vector2 postionTexture = {(float)screenWidth / 2 - (float)screenWidth / 2, (float)screenHeight / 2 - (float)screenHeight / 2};
    /******* textura selecciona un nivel*******/
    Texture2D selecNivel = LoadTexture("imagenes_danna\\SELECCIONA_UN_NIVEL.png");
    Vector2 positionZero = {screenWidth / 2 - selecNivel.width / 2, screenHeight / 2 - selecNivel.height * 1.8};
    /****************************  Movimiento dinosaurio ****************************/
    int frame = 0;
    float runningTime = 0;
    const float frameTime = 1.0f / 10.0f;
    float dT;

    /**************************** GENERAR MATRIZ CON DATOS ALEATORIOS **********************/
    int gameMatrix[MATRIX_HEIGHT][MATRIX_WIDTH];
    int squareMatrixColor[MATRIX_HEIGHT][MATRIX_WIDTH];
    for (int i = 0; i < MATRIX_HEIGHT; i++)
    {
        for (int j = 0; j < MATRIX_WIDTH; j++)
        {
            gameMatrix[i][j] = getRandomNumber(1, 10);
            squareMatrixColor[i][j] = getRandomNumber(0, 2);

            if (j < MATRIX_WIDTH - 2 && squareMatrixColor[i][j] == squareMatrixColor[i][j + 1] && squareMatrixColor[i][j + 1] == squareMatrixColor[i][j + 2])
            {
                squareMatrixColor[i][j + 2] = getRandomNumber(0, 2);
            }

            if (i < MATRIX_HEIGHT - 2 && squareMatrixColor[i][j] == squareMatrixColor[i + 1][j] && squareMatrixColor[i + 1][j] == squareMatrixColor[i + 2][j])
            {
                squareMatrixColor[i + 2][j] = getRandomNumber(0, 2);
            }
        }
    }

    Color preColors[3] = {GREEN, RED, VIOLET};
    do
    {
        /***************************************************** MOVIMIENTO ****************************************************/
        dT = GetFrameTime();
        runningTime += dT;
        if (runningTime >= frameTime)
        {
            runningTime = 0.f;
            frame++;
            if (frame > 4)
            {
                frame = 0;
            }
        }
        switch (currentGameLevel)
        {
        case WAITING:
            UpdateSelectGame(sonido, sonido2);
            DrawTextureEx(texture_selectgame, postionTexture, 0, 1.0f, WHITE); // fondo
            DrawTextureEx(selecNivel, positionZero, 0, 1.0f, WHITE);           // imagen selecciona un nivel
            DrawSelectGame(level1, level2, menu, espy, nacky, juan, sombra, frame, runningTime, frameTime);
            break;
        case LEVEL1:
            DrawGameLv1(gameMatrix, squareMatrixColor, preColors);
            break;
        case LEVEL2:
            BeginDrawing();
            ClearBackground(WHITE);
            EndDrawing();
            break;
        case LEAVE:
            salir = true;
            break;
        }
    } while (!WindowShouldClose() && !salir);

    UnloadTexture(level1);
    UnloadTexture(level2);
    UnloadTexture(selecNivel);
    UnloadTexture(texture_selectgame);
}

void DrawSelectGame(Texture2D txt_leve1, Texture2D txt_level2, Music musica, Texture2D espy, Texture2D nacky, Texture2D juan, Texture2D sombra, int frame, float runningTime, float frameTime)
{
    BeginDrawing();
    ClearBackground(WHITE);
    if (!musicPaused)
    {
        UpdateMusicStream(musica);
    }
    Vector2 pos_level1 = {screenWidth / 3.5, screenHeight / 2};
    Vector2 pos_level2 = {screenWidth / 1.79, screenHeight / 2};

    Rectangle rec = {screenWidth / 4.5, screenHeight / 2.01, screenWidth / 1.79, screenHeight / 3};
    Color rectangleColor = {0, 0, 0, 128};
    Color border = {0, 0, 0, 220};

    Color select = {255, 200, 0, 255};
    float fontSize = 80.0f + 10.0f * sinf(GetTime() * 8.0f);

    if (CheckMouseOnOptionY("Regresar", 75, 0.920))
    {
        DrawText("Regresar", screenWidth / 2 - MeasureText("Regresar", fontSize) / 2, screenHeight * 0.860, fontSize, select);
    }
    else
    {
        DrawText("Regresar", screenWidth / 2 - MeasureText("Regresar", 70) / 2, screenHeight * 0.860, 70, WHITE);
    }

    DrawRectangleRoundedLines(rec, .30, .20, 13.f, border);
    DrawRectangleRounded(rec, .30, .50, rectangleColor);

    DrawTextureEx(txt_leve1, pos_level1, 0, 1.0f, WHITE);
    DrawTextureEx(txt_level2, pos_level2, 0, 1.0f, WHITE);
    /***********************************  Dibujar dinosaurio que escogio el usuario *******************************************/
    if (selectDino == 1)
    {
        // dibujar a espy
        generate_dinos(frame, runningTime, frameTime, espy, sombra, screenWidth - 1850, screenHeight / 2.1, 24, 0);
    }
    else
    {
        if (selectDino == 2)
        {
            // dibujar a nacky
            generate_dinos(frame, runningTime, frameTime, nacky, sombra, screenWidth - 1850, screenHeight / 2.1, 24, 0);
        }
        else
        {
            if (selectDino == 3)
            {
                // dibujar a juan
                generate_dinos(frame, runningTime, frameTime, juan, sombra, screenWidth - 1850, screenHeight / 2.1, 24, 0);
            }
        }
    }

    EndDrawing();
}

//******************************** NIVELES ******************************************
void DrawGameLv1(int gameMatrix[][MATRIX_WIDTH], int squareMatrixColor[][MATRIX_WIDTH], Color preColors[])
{
    // Calculates position of the matrix on the screen
    int matrixX = 405 + (screenWidth - MATRIX_WIDTH * (RECTANGLE_SIZE + 10)) / 2;
    int matrixY = 50 + (screenHeight - MATRIX_HEIGHT * (RECTANGLE_SIZE + 10)) / 2;

    Rectangle rectangulo;
    rectangulo.height = RECTANGLE_SIZE;
    rectangulo.width = RECTANGLE_SIZE;

    Rectangle number1 = {0};
    Rectangle number2 = {0};
    number1 = rectangulo;
    number2 = rectangulo;

    static int inputLengthNumbers = 0;

    char number[4];

    Rectangle displayNumber = {0};
    int tempCorrectedGuess[2][2];

    // Temp values variables. It calculates the position of the text depending on a rectangle.
    float textX;
    float textY;

    // Saves user's input as an array so i can be displayed.
    char inputNumbers[11];

    Rectangle enlargedRect = {0}; // Temp rectangle to save where the rectangle did collision, so it can be displayed with an animation

    BeginDrawing();
    ClearBackground(BLACK);
    // DrawRectangle(0, 0, 1920, 114, RED);

    for (int i = 0; i < MATRIX_HEIGHT; i++)
    {
        for (int j = 0; j < MATRIX_WIDTH; j++)
        {
            rectangulo.x = matrixX + j * (RECTANGLE_SIZE + 10);
            rectangulo.y = matrixY + i * (RECTANGLE_SIZE + 10);

            if (CheckCollisionPointRec(GetMousePosition(), rectangulo))
            {
                enlargedRect = rectangulo;
                getMouseCollision.x = i;
                getMouseCollision.y = j;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    if (!pressedButtonNo2Flag)
                    {
                        if (!pressedButtonNo1Flag)
                        {
                            isMousePressedCollision[0].x = i;
                            isMousePressedCollision[0].y = j;
                            pressedButtonNo1Flag = 1;
                            inputNumbers[0] = '\0';
                        }
                        else
                        {
                            if (isMousePressedCollision[0].x != i || isMousePressedCollision[0].y != j)
                            {
                                if ((isMousePressedCollision[0].x == i && (isMousePressedCollision[0].y == j + 1 || isMousePressedCollision[0].y == j - 1)) ||
                                    (isMousePressedCollision[0].y == j && (isMousePressedCollision[0].x == i + 1 || isMousePressedCollision[0].x == i - 1)))
                                {
                                    if (squareMatrixColor[(int)isMousePressedCollision[0].x][(int)isMousePressedCollision[0].y] != squareMatrixColor[i][j])
                                    {
                                        isMousePressedCollision[1].x = i;
                                        isMousePressedCollision[1].y = j;
                                        pressedButtonNo2Flag = 1;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        isMousePressedCollision[0].x = i;
                        isMousePressedCollision[0].y = j;
                        isMousePressedCollision[1].x = 0.0f;
                        isMousePressedCollision[1].y = 0.0f;
                        pressedButtonNo1Flag = 1;
                        pressedButtonNo2Flag = 0;
                    }
                }
            }
            else
            {
                // Display squares with no animation
                snprintf(number, sizeof(number), "%d", gameMatrix[i][j]);
                textX = rectangulo.x + (RECTANGLE_SIZE - MeasureText(number, 50)) / 2;
                textY = rectangulo.y + (RECTANGLE_SIZE - 50) / 2;
                DrawRectangleRounded(rectangulo, 0.4, 0, preColors[squareMatrixColor[i][j]]);
                DrawRectangleRoundedLines(rectangulo, 0.4, 20, 2, WHITE);
                DrawText(number, textX, textY, 50, WHITE);
            }

            if (!guessedRight)
            {
                if (j < MATRIX_WIDTH - 2 && squareMatrixColor[i][j] == squareMatrixColor[i][j + 1] && squareMatrixColor[i][j + 1] == squareMatrixColor[i][j + 2])
                {
                    squareMatrixColor[i][j + 2] = getRandomNumber(0, 2);
                }

                if (i < MATRIX_HEIGHT - 2 && squareMatrixColor[i][j] == squareMatrixColor[i + 1][j] && squareMatrixColor[i + 1][j] == squareMatrixColor[i + 2][j])
                {
                    squareMatrixColor[i + 2][j] = getRandomNumber(0, 2);
                }
            }
        }
    }

    if (pressedButtonNo1Flag)
    {
        displayNumber.height = 150;
        displayNumber.width = 160;
        displayNumber.x = 195;
        displayNumber.y = 310;
        // In this part of the code, it displays the number on screen (left size)
        //  and also it animates when it's selected (the number)
        snprintf(number, sizeof(number), "%d", gameMatrix[(int)isMousePressedCollision[0].x][(int)isMousePressedCollision[0].y]);

        textX = displayNumber.x + (displayNumber.width - MeasureText(number, displayNumber.height)) / 2;
        textY = displayNumber.y;

        DrawText(number, textX, textY, 150, WHITE); // Modify this if you want to change how it looks like. TextX and TextY must be the position.
        drawMatrixSelected(number1, gameMatrix, matrixX, matrixY, (int)isMousePressedCollision[0].x, (int)isMousePressedCollision[0].y, number, preColors, squareMatrixColor[(int)isMousePressedCollision[0].x][(int)isMousePressedCollision[0].y]);

        if (pressedButtonNo2Flag)
        {
            // In this part of the code, it displays the number on screen (left size)
            //  and also it animates when it's selected (the number)
            displayNumber.x = 500;
            displayNumber.y = 310;

            snprintf(number, sizeof(number), "%d", gameMatrix[(int)isMousePressedCollision[1].x][(int)isMousePressedCollision[1].y]);
            textX = displayNumber.x + (displayNumber.width - MeasureText(number, displayNumber.height)) / 2;
            textY = displayNumber.y;

            DrawText(number, textX, textY, 150, WHITE);
            drawMatrixSelected(number2, gameMatrix, matrixX, matrixY, (int)isMousePressedCollision[1].x, (int)isMousePressedCollision[1].y, number, preColors, squareMatrixColor[(int)isMousePressedCollision[1].x][(int)isMousePressedCollision[1].y]);
        }
    }

    if (enlargedRect.width > 0)
    {
        drawMatrixCollision(enlargedRect, gameMatrix, squareMatrixColor, preColors); // Check collision and display it (Do not modify unless you want modify how it looks like)
    }

    if (modifyMatrix(gameMatrix, squareMatrixColor, preColors))
    {
        if (pressedButtonNo2Flag)
        {
            int key = GetKeyPressed();
            if (key >= 48 && key <= 57)
            {
                if (inputLengthNumbers < 4)
                {
                    inputNumbers[inputLengthNumbers] = (char)key;
                    inputLengthNumbers++;
                    inputNumbers[inputLengthNumbers] = '\0';
                }
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                if (inputLengthNumbers > 0)
                {
                    inputLengthNumbers--;
                    inputNumbers[inputLengthNumbers] = '\0';
                }
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                if (inputLengthNumbers > 0)
                {
                    bool resultFlag;
                    int userInput = atoi(inputNumbers);

                    resultFlag = UpdateGameLv1(gameMatrix, isMousePressedCollision, userInput);

                    if (resultFlag)
                    {
                        pressedButtonNo1Flag = 0;
                        pressedButtonNo2Flag = 0;

                        tempCorrectedGuess[0][0] = gameMatrix[(int)isMousePressedCollision[0].x][(int)isMousePressedCollision[0].y];
                        gameMatrix[(int)isMousePressedCollision[0].x][(int)isMousePressedCollision[0].y] = gameMatrix[(int)isMousePressedCollision[1].x][(int)isMousePressedCollision[1].y];
                        gameMatrix[(int)isMousePressedCollision[1].x][(int)isMousePressedCollision[1].y] = tempCorrectedGuess[0][0];

                        tempCorrectedGuess[0][0] = squareMatrixColor[(int)isMousePressedCollision[0].x][(int)isMousePressedCollision[0].y];
                        squareMatrixColor[(int)isMousePressedCollision[0].x][(int)isMousePressedCollision[0].y] = squareMatrixColor[(int)isMousePressedCollision[1].x][(int)isMousePressedCollision[1].y];
                        squareMatrixColor[(int)isMousePressedCollision[1].x][(int)isMousePressedCollision[1].y] = tempCorrectedGuess[0][0];

                        printf("It was correct!\n"); // If the user guessed right, we can display the message here, so you can draw whatever you want if he guessed right. (add animation if it's necessary)
                        guessedRight = true;
                    }
                    else
                    {
                        // In this part, we will display a message saying it wasn't correct.
                        printf("It wasn't correct!\n");
                    }
                    inputLengthNumbers = 0;
                    inputNumbers[0] = '\0';
                }
            }
            else
            {
                DrawText(inputNumbers, 100, 200, 200, BLUE); // Display numbers on screen. You can modify this for a different font.
            }
        }
    }

    EndDrawing();
}
bool UpdateGameLv1(int gameMatrix[][MATRIX_WIDTH], Vector2 position[], int userInput)
{
    int gameNumberSum;
    gameNumberSum = gameMatrix[(int)position[0].x][(int)position[0].y] + gameMatrix[(int)position[1].x][(int)position[1].y];

    if (gameNumberSum == userInput)
    {
        return true;
    }
    return false;
}

//******************************   DINOSAURIOS   *************************************
void DrawCustome(Texture2D dino, Texture2D dino2, Texture2D dino3, Texture2D sombra, int frame, float runningTime, float frameTime, Music music, Font fuente)
{
    BeginDrawing();
    ClearBackground(WHITE);
    Color select = {255, 200, 0, 255};
    if (!musicPaused)
    {
        UpdateMusicStream(music);
    }
    /******************************   rectangulo negro   **********************************/
    Rectangle rec = {(float)screenWidth / 2 - MeasureText("Regresar", 87) / 2, screenHeight * 0.79, 400, 100};
    Color rectangleColor = {0, 0, 0, 128};
    Color borde = {0, 0, 0, 220};
    DrawRectangleRoundedLines(rec, .30, .20, 13.f, borde);
    DrawRectangleRounded(rec, .30, .50, rectangleColor);
    /***************************     animar texto      ***************************/
    texto_sencillo("Regresar", 0.84, 70, 2, 0.800, true, fuente);
    /**********************************   dinosaurios  ****************************************/
    // X    Y
    if (CheckMouseOnOptionXandY("Espy", 70, 0.5, 0.43))
    {
        // DrawTexture(nameespy, screenWidth / 2 - MeasureText("Espy", 70) / 0.3, screenHeight / 2.5, WHITE);
        DrawText("Espy", screenWidth / 2 - MeasureText("Espy", 70) / 0.3, screenHeight / 2.5, 70, select);
        generate_dinos(frame, runningTime, frameTime, dino, sombra, (screenWidth / 2 - MeasureText("Regresar", 90) / 2) - 400, 500.f, 24, 0);
    }
    else
    {
        // DrawTexture(nameespy, screenWidth / 2 - MeasureText("Espy", 70) / 0.3, screenHeight / 2.5, WHITE);

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
void UpdateCustome(Texture2D selectPers)
{
    // Lógica de actualización de créditos
    float fontSize = 80.0f + 10.0f * sinf(GetTime() * 8.0f);
    static bool mostrarMensaje = false;
    Vector2 positionZero = {screenWidth / 2 - selectPers.width / 2, screenHeight / 2 - selectPers.height * 3};

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
        // aqui se debe de dibujar la imagen LISTO con probablemente estas posiciones, puede que se tenga que cambiar la posicion Y
        DrawText("LISTO", screenWidth / 2.35 - MeasureText("LISTO", fontSize) / 2, screenHeight / 4, fontSize * 2.0f, BLACK);
    }
    else
    {
        // cambiar la textura por la de brayan
        DrawTextureEx(selectPers, positionZero, 0, 1.0f, WHITE);
    }
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
void generate_dino_noAnimated(Texture2D dinosaurio, int maxFrames, Texture2D sombra, float posX, float posY)
{
    Rectangle source = {0.f, 0.f, (float)dinosaurio.width / maxFrames, (float)dinosaurio.height};
    Rectangle dest = {posX, posY, 15 * (float)dinosaurio.width / maxFrames, 15 * (float)dinosaurio.height};
    Vector2 origin = {0.f, 0.f};
    DrawTexture(sombra, posX + 30, 640, WHITE);
    DrawTexturePro(dinosaurio, source, dest, origin, 0.f, WHITE);
}

/********************************** FUNCIONES PARA ANIMACION PARA EL JUEGO ************************************/
void drawMatrixCollision(Rectangle enlargedRect, int gameMatrix[][MATRIX_WIDTH], int squareMatrixColor[][MATRIX_WIDTH], Color preColors[])
{
    char number[5];
    float getTime = 0;
    float textY;
    float textX;

    getTime = cosf(GetTime() * 5.0f);
    enlargedRect.x -= 10 + 20 / 2 * getTime;
    enlargedRect.y -= 10 + 20 / 2 * getTime;
    enlargedRect.width += 20 + 40 / 2 * getTime;
    enlargedRect.height += 20 + 40 / 2 * getTime;

    DrawRectangleRounded(enlargedRect, 0.4, 0, preColors[squareMatrixColor[(int)getMouseCollision.x][(int)getMouseCollision.y]]);
    DrawRectangleRoundedLines(enlargedRect, 0.4, 20, 2, WHITE);

    snprintf(number, sizeof(number), "%d", gameMatrix[(int)getMouseCollision.x][(int)getMouseCollision.y]);

    textX = enlargedRect.x + (enlargedRect.width - MeasureText(number, (float)(80 + 50 * getTime / 2))) / 2;
    textY = enlargedRect.y + (enlargedRect.height - (float)(80 + 50 * getTime / 2)) / 2;

    DrawText(number, textX, textY + 3, (float)(80 + 50 * getTime / 2), WHITE);
}

void drawMatrixSelected(Rectangle number1, int gameMatrix[][MATRIX_WIDTH], int matrixX, int matrixY, int valueX, int valueY, char number[], Color preColors[], int colorNumber)
{
    float getTime;
    float textY;
    float textX;
    number1.x = matrixX + valueY * (RECTANGLE_SIZE + 10);
    number1.y = matrixY + valueX * (RECTANGLE_SIZE + 10);
    getTime = easeInOutCirc(sinf(GetTime() * 8.0f));

    DrawRectangleRounded(number1, 0.4, 0, preColors[colorNumber]);
    DrawRectangleRoundedLines(number1, 0.4, 20, 2, WHITE);

    textX = number1.x + (number1.width - MeasureText(number, (float)(80 + 50 * getTime / 2))) / 2;
    textY = number1.y + (number1.height - (float)(80 + 50 * getTime / 2)) / 2;

    DrawText(number, textX, textY + 5, (float)(80 + 50 * getTime / 2), WHITE);
}

bool modifyMatrix(int gameMatrix[][MATRIX_WIDTH], int squareMatrixColor[][MATRIX_WIDTH], Color preColors[3])
{
    int positionX1 = (int)isMousePressedCollision[0].x;
    int positionY1 = (int)isMousePressedCollision[0].y;

    int positionX2 = (int)isMousePressedCollision[1].x;
    int positionY2 = (int)isMousePressedCollision[1].y;

    //******************************** CHECK LEFT AND RIGHT SIZE ****************************
    if (positionX1 == positionX2)
    {
        /*************************** LEFT SIZE**********************************************/
        if (positionY1 - 1 == positionY2)
        {
            if (squareMatrixColor[positionX1 - 1][positionY1 - 1] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1 + 1][positionY1 - 1] == squareMatrixColor[positionX1][positionY1])
                {
                    // printf("JOINED 1\n");
                    return true;
                }
                if (squareMatrixColor[positionX1 - 2][positionY1 - 1] == squareMatrixColor[positionX1][positionY1])
                {
                    //  printf("JOINED 2\n");
                    return true;
                }
            }

            if (squareMatrixColor[positionX1][positionY1 - 3] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1][positionY1 - 2] == squareMatrixColor[positionX1][positionY1])
                {
                    //  printf("JOINED 3\n");
                    return true;
                }
            }
            if (squareMatrixColor[positionX1 + 2][positionY1 - 1] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1 + 1][positionY1 - 1] == squareMatrixColor[positionX1][positionY1])
                {
                    //  printf("JOINED 4\n");
                    return true;
                }
            }
        }

        //*************************************RIGHT SIZE****************************************
        if (positionY1 + 1 == positionY2)
        {
            if (squareMatrixColor[positionX1 - 1][positionY1 + 1] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1 + 1][positionY1 + 1] == squareMatrixColor[positionX1][positionY1])
                {
                    // printf("JOINED 1.1\n");
                    return true;
                }
                if (squareMatrixColor[positionX1 - 2][positionY1 + 1] == squareMatrixColor[positionX1][positionY1])
                {

                    // printf("JOINED 2.1\n");
                    return true;
                }
            }

            if (squareMatrixColor[positionX1][positionY1 + 3] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1][positionY1 + 2] == squareMatrixColor[positionX1][positionY1])
                {

                    // printf("JOINED 3.1\n");
                    return true;
                }
            }
            if (squareMatrixColor[positionX1 + 2][positionY1 + 1] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1 + 1][positionY1 + 1] == squareMatrixColor[positionX1][positionY1])
                {

                    //  printf("JOINED 4.1\n");
                    return true;
                }
            }
        }
    }
    //******************************* DOWN AND UP CHECK *******************************************
    if (positionY1 == positionY2)
    {
        //*************************** UP CHECK ***********************************************
        if (positionX1 - 1 == positionX2)
        {
            if (squareMatrixColor[positionX1 - 1][positionY1 - 1] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1 - 1][positionY1 + 1] == squareMatrixColor[positionX1][positionY1])
                {

                    // printf("JOINED UP 1\n");
                    return true;
                }

                if (squareMatrixColor[positionX1 - 1][positionY1 - 2] == squareMatrixColor[positionX1][positionY1])
                {

                    //  printf("JOINED UP 2\n");
                    return true;
                }
            }

            if (squareMatrixColor[positionX1 - 3][positionY1] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1 - 2][positionY1] == squareMatrixColor[positionX1][positionY1])
                {

                    // printf("JOINED UP 3\n");
                    return true;
                }
            }
            if (squareMatrixColor[positionX1 - 1][positionY1 + 1] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1 - 1][positionY1 + 2] == squareMatrixColor[positionX1][positionY1])
                {

                    //  printf("JOINED UP 4\n");
                    return true;
                }
            }
        }

        //***************************** DOWN CHECK ******************************************
        if (positionX1 + 1 == positionX2)
        {
            if (squareMatrixColor[positionX1 + 1][positionY1 - 1] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1 + 1][positionY1 + 1] == squareMatrixColor[positionX1][positionY1])
                {
                    // printf("JOINED DOWN 1\n");
                    return true;
                }

                if (squareMatrixColor[positionX1 + 1][positionY1 - 2] == squareMatrixColor[positionX1][positionY1])
                {
                    // printf("JOINED DOWN 2\n");
                    return true;
                }
            }

            if (squareMatrixColor[positionX1 + 3][positionY1] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1 + 2][positionY1] == squareMatrixColor[positionX1][positionY1])
                {

                    // printf("JOINED DOWN 3\n");
                    return true;
                }
            }
            if (squareMatrixColor[positionX1 + 1][positionY1 + 1] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1 + 1][positionY1 + 2] == squareMatrixColor[positionX1][positionY1])
                {

                    // printf("JOINED DOWN 4\n");
                    return true;
                }
            }
        }
    }
    return false;
}

double easeInOutCirc(double x)
{
    if (x < 0)
    {
        x = 0;
    }

    return 0.5 * (1 - cos(x * 3.1416));
}

//**************************** FUNCIONES EXTRAS *************************

int getRandomNumber(int ri, int rf)
{
    int range = (rf - ri + 1);
    return rand() % range + ri;
}

void texto_sencillo(char texto[], float posicion, float font, float x, float y, bool mult, Font fonT)
{
    float fontSize = 80.0f + 10.0f * sinf(GetTime() * 8.0f);
    Color select = {255, 200, 0, 255};
    Color color1 = {234, 255, 166, 255};
    /* vectores 1*/
    Vector2 vect01 = {screenWidth / x - MeasureText(texto, fontSize) / 2.4, screenHeight * y};
    Vector2 vect02 = {screenWidth / x - MeasureText(texto, fontSize) / 2.4, screenHeight / y};
    /* vectores 2*/
    Vector2 vect = {screenWidth / x - MeasureText(texto, 80) / 2.4, screenHeight * y};
    Vector2 vect2 = {screenWidth / x - MeasureText(texto, 80) / 2.4, screenHeight / y};
    if (CheckMouseOnOptionY(texto, font, posicion))
    {
        if (mult) // se multiplica la posicion de y
        {
            DrawTextEx(fonT, texto, vect01, fontSize, 0.0, select);
        }
        else // se divide la posicion de y
        {
            DrawTextEx(fonT, texto, vect02, fontSize, 0.0, select);
        }
    }
    else
    {
        if (mult) // se multiplica la posicion de y
        {
            DrawTextEx(fonT, texto, vect, 80, 0.0, color1);
        }
        else // se divide la posicion de y
        {
            DrawTextEx(fonT, texto, vect2, 80, 0.0, color1);
        }
    }
}

void playsound(Sound sonido, bool flag)
{
    if (flag)
    {
        PlaySound(sonido);
    }
}

bool CheckMouseOnOptionXandY(const char *optionText, float fontSize, float positionX, float positionY)
{
    Vector2 mousePosition = GetMousePosition();
    Vector2 textSize = MeasureTextEx(GetFontDefault(), optionText, fontSize, 0);

    float centerX = screenWidth * positionX / 2 - textSize.x / 2;
    float centerY = screenHeight * positionY - textSize.y / 2;

    Rectangle optionBounds = {centerX, centerY, textSize.x, textSize.y};
    // DrawRectangle(centerX, centerY, textSize.x, textSize.y, VIOLET);
    return CheckCollisionPointRec(mousePosition, optionBounds);
}

bool CheckMouseOnOptionY(char optionText[], float fontSize, float position)
{
    Vector2 mousePosition = GetMousePosition();
    Vector2 textSize = MeasureTextEx(GetFontDefault(), optionText, fontSize, 0);
    float centerX = screenWidth / 2 - textSize.x / 2;
    float centerY = screenHeight * position - textSize.y / 2;

    Rectangle optionBounds = {centerX, centerY, textSize.x, textSize.y};
    // DrawRectangle(centerX, centerY, textSize.x, textSize.y, GREEN);

    return CheckCollisionPointRec(mousePosition, optionBounds);
}

void generte_rec()
{
    float centerX = screenWidth / 2.01f;
    float centerY = screenHeight / 1.516f;

    float rectWidth = screenWidth / 2.5f;
    float rectHeight = screenHeight / 2.89f;

    Rectangle rec = {centerX - rectWidth / 2.0f, centerY - rectHeight / 2.0f, rectWidth, rectHeight};
    Color rectangleColor = {0, 0, 0, 140};
    Color border = {0, 0, 0, 220};

    DrawRectangleRoundedLines(rec, .30, .20, 13.f, border);

    DrawRectangleRounded(rec, .30, .50, rectangleColor);
}