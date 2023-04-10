#include <LCD/screens/demoscreen.h>

void DemoScreen::init()
{
    Serial.println("DemoScreen::defining main screen");
    Screen::init();

    auto back = [&](int x) -> void
    {
        Serial.println("We are in the callback funtion");
        menuref.prevScreen();
    };
    auto loadDemo = [&](int x) -> void
    {
        Serial.println("We are in the callback funtion");
        menuref.setCurrentDemo(x);
        menuref.setSelectedScreen(5);
    };

    Vec2 listScale = {LCD_WIDTH / 3, LCD_HEIGHT};
    ListComponent *list = (new ListComponent({LCD_WIDTH * 1 / 6, LCD_HEIGHT / 2}, listScale))
                              ->addComponent(new Button("Back", back, 0))
                              ->addComponent(new Button("Shapes", loadDemo, 0))
                              ->addComponent(new Button("Grid", loadDemo, 1))
                              ->addComponent(new Button("Characters", loadDemo, 2))
                              ->addComponent(new Button("Sentences", loadDemo, 3));

    ListComponent *list2 = (new ListComponent({LCD_WIDTH * 3 / 6, LCD_HEIGHT / 2}, listScale))
                               ->addComponent(new Button("Velocity", loadDemo, 4))
                               ->addComponent(new Button("Gravity", loadDemo, 5))
                               ->addComponent(new Button("Collision", loadDemo, 6))
                               ->addComponent(new Button("Balls", loadDemo, 7))
                               ->addComponent(new Button("BeeMovie", loadDemo, 8));
    ListComponent *list3 = (new ListComponent({LCD_WIDTH * 5 / 6, LCD_HEIGHT / 2}, listScale))
                               ->addComponent(new Button("cube3d", loadDemo, 9))
                               ->addComponent(new Button("badapple", loadDemo, 10))
                               ->addComponent(new Button("tbd", loadDemo, 11))
                               ->addComponent(new Button("tbd", loadDemo, 12))
                               ->addComponent(new Button("tbd", loadDemo, 13));

    components.push_back(list);
    components.push_back(list2);
    components.push_back(list3);
}

void DemoScreen::draw()
{

    Screen::draw();
}

void DemoScreen::detectTouch()
{
    Screen::detectTouch();
}