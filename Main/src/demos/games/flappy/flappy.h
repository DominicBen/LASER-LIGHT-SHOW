#pragma once
#include <SPI.h>
// #include <ILI9341_t3.h>
#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <graphics/graphic.h>
#include <string>
#include <SerialFlash.h>
#include <vector>
#include <demos/demo.h>
#include <physics/physicsworld.h>
#include <controller.h>

// #define SDCARD_CS_PIN 10
// #define SDCARD_MOSI_PIN 11
// #define SDCARD_MISO_PIN 12w
// #define SDCARD_SCK_PIN 13

// // p screen
// #define p_DC 2
// #define p_CS 3
// #define p_RST 255 // 255 = unused, connect to 3.3V
// #define p_MOSI 11
// #define p_SCLK 13
// #define p_MISO 12

class Flappy : public Demo
{
private:
public:
    // Physics
    PhysicsWorld2D world;
    PositionSolver solver1 = PositionSolver();
    ImpulseSolver solver2 = ImpulseSolver();

    // Controller player1_input = Controller("943c,c6,38818e");
    Controller player1_input = Controller(PLAYER1SERIAL);
    Controller player2_input = Controller(PLAYER2SERIAL);

    // Game Variables
    float mJumpStrength = 90;
    float mPipeSpeed = 20;
    float mGoalSize = 1200;
    float mGoalRange = 1600;
    float mPipeThickness = 200;
    float mPipeSpawnPoint = WIDTH - 50 - mPipeThickness;
    u_int64_t mScoreCooldown = 1000;

    // Player info
    Color mPlayer1Color = WHITE;
    Color mPlayer2Color = WHITE;
    int mPlayer1Score = 0;
    int mPlayer2Score = 0;
    uint64_t mPlayer1LastScore = 0;
    uint64_t mPlayer2LastScore = 0;
    Char mPlayer1ScoreDisplay = Char(mPlayer1Score);
    Char mPlayer2ScoreDisplay = Char(mPlayer2Score);
    Vec2 mPlayer1ScoreLocation = {WIDTH / 2 - 300, HEIGHT - 300};
    Vec2 mPlayer2ScoreLocation = {WIDTH / 2 + 300, HEIGHT - 300};

    int font_size = 100;
    Transform2D mPlayer1ScoreTransform = Transform2D().setPosition(mPlayer1ScoreLocation).setScale({font_size * 2, font_size});
    Transform2D mPlayer2ScoreTransform = Transform2D().setPosition(mPlayer2ScoreLocation).setScale({font_size * 2, font_size});

    // Game state
    bool gameEnd = false;
    float gameEndTime = 0;
    bool mIsPlayer1Dead = false;
    bool mIsPlayer2Dead = false;

    // Audio
    AudioPlaySdWav playWav1;     // xy=88,55
    AudioOutputI2S2 audioOutput; // xy=280,79
    AudioConnection patchCord1 = AudioConnection(playWav1, 0, audioOutput, 0);
    AudioConnection patchCord2 = AudioConnection(playWav1, 1, audioOutput, 1);

    // Game OBjects
    GameObject2D *player1 = NULL;
    GameObject2D *player2 = NULL;
    GameObject2D *ground = NULL;
    GameObject2D *ceiling = NULL;

    GameObject2D *pipeTop = NULL;
    GameObject2D *pipeBot = NULL;
    GameObject2D *pipeGoal = NULL;
    GameObject2D *player1FinalScore = NULL;
    GameObject2D *player2FinalScore = NULL;

    Flappy(/* args */){};
    ~Flappy(){};

    // Helper Functions

    void restart();
    void init();
    void update();
    void draw();
    void drawHud();
    void gameOver();
    void displayScore();
    void resetPipe();
    void resetPlayers();
    void restartRound();
    void player1Score();
    void player2Score();
    void playFile(const char *filename);
};
