#pragma once
#include <vec.h>
#include <Adafruit_RA8875.h>
#include <functional>

class Button
{
private:
    /* data */
public:
    using CallbackFunc = std::function<void()>;
    CallbackFunc m_callback;

    Vec2 pos;
    Vec2 scale;
    String text;
    void draw();
    void draw(Vec2 pos_, Vec2 scale_);
    bool detectTouch(int x, int y);
    Button(CallbackFunc callback, String text_);
    Button(String text_);
    ~Button();
};
Button::Button(CallbackFunc callback, String text_)
    : m_callback(callback), text(text_) {}

Button::Button(String text_)
    : text(text_) { Serial.println("button defined"); }

void Button::draw()
{
    Vec2 fixedPos = pos - (scale / 2);

    tft.fillRect(fixedPos.x, fixedPos.y, scale.x, scale.y, RA8875_BLACK);
    tft.drawRect(fixedPos.x, fixedPos.y, scale.x, scale.y, RA8875_CYAN);
    tft.setTextSize(1);
    tft.textEnlarge(1);
    tft.textSetCursor(pos.x - scale.x / 4, pos.y - scale.y / 4);
    tft.print(text);
}
void Button::draw(Vec2 pos_, Vec2 scale_)
{
    pos = pos_;
    scale = scale_;
    draw();
}

bool Button::detectTouch(int x, int y)
{
    if (x > pos.x - scale.x / 2 && x < pos.x + scale.x / 2)
    {
        if (y > pos.y - scale.y / 2 && y < pos.y + scale.y / 2)
        {
            return true;
        }
    }
    return false;
}

Button::~Button()
{
}
