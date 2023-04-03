#include <SPI.h>
#include <ILI9341_t3.h>
#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <mesh.h>
#include <shape.h>
#include <char.h>
#include <string>
#include <SerialFlash.h>
#include <vector>
#include "game.h"
#include "physicsworld.h"
#include <controller.h>

#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 11
#define SDCARD_MISO_PIN 12
#define SDCARD_SCK_PIN 13

// p screen
#define p_DC 2
#define p_CS 3
#define p_RST 255 // 255 = unused, connect to 3.3V
#define p_MOSI 11
#define p_SCLK 13
#define p_MISO 12

class Pong : public Game
{
private:
public:
    // Physics
    PhysicsWorld2D world;
    PositionSolver solver1 = PositionSolver();
    ImpulseSolver solver2 = ImpulseSolver();

    Controller player1_input = Controller("943c,c6,38818e");

    // Game Variables
    Vec2 rightPaddleOffset = {WIDTH - 300, HEIGHT / 2};
    Vec2 leftPaddleOffset = {300, HEIGHT / 2};
    Vec2 paddleSize = {100, 500};
    float paddleSpeed = 75;
    Vec2 ballSpeed = {-50, 24};

    // Player info
    Color player1_color = GREEN;
    Color player2_color = GREEN;
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

    AudioPlaySdWav playWav1;    // xy=88,55
    AudioOutputI2S audioOutput; // xy=280,79
    AudioConnection patchCord1 = AudioConnection(playWav1, 0, audioOutput, 0);
    AudioConnection patchCord2 = AudioConnection(playWav1, 1, audioOutput, 1);
    AudioControlSGTL5000 sgtl5000_1; // xy=209,140

    Graphic *ballg = new Shape(Graphic::Circle);
    Graphic *floorg = new Shape(Graphic::Rectangle);

    GameObject2D *ball = (new GameObject2D(ballg))->setPosition({WIDTH / 2, HEIGHT / 2})->setScale({100, 100})->setColor(WHITE)->fitColliderToObject();
    GameObject2D *leftPaddle = (new GameObject2D(floorg))->setPosition(leftPaddleOffset)->setScale(paddleSize)->setColor(player1_color)->fitColliderToObject();
    GameObject2D *rightPaddle = (new GameObject2D(floorg))->setPosition(rightPaddleOffset)->setScale(paddleSize)->setColor(player2_color)->fitColliderToObject();
    GameObject2D *player1border = (new GameObject2D(floorg))->setPosition({WIDTH / 4, HEIGHT / 2})->setScale({WIDTH / 2, HEIGHT - 1})->setColor(player1_color);
    GameObject2D *player2border = (new GameObject2D(floorg))->setPosition({(WIDTH - WIDTH / 4), HEIGHT / 2})->setScale({WIDTH / 2 - 1, HEIGHT - 1})->setColor(player2_color);

    Pong(/* args */);
    ~Pong();

    // Helper Functions
    void init();
    void update();
    void draw();
    void drawHud();
    void win(std::string winner);
    void resetRound();
    void playFile(const char *filename);
};

