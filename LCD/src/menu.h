#ifndef MENU_H
#define MENU_H

#include <Adafruit_GFX.h>
#include <screenwrapper.h>
#include <vector>
#include <screen.h>

#define OPTION_WIDTH 350
#define OPTION_HEIGHT 100
#define OPTION_SPACING 50
#define OPTION_Y 50
#define OPTION_X_START 200

class Menu
{
private:
  std::vector<Screen *> screens;

  int selectedScreen = 0;
  int previousScreen = 0;

public:
  Menu() : selectedScreen(0) {}

  void drawSelectedScreen()
  {
    Serial.println("drawing currently selected screen");
    screens[selectedScreen]->draw();
  }

  Screen *getSelectedScreen()
  {
    return screens[selectedScreen];
  }

  void setSelectedScreen(int option)
  {
    previousScreen = selectedScreen;
    selectedScreen = option;
  }

  void nextScreen()
  {
    previousScreen = selectedScreen;
    selectedScreen++;
    if (selectedScreen >= screens.size())
    {
      selectedScreen = 0;
    }
  }

  void prevScreen()
  {
    previousScreen = selectedScreen;

    selectedScreen--;
    if (selectedScreen < 0)
    {
      selectedScreen = screens.size() - 1;
    }
  }

  void addScreen(Screen *s)
  {
    Serial.println("Menu:: Adding screen with buttons " + s->buttons.size());
    screens.push_back(s);
  }
  void removeScreen()
  {
  }
};

#endif
