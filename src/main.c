/*
    Código creado: 7 de noviembre del 2023 // Última modificación: 11 de Diciembre del 2023
    Este juego fue creado por los usuarios keiwv y nanna para la clase de Programación Estructurada en la Universidad Autónoma de Baja California.
    Es una simulación del juego "Candy Crush" agregando mecánicas lúdicas para el aprendizaje matemáticos de niños.

    Es sin fines de lucros.

    @keiwv
    @dannasndz
*/

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
    OPTIONS2,
    LEAVE
} GameLevel;

typedef struct _SaveProgress
{
    int lastPointsLevel1;
    int lastPointsLevel2;
} TSaveProgress;

GameLevel currentGameLevel = WAITING;
GameScene currentScene = LOGO;
Vector2 mousePosition = {0};
/********************  VARIABLES Y CONSTANTES GLOBALES *************************/
Font fonT;
Sound sound1;
Sound sound2;
Sound sound3;
Image icon;
Music music;
Music level1;
Music NIVEL1;
Image background_options;
Texture2D texture_options;
Image som;
Texture2D sombra;
Texture2D texture_logo;
Image background_start;
Texture2D texture_start;
Image background_custome;
Texture2D texture_custome;
Texture2D listo;
Texture2D selectPers;
Texture2D dino1;
Texture2D dino2;
Texture2D dino3;
Texture2D dino4;
Texture2D espy;
Texture2D nacky;
Texture2D juan;
// main2
Image background_selectgame;
Texture2D selectgame_txt;
Image bg_level1;
Texture2D bg_level1_txt;
Texture2D bordes;
Texture2D icono;
Texture2D level1_txt;
Texture2D level2_txt;
Texture2D estrellas_vacias;
Texture2D estrellas;
Texture2D selecNivel;
Texture2D mnsj_correcto;
Texture2D mnsj_incorrecto;
Texture2D borde;
Texture2D ajustes;
Texture2D estrellas_vacias_1;
Texture2D perdiste;
Texture2D ganaste;
Music gameover;
Music win;
Music NIVEL2;
bool waiting = true;
int selectDino = 0;
const int screenWidth = 1920;
const int screenHeight = 1080;
static bool musicPaused = false;
static bool soundPaused = true;
bool flagLoadTextures = false;
bool mostrar_mnsj = false;
bool mnsj_win = false;
bool mnsj_win2 = false;
/*************** JUEGO GLOBALES IMPORTANTES**************************/
#define MATRIX_WIDTH 9
#define MATRIX_HEIGHT 7
#define RECTANGLE_SIZE 100
bool pressedButtonNo1Flag = 0;
bool pressedButtonNo2Flag = 0;
Vector2 getMouseCollision = {0};
Vector2 isMousePressedCollision[2] = {0};
bool guessedRight = false;
bool guessedRight2 = false;
int validate = 0;
char number[10];
char inputNumbers[11];
int inputLengthNumbers = 0;
int intentos = 3;
bool returnFlag = false;
bool leaveGameFlag = false;
bool returnFlag2 = false;
TSaveProgress SaveProgression = {0};
/********************************** PROTOTIPO DE FUNCIONES ************************************/
/*      ************************ MANEJO DE ESCENARIOS Y JUEGO ***********************/
void logoLoading(int frameCounter);

void UpdateMenu();
void DrawMenu(int frame, float runningTime, float frameTime);

void UpdateOptions();
void DrawOptions(int frame, float runningTime, float frameTime);

void UpdateSelectGame();
void MainSelectGame();

void DrawSelectGame(int frame, float runningTime, float frameTime, TSaveProgress userProgression, int maxPoints[]);

/*        ************************ NIVELES **************************************         */
int DrawGameLv1(int gameMatrix[][MATRIX_WIDTH], int squareMatrixColor[][MATRIX_WIDTH], Color preColors[], Vector2 posicion, int frame, float runningTime, float frameTime, int maxPoints[], int currentPoints);
void UpdateGameLv1();
int DrawGameLv2(int gameMatrix[][MATRIX_WIDTH], int squareMatrixColor[][MATRIX_WIDTH], Color preColors[], Vector2 posicion, int frame, float runningTime, float frameTime, int maxPoints[], int currentPoints);
bool verificar_multi(int gameMatrix[][MATRIX_WIDTH], Vector2 position[], int userInput);
void DrawOptionsLevel(int frame, float runningTime, float frameTime);
void UpdateOptionLevel1();
void DrawWin(int num);
void DrawGameOverLevel1();
void DrawGameOverLevel2();
void UpdateOptionLevel2();
void CheckOptions();
void CheckWinOptionsLv1();
void CheckWinOptionsLv2();

bool verificar_suma(int gameMatrix[][MATRIX_WIDTH], Vector2 position[], int userInput);
//******************************   DINOSAURIOS   *************************************
void DrawCustome(int frame, float runningTime, float frameTime);
void UpdateCustome();

void generate_dinos(int frame, float runningTime, float frameTime, Texture2D dinosaurio, float posX, float posY, int maxFrames, int op);
void generate_dino_noAnimated(Texture2D dinosaurio, int maxFrames, float posX, float posY);

//*************** FUNCIONES DE ANIMACION PARA EL JUEGO ******************************
void drawMatrixCollision(Rectangle enlargedRect, int gameMatrix[][MATRIX_WIDTH], int squareMatrixColor[][MATRIX_WIDTH], Color preColors[]);
void drawMatrixSelected(Rectangle number1, int gameMatrix[][MATRIX_WIDTH], int matrixX, int matrixY, int valueX, int valueY, char number[], Color preColors[], int colorNumber);
int ValidateMatrix(int squareMatrixColor[][MATRIX_WIDTH], int positionX1, int positionY1, int positionX2, int positionY2);
void modifyMatrix(int gameMatrix[][MATRIX_WIDTH], Color preColors[], int conditionModified, int squareMatrixColor[][MATRIX_WIDTH], int positionX1, int positionY1, int positionX2, int positionY2);
double easeInOutCirc(double x);
void animationChange(int squareMatrixColor[][MATRIX_WIDTH], int gameMatrix[][MATRIX_WIDTH], Color preColors[], Vector2 posicion, int frame, float runningTime, float frameTime, int maxPoints[], int currentPoints, int maxPointsIndex);
float animation2(float start, float end, float t);
//**************************** FUNCIONES EXTRAS ************************
void cargar_texturas(void);
void cargar_texturas_main2(void);
int getRandomNumber(int ri, int rf);
void texto_sencillo(char texto[], float posicion, float font, float x, float y, bool mult);
void playsound(Sound sonido, bool flag);
bool CheckMouseOnOptionXandY(const char *optionText, float fontSize, float positionX, float positionY);
bool CheckMouseOnOptionY(char optionText[], float fontSize, float position);
void generte_rec(void);
void verifyLineThree(int squareMatrixColor[][MATRIX_WIDTH]);
//******************************* FUNCIONES PARA GUARDAR PARTIDA ******************
void SaveProgressFile(TSaveProgress progress);
TSaveProgress LoadProgressFile();
/************************************* FUNCIÓN PRINCIPAL *************************/
int main()
{
    InitWindow(screenWidth, screenHeight, "Sumpy");
    InitAudioDevice();
    cargar_texturas();
    SetWindowIcon(icon);
    PlayMusicStream(music);
    PlayMusicStream(gameover);
    PlayMusicStream(win);
    PlayMusicStream(level1);
    PlayMusicStream(NIVEL1);
    PlayMusicStream(NIVEL2);
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
            logoLoading(frameCounter); // NO MODIFICAR ESTA FUNCIÓN, SOLUCIONARÉ ALGUNOS PROBLEMAS.
            break;
        case START:
            DrawTextureEx(texture_start, postionTexture, 0, 1.0f, WHITE);
            DrawTextureEx(texture_logo, positionZero, 0, 1.0f, WHITE);
            UpdateMenu();
            DrawMenu(frame, runningTime, frameTime);
            break;
        case OPTIONS:
            DrawTextureEx(texture_options, postionTexture, 0, 1.0f, WHITE);
            UpdateOptions(music, level1);
            DrawOptions(frame, runningTime, frameTime);
            break;
        case CUSTOME:
            DrawTextureEx(texture_custome, postionTexture, 0, 1.0f, WHITE);
            UpdateCustome();
            DrawCustome(frame, runningTime, frameTime);
            break;
        case SELECTGAME:
            currentGameLevel = WAITING;
            MainSelectGame();
            PlayMusicStream(music);
            currentScene = START;
            break;
        case EXIT:
            exitProgram = true;
            break;
        }
    }
    UnloadFont(fonT);
    UnloadTexture(listo);
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
    UnloadTexture(espy);
    UnloadTexture(nacky);
    UnloadTexture(juan);

    UnloadSound(sound1);
    UnloadSound(sound2);
    UnloadSound(sound3);
    UnloadMusicStream(gameover);
    UnloadMusicStream(NIVEL1);
    UnloadMusicStream(NIVEL2);
    UnloadMusicStream(level1);
    UnloadMusicStream(music);
    CloseAudioDevice();

    CloseWindow();

    return 0;
}
/********************************** DESARROLLO DE FUNCIONES ************************************/

/*      ************************ MANEJO DE ESCENARIOS ***********************/
void logoLoading(int frameCounter)
{
    if (frameCounter == 3200)
    {
        currentScene = START;
    }

    double value = fabs(sinf(0.001f * frameCounter));

    BeginDrawing();
    DrawTexturePro(texture_logo, (Rectangle){0, 0, texture_logo.width, texture_logo.height},
                   (Rectangle){screenWidth / 2 - texture_logo.width / 2, screenHeight / 2 - texture_logo.height / 2,
                               texture_logo.width, texture_logo.height},
                   (Vector2){0, 0}, 0.0f, Fade(WHITE, value));
    ClearBackground(WHITE);
    EndDrawing();
}

void DrawMenu(int frame, float runningTime, float frameTime)
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
    generate_dinos(frame, runningTime, frameTime, dino1, (float)screenWidth / 12, (float)screenHeight / 1.9, maxFrames, 1);
    /******************************************** Dibujar mensajes **************************************************/
    texto_sencillo("Jugar", 0.532, 70, 2, 2, false);
    texto_sencillo("Personajes", 0.615, 70, 2, 0.5905, true);
    texto_sencillo("Opciones", 0.697, 70, 2, 0.67545, true);
    texto_sencillo("Salir", 0.78, 70, 2, 0.755, true);
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

