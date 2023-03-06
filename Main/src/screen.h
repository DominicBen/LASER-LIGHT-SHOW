#ifndef SCREEN_H
#define SCREEN_H
#include <Arduino.h>
#include <ILI9341_t3.h>

// TFT screen
#define TFT_DC 2
#define TFT_CS 3
#define TFT_RST 255 // 255 = unused, connect to 3.3V
#define TFT_MOSI 11
#define TFT_SCLK 13
#define TFT_MISO 12

class Screen
{
private:
    /* data */
public:
    ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);
    Screen(/* args */);
    ~Screen();
};

Screen::Screen(/* args */)
{
    tft.begin(); // 320x240
    tft.setRotation(3);
    tft.fillScreen(ILI9341_BLACK);
    tft.drawRect(1, 1, 318, 238, ILI9341_WHITE);  // border
    tft.drawRect(10, 105, 2, 30, ILI9341_WHITE);  // left paddle
    tft.drawRect(308, 105, 2, 30, ILI9341_WHITE); // right paddle
    tft.fillCircle(160, 120, 2, ILI9341_WHITE);   // ball
}

Screen::~Screen()
{
}

#endif
