#include <LCD/components/textcomponent.h>

void TextComponent::draw()
{
    tft.textMode();
    tft.setTextSize(1);
    tft.textEnlarge(1);
    tft.textSetCursor(pos.x - scale.x / 4, pos.y - scale.y / 4);
    tft.print(text);
    if (data != NULL)
    {
        tft.print(*data);
        Serial.print("TextComponent: Printing Variable");
        Serial.println(*data);
    }
}
// void TextComponent::draw(Vec2 pos_, Vec2 scale_)
// {
//     pos = pos_;
//     scale = scale_;
//     draw();
// }
TextComponent::TextComponent(String text_, float *data_) : data(data_)
{
    text = text_;
}
TextComponent::TextComponent(String text_) : data()
{

    text = text_;
}