void UpdateOptions()
{
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
void DrawOptions(int frame, float runningTime, float frameTime)
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
    generate_dinos(frame, runningTime, frameTime, dino2, screenWidth / 1.35, screenHeight / 2, 24, 1);
    /********************************************************************************/
    texto_sencillo("Efectos", 0.532, 70, 2.1, 2, false);
    if (soundPaused)
    {
        DrawText("ON", screenWidth / 1.559 - MeasureText("Efectos", 70) / 2, screenHeight / 1.96, 60, colo1);
    }
    else
    {
        DrawText("OFF", screenWidth / 1.559 - MeasureText("Efectos", 70) / 2, screenHeight / 1.96, 60, select);
    }
    texto_sencillo("Musica", 0.655, 70, 2.1, 0.630, true);
    if (musicPaused)
    {
        DrawText("OFF", screenWidth / 1.6 - MeasureText("Musica", 70) / 2, screenHeight * 0.640, 60, select);
    }
    else
    {
        DrawText("ON", screenWidth / 1.6 - MeasureText("Musica", 70) / 2, screenHeight * 0.640, 60, colo1);
    }
    texto_sencillo("Regresar", 0.78, 70, 2, 0.755, true);

    EndDrawing();
}

void UpdateSelectGame()
{
    Vector2 mousePosition = GetMousePosition();
    Rectangle LEVEL1_RECT = {screenWidth / 3.5, screenHeight / 2, 235, 250};
    Rectangle LEVEL2_RECT = {screenWidth / 1.75, screenHeight / 2, 225, 250};

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointRec(mousePosition, LEVEL1_RECT))
        {
            playsound(sound3, soundPaused);
            currentGameLevel = LEVEL1;
        }
        if (CheckCollisionPointRec(mousePosition, LEVEL2_RECT))
        {
            playsound(sound3, soundPaused);
            currentGameLevel = LEVEL2;
        }
        if (CheckMouseOnOptionY("Regresar", 75, 0.920))
        {
            playsound(sound1, soundPaused);
            currentGameLevel = LEAVE;
            leaveGameFlag = false;
        }
    }
}
void MainSelectGame()
{
    bool salir = false;
    /************************ Background SELECTGAME ******************************/
    cargar_texturas_main2();
    /****************************  Movimiento dinosaurio ****************************/
    Vector2 postionTexture = {(float)screenWidth / 2 - (float)screenWidth / 2, (float)screenHeight / 2 - (float)screenHeight / 2};
    int frame = 0;
    float runningTime = 0;
    const float frameTime = 1.0f / 10.0f;
    float dT;
    /**************************** GENERAR MATRIZ CON DATOS ALEATORIOS **********************/
    int gameMatrix[MATRIX_HEIGHT][MATRIX_WIDTH];
    int squareMatrixColor[MATRIX_HEIGHT][MATRIX_WIDTH];
    int levelFlag = 0;
    for (int i = 0; i < MATRIX_HEIGHT; i++)
    {
        for (int j = 0; j < MATRIX_WIDTH; j++)
        {
            gameMatrix[i][j] = getRandomNumber(1, 5);
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

    Color preColors[3] = {GREEN, ORANGE, RED};
    int maxPoints[] = {200, 200};
    TSaveProgress userProgression = LoadProgressFile();
    TSaveProgress currentUserProgression = {0};
    currentUserProgression.lastPointsLevel1 = 0;
    currentUserProgression.lastPointsLevel2 = 0;
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
            if (returnFlag2 || leaveGameFlag)
            {
                intentos = 3;
            }
            userProgression = LoadProgressFile();
            UpdateSelectGame();
            DrawTextureEx(selectgame_txt, postionTexture, 0, 1.0f, WHITE); // fondo
            DrawTexture(selecNivel, 250, 150, WHITE);                      // imagen selecciona un nivel
            DrawSelectGame(frame, runningTime, frameTime, userProgression, maxPoints);
            break;
        case LEVEL1:
            if (returnFlag2)
            {
                currentUserProgression.lastPointsLevel2 = SaveProgression.lastPointsLevel2;
                currentUserProgression.lastPointsLevel1 = 0;
                intentos = 3;
                returnFlag2 = false;
                PlayMusicStream(NIVEL1);
            }
            currentUserProgression.lastPointsLevel1 = DrawGameLv1(gameMatrix, squareMatrixColor, preColors, postionTexture, frame, runningTime, frameTime, maxPoints, currentUserProgression.lastPointsLevel1);
            CheckOptions();
            if (currentUserProgression.lastPointsLevel1 > 0)
            {
                SaveProgression.lastPointsLevel1 = currentUserProgression.lastPointsLevel1;
                SaveProgressFile(SaveProgression);
            }
            levelFlag = 0;
            break;
        case LEVEL2:
            if (leaveGameFlag)
            {
                currentUserProgression.lastPointsLevel1 = SaveProgression.lastPointsLevel1;
                currentUserProgression.lastPointsLevel2 = 0;
                intentos = 3;
                leaveGameFlag = false;
                PlayMusicStream(NIVEL2);
            }
            currentUserProgression.lastPointsLevel2 = DrawGameLv2(gameMatrix, squareMatrixColor, preColors, postionTexture, frame, runningTime, frameTime, maxPoints, currentUserProgression.lastPointsLevel2);
            levelFlag = 1;
            CheckOptions();
            if (currentUserProgression.lastPointsLevel2 > 0)
            {
                SaveProgression.lastPointsLevel2 = currentUserProgression.lastPointsLevel2;
                SaveProgressFile(SaveProgression);
            }
            printf("LEVEL 1: %d LEVEL 2: %d\n", currentUserProgression.lastPointsLevel1, currentUserProgression.lastPointsLevel2);
            break;
        case OPTIONS2:
            DrawOptionsLevel(frame, runningTime, frameTime);
            if (levelFlag)
            {
                UpdateOptionLevel2();
            }
            else
            {
                UpdateOptionLevel1();
            }
            break;
        case LEAVE:
            salir = true;
            break;
        }
        if (intentos == 0)
        {
            inputLengthNumbers = 0;
            inputNumbers[0] = '\0';
            mostrar_mnsj = false;
            guessedRight = false;
            guessedRight2 = false;
            pressedButtonNo1Flag = false;
            pressedButtonNo2Flag = false;
        }
    } while (!WindowShouldClose() && !salir);
    UnloadTexture(perdiste);
    UnloadTexture(ajustes);
    UnloadTexture(borde);
    UnloadTexture(mnsj_incorrecto);
    UnloadTexture(mnsj_correcto);
    UnloadTexture(icono);
    UnloadTexture(bordes);
    UnloadTexture(bg_level1_txt);
    UnloadTexture(estrellas);
    UnloadTexture(estrellas_vacias);
    UnloadTexture(estrellas_vacias_1);
    UnloadTexture(level1_txt);
    UnloadTexture(level2_txt);
    UnloadTexture(selecNivel);
    UnloadTexture(selectgame_txt);
    SaveProgressFile(SaveProgression);
}

void DrawSelectGame(int frame, float runningTime, float frameTime, TSaveProgress userProgression, int maxPoints[])
{
    BeginDrawing();
    ClearBackground(WHITE);
    if (!musicPaused)
    {
        UpdateMusicStream(level1);
    }
    Vector2 pos_level1 = {screenWidth / 3.5, screenHeight / 2.3};
    Vector2 pos_level2 = {screenWidth / 1.79, screenHeight / 2.3};

    Rectangle rec = {screenWidth / 4.5, screenHeight / 2.3, screenWidth / 1.79, screenHeight / 3};
    Color rectangleColor = {0, 0, 0, 128};
    Color border = {0, 0, 0, 220};

    texto_sencillo("Regresar", 0.920, 75, 2, 0.860, 1);

    DrawRectangleRoundedLines(rec, .30, .20, 13.f, border);
    DrawRectangleRounded(rec, .30, .50, rectangleColor);

    DrawTextureEx(level1_txt, pos_level1, 0, 1.0f, WHITE);
    DrawTextureEx(level2_txt, pos_level2, 0, 1.0f, WHITE);

    // printf("%d\n", userProgression.lastPointsLevel1);

    if (userProgression.lastPointsLevel1 >= maxPoints[0]) // dibujar 3 estrellas amarillas
    {
        DrawTexture(estrellas, screenWidth / 3.25, screenHeight / 1.48, WHITE);
        DrawTexture(estrellas, screenWidth / 2.85, screenHeight / 1.48, WHITE);
        DrawTexture(estrellas, screenWidth / 2.55, screenHeight / 1.48, WHITE);
    }
    else
    {
        if (userProgression.lastPointsLevel1 >= (maxPoints[0] / 2)) // dibujar 2 estrellas amarillas 1 vacia
        {
            DrawTexture(estrellas, screenWidth / 3.25, screenHeight / 1.48, WHITE);
            DrawTexture(estrellas, screenWidth / 2.85, screenHeight / 1.48, WHITE);
            DrawTexture(estrellas_vacias_1, screenWidth / 2.55, screenHeight / 1.469, WHITE);
        }
        else
        {
            if (userProgression.lastPointsLevel1 >= (maxPoints[0] / 3)) // dibujar 1 estrella amarilla y 2 vacias
            {
                DrawTexture(estrellas, screenWidth / 3.25, screenHeight / 1.48, WHITE);
                DrawTexture(estrellas_vacias_1, screenWidth / 2.85, screenHeight / 1.469, WHITE);
                DrawTexture(estrellas_vacias_1, screenWidth / 2.55, screenHeight / 1.469, WHITE);
            }
            else // dibujar 3 estrellas vacias
            {
                DrawTexture(estrellas_vacias, screenWidth / 3.5, screenHeight / 1.52, WHITE);
            }
        }
    }

    if (userProgression.lastPointsLevel2 >= maxPoints[1]) // dibujar 3 estrellas amarillas
    {
        DrawTexture(estrellas, 145 + screenWidth / 2, screenHeight / 1.48, WHITE);
        DrawTexture(estrellas, 180 + screenWidth / 1.9, screenHeight / 1.48, WHITE);
        DrawTexture(estrellas, 205 + screenWidth / 1.8, screenHeight / 1.48, WHITE);
    }
    else
    {
        if (userProgression.lastPointsLevel2 >= (maxPoints[1] / 2)) // dibujar 2 estrellas amarillas 1 vacia
        {
            DrawTexture(estrellas, 145 + screenWidth / 2, screenHeight / 1.48, WHITE);
            DrawTexture(estrellas, 180 + screenWidth / 1.9, screenHeight / 1.48, WHITE);
            DrawTexture(estrellas_vacias_1, 205 + screenWidth / 1.8, screenHeight / 1.469, WHITE);
        }
        else
        {
            if (userProgression.lastPointsLevel2 >= (maxPoints[1] / 3)) // dibujar 1 estrella amarilla y 2 vacias
            {
                DrawTexture(estrellas, 145 + screenWidth / 2, screenHeight / 1.48, WHITE);
                DrawTexture(estrellas_vacias_1, 180 + screenWidth / 1.9, screenHeight / 1.469, WHITE);
                DrawTexture(estrellas_vacias_1, 205 + screenWidth / 1.8, screenHeight / 1.469, WHITE);
            }
            else // dibujar 3 estrellas vacias
            {
                DrawTexture(estrellas_vacias, 115 + screenWidth / 2, screenHeight / 1.52, WHITE);
            }
        }
    }

    /***********************************  Dibujar dinosaurio que escogio el usuario *******************************************/
    if (selectDino == 1)
    {
        // dibujar a espy
        generate_dinos(frame, runningTime, frameTime, dino1, screenWidth - 1850, screenHeight / 2.1, 24, 0);
    }
    else
    {
        if (selectDino == 2)
        {
            // dibujar a nacky
            generate_dinos(frame, runningTime, frameTime, dino4, screenWidth - 1850, screenHeight / 2.1, 24, 0);
        }
        else
        {
            if (selectDino == 3)
            {
                // dibujar a juan
                generate_dinos(frame, runningTime, frameTime, dino3, screenWidth - 1850, screenHeight / 2.1, 24, 0);
            }
        }
    }

    EndDrawing();
}

