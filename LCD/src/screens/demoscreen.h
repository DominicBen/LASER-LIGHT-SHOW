#include <screen.h>

class DemoScreen : public Screen
{
private:
    /* data */
    void draw() override;
    void detectTouch() override;
    void init() override;

public:
    DemoScreen(Menu *menu) : Screen(menu) { init(); };
    ~DemoScreen(){};
};

void DemoScreen::init()
{
    Serial.println("DemoScreen::defining main screen");
    Screen::init();

    auto changeToDemos = [&]() -> void
    {
        Serial.println("We are in the callback funtion");
        menuref->setSelectedScreen(0);
    };
    ListComponent *list = (new ListComponent({LCD_WIDTH / 2, LCD_HEIGHT / 2}, {LCD_WIDTH / 2, LCD_HEIGHT}))
                              ->addButton(new Button(String("Main Menu"), changeToDemos))
                              ->addButton(new Button("Rotating Cube Demo", changeToDemos));

    components.push_back(list);
}

void DemoScreen::draw()
{

    Screen::draw();
}

void DemoScreen::detectTouch()
{
    Screen::detectTouch();
}