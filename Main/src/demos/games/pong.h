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
// #define SDCARD_MISO_PIN 12
// #define SDCARD_SCK_PIN 13

// // p screen
// #define p_DC 2
// #define p_CS 3
// #define p_RST 255 // 255 = unused, connect to 3.3V
// #define p_MOSI 11
// #define p_SCLK 13
// #define p_MISO 12

class Pong : public Demo
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

    // Game Variablesga
    Vec2 rightPaddleOffset = {WIDTH - 300, HEIGHT / 2};
    Vec2 leftPaddleOffset = {300, HEIGHT / 2};
    Vec2 paddleSize = {200, 500};
    float mPaddleSpeed = 20;
    int mMaxBallSpeed;
    int mDifficultyScaling = 10;
    const int mStartingMaxSpeed = 50;

    // Player info
    Color mPlayer1Color = WHITE;
    Color mPlayer2Color = WHITE;
    char mPlayer1Score = '0';
    char mPlayer2Score = '0';
    Char mPlayer1ScoreDisplay = Char(mPlayer1Score);
    Char mPlayer2ScoreDisplay = Char(mPlayer2Score);
    Vec2 mPlayer1ScoreLocation = {WIDTH / 2 - 300, HEIGHT - 300};
    Vec2 mPlayer2ScoreLocation = {WIDTH / 2 + 300, HEIGHT - 300};
    int font_size = 100;
    Transform2D mPlayer1ScoreTransform = Transform2D().setPosition(mPlayer1ScoreLocation).setScale({font_size * 2, font_size});
    Transform2D mPlayer2ScoreTransform = Transform2D().setPosition(mPlayer2ScoreLocation).setScale({font_size * 2, font_size});

    // Game state
    bool gameEnd = false;

    // Audio
    AudioPlaySdWav playWav1;     // xy=88,55
    AudioOutputI2S2 audioOutput; // xy=280,79
    AudioConnection patchCord1 = AudioConnection(playWav1, 0, audioOutput, 0);
    AudioConnection patchCord2 = AudioConnection(playWav1, 1, audioOutput, 1);

    // Game OBjects
    GameObject2D *ball;
    GameObject2D *leftPaddle;
    GameObject2D *rightPaddle;
    GameObject2D *player1border;
    GameObject2D *player2border;
    GameObject2D *player1goal;
    GameObject2D *player2goal;

    Pong(/* args */){};
    ~Pong()
    {
        delete ball;
        delete leftPaddle;
        delete rightPaddle;
        delete player1border;
        delete player2border;
        delete player1goal;
        delete player2goal;
    };

    // Helper Functions

    void restart();
    void init();
    void update();
    void draw();
    void drawHud();
    void win(std::string winner);
    void restartRound();
    void playFile(const char *filename);
};