//******************************** NIVELES ******************************************
int DrawGameLv1(int gameMatrix[][MATRIX_WIDTH], int squareMatrixColor[][MATRIX_WIDTH], Color preColors[], Vector2 posicion, int frame, float runningTime, float frameTime, int maxPoints[], int currentPoints)
{
    // Calculates position of the matrix on the screen
    if (!musicPaused)
    {
        UpdateMusicStream(NIVEL1);
    }
    int matrixX = 405 + (screenWidth - MATRIX_WIDTH * (RECTANGLE_SIZE + 10)) / 2;
    int matrixY = 50 + (screenHeight - MATRIX_HEIGHT * (RECTANGLE_SIZE + 10)) / 2;

    Rectangle rectangulo;
    rectangulo.height = RECTANGLE_SIZE;
    rectangulo.width = RECTANGLE_SIZE;

    Rectangle number1 = {0};
    Rectangle number2 = {0};
    number1 = rectangulo;
    number2 = rectangulo;

    Rectangle displayNumber = {0};
    int tempCorrectedGuess[2][2];

    // Temp values variables. It calculates the position of the text depending on a rectangle.
    float textX;
    float textY;

    // Saves user's input as an array so i can be displayed.
    guessedRight = false;
    Rectangle enlargedRect = {0}; // Temp rectangle to save where the rectangle did collision, so it can be displayed with an animation

    BeginDrawing();
    ClearBackground(BLACK);
    /**** dibujar cosas necesarias para nivel  ***/
    Rectangle rec = {63, 215, 762, 305};
    Rectangle rec2 = {150, 552, 600, 150};
    Rectangle rec3 = {860, 200, 1000, 780};
    Rectangle rec_pnts = {595, 740, 240, 240};
    Rectangle rec_int = {1520, 990, 330, 65};

    Color rectangleColor = {0, 0, 0, 140};
    Color rectangleColor2 = {0, 0, 0, 200};
    Vector2 pos = {375, 285};
    DrawTextureEx(bg_level1_txt, posicion, 0, 1.0f, WHITE);
    DrawRectangleRounded(rec2, .30, .50, rectangleColor2);
    DrawRectangleRounded(rec, .35, .50, rectangleColor);
    DrawRectangleRounded(rec3, .10, .50, rectangleColor);
    DrawTexture(borde, 0, 0, WHITE);
    DrawTexture(bordes, 50, 200, WHITE);
    DrawTexture(icono, screenWidth / 2, 30, WHITE); // FALTTA PONER LOGO DE SUMPY
    DrawTextEx(fonT, "+", pos, 220, 0, WHITE);
    Vector2 pos_nivel = {40, 40};
    DrawTextEx(fonT, "Nivel 1", pos_nivel, 100, 0, WHITE);
    DrawTexture(ajustes, 1800, 30, WHITE);
    DrawRectangleRounded(rec_pnts, 0.30, 0.50, rectangleColor);
    Vector2 po_objt = {600, 750};
    DrawTextEx(fonT, "Objetivo", po_objt, 60, 0, WHITE);
    Vector2 pos_pnt = {630, 865};
    DrawTextEx(fonT, "Puntos", pos_pnt, 60, 0, WHITE);
    Vector2 pos_intentos = {1530, 995};
    DrawRectangleRounded(rec_int, 0.35, 0.50, rectangleColor);
    DrawTextEx(fonT, "Intentos:", pos_intentos, 60, 0, WHITE);

    if (selectDino == 1)
    {
        // dibujar a espy
        generate_dinos(frame, runningTime, frameTime, dino1, screenWidth - 2000, screenHeight / 1.45, 24, 0);
    }
    else
    {
        if (selectDino == 2)
        {
            // dibujar a nacky
            generate_dinos(frame, runningTime, frameTime, dino4, screenWidth - 2000, screenHeight / 1.45, 24, 0);
        }
        else
        {
            if (selectDino == 3)
            {
                // dibujar a juan
                generate_dinos(frame, runningTime, frameTime, dino3, screenWidth - 2000, screenHeight / 1.45, 24, 0);
            }
        }
    }

    for (int i = 0; i < MATRIX_HEIGHT; i++)
    {
        for (int j = 0; j < MATRIX_WIDTH; j++)
        {
            rectangulo.x = matrixX + j * (RECTANGLE_SIZE + 10);
            rectangulo.y = matrixY + i * (RECTANGLE_SIZE + 10);

            if (!returnFlag)
            {
                if (CheckCollisionPointRec(GetMousePosition(), rectangulo))
                {
                    enlargedRect = rectangulo;
                    getMouseCollision.x = i;
                    getMouseCollision.y = j;
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {

                        if (!pressedButtonNo2Flag)
                        {
                            playsound(sound1, soundPaused);
                            if (!pressedButtonNo1Flag)
                            {
                                playsound(sound1, soundPaused);
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
                            if (isMousePressedCollision[0].x != -1.0f)
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

    if (pressedButtonNo1Flag && intentos != 0)
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
        Vector2 pos1 = {textX, textY};
        DrawTextEx(fonT, number, pos1, 150, 0, WHITE);
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
            Vector2 pos2 = {textX, textY};

            DrawTextEx(fonT, number, pos2, 150, 0, WHITE);
            drawMatrixSelected(number2, gameMatrix, matrixX, matrixY, (int)isMousePressedCollision[1].x, (int)isMousePressedCollision[1].y, number, preColors, squareMatrixColor[(int)isMousePressedCollision[1].x][(int)isMousePressedCollision[1].y]);
        }
    }

    if (enlargedRect.width > 0)
    {
        drawMatrixCollision(enlargedRect, gameMatrix, squareMatrixColor, preColors); // Check collision and display it (Do not modify unless you want modify how it looks like)
    }

    if (pressedButtonNo2Flag && intentos != 0)
    {
        validate = ValidateMatrix(squareMatrixColor, (int)isMousePressedCollision[0].x, (int)isMousePressedCollision[0].y, (int)isMousePressedCollision[1].x, (int)isMousePressedCollision[1].y);
        if (validate != 0)
        {
            int key = GetKeyPressed();
            if (key >= 48 && key <= 57)
            {
                if (inputLengthNumbers < 2)
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
            if (inputLengthNumbers == 0)
            {
                // Draw text "Ingresa la respuesta"
                Vector2 pos2 = {215, 600};
                DrawTextEx(fonT, "Ingresa la respuesta", pos2, 50, 0, WHITE);
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                mostrar_mnsj = true;
                if (inputLengthNumbers > 0)
                {
                    bool resultFlag;
                    int userInput = atoi(inputNumbers);
                    resultFlag = verificar_suma(gameMatrix, isMousePressedCollision, userInput);

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
                        guessedRight2 = true;
                        currentPoints += 50 * intentos;
                    }
                    else
                    {
                        // In this part, we will display a message saying it wasn't correct.
                        guessedRight2 = false;
                        intentos--;
                        printf("It wasn't correct!\n");
                    }
                    inputLengthNumbers = 0;
                    inputNumbers[0] = '\0';
                }
            }
            else
            {
                Vector2 pos3 = {390, 560};
                DrawTextEx(fonT, inputNumbers, pos3, 155, 0, YELLOW);
                // DrawText(inputNumbers, 520, 580, 150, BLACK); // Display numbers on screen. You can modify this for a different font.
            }
        }
    }

    if (selectDino != 0)
    {
        if (guessedRight2)
        {
            DrawTexture(mnsj_correcto, 200, 650, WHITE);
        }
        else
        {
            if (mostrar_mnsj)
            {
                DrawTexture(mnsj_incorrecto, 200, 650, WHITE);
            }
        }
    }

    // Dibujando puntaje y puntaje maximo
    itoa(intentos, number, 10);
    pos_intentos.y = 1000;
    pos_intentos.x = 1765;
    DrawTextEx(fonT, number, pos_intentos, 55, 0, WHITE);
    itoa(currentPoints, number, 10);
    if (currentPoints < 1000)
    {
        pos_pnt.y = 920;
        pos_pnt.x = 680;
        DrawTextEx(fonT, number, pos_pnt, 55, 0, WHITE);
    }
    else
    {
        pos_pnt.y = 920;
        pos_pnt.x = 650;
        DrawTextEx(fonT, number, pos_pnt, 55, 0, WHITE);
    }
    itoa(maxPoints[0], number, 10);
    pos_pnt.x = 660;
    pos_pnt.y = 815;
    DrawTextEx(fonT, number, pos_pnt, 55, 1, WHITE);
    if (intentos == 0)
    {
        if (!musicPaused)
        {
            PauseMusicStream(NIVEL1);
            UpdateMusicStream(gameover);
        }
        DrawGameOverLevel1();
    }
    if (currentPoints >= maxPoints[0])
    {
        if (!mnsj_win)
        {
            if (!musicPaused)
            {
                PauseMusicStream(NIVEL1);
                UpdateMusicStream(win);
            }
            DrawWin(1);
        }
    }

    EndDrawing();

    if (guessedRight)
    {
        animationChange(squareMatrixColor, gameMatrix, preColors, posicion, frame, runningTime, frameTime, maxPoints, currentPoints, 0);
        tempCorrectedGuess[0][0] = gameMatrix[(int)isMousePressedCollision[0].x][(int)isMousePressedCollision[0].y];
        gameMatrix[(int)isMousePressedCollision[0].x][(int)isMousePressedCollision[0].y] = gameMatrix[(int)isMousePressedCollision[1].x][(int)isMousePressedCollision[1].y];
        gameMatrix[(int)isMousePressedCollision[1].x][(int)isMousePressedCollision[1].y] = tempCorrectedGuess[0][0];

        tempCorrectedGuess[0][0] = squareMatrixColor[(int)isMousePressedCollision[0].x][(int)isMousePressedCollision[0].y];
        squareMatrixColor[(int)isMousePressedCollision[0].x][(int)isMousePressedCollision[0].y] = squareMatrixColor[(int)isMousePressedCollision[1].x][(int)isMousePressedCollision[1].y];
        squareMatrixColor[(int)isMousePressedCollision[1].x][(int)isMousePressedCollision[1].y] = tempCorrectedGuess[0][0];
        modifyMatrix(gameMatrix, preColors, validate, squareMatrixColor, (int)isMousePressedCollision[0].x, (int)isMousePressedCollision[0].y, (int)isMousePressedCollision[1].x, (int)isMousePressedCollision[1].y);
    }
    returnFlag = false;
    return currentPoints;
}

bool verificar_suma(int gameMatrix[][MATRIX_WIDTH], Vector2 position[], int userInput)
{
    int gameNumberSum;
    gameNumberSum = gameMatrix[(int)position[0].x][(int)position[0].y] + gameMatrix[(int)position[1].x][(int)position[1].y];

    if (gameNumberSum == userInput)
    {
        return true;
    }
    return false;
}

void UpdateGameLv1()
{
    Vector2 mousePosition = GetMousePosition();
    Rectangle ajustes = {1820, 40, 300, 80};
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointRec(mousePosition, ajustes))
        {
            playsound(sound1, soundPaused);
            currentGameLevel = OPTIONS2;
        }
        if (CheckMouseOnOptionY("Salir", 70, 0.78))
        {
            playsound(sound1, soundPaused);
            currentGameLevel = WAITING;
            returnFlag2 = true;
        }
    }
}

int DrawGameLv2(int gameMatrix[][MATRIX_WIDTH], int squareMatrixColor[][MATRIX_WIDTH], Color preColors[], Vector2 posicion, int frame, float runningTime, float frameTime, int maxPoints[], int currentPoints)
{
    if (!musicPaused)
    {
        UpdateMusicStream(NIVEL2);
    }
    int matrixX = 405 + (screenWidth - MATRIX_WIDTH * (RECTANGLE_SIZE + 10)) / 2;
    int matrixY = 50 + (screenHeight - MATRIX_HEIGHT * (RECTANGLE_SIZE + 10)) / 2;

    Rectangle rectangulo;
    rectangulo.height = RECTANGLE_SIZE;
    rectangulo.width = RECTANGLE_SIZE;

    Rectangle number1 = {0};
    Rectangle number2 = {0};
    number1 = rectangulo;
    number2 = rectangulo;

    Rectangle displayNumber = {0};
    int tempCorrectedGuess[2][2];

    // Temp values variables. It calculates the position of the text depending on a rectangle.
    float textX;
    float textY;

    // Saves user's input as an array so i can be displayed.
    guessedRight = false;
    Rectangle enlargedRect = {0}; // Temp rectangle to save where the rectangle did collision, so it can be displayed with an animation

    BeginDrawing();
    ClearBackground(BLACK);
    /**** dibujar cosas necesarias para nivel  ***/
    Rectangle rec = {63, 215, 762, 305};
    Rectangle rec2 = {150, 552, 600, 150};
    Rectangle rec3 = {860, 200, 1000, 780};
    Rectangle rec_pnts = {595, 740, 240, 240};
    Rectangle rec_int = {1520, 990, 330, 65};

    Color rectangleColor = {0, 0, 0, 140};
    Color rectangleColor2 = {0, 0, 0, 200};
    Vector2 pos = {375, 285};
    DrawTextureEx(bg_level1_txt, posicion, 0, 1.0f, WHITE);
    DrawRectangleRounded(rec2, .30, .50, rectangleColor2);
    DrawRectangleRounded(rec, .35, .50, rectangleColor);
    DrawRectangleRounded(rec3, .10, .50, rectangleColor);
    DrawTexture(borde, 0, 0, WHITE);
    DrawTexture(bordes, 50, 200, WHITE);
    DrawTexture(icono, screenWidth / 2, 30, WHITE); // FALTTA PONER LOGO DE SUMPY
    DrawTextEx(fonT, "x", pos, 220, 0, WHITE);
    Vector2 pos_nivel = {40, 40};
    DrawTextEx(fonT, "Nivel 2", pos_nivel, 100, 0, WHITE);
    DrawTexture(ajustes, 1800, 30, WHITE);
    DrawRectangleRounded(rec_pnts, 0.30, 0.50, rectangleColor);
    Vector2 po_objt = {600, 750};
    DrawTextEx(fonT, "Objetivo", po_objt, 60, 0, WHITE);
    Vector2 pos_pnt = {630, 865};
    DrawTextEx(fonT, "Puntos", pos_pnt, 60, 0, WHITE);
    Vector2 pos_intentos = {1530, 995};
    DrawRectangleRounded(rec_int, 0.35, 0.50, rectangleColor);
    DrawTextEx(fonT, "Intentos:", pos_intentos, 60, 0, WHITE);

    if (selectDino == 1)
    {
        // dibujar a espy
        generate_dinos(frame, runningTime, frameTime, dino1, screenWidth - 2000, screenHeight / 1.45, 24, 0);
    }
    else
    {
        if (selectDino == 2)
        {
            // dibujar a nacky
            generate_dinos(frame, runningTime, frameTime, dino4, screenWidth - 2000, screenHeight / 1.45, 24, 0);
        }
        else
        {
            if (selectDino == 3)
            {
                // dibujar a juan
                generate_dinos(frame, runningTime, frameTime, dino3, screenWidth - 2000, screenHeight / 1.45, 24, 0);
            }
        }
    }

    for (int i = 0; i < MATRIX_HEIGHT; i++)
    {
        for (int j = 0; j < MATRIX_WIDTH; j++)
        {
            rectangulo.x = matrixX + j * (RECTANGLE_SIZE + 10);
            rectangulo.y = matrixY + i * (RECTANGLE_SIZE + 10);

            if (!returnFlag)
            {
                if (CheckCollisionPointRec(GetMousePosition(), rectangulo))
                {
                    enlargedRect = rectangulo;
                    getMouseCollision.x = i;
                    getMouseCollision.y = j;
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        if (!pressedButtonNo2Flag)
                        {
                            playsound(sound1, soundPaused);
                            if (!pressedButtonNo1Flag)
                            {
                                playsound(sound1, soundPaused);
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
                            if (isMousePressedCollision[0].x != -1.0f)
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

    if (pressedButtonNo1Flag && intentos != 0)
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
        Vector2 pos1 = {textX, textY};
        DrawTextEx(fonT, number, pos1, 150, 0, WHITE);
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
            Vector2 pos2 = {textX, textY};

            DrawTextEx(fonT, number, pos2, 150, 0, WHITE);
            drawMatrixSelected(number2, gameMatrix, matrixX, matrixY, (int)isMousePressedCollision[1].x, (int)isMousePressedCollision[1].y, number, preColors, squareMatrixColor[(int)isMousePressedCollision[1].x][(int)isMousePressedCollision[1].y]);
        }
    }

    if (enlargedRect.width > 0)
    {
        drawMatrixCollision(enlargedRect, gameMatrix, squareMatrixColor, preColors); // Check collision and display it (Do not modify unless you want modify how it looks like)
    }

    if (pressedButtonNo2Flag && intentos != 0)
    {
        validate = ValidateMatrix(squareMatrixColor, (int)isMousePressedCollision[0].x, (int)isMousePressedCollision[0].y, (int)isMousePressedCollision[1].x, (int)isMousePressedCollision[1].y);
        if (validate != 0)
        {
            int key = GetKeyPressed();
            if (key >= 48 && key <= 57)
            {
                if (inputLengthNumbers < 2)
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
            if (inputLengthNumbers == 0)
            {
                // Draw text "Ingresa la respuesta"
                Vector2 pos2 = {215, 600};
                DrawTextEx(fonT, "Ingresa la respuesta", pos2, 50, 0, WHITE);
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                mostrar_mnsj = true;
                if (inputLengthNumbers > 0)
                {
                    bool resultFlag;
                    int userInput = atoi(inputNumbers);
                    resultFlag = verificar_multi(gameMatrix, isMousePressedCollision, userInput);

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
                        guessedRight2 = true;
                        currentPoints += 50 * intentos;
                    }
                    else
                    {
                        // In this part, we will display a message saying it wasn't correct.
                        guessedRight2 = false;
                        intentos--;
                        printf("It wasn't correct!\n");
                    }
                    inputLengthNumbers = 0;
                    inputNumbers[0] = '\0';
                }
            }
            else
            {
                Vector2 pos3 = {390, 560};
                DrawTextEx(fonT, inputNumbers, pos3, 155, 0, YELLOW);
                // DrawText(inputNumbers, 520, 580, 150, BLACK); // Display numbers on screen. You can modify this for a different font.
            }
        }
    }

    if (selectDino != 0)
    {
        if (guessedRight2)
        {
            DrawTexture(mnsj_correcto, 200, 650, WHITE);
        }
        else
        {
            if (mostrar_mnsj)
            {
                DrawTexture(mnsj_incorrecto, 200, 650, WHITE);
            }
        }
    }

    // Dibujando puntaje y puntaje maximo
    itoa(intentos, number, 10);
    pos_intentos.y = 1000;
    pos_intentos.x = 1765;
    DrawTextEx(fonT, number, pos_intentos, 55, 0, WHITE);
    itoa(currentPoints, number, 10);
    if (currentPoints < 1000)
    {
        pos_pnt.y = 920;
        pos_pnt.x = 680;
        DrawTextEx(fonT, number, pos_pnt, 55, 0, WHITE);
    }
    else
    {
        pos_pnt.y = 920;
        pos_pnt.x = 650;
        DrawTextEx(fonT, number, pos_pnt, 55, 0, WHITE);
    }
    itoa(maxPoints[1], number, 10);
    pos_pnt.x = 660;
    pos_pnt.y = 815;
    DrawTextEx(fonT, number, pos_pnt, 55, 1, WHITE);
    if (intentos == 0)
    {
        if (!musicPaused)
        {
            PauseMusicStream(NIVEL2);
            UpdateMusicStream(gameover);
        }
        DrawGameOverLevel2();
    }
    if (currentPoints >= maxPoints[1])
    {
        if (!mnsj_win2)
        {
            if (!musicPaused)
            {
                PauseMusicStream(NIVEL2);
                UpdateMusicStream(win);
            }
            DrawWin(2);
        }
    }
    EndDrawing();

    if (guessedRight)
    {
        animationChange(squareMatrixColor, gameMatrix, preColors, posicion, frame, runningTime, frameTime, maxPoints, currentPoints, 1);
        tempCorrectedGuess[0][0] = gameMatrix[(int)isMousePressedCollision[0].x][(int)isMousePressedCollision[0].y];
        gameMatrix[(int)isMousePressedCollision[0].x][(int)isMousePressedCollision[0].y] = gameMatrix[(int)isMousePressedCollision[1].x][(int)isMousePressedCollision[1].y];
        gameMatrix[(int)isMousePressedCollision[1].x][(int)isMousePressedCollision[1].y] = tempCorrectedGuess[0][0];

        tempCorrectedGuess[0][0] = squareMatrixColor[(int)isMousePressedCollision[0].x][(int)isMousePressedCollision[0].y];
        squareMatrixColor[(int)isMousePressedCollision[0].x][(int)isMousePressedCollision[0].y] = squareMatrixColor[(int)isMousePressedCollision[1].x][(int)isMousePressedCollision[1].y];
        squareMatrixColor[(int)isMousePressedCollision[1].x][(int)isMousePressedCollision[1].y] = tempCorrectedGuess[0][0];
        modifyMatrix(gameMatrix, preColors, validate, squareMatrixColor, (int)isMousePressedCollision[0].x, (int)isMousePressedCollision[0].y, (int)isMousePressedCollision[1].x, (int)isMousePressedCollision[1].y);
    }
    returnFlag = false;
    return currentPoints;
}

bool verificar_multi(int gameMatrix[][MATRIX_WIDTH], Vector2 position[], int userInput)
{
    int gameNumberSum;
    gameNumberSum = gameMatrix[(int)position[0].x][(int)position[0].y] * gameMatrix[(int)position[1].x][(int)position[1].y];

    if (gameNumberSum == userInput)
    {
        return true;
    }
    return false;
}

void DrawOptionsLevel(int frame, float runningTime, float frameTime)
{
    BeginDrawing();
    ClearBackground(WHITE);
    Vector2 postionTexture = {(float)screenWidth / 2 - (float)screenWidth / 2, (float)screenHeight / 2 - (float)screenHeight / 2};
    DrawTextureEx(texture_options, postionTexture, 0, 1.0f, WHITE);

    Color colo1 = {207, 207, 207, 255};
    if (!musicPaused)
    {
        UpdateMusicStream(music);
    }
    Color select = {255, 200, 0, 255};
    /******************************* GENERAR RECTANGULO ******************************/
    generte_rec();
    /**************************** GENERAR DINOSAURIO  *******************************/
    generate_dinos(frame, runningTime, frameTime, dino2, screenWidth / 1.35, screenHeight / 2, 24, 1);
    /********************************************************************************/
    texto_sencillo("Efectos", 0.532, 70, 2.1, 2, false);
    if (soundPaused)
    {
        DrawText("ON", screenWidth / 1.559 - MeasureText("Efectos", 70) / 2, screenHeight / 1.96, 60, colo1);
    }
    else
    {
        DrawText("OFF", screenWidth / 1.559 - MeasureText("Efectos", 70) / 2, screenHeight / 1.96, 60, select);
    }
    texto_sencillo("Musica", 0.620, 70, 2.1, 0.580, true);
    if (musicPaused)
    {
        DrawText("OFF", screenWidth / 1.6 - MeasureText("Musica", 70) / 2, screenHeight * 0.595, 60, select);
    }
    else
    {
        DrawText("ON", screenWidth / 1.6 - MeasureText("Musica", 70) / 2, screenHeight * 0.595, 60, colo1);
    }
    texto_sencillo("Regresar", 0.70, 70, 2, 0.660, true);
    texto_sencillo("Abandonar nivel", 0.78, 70, 2, 0.755, true);

    EndDrawing();
}
void UpdateOptionLevel1()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckMouseOnOptionY("Abandonar nivel", 70, 0.78))
        {
            playsound(sound1, soundPaused);
            currentGameLevel = WAITING;
            inputLengthNumbers = 0;
            inputNumbers[0] = '\0';
            mostrar_mnsj = false;
            guessedRight = false;
            guessedRight2 = false;
            pressedButtonNo1Flag = false;
            pressedButtonNo2Flag = false;
            isMousePressedCollision[0].x = -1.0f;
            returnFlag2 = true;
            intentos = 3;
            mnsj_win = false;
        }
        if (CheckMouseOnOptionY("Regresar", 70, 0.70))
        {
            playsound(sound1, soundPaused);
            returnFlag = true;
            currentGameLevel = LEVEL1;
        }
        if (CheckMouseOnOptionY("Musica", 70, 0.620))
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

void CheckOptions()
{
    Vector2 mousePosition = GetMousePosition();
    Rectangle ajustes = {1820, 40, 300, 80};
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointRec(mousePosition, ajustes))
        {
            playsound(sound1, soundPaused);
            currentGameLevel = OPTIONS2;
        }
    }
}
void UpdateOptionLevel2()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckMouseOnOptionY("Abandonar nivel", 70, 0.78))
        {
            playsound(sound1, soundPaused);
            currentGameLevel = WAITING;
            inputLengthNumbers = 0;
            inputNumbers[0] = '\0';
            mostrar_mnsj = false;
            guessedRight = false;
            guessedRight2 = false;
            pressedButtonNo1Flag = false;
            pressedButtonNo2Flag = false;
            isMousePressedCollision[0].x = -1.0f;
            leaveGameFlag = true;
            intentos = 3;
            mnsj_win2 = false;
        }
        if (CheckMouseOnOptionY("Regresar", 70, 0.70))
        {
            playsound(sound1, soundPaused);
            returnFlag = true;
            currentGameLevel = LEVEL2;
        }
        if (CheckMouseOnOptionY("Musica", 70, 0.620))
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
void CheckWinOptionsLv1()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckMouseOnOptionXandY("No", 75, 1.15, 0.80)) // el usuario gano y  desea salir del juego
        {
            playsound(sound1, soundPaused);
            currentGameLevel = WAITING;
            returnFlag2 = true;
        }
        if (CheckMouseOnOptionXandY("Si", 75, 0.75, 0.80)) // el usuario gano y desea seguir jugando
        {
            mnsj_win = true;
            playsound(sound1, soundPaused);
            PlayMusicStream(NIVEL1);
            currentGameLevel = LEVEL1;
        }
    }
}
void CheckWinOptionsLv2()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckMouseOnOptionXandY("No", 75, 1.15, 0.80)) // el usuario gano y  desea salir del juego
        {
            playsound(sound1, soundPaused);
            currentGameLevel = WAITING;
            leaveGameFlag = true;
        }
        if (CheckMouseOnOptionXandY("Si", 75, 0.75, 0.80)) // el usuario gano y desea seguir jugando
        {
            mnsj_win2 = true;
            playsound(sound1, soundPaused);
            PlayMusicStream(NIVEL2);
            currentGameLevel = LEVEL2;
        }
    }
}
void DrawWin(int num)
{
    Color color1 = {234, 255, 166, 255};
    Color select = {255, 200, 0, 255};
    float fontSize = 80.0f + 10.0f * sinf(GetTime() * 8.0f);
    Color rectangleColor = {0, 0, 0, 140};
    DrawRectangle(0, 0, 1920, 1080, rectangleColor);

    Rectangle rec = {200, 180, 1500, 800};
    Color color_rec = {21, 53, 13, 255};
    Color color_bordes = {12, 29, 7, 255};
    DrawRectangleRounded(rec, 0.35, 0.50, color_rec);
    DrawRectangleRoundedLines(rec, 0.35, 0.50, 20, color_bordes);
    DrawTexture(ganaste, screenWidth / 3.5, 200, WHITE);

    Vector2 pos = {screenWidth / 3.5, screenHeight / 2};
    Vector2 pos2 = {screenWidth / 3.7, screenHeight / 1.8};
    DrawTextEx(fonT, "Has alcanzado el objetivo!", pos, 70, 0, color1);
    DrawTextEx(fonT, "Te gustaria seguir jugando?", pos2, 70, 0, color1);

    Rectangle rec_mini1 = {screenWidth / 2, screenHeight / 1.3, 300, 70};
    DrawRectangleRounded(rec_mini1, 0.35, 0.50, rectangleColor);
    DrawRectangleRoundedLines(rec_mini1, 0.35, 0.50, 10, color_bordes);

    Rectangle rec_mini2 = {screenWidth / 3.3, screenHeight / 1.3, 300, 70};
    DrawRectangleRounded(rec_mini2, 0.35, 0.50, rectangleColor);
    DrawRectangleRoundedLines(rec_mini2, 0.35, 0.50, 10, color_bordes);

    Vector2 pos_si = {screenWidth / 2.8, screenHeight / 1.3};
    Vector2 pos_no = {screenWidth / 1.8, screenHeight / 1.3};
    if (CheckMouseOnOptionXandY("Si", 75, 0.75, 0.80))
    {
        DrawTextEx(fonT, "Si", pos_si, fontSize, 0.0, select);
    }
    else
    {
        DrawTextEx(fonT, "Si", pos_si, 80, 0.0, color1);
    }
    if (CheckMouseOnOptionXandY("No", 75, 1.15, 0.80))
    {
        DrawTextEx(fonT, "No", pos_no, fontSize, 0.0, select);
    }
    else
    {
        DrawTextEx(fonT, "No", pos_no, 80, 0.0, color1);
    }
    if (num == 1)
    {
        CheckWinOptionsLv1();
    }
    else
    {
        CheckWinOptionsLv2();
    }
}
void DrawGameOverLevel1(void)
{
    Color color1 = {234, 255, 166, 255};
    Color rectangleColor = {0, 0, 0, 140};
    DrawRectangle(0, 0, 1920, 1080, rectangleColor);

    Rectangle rec = {200, 180, 1500, 800};
    Color color_rec = {21, 53, 13, 255};
    Color color_bordes = {12, 29, 7, 255};
    DrawRectangleRounded(rec, 0.35, 0.50, color_rec);
    DrawRectangleRoundedLines(rec, 0.35, 0.50, 20, color_bordes);
    DrawTexture(perdiste, screenWidth / 3.5, 200, WHITE);
    Vector2 pos = {screenWidth / 3.5, screenHeight / 2};
    Vector2 pos2 = {screenWidth / 2.6, screenHeight / 1.8};
    DrawTextEx(fonT, "Te has quedado sin intentos", pos, 70, 0, color1);
    DrawTextEx(fonT, "Juega de nuevo!", pos2, 70, 0, color1);
    Rectangle rec_mini = {screenWidth / 2.35, screenHeight / 1.3, 300, 70};
    DrawRectangleRounded(rec_mini, 0.35, 0.50, rectangleColor);
    DrawRectangleRoundedLines(rec_mini, 0.35, 0.50, 10, color_bordes);
    texto_sencillo("Salir", 0.78, 70, 2, 1.3, 0);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckMouseOnOptionY("Salir", 70, 0.78))
        {
            playsound(sound1, soundPaused);
            returnFlag2 = true;
            currentGameLevel = WAITING;
        }
    }
}
void DrawGameOverLevel2(void)
{
    Color color1 = {234, 255, 166, 255};
    Color rectangleColor = {0, 0, 0, 140};
    DrawRectangle(0, 0, 1920, 1080, rectangleColor);

    Rectangle rec = {200, 180, 1500, 800};
    Color color_rec = {21, 53, 13, 255};
    Color color_bordes = {12, 29, 7, 255};
    DrawRectangleRounded(rec, 0.35, 0.50, color_rec);
    DrawRectangleRoundedLines(rec, 0.35, 0.50, 20, color_bordes);
    DrawTexture(perdiste, screenWidth / 3.5, 200, WHITE);
    Vector2 pos = {screenWidth / 3.5, screenHeight / 2};
    Vector2 pos2 = {screenWidth / 2.6, screenHeight / 1.8};
    DrawTextEx(fonT, "Te has quedado sin intentos", pos, 70, 0, color1);
    DrawTextEx(fonT, "Juega de nuevo!", pos2, 70, 0, color1);
    Rectangle rec_mini = {screenWidth / 2.35, screenHeight / 1.3, 300, 70};
    DrawRectangleRounded(rec_mini, 0.35, 0.50, rectangleColor);
    DrawRectangleRoundedLines(rec_mini, 0.35, 0.50, 10, color_bordes);
    texto_sencillo("Salir", 0.78, 70, 2, 1.3, 0);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckMouseOnOptionY("Salir", 70, 0.78))
        {
            playsound(sound1, soundPaused);
            leaveGameFlag = true;
            currentGameLevel = WAITING;
        }
    }
}
//******************************   DINOSAURIOS   *************************************
void DrawCustome(int frame, float runningTime, float frameTime)
{
    BeginDrawing();
    ClearBackground(WHITE);
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
    texto_sencillo("Regresar", 0.84, 70, 2, 0.800, true);
    /**********************************   dinosaurios  ****************************************/
    // X    Y
    Vector2 pos_espy = {370, 420};
    Vector2 pos_nacky = {780, 420};
    Vector2 pos_juan = {1200, 420};

    if (CheckMouseOnOptionXandY("Espy", 70, 0.5, 0.43))
    {
        DrawTextureEx(espy, pos_espy, 0, 1.0f, WHITE);
        generate_dinos(frame, runningTime, frameTime, dino1, (screenWidth / 2 - MeasureText("Regresar", 90) / 2) - 400, 500.f, 24, 0);
    }
    else
    {
        DrawTextureEx(espy, pos_espy, 0, 1.0f, WHITE);
        generate_dino_noAnimated(dino1, 24, (screenWidth / 2 - MeasureText("Regresar", 90) / 2) - 400, 500.f);
    }

    if (CheckMouseOnOptionXandY("Nacky", 70, 1, 0.43))
    {
        DrawTextureEx(nacky, pos_nacky, 0, 1.0f, WHITE);
        generate_dinos(frame, runningTime, frameTime, dino4, screenWidth / 2 - MeasureText("Regresar", 90) / 2, 500.f, 24, 0);
    }
    else
    {
        DrawTextureEx(nacky, pos_nacky, 0, 1.0f, WHITE);
        generate_dino_noAnimated(dino4, 24, screenWidth / 2 - MeasureText("Regresar", 90) / 2, 500.f);
    }
    if (CheckMouseOnOptionXandY("Juan", 80, 1.4, 0.43))
    {
        DrawTextureEx(juan, pos_juan, 0, 1.0f, WHITE);
        generate_dinos(frame, runningTime, frameTime, dino3, (screenWidth / 2 - MeasureText("Regresar", 90) / 2) + 400, 500, 24, 0);
    }
    else
    {
        DrawTextureEx(juan, pos_juan, 0, 1.0f, WHITE);
        generate_dino_noAnimated(dino3, 24, (screenWidth / 2 - MeasureText("Regresar", 90) / 2) + 400, 500.f);
    }
    EndDrawing();
}
void UpdateCustome()
{
    // Lógica de actualización de créditos
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
        // aqui se debe de dibujar la imagen LISTO con probablemente estas posiciones, puede que se tenga que cambiar la posicion Y
        DrawTexture(listo, 550, screenHeight / 7, WHITE);
    }
    else
    {
        // cambiar la textura por la de brayan
        DrawTexture(selectPers, 250, screenHeight / 7, WHITE);
    }
}

