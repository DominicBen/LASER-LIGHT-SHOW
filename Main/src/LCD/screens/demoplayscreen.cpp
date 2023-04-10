#include <LCD/screens/demoplayscreen.h>
void DemoPlayScreen::init()
{
    Serial.println("DemoPlayScreen::defining main screen");
    Screen::init();

    auto back = [&](int x) -> void
    {
        Serial.println("We are in the callback funtion");
        menuref.prevScreen();
    };
    auto loadDemo = [&](int x) -> void
    {
        Serial.println("We are in the callback funtion");
        menuref.setSelectedScreen(0);
    };
    auto pause = [&](int x) -> void
    {
        mIsPaused = !mIsPaused;
        Serial.println("We are in the callback funtion");
        // menuref.setSelectedScreen(0);
    };
    auto reset = [&](int x) -> void
    {
        Serial.println("We are in the callback funtion");
    };
    auto changeSpeed = [&](int x) -> void
    {
        mGameSpeed += x * (0.1);
        if (mGameSpeed < 0)
            mGameSpeed = 0;
        if (mGameSpeed > 5)
            mGameSpeed = 5;

        Serial.println(mGameSpeed);
        draw();
    };
    components.push_back((new VariableComponent({LCD_WIDTH * 1 / 8, LCD_HEIGHT / 2}, {LCD_WIDTH * (2.0 / 8.0), LCD_HEIGHT}, "SPEED", 1, 5, &mGameSpeed, changeSpeed)));

    components.push_back((new Button("Pause", pause, 0))
                             ->setPos(MIDDLE)
                             ->setScale({LCD_WIDTH / 4, LCD_HEIGHT / 2}));
    components.push_back((new Button("Reset", pause, 0))
                             ->setPos({LCD_WIDTH * (3.0 / 4.0), LCD_HEIGHT * (3.0 / 8.0)})
                             ->setScale({LCD_WIDTH / 4, LCD_HEIGHT / 4}));
    components.push_back((new Button("Back", back, 0))
                             ->setPos({LCD_WIDTH * (3.0 / 4.0), LCD_HEIGHT * (5.0 / 8.0)})
                             ->setScale({LCD_WIDTH / 4, LCD_HEIGHT / 4}));
}

void DemoPlayScreen::draw()
{

    Screen::draw();
}

void DemoPlayScreen::detectTouch()
{
    Screen::detectTouch();
}