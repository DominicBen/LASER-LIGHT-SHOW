#pragma once

#define sd_cs BUILTIN_SDCARD // using ethernet shield sd

// Library only supports hardware SPI at this time
// Connect SCLK to UNO Digital #13 (Hardware SPI clock)
// Connect MISO to UNO Digital #12 (Hardware SPI MISO)
// Connect MOSI to UNO Digital #11 (Hardware SPI MOSI)
#define RA8875_INT 33
#define RA8875_CS 0
#define RA8875_RESET 34
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
const int LCD_WIDTH = 800;
const int LCD_HEIGHT = 480;