void generate_dinos(int frame, float runningTime, float frameTime, Texture2D dinosaurio, float posX, float posY, int maxFrames, int op)
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
void generate_dino_noAnimated(Texture2D dinosaurio, int maxFrames, float posX, float posY)
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

int ValidateMatrix(int squareMatrixColor[][MATRIX_WIDTH], int positionX1, int positionY1, int positionX2, int positionY2)
{

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
                    return 1;
                }
                if (squareMatrixColor[positionX1 - 2][positionY1 - 1] == squareMatrixColor[positionX1][positionY1])
                {
                    //  printf("JOINED 2\n");
                    return 2;
                }
            }

            if (squareMatrixColor[positionX1][positionY1 - 3] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1][positionY1 - 2] == squareMatrixColor[positionX1][positionY1])
                {
                    //  printf("JOINED 3\n");
                    return 3;
                }
            }
            if (squareMatrixColor[positionX1 + 2][positionY1 - 1] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1 + 1][positionY1 - 1] == squareMatrixColor[positionX1][positionY1])
                {
                    //  printf("JOINED 4\n");
                    return 4;
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
                    return 5;
                }
                if (squareMatrixColor[positionX1 - 2][positionY1 + 1] == squareMatrixColor[positionX1][positionY1])
                {

                    // printf("JOINED 2.1\n");
                    return 6;
                }
            }

            if (squareMatrixColor[positionX1][positionY1 + 3] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1][positionY1 + 2] == squareMatrixColor[positionX1][positionY1])
                {

                    // printf("JOINED 3.1\n");
                    return 7;
                }
            }
            if (squareMatrixColor[positionX1 + 2][positionY1 + 1] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1 + 1][positionY1 + 1] == squareMatrixColor[positionX1][positionY1])
                {

                    //  printf("JOINED 4.1\n");
                    return 8;
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
                    return 9;
                }

                if (squareMatrixColor[positionX1 - 1][positionY1 - 2] == squareMatrixColor[positionX1][positionY1])
                {

                    //  printf("JOINED UP 2\n");
                    return 10;
                }
            }

            if (squareMatrixColor[positionX1 - 3][positionY1] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1 - 2][positionY1] == squareMatrixColor[positionX1][positionY1])
                {

                    // printf("JOINED UP 3\n");
                    return 11;
                }
            }
            if (squareMatrixColor[positionX1 - 1][positionY1 + 1] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1 - 1][positionY1 + 2] == squareMatrixColor[positionX1][positionY1])
                {

                    //  printf("JOINED UP 4\n");
                    return 12;
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
                    return 13;
                }

                if (squareMatrixColor[positionX1 + 1][positionY1 - 2] == squareMatrixColor[positionX1][positionY1])
                {
                    // printf("JOINED DOWN 2\n");
                    return 14;
                }
            }

            if (squareMatrixColor[positionX1 + 3][positionY1] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1 + 2][positionY1] == squareMatrixColor[positionX1][positionY1])
                {

                    // printf("JOINED DOWN 3\n");
                    return 15;
                }
            }
            if (squareMatrixColor[positionX1 + 1][positionY1 + 1] == squareMatrixColor[positionX1][positionY1])
            {
                if (squareMatrixColor[positionX1 + 1][positionY1 + 2] == squareMatrixColor[positionX1][positionY1])
                {

                    // printf("JOINED DOWN 4\n");
                    return 16;
                }
            }
        }
    }
    return 0;
}

