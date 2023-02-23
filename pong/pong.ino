#include <SPI.h>
#include <ILI9341_t3.h>
#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SerialFlash.h>

// Audio shield
AudioPlaySdWav playWav1;    // xy=88,55
AudioOutputI2S audioOutput; // xy=280,79
AudioConnection patchCord1(playWav1, 0, audioOutput, 0);
AudioConnection patchCord2(playWav1, 1, audioOutput, 1);
AudioControlSGTL5000 sgtl5000_1; // xy=209,140
#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 11
#define SDCARD_MISO_PIN 12
#define SDCARD_SCK_PIN 13

// TFT screen
#define TFT_DC 2
#define TFT_CS 3
#define TFT_RST 255 // 255 = unused, connect to 3.3V
#define TFT_MOSI 11
#define TFT_SCLK 13
#define TFT_MISO 12
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);

int ballX = 160;
int ballY = 120;
int ballSpeedX = -1;
int ballSpeedY = 1;

int rightPaddleX = 308;
int rightPaddleY = 105;

int leftPaddleX = 10;
int leftPaddleY = 105;

char player1 = '0';
char player2 = '0';

bool gameEnd = false;

void setup()
{
  Serial.begin(9600);
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  SPI.setMISO(SDCARD_MISO_PIN);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN)))
  {
    // stop here, but print a message repetitively
    while (1)
    {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  tft.begin(); // 320x240
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  tft.drawRect(1, 1, 318, 238, ILI9341_WHITE);  // border
  tft.drawRect(10, 105, 2, 30, ILI9341_WHITE);  // left paddle
  tft.drawRect(308, 105, 2, 30, ILI9341_WHITE); // right paddle
  tft.fillCircle(160, 120, 2, ILI9341_WHITE);   // ball
  pinMode(41, INPUT_PULLUP);
  pinMode(40, INPUT_PULLUP);
  pinMode(37, INPUT_PULLUP);
  pinMode(36, INPUT_PULLUP);
}


void loop()
{
  Serial.println("Test");
  delay(500);
}
// void loop()
// {
//   Serial.println("Test");
//   if (gameEnd == false)
//   {
//     if (ballY >= 234)
//     { // bottom bounce
//       ballSpeedY *= -1;
//       playFile("bounce.WAV");
//       delay(25);
//     }
//     if (ballY <= 5)
//     { // top bounce
//       ballSpeedY *= -1;
//       playFile("bounce.WAV");
//       delay(25);
//     }
//     if (ballX >= rightPaddleX - 4 && ballY >= rightPaddleY && ballY <= rightPaddleY + 30)
//     { // right paddle bounce
//       ballSpeedX *= -1;
//       playFile("bounce.WAV");
//       delay(25);
//     }
//     if (ballX <= leftPaddleX + 5 && ballY >= leftPaddleY && ballY <= leftPaddleY + 30)
//     { // left paddle bounce
//       ballSpeedX *= -1;
//       playFile("bounce.WAV");
//       delay(25);
//     }
//     if (ballX >= 315)
//     { // right goal
//       player1++;
//       playFile("goal.WAV");
//       delay(25);
//       resetRound();
//     }
//     if (ballX <= 5)
//     { // left goal
//       player2++;
//       playFile("goal.WAV");
//       delay(25);
//       resetRound();
//     }
//     tft.drawChar(100, 15, player1, ILI9341_WHITE, 2, 3);
//     tft.drawChar(200, 15, player2, ILI9341_WHITE, 2, 3);
//     tft.fillCircle(ballX, ballY, 2, ILI9341_BLACK); // ball
//     ballX += ballSpeedX;
//     ballY += ballSpeedY;
//     tft.fillCircle(ballX, ballY, 2, ILI9341_WHITE); // ball
//     tft.drawRect(1, 1, 318, 238, ILI9341_WHITE);    // border

//     tft.drawRect(10, leftPaddleY, 2, 30, ILI9341_BLACK);   // left paddle
//     tft.drawRect(308, rightPaddleY, 2, 30, ILI9341_BLACK); // right paddle
//     if (digitalRead(41) == LOW)
//     {
//       leftPaddleY += 1;
//     }
//     if (digitalRead(40) == LOW)
//     {
//       leftPaddleY -= 1;
//     }
//     if (digitalRead(37) == LOW)
//     {
//       rightPaddleY += 1;
//     }
//     if (digitalRead(36) == LOW)
//     {
//       rightPaddleY -= 1;
//     }
//     tft.drawRect(10, leftPaddleY, 2, 30, ILI9341_WHITE);   // left paddle
//     tft.drawRect(308, rightPaddleY, 2, 30, ILI9341_WHITE); // right paddle

//     delay(15);
//   }
//   if (player1 >= '9')
//   {
//     gameEnd = true;
//     win(1);
//   }
//   if (player2 >= '9')
//   {
//     gameEnd = true;
//     win(2);
//   }
// }

void win(int winner)
{
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(20, 40);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(6);
  tft.print("PLAYER ");
  tft.println(winner);
  tft.print(" ");
  tft.print("WINNER");
  playFile("victory.WAV");
  delay(7000);
}

void resetRound()
{
  ballX = 160;
  ballY = 120;
  tft.fillScreen(ILI9341_BLACK);
  tft.drawRect(1, 1, 318, 238, ILI9341_WHITE); // border
  tft.fillCircle(160, 120, 2, ILI9341_WHITE);  // ball
}

void playFile(const char *filename)
{
  playWav1.play(filename);
}
