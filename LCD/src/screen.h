#pragma once
#include <button.h>
#include <vector>
#include <screenwrapper.h>
class Screen
{
private:
    /* data */
public:
    std::vector<Button *> buttons;
    void addButton(Button *b) { buttons.push_back(b); };
    void draw();
    void detectTouch();

    Vec2 lastTouchPos = {0, 0};

    const int BUTTON_Y_START = 50;
    const int BUTTON_X_START = LCD_WIDTH / 2;
    const int BUTTON_SPACING = 40;
    const int BUTTON_X_SCALE = 300;

    Screen(std::vector<String> buttonTexts);
    ~Screen();
};
void Screen::draw()
{

    Serial.println("Screen::Drawing screen");
    tft.setTextSize(3);
    tft.textMode();
    tft.textEnlarge(3);
    Serial.println("Screen::Text size set");
    Serial.println("Screen::button ratio");
    Serial.print(buttons.size());
    float button_y_ratio = (LCD_HEIGHT - BUTTON_Y_START) / buttons.size();
    float button_y_scale = button_y_ratio - BUTTON_SPACING;
    Serial.println("Screen::button ratio");
    Serial.print(button_y_ratio);
    Serial.println("Screen::button scale");
    Serial.print(button_y_scale);

    for (size_t i = 0; i < buttons.size(); i++)
    {
        Serial.println("Screen::Drawing button");
        buttons[i]->draw({LCD_WIDTH / 2, BUTTON_Y_START + (button_y_ratio)*i}, {BUTTON_X_SCALE, button_y_scale});
    }
}

void Screen::detectTouch()
{
    uint16_t x;
    uint16_t y;
    tft.touched();

    if (tft.touchRead(&x, &y))
    {
        if (lastTouchPos.x == x && lastTouchPos.y == y)
        {
            return;
        }

        lastTouchPos = {x, y};
        Serial.print("Touch detected at x=");
        Serial.print(x);
        Serial.print(", y=");
        Serial.println(y);

        x = map(x, 50, 975, 0, LCD_WIDTH);
        y = map(y, 150, 930, 0, LCD_HEIGHT);

        tft.drawCircle(x, y, 15, RA8875_BLUE);
        for (Button *b : buttons)
        {
            if (b->detectTouch(x, y))
            {
                Serial.println("Touch being detected at button " + b->text);
                break;
            }
        }
    }
}
Screen::Screen(std::vector<String> buttonTexts)
{
    for (int i = 0; i < buttonTexts.size(); i++)
    {
        Serial.println("adding button" + buttonTexts[i]);
        if (buttonTexts[i] == NULL)
        {
            Serial.println("string is null");
        }
        buttons.push_back(new Button(String(buttonTexts[i])));
    }
    Serial.println("done setting all those buttons");
    Serial.print(buttons.size());
}

Screen::~Screen()
{
    buttons.empty();
}
