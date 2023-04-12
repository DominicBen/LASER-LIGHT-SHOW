#pragma once
#include <SPI.h>
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



class Breakout : public Demo
{
private:
public:
    // Physics
    PhysicsWorld2D world;
    PositionSolver solver1 = PositionSolver();
    ImpulseSolver solver2 = ImpulseSolver();

   
    Controller player1_input = Controller(28, 29);

    // Game Variables
    Vec2 PaddleOffset = {WIDTH/2, 100};
    Vec2 paddleSize = {500, 100};
    Vec2 brickSize = {WIDTH/6,HEIGHT/6}; // five bricks + 1/2 + 1/2 offset
    Vec2 brickA = {WIDTH/6 + (WIDTH/6)*0,(HEIGHT/6)*6 - HEIGHT/12};
    Vec2 brickB = {WIDTH/6 + (WIDTH/6)*1,(HEIGHT/6)*6 - HEIGHT/12};
    Vec2 brickC = {WIDTH/6 + (WIDTH/6)*2,(HEIGHT/6)*6 - HEIGHT/12};
    Vec2 brickD = {WIDTH/6 + (WIDTH/6)*3,(HEIGHT/6)*6 - HEIGHT/12};
    Vec2 brickE = {WIDTH/6 + (WIDTH/6)*4,(HEIGHT/6)*6 - HEIGHT/12};
    Vec2 brickF = {(WIDTH/6)*1 - WIDTH/12,(HEIGHT/6)*5 - HEIGHT/12};
    Vec2 brickG = {(WIDTH/6)*2 - WIDTH/12,(HEIGHT/6)*5 - HEIGHT/12};
    Vec2 brickH = {(WIDTH/6)*3 - WIDTH/12,(HEIGHT/6)*5 - HEIGHT/12};
    Vec2 brickI = {(WIDTH/6)*4 - WIDTH/12,(HEIGHT/6)*5 - HEIGHT/12};
    Vec2 brickJ = {(WIDTH/6)*5 - WIDTH/12,(HEIGHT/6)*5 - HEIGHT/12};
    Vec2 brickK = {(WIDTH/6)*6 - WIDTH/12,(HEIGHT/6)*5 - HEIGHT/12};
    Vec2 brickL = {WIDTH/6 + (WIDTH/6)*0,(HEIGHT/6)*4 - HEIGHT/12};
    Vec2 brickM = {WIDTH/6 + (WIDTH/6)*1,(HEIGHT/6)*4 - HEIGHT/12};
    Vec2 brickN = {WIDTH/6 + (WIDTH/6)*2,(HEIGHT/6)*4 - HEIGHT/12};
    Vec2 brickO = {WIDTH/6 + (WIDTH/6)*3,(HEIGHT/6)*4 - HEIGHT/12};
    Vec2 brickP = {WIDTH/6 + (WIDTH/6)*4,(HEIGHT/6)*4 - HEIGHT/12};
    float paddleSpeed = 75;
    Vec2 ballSpeed = {-50, 24};

    // Player info
    Color player1_color = WHITE;
    Color topBricks = RED;
    Color middleBricks = BLUE;
    Color bottomBricks = GREEN;
    int font_size = 100;
    // Game state
    bool gameEnd = false;

    // Audio
    AudioPlaySdWav playWav1;     // xy=88,55
    AudioOutputI2S2 audioOutput; // xy=280,79
    AudioConnection patchCord1 = AudioConnection(playWav1, 0, audioOutput, 0);
    AudioConnection patchCord2 = AudioConnection(playWav1, 1, audioOutput, 1);

    // Game OBjects
    GameObject2D *ball;
    GameObject2D *Paddle;
    GameObject2D *border;
    GameObject2D *brick11;  //(1,1)
    GameObject2D *brick12;  //(1,2)
    GameObject2D *brick13;  //(1,3)
    GameObject2D *brick14;  //(1,4)
    GameObject2D *brick15;  //(1,5)
    GameObject2D *brick21;  //(2,1)
    GameObject2D *brick22;  //(2,2)
    GameObject2D *brick23;  //(2,3)
    GameObject2D *brick24;  //(2,4)
    GameObject2D *brick25;  //(2,5)
    GameObject2D *brick26;  //(2,6)
    GameObject2D *brick31;  //(3,1)
    GameObject2D *brick32;  //(3,2)
    GameObject2D *brick33;  //(3,3)
    GameObject2D *brick34;  //(3,4)
    GameObject2D *brick35;  //(3,5)

    Breakout(/* args */){};
    ~Breakout(){};

    // Helper Functions

    void restart();
    void init();
    void update();
    void draw();
    void win(std::string winner);
    void restartRound();
    void playFile(const char *filename);
};
