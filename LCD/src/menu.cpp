#include <menu.h>

void Menu::drawSelectedScreen()
{
    Serial.println("drawing currently selected screen ... " + selectedScreen);
    changedScreens = true;
    bmpDraw("background.bmp", 0, 0);

    screens[selectedScreen]->draw();
}

Screen *Menu::getSelectedScreen()
{
    return screens[selectedScreen];
}

void Menu::setSelectedScreen(int option)
{
    previousScreen = selectedScreen;
    selectedScreen = option;
    drawSelectedScreen();
}

void Menu::nextScreen()
{
    previousScreen = selectedScreen;
    selectedScreen++;
    if (selectedScreen >= screens.size())
    {
        selectedScreen = 0;
    }
    drawSelectedScreen();
}

void Menu::prevScreen()
{
    previousScreen = selectedScreen;

    selectedScreen--;
    if (selectedScreen < 0)
    {
        selectedScreen = screens.size() - 1;
    }
    drawSelectedScreen();
}

void Menu::addScreen(Screen *s)
{
    Serial.println("Menu:: Adding screen with buttons " + s->components.size());
    screens.push_back(s);
}
void Menu::removeScreen()
{
}