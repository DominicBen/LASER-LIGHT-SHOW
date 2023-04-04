#include <Adafruit_GFX.h> // Core graphics library
#include <SPI.h>
#include <Wire.h>
#include <SD.h>
#include <bmp.h>
#include "menu.h"
#include <screen.h>
#include <constants.h>

void bmpDraw(const char *filename, int x, int y);
uint16_t read16(File f);
uint32_t read32(File f);
uint16_t color565(uint8_t r, uint8_t g, uint8_t b);
Menu menu;
Screen *start;
Screen *demos;
Screen *settings;
Screen *gameselect;

int brightness = 255;
int selectedOption = 0;

void drawMenu();
void drawOption(const char *text, int y);
void drawGameSelectMenu();
void drawSettingsMenu();

void setup()
{
  Serial.begin(9600);

  if (!SD.begin(sd_cs))
  {
    Serial.println("SDCARD initialization failed!");
    return;
  }
  Serial.println("RA8875 start");
  /* Initialize the display using 'RA8875_480x80', 'RA8875_480x128', 'RA8875_480x272' or 'RA8875_800x480' */
  if (!tft.begin(RA8875_800x480))
  {
    Serial.println("RA8875 Not Found!");
    while (1)
      ;
  }
  Serial.println("Found RA8875");

  tft.displayOn(true);
  tft.GPIOX(true);                              // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(255);

  Serial.print("(");
  Serial.print(tft.width());
  Serial.print(", ");
  Serial.print(tft.height());
  Serial.println(")");

  tft.touchEnable(true);
  tft.graphicsMode(); // go back to graphics mode
  tft.fillScreen(RA8875_BLACK);
  tft.graphicsMode();
  // bmpDraw("caution.bmp", 0, 0);
  delay(1000);
  // tft.drawRect(0, 0, LCD_WIDTH / 2, LCD_HEIGHT / 2, RA8875_CYAN);

  // bmpDraw("background.bmp", 0, 0);
  Serial.println("Adding start screen");
  // menu.addScreen(demos);
  // menu.addScreen(settings);
  // menu.addScreen(gameselect);
  std::vector<String> temp = {"Game Select", "Demos", "Settings", "About"};
  Serial.println("defining main screen");
  start = new Screen(temp);
  menu.addScreen(start);
  Serial.println("Changing selected screen");
  menu.setSelectedScreen(0);
  Serial.println("Drawing selected screen");
  menu.drawSelectedScreen();
}

void loop()
{
  menu.getSelectedScreen()->detectTouch();
}

// void drawMenu()
// {
//   const char *optionTexts[] = {"Game Select", "Demo", "Settings"};
//   int numOptions = sizeof(optionTexts) / sizeof(optionTexts[0]);
//   Menu menu(tft, numOptions, optionTexts);
//   menu.setSelectedOption(selectedOption);
//   menu.draw();
//   selectedOption = menu.getSelectedOption();
// }
