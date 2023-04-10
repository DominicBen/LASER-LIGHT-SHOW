#include <LCD/screens/aboutscreen.h>
void AboutScreen::init()
{
    Serial.println("AboutScreen::defining main screen");
    Screen::init();

    auto back = [&](int x) -> void
    {
        
        menuref.prevScreen();
    };
    components.push_back((new ListComponent())
                             ->addComponent(new TextComponent("This progject is brought to you by"))
                             ->addComponent(new TextComponent("The Laser Light Show!"))
                             ->addComponent(new TextComponent("Software By Dominic Benintendi"))
                             ->addComponent(new TextComponent("Hardware By Ian Gant"))
                             ->addComponent(new TextComponent("Version 1.0"))
                             ->setScale({LCD_WIDTH / 2, LCD_HEIGHT / 2})
                             ->setPos({LCD_WIDTH / 4, LCD_HEIGHT / 2 + 10}));

    components.push_back((new Button("Back", back, 0))->setScale({150, 100})->setPos({100, 100}));
}

void AboutScreen::draw()
{

    Screen::draw();
}

void AboutScreen::detectTouch()
{
    Screen::detectTouch();
}