#pragma once
#include <Arduino.h>

const int BAUD_RATE = 9600;

const int KERNELING = 350;
const int FONT_SIZE = 500;

const uint16_t LED_PIN = 5;
// LED_POW 5
const uint16_t CS = 10;
/// @brief Pin to toggle the LDAC on the dac
const uint16_t LDAC = 9;

#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 11
#define SDCARD_MISO_PIN 12
#define SDCARD_SCK_PIN 13

/// @brief Maximum delay the laser experiences when moving, usually from one side of the screen to another.
// 1300 MicroSeconds for Low Resolution
// 1350 Medium resolution
// 1400 Medium- High
// 1450 High, Dots appear
// 1500 Highest, Dots appear
const uint32_t MAX_DELAY = 1500;
/// @brief Minimum delay the laser experiences when moving
const uint32_t MIN_DELAY = 300;

/// @brief Max resolution when drawing circles
const u_int16_t CIRCLE_RESOLUTION = 15;

/// @brief Max Width and Height on a screen
const uint16_t WIDTH = 4096;
const uint16_t HEIGHT = 4096;

const float GRAVITY = 9.81;