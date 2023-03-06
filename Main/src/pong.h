#include <SPI.h>
#include <ILI9341_t3.h>
#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SerialFlash.h>
#include "game.h"

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
    AudioPlaySdWav playWav1;    // xy=88,55
    AudioOutputI2S audioOutput; // xy=280,79
    AudioConnection patchCord1 = AudioConnection(playWav1, 0, audioOutput, 0);
    AudioConnection patchCord2 = AudioConnection(playWav1, 1, audioOutput, 1);
    AudioControlSGTL5000 sgtl5000_1; // xy=209,140
    Vec2 rightPaddleOffset = {WIDTH - 300, HEIGHT / 2};
    Vec2 leftPaddleOffset = {300, HEIGHT / 2};
    Shape ball = Shape(Shape::Circle, Transform2D().setPosition({WIDTH / 2, HEIGHT / 2}).setScale({100, 100}));
    Shape leftPaddle = Shape(Shape::Rectangle, Transform2D().setPosition(leftPaddleOffset).setScale({100, 400}));
    Shape rightPaddle = Shape(Shape::Rectangle, Transform2D().setPosition(rightPaddleOffset).setScale({100, 400}));
    Shape border = Shape(Shape::Rectangle, Transform2D().setPosition({WIDTH / 2, HEIGHT / 2}).setScale({WIDTH - 1, HEIGHT - 1}));
    Char player1_score_display = Char('0', Transform2D().setPosition({WIDTH / 2 - 100, 100}));
    Char player2_score_display = Char('0', Transform2D().setPosition({WIDTH / 2 + 100, 100}));

    char player1_score = '0';
    char player2_score = '0';

    int ballSpeedX = -10;
    int ballSpeedY = 10;

    int font_size = 30;

    bool gameEnd = false;
    void init();
    void update();
    void draw();
    void drawHud();

    Pong(/* args */);
    ~Pong();
    // Helper Functions
    void win(std::string winner);
    void resetRound();
    void playFile(const char *filename);
};
void Pong::init()
{
    Serial.begin(9600);
    AudioMemory(8);
    sgtl5000_1.enable();
    sgtl5000_1.volume(1);
    // SPI.setMISO(SDCARD_MISO_PIN);
    // SPI.setMOSI(SDCARD_MOSI_PIN);
    // SPI.setSCK(SDCARD_SCK_PIN);

    if (!(SD.begin(BUILTIN_SDCARD)))
    {
        // stop here, but print a message repetitively
        while (1)
        {
            Serial.println("Unable to access the SD card");
            delay(500);
        }
    }

    // p.begin(); // 320x240
    // p.setRotation(3);
    // p.fillScreen(ILI9341_BLACK);
    // p.drawRect(border);
    // p.drawRect(leftPaddle);
    // p.drawCircle(ball);
    // p.drawRect(rightPaddle);
    // p.drawRect(WIDTH / 2, HEIGHT / 2, WIDTH, HEIGHT); // border
    // p.drawRect(100, HEIGHT / 2, 2, 30);               // left paddle
    // p.drawRect(308, 105, 2, 30);                      // right paddle
    // p.drawCircle(160, 120, 2);                        // ball

    pinMode(41, INPUT_PULLUP);
    pinMode(40, INPUT_PULLUP);
    pinMode(37, INPUT_PULLUP);
    pinMode(36, INPUT_PULLUP);
}
void Pong::update()
{
    if (gameEnd == false)
    {
        if (ball.transform.pos.y >= HEIGHT - ball.transform.scale.y)
        { // bottom bounce
            ballSpeedY *= -1;
            playFile("bounce.WAV");
            delay(25);
        }
        if (ball.transform.pos.y <= ball.transform.scale.y)
        { // top bounce
            ballSpeedY *= -1;
            playFile("bounce.WAV");
            delay(25);
        }
        if (ball.transform.pos.x >= rightPaddle.transform.pos.x - 4 && ball.transform.pos.y >= rightPaddle.transform.pos.y && ball.transform.pos.y <= rightPaddle.transform.pos.y + 30)
        { // right paddle bounce
            ballSpeedX *= -1;
            playFile("bounce.WAV");
            delay(25);
        }
        if (ball.transform.pos.x <= leftPaddle.transform.pos.x + 5 && ball.transform.pos.y >= leftPaddle.transform.pos.y && ball.transform.pos.y <= leftPaddle.transform.pos.y + 30)
        { // left paddle bounce
            ballSpeedX *= -1;
            playFile("bounce.WAV");
            delay(25);
        }
        if (ball.transform.pos.x >= WIDTH - ball.transform.scale.x)
        { // right goal
            player1_score++;
            playFile("goal.WAV");
            delay(25);
            resetRound();
        }
        if (ball.transform.pos.x <= ball.transform.scale.x)
        { // left goal
            player2_score++;
            playFile("goal.WAV");
            delay(25);
            resetRound();
        }
        // p.drawChar(WIDTH - 100, 150, player1, font_size);
        // p.drawChar(WIDTH + 100, 150, player2, font_size);
        // p.drawCircle(ballX, ballY, 2); // ball
        ball.transform.pos.x += ballSpeedX;
        ball.transform.pos.y += ballSpeedY;
        // p.drawCircle(ballX, ballY, 20);                           // ball
        // p.drawRect(WIDTH / 2, HEIGHT / 2, WIDTH - 1, HEIGHT - 1); // border

        // p.drawRect(leftPaddleOffset.x, leftPaddle.transform.pos.y, 2, 30);   // left paddle
        // p.drawRect(rightPaddleOffset.x, rightPaddle.transform.pos.y, 2, 30); // right paddle
        if (digitalRead(41) == LOW)
        {
            leftPaddle.transform.pos.y += 1;
        }
        if (digitalRead(40) == LOW)
        {
            leftPaddle.transform.pos.y -= 1;
        }
        if (digitalRead(37) == LOW)
        {
            rightPaddle.transform.pos.y += 1;
        }
        if (digitalRead(36) == LOW)
        {
            rightPaddle.transform.pos.y -= 1;
        }
        // p.drawRect(leftPaddleOffset.x, leftPaddle.transform.pos.y, 20, 300);   // left paddle
        // p.drawRect(WIDTH / 2, HEIGHT / 2, 20, 300);             // left paddle
        // p.drawRect(rightPaddleOffset.x, rightPaddle.transform.pos.y, 20, 300); // right paddle

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
    player1_score_display.m = Mesh(player1_score);
    player2_score_display.m = Mesh(player2_score);
    p.drawChar(player1_score_display);
    p.drawChar(player2_score_display);
    p.drawRect(leftPaddle);
    p.drawRect(rightPaddle);
    p.drawCircle(ball);
    p.drawRect(border);
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

        p.print("player ");
        p.print(winner);
        p.println("winner");
        playFile("victory.WAV");
    }
}

void Pong::resetRound()
{
    int range = 300;
    // gives value between -range/2 to range/2
    range = random(range) - range / 2;
    ball.transform.pos.x = WIDTH / 2 + range;
    ball.transform.pos.y = HEIGHT / 2 + range;
    // p.fillScreen(ILI9341_BLACK);
    // p.drawRect(WIDTH / 2, HEIGHT / 2, WIDTH, HEIGHT); // border
    // p.drawCircle(ballX, ballY, 20);                   // ball
}

void Pong::playFile(const char *filename)
{
    playWav1.play(filename);
}
