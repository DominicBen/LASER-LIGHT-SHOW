#ifndef MENU_H
#define MENU_H

#include <Adafruit_GFX.h>
#include "Adafruit_RA8875.h"

#define OPTION_WIDTH 350
#define OPTION_HEIGHT 100
#define OPTION_SPACING 50
#define OPTION_Y 50
#define OPTION_X_START 200

class Menu {
  private:
    Adafruit_RA8875& tft;
    int selectedOption;
    int numOptions;
    const char** optionTexts;
    
    void drawOption(const char* text, int y) {
      tft.fillRect(OPTION_X_START, y, OPTION_WIDTH, OPTION_HEIGHT, RA8875_BLACK);
      tft.drawRect(OPTION_X_START, y, OPTION_WIDTH, OPTION_HEIGHT, RA8875_CYAN);
      int16_t x1, y1;
      uint16_t w, h;
      tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
      tft.setCursor(OPTION_X_START + (OPTION_WIDTH - w) / 2, y + (OPTION_HEIGHT - h) / 2);
      tft.print(text);
    }

  public:
    Menu(Adafruit_RA8875& _tft, int _numOptions, const char** _optionTexts) 
      : tft(_tft), selectedOption(0), numOptions(_numOptions), optionTexts(_optionTexts) {}

    void draw() {
      tft.setTextSize(3);
      tft.textMode();
      tft.textEnlarge(3);

      for (int i = 0; i < numOptions; i++) {
        drawOption(optionTexts[i], OPTION_Y + (OPTION_HEIGHT + OPTION_SPACING) * i);
      }

      tft.textEnlarge(2);
      tft.textSetCursor(225, 100);
      if (selectedOption == 0) {
        tft.textWrite(">");
      }
      tft.textWrite(optionTexts[0]);

      for (int i = 1; i < numOptions; i++) {
        tft.textSetCursor(280, 250 + (OPTION_HEIGHT + OPTION_SPACING) * (i - 1));
        if (selectedOption == i) {
          tft.textWrite(">");
        }
        tft.textWrite(optionTexts[i]);
      }

      tft.textEnlarge(2);
    }

    int getSelectedOption() {
      return selectedOption;
    }

    void setSelectedOption(int option) {
      selectedOption = option;
    }

    void nextOption() {
      selectedOption++;
      if (selectedOption >= numOptions) {
        selectedOption = 0;
      }
    }

    void prevOption() {
      selectedOption--;
      if (selectedOption < 0) {
        selectedOption = numOptions - 1;
      }
    }
};

#endif