void Pong::init()
{
    // Serial.begin(BAUD_RATE);
    AudioMemory(8);
    sgtl5000_1.enable();
    sgtl5000_1.volume(1);

    player1_input.pair();
    // SPI.setMISO(SDCARD_MISO_PIN);
    // SPI.setMOSI(SDCARD_MOSI_PIN);
    // SPI.setSCK(SDCARD_SCK_PIN);

    // if (!(SD.begin(BUILTIN_SDCARD)))
    // {
    //     // stop here, but print a message repetitively
    //     while (1)
    //     {
    //         Serial.println("Unable to access the SD card");
    //         delay(500);
    //     }
    // }
    // delay(1000);

    ball->velocity = ballSpeed;
    ball->is_gravity = false;

    leftPaddle->is_gravity = false;
    leftPaddle->is_collision = true;
    leftPaddle->is_static = true;
    rightPaddle->is_gravity = false;
    rightPaddle->is_collision = true;
    rightPaddle->is_static = true;
    player1border->is_collision = false;
    player1border->is_gravity = false;
    player1border->is_static = true;
    player2border->is_collision = false;
    player2border->is_gravity = false;
    player2border->is_static = true;

    Serial.println("Filling game vector");

    world.addObject(ball);
    world.addObject(leftPaddle);
    world.addObject(rightPaddle);
    world.addObject(player1border);
    world.addObject(player2border);

    world.addSolver(&solver1);
    world.addSolver(&solver2);

    // ball

    // pinMode(41, INPUT_PULLUP);
    // pinMode(40, INPUT_PULLUP);
    // pinMode(37, INPUT_PULLUP);
    // pinMode(36, INPUT_PULLUP);
}
void Pong::update()
{

    ControllerState player1_state = player1_input.read();
    world.step(1);

    if (gameEnd == false)
    {
        if (ball->is_collided)
        {
            playFile("bounce.WAV");
        }
        // if (ball.transform.pos.y >= HEIGHT - ball.transform.scale.y)
        // { // bottom bounce
        //     ballSpeedY *= -1;
        //     playFile("bounce.WAV");
        //     delay(25);
        // }
        // if (ball.transform.pos.y <= ball.transform.scale.y)
        // { // top bounce
        //     ballSpeedY *= -1;
        //     playFile("bounce.WAV");
        //     delay(25);
        // }
        // if (ball.transform.pos.x >= rightPaddle.transform.pos.x - 4 && ball.transform.pos.y >= rightPaddle.transform.pos.y && ball.transform.pos.y <= rightPaddle.transform.pos.y + 30)
        // { // right paddle bounce
        //     ballSpeedX *= -1;
        //     playFile("bounce.WAV");
        //     delay(25);
        // }
        // if (ball.transform.pos.x <= leftPaddle.transform.pos.x + 5 && ball.transform.pos.y >= leftPaddle.transform.pos.y && ball.transform.pos.y <= leftPaddle.transform.pos.y + 30)
        // { // left paddle bounce
        //     ballSpeedX *= -1;
        //     playFile("bounce.WAV");
        //     delay(25);
        // }

        if (ball->transform->pos.x >= WIDTH - ball->transform->scale.x)
        { // right goal
            player1_score++;
            playFile("goal.WAV");
            delay(25);
            resetRound();
        }
        if (ball->transform->pos.x <= ball->transform->scale.x)
        { // left goal
            player2_score++;
            playFile("goal.WAV");
            delay(25);
            resetRound();
        }

        if (player1_state.left)
        {
            leftPaddle->transform->pos.y += paddleSpeed;
        }
        if (player1_state.down)
        {
            leftPaddle->transform->pos.y -= paddleSpeed;
        }
        if (player1_state.up)
        {
            rightPaddle->transform->pos.y += paddleSpeed;
        }
        if (player1_state.right)
        {
            rightPaddle->transform->pos.y -= paddleSpeed;
        }

        delay(1);
    }
    if (player1_score >= '9')
    {
        gameEnd = true;
        win("1");
    }
    if (player2_score >= '9')
    {
        gameEnd = true;
        win("2");
    }
}
void Pong::draw()
{
    world.draw();
    player1_score_display.m = Mesh(player1_score);
    player2_score_display.m = Mesh(player2_score);
    player1_score_display.draw(player1_score_transform, player1_color);
    player2_score_display.draw(player2_score_transform, player2_color);
}

Pong::Pong(/* args */)
{
}

Pong::~Pong()
{
}

void Pong::win(std::string winner)
{
    for (size_t i = 0; i < 700; i++)
    {
        // p.fillScreen(ILI9341_BLACK);
        p.format_info.cursor_pos = {100, 3000};
        // p.setTextColor(ILI9341_WHITE);
        // p.setTextSize(6);

        // p.print("player ");
        // // Sentence("player ").draw()
        // p.print(winner);
        // p.println("winner");
        // playFile("victory.WAV");
    }
}

void Pong::resetRound()
{
    int range = 300;
    // gives value between -range/2 to range/2
    range = random(range) - range / 2;
    ball->transform->pos.x = WIDTH / 2 + range;
    ball->transform->pos.y = HEIGHT / 2 + range;
    // p.fillScreen(ILI9341_BLACK);
    // p.drawRect(WIDTH / 2, HEIGHT / 2, WIDTH, HEIGHT); // border
    // p.drawCircle(ballX, ballY, 20);                   // ball
}

void Pong::playFile(const char *filename)
{
    playWav1.play(filename);
}
