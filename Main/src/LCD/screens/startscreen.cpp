
#include <LCD/screens/startscreen.h>

void StartScreen::init()
{
    Serial.println("MainScreen::defining main screen");
    Screen::init();

    auto changeToDemos = [&](int x) -> void
    {
        Serial.println("We are in the callback funtion");
        menuref.setSelectedScreen(x);
    };
    ListComponent *list = (new ListComponent({LCD_WIDTH / 2, LCD_HEIGHT / 2}, {LCD_WIDTH / 2, LCD_HEIGHT}))
                              ->addComponent(new Button(String("Game Select"), changeToDemos, 1))
                              ->addComponent(new Button("Demos", changeToDemos, 2))
                              ->addComponent(new Button("Settings", changeToDemos, 3))
                              ->addComponent(new Button("About", changeToDemos, 4));
    components.push_back(list);
    Serial.println("MainScreen::Defined");
}

void StartScreen::draw()
{

    Screen::draw();
}

void StartScreen::detectTouch()
{
    Screen::detectTouch();
}