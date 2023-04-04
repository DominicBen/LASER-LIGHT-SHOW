#include <screen.h>

class StartScreen : public Screen
{
private:
    /* data */
    void draw() override;
    void detectTouch() override;
    void init() override;

public:
    StartScreen(Menu *menu) : Screen(menu) { init(); };
    ~StartScreen(){};
};

void StartScreen::init()
{
    Serial.println("MainScreen::defining main screen");
    Screen::init();

    auto changeToDemos = [&]() -> void
    {
        Serial.println("We are in the callback funtion");
        menuref->setSelectedScreen(1);
    };
    ListComponent *list = (new ListComponent({LCD_WIDTH / 2, LCD_HEIGHT / 2}, {LCD_WIDTH / 2, LCD_HEIGHT}))
                              ->addButton(new Button(String("Game Select"), changeToDemos))
                              ->addButton(new Button("Demos", changeToDemos))
                              ->addButton(new Button("Settings", changeToDemos))
                              ->addButton(new Button("About", changeToDemos));
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