void modifyMatrix(int gameMatrix[][MATRIX_WIDTH], Color preColors[], int conditionModified, int squareMatrixColor[][MATRIX_WIDTH], int positionX1, int positionY1, int positionX2, int positionY2)
{
    switch (conditionModified)
    {
    case 1:
        gameMatrix[positionX1 - 1][positionY1 - 1] = getRandomNumber(1, 10);
        gameMatrix[positionX1 + 1][positionY1 - 1] = getRandomNumber(1, 10);
        gameMatrix[positionX2][positionY2] = getRandomNumber(1, 10);

        squareMatrixColor[positionX1 - 1][positionY1 - 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX1 + 1][positionY1 - 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX2][positionY2] = getRandomNumber(0, 2);
        break;
    case 2:
        gameMatrix[positionX1 - 1][positionY1 - 1] = getRandomNumber(1, 10);
        gameMatrix[positionX1 - 2][positionY1 - 1] = getRandomNumber(1, 10);
        gameMatrix[positionX2][positionY2] = getRandomNumber(1, 10);

        squareMatrixColor[positionX1 - 1][positionY1 - 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX1 - 2][positionY1 - 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX2][positionY2] = getRandomNumber(0, 2);
        break;
    case 3:
        gameMatrix[positionX1][positionY1 - 3] = getRandomNumber(1, 10);
        gameMatrix[positionX1][positionY1 - 2] = getRandomNumber(1, 10);
        gameMatrix[positionX2][positionY2] = getRandomNumber(1, 10);

        squareMatrixColor[positionX1][positionY1 - 3] = getRandomNumber(0, 2);
        squareMatrixColor[positionX1][positionY1 - 2] = getRandomNumber(0, 2);
        squareMatrixColor[positionX2][positionY2] = getRandomNumber(0, 2);
        break;
    case 4:
        gameMatrix[positionX1 + 2][positionY1 - 1] = getRandomNumber(1, 10);
        gameMatrix[positionX1 + 1][positionY1 - 1] = getRandomNumber(1, 10);
        gameMatrix[positionX2][positionY2] = getRandomNumber(1, 10);

        squareMatrixColor[positionX1 + 2][positionY1 - 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX1 + 1][positionY1 - 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX2][positionY2] = getRandomNumber(0, 2);
        break;
    case 5:
        gameMatrix[positionX1 - 1][positionY1 + 1] = getRandomNumber(1, 10);
        gameMatrix[positionX1 + 1][positionY1 + 1] = getRandomNumber(1, 10);
        gameMatrix[positionX2][positionY2] = getRandomNumber(1, 10);

        squareMatrixColor[positionX1 - 1][positionY1 + 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX1 + 1][positionY1 + 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX2][positionY2] = getRandomNumber(0, 2);
        break;
    case 6:
        gameMatrix[positionX1 - 1][positionY1 + 1] = getRandomNumber(1, 10);
        gameMatrix[positionX1 - 2][positionY1 + 1] = getRandomNumber(1, 10);
        gameMatrix[positionX2][positionY2] = getRandomNumber(1, 10);

        squareMatrixColor[positionX1 - 1][positionY1 + 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX1 - 2][positionY1 + 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX2][positionY2] = getRandomNumber(0, 2);
        break;
    case 7:
        gameMatrix[positionX1][positionY1 + 3] = getRandomNumber(1, 10);
        gameMatrix[positionX1][positionY1 + 2] = getRandomNumber(1, 10);
        gameMatrix[positionX2][positionY2] = getRandomNumber(1, 10);

        squareMatrixColor[positionX1][positionY1 + 3] = getRandomNumber(0, 2);
        squareMatrixColor[positionX1][positionY1 + 2] = getRandomNumber(0, 2);
        squareMatrixColor[positionX2][positionY2] = getRandomNumber(0, 2);

        break;
    case 8:
        gameMatrix[positionX1 + 2][positionY1 + 1] = getRandomNumber(1, 10);
        gameMatrix[positionX1 + 1][positionY1 + 1] = getRandomNumber(1, 10);
        gameMatrix[positionX2][positionY2] = getRandomNumber(1, 10);

        squareMatrixColor[positionX1 + 2][positionY1 + 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX1 + 1][positionY1 + 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX2][positionY2] = getRandomNumber(0, 2);

        break;
    case 9:
        gameMatrix[positionX1 - 1][positionY1 - 1] = getRandomNumber(1, 10);
        gameMatrix[positionX1 - 1][positionY1 + 1] = getRandomNumber(1, 10);
        gameMatrix[positionX2][positionY2] = getRandomNumber(1, 10);

        squareMatrixColor[positionX1 - 1][positionY1 - 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX1 - 1][positionY1 + 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX2][positionY2] = getRandomNumber(0, 2);
        break;
    case 10:
        gameMatrix[positionX1 - 1][positionY1 - 1] = getRandomNumber(1, 10);
        gameMatrix[positionX1 - 1][positionY1 - 2] = getRandomNumber(1, 10);
        gameMatrix[positionX2][positionY2] = getRandomNumber(1, 10);

        squareMatrixColor[positionX1 - 1][positionY1 - 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX1 - 1][positionY1 - 2] = getRandomNumber(0, 2);
        squareMatrixColor[positionX2][positionY2] = getRandomNumber(0, 2);
        break;
    case 11:
        gameMatrix[positionX1 - 3][positionY1] = getRandomNumber(1, 10);
        gameMatrix[positionX1 - 2][positionY1] = getRandomNumber(1, 10);
        gameMatrix[positionX2][positionY2] = getRandomNumber(1, 10);

        squareMatrixColor[positionX1 - 3][positionY1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX1 - 2][positionY1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX2][positionY2] = getRandomNumber(0, 2);
        break;
    case 12: //
        gameMatrix[positionX1 - 1][positionY1 + 1] = getRandomNumber(1, 10);
        gameMatrix[positionX1 - 1][positionY1 + 2] = getRandomNumber(1, 10);
        gameMatrix[positionX2][positionY2] = getRandomNumber(1, 10);

        squareMatrixColor[positionX1 - 1][positionY1 + 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX1 - 1][positionY1 + 2] = getRandomNumber(0, 2);
        squareMatrixColor[positionX2][positionY2] = getRandomNumber(0, 2);
        break;
    case 13:
        gameMatrix[positionX1 + 1][positionY1 - 1] = getRandomNumber(1, 10);
        gameMatrix[positionX1 + 1][positionY1 + 1] = getRandomNumber(1, 10);
        gameMatrix[positionX2][positionY2] = getRandomNumber(1, 10);

        squareMatrixColor[positionX1 + 1][positionY1 - 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX1 + 1][positionY1 + 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX2][positionY2] = getRandomNumber(0, 2);
        break;
    case 14:
        gameMatrix[positionX1 + 1][positionY1 - 1] = getRandomNumber(1, 10);
        gameMatrix[positionX1 + 1][positionY1 - 2] = getRandomNumber(1, 10);
        gameMatrix[positionX2][positionY2] = getRandomNumber(1, 10);

        squareMatrixColor[positionX1 + 1][positionY1 - 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX1 + 1][positionY1 - 2] = getRandomNumber(0, 2);
        squareMatrixColor[positionX2][positionY2] = getRandomNumber(0, 2);
        break;
    case 15:
        gameMatrix[positionX1 + 3][positionY1] = getRandomNumber(1, 10);
        gameMatrix[positionX1 + 2][positionY1] = getRandomNumber(1, 10);
        gameMatrix[positionX2][positionY2] = getRandomNumber(1, 10);

        squareMatrixColor[positionX1 + 3][positionY1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX1 + 2][positionY1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX2][positionY2] = getRandomNumber(0, 2);
        break;
    case 16:
        gameMatrix[positionX1 + 1][positionY1 + 1] = getRandomNumber(1, 10);
        gameMatrix[positionX1 + 1][positionY1 + 2] = getRandomNumber(1, 10);
        gameMatrix[positionX2][positionY2] = getRandomNumber(1, 10);

        squareMatrixColor[positionX1 + 1][positionY1 + 1] = getRandomNumber(0, 2);
        squareMatrixColor[positionX1 + 1][positionY1 + 2] = getRandomNumber(0, 2);
        squareMatrixColor[positionX2][positionY2] = getRandomNumber(0, 2);
        break;
    default:
        break;
    }
}

