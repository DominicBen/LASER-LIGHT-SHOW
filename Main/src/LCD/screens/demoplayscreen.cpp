#include <LCD/screens/demoplayscreen.h>
void DemoPlayScreen::init()
{
    Serial.println("DemoPlayScreen::defining main screen");
    Screen::init();

    auto back = [&](int x) -> void
    {
        Demo *temp = menuref.mCurDemo;
        menuref.mCurDemo = NULL;
        delete temp;
        menuref.prevScreen();
    };
    auto loadDemo = [&](int x) -> void
    {
        mA = menuref.mCurDemo->getA();
        menuref.mCurDemo->setA(mA + x);
        mA = menuref.mCurDemo->getA();
        draw();
    };
    auto pause = [&](int x) -> void
    {
        menuref.mCurDemo->mIsPaused = !menuref.mCurDemo->mIsPaused;
        draw();
    };
    auto restart = [&](int x) -> void
    {
        menuref.mCurDemo->restart();
    };
    auto changeSpeed = [&](int x) -> void
    {
        mGameSpeed += x * (0.1);
        if (mGameSpeed < 0)
            mGameSpeed = 0;
        if (mGameSpeed > 5)
            mGameSpeed = 5;

        Serial.println(mGameSpeed);
        menuref.mCurDemo->dt = mGameSpeed;
        draw();
    };
    components.push_back((new VariableComponent({LCD_WIDTH * 1 / 8, LCD_HEIGHT * 1 / 4}, {LCD_WIDTH * 1 / 4, LCD_HEIGHT / 2}, "SPEED", 1, 5, &mGameSpeed, changeSpeed)));
    components.push_back((new VariableComponent({LCD_WIDTH * 3 / 8, LCD_HEIGHT * 1 / 4}, {LCD_WIDTH * 1 / 4, LCD_HEIGHT / 2}, "A", 1, 5, &mA, loadDemo)));
    components.push_back((new VariableComponent({LCD_WIDTH * 1 / 8, LCD_HEIGHT * 3 / 4}, {LCD_WIDTH * 1 / 4, LCD_HEIGHT / 2}, "B", 1, 5, &mGameSpeed, changeSpeed)));
    components.push_back((new VariableComponent({LCD_WIDTH * 3 / 8, LCD_HEIGHT * 3 / 4}, {LCD_WIDTH * 1 / 4, LCD_HEIGHT / 2}, "C", 1, 5, &mGameSpeed, changeSpeed)));
    components.push_back((new Button("Pause", pause, 0))
                             ->setPos({LCD_WIDTH * 6 / 8, LCD_HEIGHT * 1 / 4})
                             ->setScale({LCD_WIDTH / 2, LCD_HEIGHT / 2}));
    components.push_back((new Button("Reset", restart, 0))
                             ->setPos({LCD_WIDTH * 5 / 8, LCD_HEIGHT * 3 / 4})
                             ->setScale({LCD_WIDTH / 4, LCD_HEIGHT / 2}));
    components.push_back((new Button("Back", back, 0))
                             ->setPos({LCD_WIDTH * 7 / 8, LCD_HEIGHT * 3 / 4})
                             ->setScale({LCD_WIDTH / 4, LCD_HEIGHT / 2}));
}

void DemoPlayScreen::draw()
{

    Screen::draw();
}

void DemoPlayScreen::detectTouch()
{
    Screen::detectTouch();
}