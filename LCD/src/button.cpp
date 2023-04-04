#include <button.h>

Button::Button(String text_, Callback callback_) : m_callback(callback_)
{
    text = text_;
}

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
            Serial.println("Button:: Touch detected at button " + text);
            m_callback();
            return true;
        }
    }
    return false;
}

Button::~Button()
{
}