double easeInOutCirc(double x)
{
    if (x < 0)
    {
        x = 0;
    }

    return 0.5 * (1 - cos(x * 3.1416));
}

void animationChange(int squareMatrixColor[][MATRIX_WIDTH], int gameMatrix[][MATRIX_WIDTH], Color preColors[], Vector2 posicion, int frame, float runningTime, float frameTime, int maxPoints[], int currentPoints, int maxPointsIndex)
{
    int frames = 0;
    const int animationDuration = 80;
    Rectangle rectangulo2;
    Rectangle rectangulo;
    rectangulo2.height = RECTANGLE_SIZE;
    rectangulo2.width = RECTANGLE_SIZE;
    rectangulo.height = RECTANGLE_SIZE;
    rectangulo.width = RECTANGLE_SIZE;
    int matrixX = 405 + (screenWidth - MATRIX_WIDTH * (RECTANGLE_SIZE + 10)) / 2;
    int matrixY = 50 + (screenHeight - MATRIX_HEIGHT * (RECTANGLE_SIZE + 10)) / 2;
    Rectangle startRect;
    Rectangle endRect;
    float textX;
    float textY;
    char number[5];

    startRect.width = RECTANGLE_SIZE;
    startRect.height = RECTANGLE_SIZE;
    startRect.x = matrixX + isMousePressedCollision[0].y * (RECTANGLE_SIZE + 10);
    startRect.y = matrixY + isMousePressedCollision[0].x * (RECTANGLE_SIZE + 10);

    endRect.width = RECTANGLE_SIZE;
    endRect.height = RECTANGLE_SIZE;
    endRect.x = matrixX + isMousePressedCollision[1].y * (RECTANGLE_SIZE + 10);
    endRect.y = matrixY + isMousePressedCollision[1].x * (RECTANGLE_SIZE + 10);

    Rectangle rec = {63, 215, 762, 305};
    Rectangle rec2 = {150, 552, 600, 150};
    Rectangle rec3 = {860, 200, 1000, 780};
    Rectangle rec_pnts = {595, 740, 240, 240};
    Rectangle rec_int = {1520, 990, 330, 65};

    Vector2 pos = {375, 285};
    Vector2 pos_nivel = {40, 40};

    Color rectangleColor = {0, 0, 0, 140};
    Color rectangleColor2 = {0, 0, 0, 200};

    BeginDrawing();

    do
    {

        frames++;
        Vector2 po_objt = {600, 750};
        Vector2 pos_pnt = {630, 865};
        Vector2 pos_intentos = {1530, 995};
        DrawTextureEx(bg_level1_txt, posicion, 0, 1.0f, WHITE);
        if (selectDino == 1)
        {
            // dibujar a espy
            generate_dinos(frame, runningTime, frameTime, dino1, screenWidth - 2000, screenHeight / 1.45, 24, 0);
        }
        else
        {
            if (selectDino == 2)
            {
                // dibujar a nacky
                generate_dinos(frame, runningTime, frameTime, dino4, screenWidth - 2000, screenHeight / 1.45, 24, 0);
            }
            else
            {
                if (selectDino == 3)
                {
                    // dibujar a juan
                    generate_dinos(frame, runningTime, frameTime, dino3, screenWidth - 2000, screenHeight / 1.45, 24, 0);
                }
            }
        }
        DrawRectangleRounded(rec2, .30, .50, rectangleColor2);
        DrawRectangleRounded(rec, .35, .50, rectangleColor);
        DrawRectangleRounded(rec3, .10, .50, rectangleColor);
        DrawTexture(borde, 0, 0, WHITE);
        DrawTexture(bordes, 50, 200, WHITE);
        DrawTexture(icono, screenWidth / 2, 30, WHITE); // FALTTA PONER LOGO DE SUMPY

        DrawTexture(ajustes, 1800, 30, WHITE);
        if (maxPointsIndex)
        {
            DrawTextEx(fonT, "Nivel 2", pos_nivel, 100, 0, WHITE);
            DrawTextEx(fonT, "x", pos, 220, 0, WHITE);
            if (!musicPaused)
            {
                UpdateMusicStream(NIVEL1);
            }
        }
        else
        {
            DrawTextEx(fonT, "Nivel 1", pos_nivel, 100, 0, WHITE);
            DrawTextEx(fonT, "+", pos, 220, 0, WHITE);
            if (!musicPaused)
            {
                // UpdateMusicStream(NIVEL1); <---- Nivel 2
            }
        }
        DrawRectangleRounded(rec_pnts, 0.30, 0.50, rectangleColor);
        DrawTextEx(fonT, "Objetivo", po_objt, 60, 0, WHITE);
        DrawTextEx(fonT, "Puntos", pos_pnt, 60, 0, WHITE);
        DrawRectangleRounded(rec_int, 0.35, 0.50, rectangleColor);
        DrawTextEx(fonT, "Intentos:", pos_intentos, 60, 0, WHITE);

        for (int i = 0; i < MATRIX_HEIGHT; i++)
        {
            for (int j = 0; j < MATRIX_WIDTH; j++)
            {
                if ((i != (int)isMousePressedCollision[0].x || j != (int)isMousePressedCollision[0].y) && (i != (int)isMousePressedCollision[1].x || j != (int)isMousePressedCollision[1].y))
                {
                    rectangulo.x = matrixX + j * (RECTANGLE_SIZE + 10);
                    rectangulo.y = matrixY + i * (RECTANGLE_SIZE + 10);
                    getMouseCollision.x = i;
                    getMouseCollision.y = j;
                    snprintf(number, sizeof(number), "%d", gameMatrix[i][j]);
                    textX = rectangulo.x + (RECTANGLE_SIZE - MeasureText(number, 50)) / 2;
                    textY = rectangulo.y + (RECTANGLE_SIZE - 50) / 2;
                    DrawRectangleRounded(rectangulo, 0.4, 0, preColors[squareMatrixColor[i][j]]);
                    DrawRectangleRoundedLines(rectangulo, 0.4, 20, 2, WHITE);
                    DrawText(number, textX, textY, 50, WHITE);
                }
            }
        }

        textX = rectangulo2.x + (RECTANGLE_SIZE - MeasureText(number, 50)) / 2;
        textY = rectangulo2.y + (RECTANGLE_SIZE - 50) / 2;
        snprintf(number, sizeof(number), "%d", gameMatrix[(int)isMousePressedCollision[0].x][(int)isMousePressedCollision[0].y]);
        DrawRectangleRounded(rectangulo2, 0.4, 0, preColors[squareMatrixColor[(int)isMousePressedCollision[0].x][(int)isMousePressedCollision[0].y]]);
        DrawRectangleRoundedLines(rectangulo2, 0.4, 20, 2, WHITE);
        DrawText(number, textX, textY, 50, WHITE);

        snprintf(number, sizeof(number), "%d", gameMatrix[(int)isMousePressedCollision[1].x][(int)isMousePressedCollision[1].y]);
        rectangulo2.x = animation2(endRect.x, startRect.x, frames / (float)animationDuration);
        rectangulo2.y = animation2(endRect.y, startRect.y, frames / (float)animationDuration);
        DrawRectangleRounded(rectangulo2, 0.4, 0, preColors[squareMatrixColor[(int)isMousePressedCollision[1].x][(int)isMousePressedCollision[1].y]]);
        DrawRectangleRoundedLines(rectangulo2, 0.4, 20, 2, WHITE);
        textX = rectangulo2.x + (RECTANGLE_SIZE - MeasureText(number, 50)) / 2;
        textY = rectangulo2.y + (RECTANGLE_SIZE - 50) / 2;
        DrawText(number, textX, textY, 50, WHITE);
        if (selectDino != 0)
        {
            DrawTexture(mnsj_correcto, 200, 650, WHITE);
        }

        itoa(intentos, number, 10);
        pos_intentos.y = 1000;
        pos_intentos.x = 1765;
        DrawTextEx(fonT, number, pos_intentos, 55, 0, WHITE);
        itoa(currentPoints, number, 10);
        if (currentPoints < 1000)
        {
            pos_pnt.y = 920;
            pos_pnt.x = 680;
            DrawTextEx(fonT, number, pos_pnt, 50, 0, WHITE);
        }
        else
        {
            pos_pnt.y = 920;
            pos_pnt.x = 650;
            DrawTextEx(fonT, number, pos_pnt, 50, 0, WHITE);
        }
        itoa(maxPoints[maxPointsIndex], number, 10);
        pos_pnt.x = 660;
        pos_pnt.y = 815;
        DrawTextEx(fonT, number, pos_pnt, 50, 1, WHITE);

        EndDrawing();
    } while (!WindowShouldClose() && frames < animationDuration);
}

