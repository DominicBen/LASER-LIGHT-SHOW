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
    Controller player1_input = Controller(28, 29);
    Controller player2_input = Controller(34, 35);

    // Game Variables
    float mJumpStrength = 30;
    float mPipeSpeed = 1;

    // Player info
    Color player1_color = WHITE;
    Color player2_color = WHITE;
    char player1_score = '0';
    char player2_score = '0';
    Char player1_score_display = Char(player1_score);
    Char player2_score_display = Char(player2_score);
    Vec2 player1_score_location = {WIDTH / 2 - 300, HEIGHT - 300};
    Vec2 player2_score_location = {WIDTH / 2 + 300, HEIGHT - 300};
    int font_size = 100;
    Transform2D player1_score_transform = Transform2D().setPosition(player1_score_location).setScale({font_size * 2, font_size});
    Transform2D player2_score_transform = Transform2D().setPosition(player2_score_location).setScale({font_size * 2, font_size});

    // Game state
    bool gameEnd = false;
    bool mIsPlayer1Dead = false;
    bool mIsPlayer2Dead = false;

    // Audio
    AudioPlaySdWav playWav1;     // xy=88,55
    AudioOutputI2S2 audioOutput; // xy=280,79
    AudioConnection patchCord1 = AudioConnection(playWav1, 0, audioOutput, 0);
    AudioConnection patchCord2 = AudioConnection(playWav1, 1, audioOutput, 1);

    // Game OBjects
    GameObject2D *player1;
    GameObject2D *player2;
    GameObject2D *ground;
    GameObject2D *pipeTop;
    GameObject2D *pipeBot;

    Flappy(/* args */){};
    ~Flappy(){};

    // Helper Functions

    void restart();
    void init();
    void update();
    void draw();
    void drawHud();
    void win(std::string winner);
    void resetPipe();
    void restartRound();
    void playFile(const char *filename);
};
