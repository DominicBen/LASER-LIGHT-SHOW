#pragma once
#include <Arduino.h>

const int BAUD_RATE = 9600;

const int KERNELING = 350;
const int FONT_SIZE = 500;

const uint16_t RED_LED = 6;
const uint16_t GREEN_LED = 8;
const uint16_t BLUE_LED = 5;
// LED_POW 5
const uint16_t CS = 10;
/// @brief Pin to toggle the LDAC on the dac
const uint16_t LDAC = 9;
const uint16_t START_MAX_DELAY = 1500;
const uint16_t START_MIN_DELAY = 300;

#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 11
#define SDCARD_MISO_PIN 12
#define SDCARD_SCK_PIN 13
#define PLAYER1SERIAL 16, 17
#define PLAYER2SERIAL 34, 35

/// @brief Maximum delay the laser experiences when moving, usually from one side of the screen to another.
// 1300 MicroSeconds for Low Resolution
// 1350 Medium resolution
// 1400 Medium- High
// 1450 High, Dots appear
// 1500 Highest, Dots appear

/// @brief Max resolution when drawing circles
const u_int16_t CIRCLE_RESOLUTION = 10;

/// @brief Max Width and Height on a screen
const uint16_t WIDTH = 4096;
const uint16_t HEIGHT = 4096;

const float GRAVITY = 9.81;

//
// LCD
//

#define sd_cs BUILTIN_SDCARD // using ethernet shield sd

// Library only supports hardware SPI at this time
// Connect SCLK to UNO Digital #13 (Hardware SPI clock)
// Connect MISO to UNO Digital #12 (Hardware SPI MISO)
// Connect MOSI to UNO Digital #11 (Hardware SPI MOSI)
#define RA8875_CS 24
#define RA8875_INT 33
#define RA8875_RESET 32
// options boxes
// #define OPTION_WIDTH 350
// #define OPTION_HEIGHT 100
// #define OPTION_SPACING 50
// // menu options
// #define OPTION_Y 50
// #define OPTION_X_START 200
// pressure for the touchscreen
#define MINPRESSURE 10
#define MAXPRESSURE 1000
// Connecting touchscreen for User Input
#define TS_CS 0
#define TOUCH_COOLDOWN 200
const int LCD_WIDTH = 800;
const int LCD_HEIGHT = 480;
#define MIDDLE                        \
    {                                 \
        LCD_WIDTH / 2, LCD_HEIGHT / 2 \
    }