float animation2(float start, float end, float t)
{
    return start + t * t * (3.0f - 2.0f * t) * (end - start);
}

//**************************** FUNCIONES EXTRAS *************************

void cargar_texturas(void)
{
    music = LoadMusicStream("audios_danna\\menu_musica.mp3");
    level1 = LoadMusicStream("audios_danna\\LEVEL_.mp3");
    NIVEL1 = LoadMusicStream("audios_danna\\LEVEL_1.mp3");
    gameover = LoadMusicStream("audios_danna\\gameOver.mp3");
    NIVEL2 = LoadMusicStream("audios_danna\\LEVEL2.mp3");
    win = LoadMusicStream("audios_danna\\win.mp3");
    /*********************************** SONIDOS ***********************************/
    sound1 = LoadSound("audios_danna\\sonido-menu.wav");
    sound2 = LoadSound("audios_danna\\selectDino.mp3");
    sound3 = LoadSound("audios_danna\\selectLevel.mp3");
    icon = LoadImage("imagenes_danna\\icon.png");
    /************************ FUENTES ****************************/
    fonT = LoadFont("fuentes_danna\\Pixellari.ttf");
    /**************************** Background OPTIONS  ******************************/
    background_options = LoadImage("imagenes_danna\\background_options.png");
    ImageResize(&background_options, screenWidth, screenHeight);
    texture_options = LoadTextureFromImage(background_options);
    UnloadImage(background_options);
    /**************************** Background START  ********************************/
    som = LoadImage("imagenes_danna\\sheets\\shadow_2.png");
    ImageResize(&som, 200, 200);
    sombra = LoadTextureFromImage(som);
    texture_logo = LoadTexture("imagenes_danna\\logo.png");
    background_start = LoadImage("imagenes_danna\\background_menu.png");
    ImageResize(&background_start, screenWidth, screenHeight);
    texture_start = LoadTextureFromImage(background_start);
    UnloadImage(som);
    UnloadImage(background_start);
    /***************************** Background CUSTOME **********************************/
    background_custome = LoadImage("imagenes_danna\\background_level2.png");
    ImageResize(&background_custome, screenWidth, screenHeight);
    texture_custome = LoadTextureFromImage(background_custome);
    UnloadImage(background_custome);
    selectPers = LoadTexture("imagenes_danna\\select_character.png");
    listo = LoadTexture("imagenes_danna\\listo.png");
    /********************************** Dinosaurios ***********************************/
    dino1 = LoadTexture("imagenes_danna\\sheets\\DinoSprites - doux.png");
    dino2 = LoadTexture("imagenes_danna\\sheets\\DinoSprites - vita.png");
    dino3 = LoadTexture("imagenes_danna\\sheets\\DinoSprites - mort.png");
    dino4 = LoadTexture("imagenes_danna\\sheets\\DinoSprites - tard.png");
    espy = LoadTexture("imagenes_danna\\ESPY.png");
    nacky = LoadTexture("imagenes_danna\\NACKY.png");
    juan = LoadTexture("imagenes_danna\\JUAN.png");
}

void cargar_texturas_main2(void)
{
    /************************ Background SELECTGAME ******************************/
    background_selectgame = LoadImage("imagenes_danna\\background_selectgame.png");
    ImageResize(&background_selectgame, screenWidth, screenHeight);
    selectgame_txt = LoadTextureFromImage(background_selectgame);
    UnloadImage(background_selectgame);
    /****************************** Background NIVEL 1 *****************************/
    bg_level1 = LoadImage("imagenes_danna\\background_level1.png");
    ImageResize(&bg_level1, screenWidth, screenHeight);
    bg_level1_txt = LoadTextureFromImage(bg_level1);
    UnloadImage(bg_level1);
    /*********************************** Texturas niveles **************************************/
    bordes = LoadTexture("imagenes_danna\\diseno_numeros.png");
    icono = LoadTexture("imagenes_danna\\logoS.png");
    mnsj_correcto = LoadTexture("imagenes_danna\\mnsj_correcto_dino.png");
    mnsj_incorrecto = LoadTexture("imagenes_danna\\mnsj_incorrecto.png");
    borde = LoadTexture("imagenes_danna\\borde.png");
    ajustes = LoadTexture("imagenes_danna\\ajustes.png");
    /***************************  Imagenes de niveles *******************************/
    level1_txt = LoadTexture("imagenes_danna\\selectLevel1-removebg-preview.png");
    level2_txt = LoadTexture("imagenes_danna\\selectLevel2-removebg-preview.png");
    estrellas_vacias = LoadTexture("imagenes_danna\\estrellas_vacias.png");
    estrellas_vacias_1 = LoadTexture("imagenes_danna\\estrella_vacia_1.png");
    estrellas = LoadTexture("imagenes_danna\\estrella.png");
    perdiste = LoadTexture("imagenes_danna\\perdiste.png");
    ganaste = LoadTexture("imagenes_danna\\ganaste.png");
    /******* textura selecciona un nivel*******/
    selecNivel = LoadTexture("imagenes_danna\\SELECCIONA_UN_NIVEL.png");
}

int getRandomNumber(int ri, int rf)
{
    int range = (rf - ri + 1);
    return rand() % range + ri;
}

void texto_sencillo(char texto[], float posicion, float font, float x, float y, bool mult)
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

void verifyLineThree(int squareMatrixColor[][MATRIX_WIDTH])
{
    for (int i = 0; i < MATRIX_HEIGHT; i++)
    {
        for (int j = 0; j < MATRIX_WIDTH; j++)
        {
            if (squareMatrixColor[i - 1][j] == squareMatrixColor[i][j] && squareMatrixColor[i + 1][j] == squareMatrixColor[i][j])
            {
                squareMatrixColor[i][j] = getRandomNumber(0, 2);
            }

            if (squareMatrixColor[i][j - 1] == squareMatrixColor[i][j] && squareMatrixColor[i][j + 1] == squareMatrixColor[i][j])
            {
                squareMatrixColor[i][j] = getRandomNumber(0, 2);
            }
        }
    }
}
//****************************** GUARDAR PARTIDA FUNCIONES *********
void SaveProgressFile(TSaveProgress progress)
{
    FILE *fa;
    fa = fopen("progress.dll", "ab");
    fseek(fa, 0, SEEK_END);
    fwrite(&progress, sizeof(TSaveProgress), 1, fa);
    fclose(fa);
}

TSaveProgress LoadProgressFile()
{
    FILE *fa;
    TSaveProgress temp, penultimate;

    fa = fopen("progress.dll", "rb");
    if (fa)
    {
        if (fread(&temp, sizeof(TSaveProgress), 1, fa))
        {
            penultimate = temp;
            while (fread(&temp, sizeof(TSaveProgress), 1, fa))
            {
                penultimate = temp;
            }
            fclose(fa);
            return penultimate;
        }

        fclose(fa);
    }

    // Si el archivo no existe o está vacío, devolver un valor predeterminado
    temp.lastPointsLevel1 = 0;
    temp.lastPointsLevel2 = 0;
    return temp;
}

/*  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  */
/* ( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o ) */
/*  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  */
/*  /\_/\      __  ___    ___     ____     ______           ____ __  __   /\_/\  */
/* ( o.o )    /  |/  /   /   |   / __ \   / ____/          / __ )\ \/ /  ( o.o ) */
/*  > ^ <    / /|_/ /   / /| |  / / / /  / __/            / __  | \  /    > ^ <  */
/*  /\_/\   / /  / /   / ___ | / /_/ /  / /___           / /_/ /  / /     /\_/\  */
/* ( o.o ) /_/  /_/   /_/  |_|/_____/  /_____/          /_____/  /_/     ( o.o ) */
/*  > ^ <                                                                 > ^ <  */
/*  /\_/\             __ __    ______    ____ _       __ _    __          /\_/\  */
/* ( o.o )           / //_/   / ____/   /  _/| |     / /| |  / /         ( o.o ) */
/*  > ^ <           / ,<     / __/      / /  | | /| / / | | / /           > ^ <  */
/*  /\_/\          / /| |   / /___    _/ /   | |/ |/ /  | |/ /            /\_/\  */
/* ( o.o )        /_/ |_|  /_____/   /___/   |__/|__/   |___/            ( o.o ) */
/*  > ^ <                                                                 > ^ <  */
/*  /\_/\                    ___     _   __    ____                       /\_/\  */
/* ( o.o )                  /   |   / | / /   / __ \                     ( o.o ) */
/*  > ^ <                  / /| |  /  |/ /   / / / /                      > ^ <  */
/*  /\_/\                 / ___ | / /|  /   / /_/ /                       /\_/\  */
/* ( o.o )               /_/  |_|/_/ |_/   /_____/                       ( o.o ) */
/*  > ^ <                                                                 > ^ <  */
/*  /\_/\             _   __    ___     _   __    _   __    ___           /\_/\  */
/* ( o.o )           / | / /   /   |   / | / /   / | / /   /   |         ( o.o ) */
/*  > ^ <           /  |/ /   / /| |  /  |/ /   /  |/ /   / /| |          > ^ <  */
/*  /\_/\          / /|  /   / ___ | / /|  /   / /|  /   / ___ |          /\_/\  */
/* ( o.o )        /_/ |_/   /_/  |_|/_/ |_/   /_/ |_/   /_/  |_|         ( o.o ) */
/*  > ^ <                                                                 > ^ <  */
/*  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  */
/* ( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o ) */
/*  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  */