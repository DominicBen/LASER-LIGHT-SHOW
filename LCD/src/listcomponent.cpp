#include <listcomponent.h>

bool ListComponent::detectTouch(int x, int y)
{
    for (Button *b : buttons)
    {
        if (b->detectTouch(x, y))
        {
            Serial.println("LIST::Touch being detected at button " + b->text);
            return true;
        }
    }
    return false;
}
// ListComponent::ListComponent(std::vector<String> buttonTexts)
// {
//     for (u_int16_t i = 0; i < buttonTexts.size(); i++)
//     {
//         Serial.println("adding button" + buttonTexts[i]);
//         if (buttonTexts[i] == NULL)
//         {
//             Serial.println("string is null");
//         }
//         buttons.push_back(new Button(String(buttonTexts[i])));
//     }
//     Serial.println("done setting all those buttons");
//     Serial.print(buttons.size());
// }

void ListComponent::draw()
{

    Serial.println("List::Drawing List");
    tft.setTextSize(3);
    tft.textMode();
    tft.textEnlarge(3);
    Serial.println("List::Text size set");
    Serial.print("List::number of buttons being printed");
    Serial.println(buttons.size());
    Serial.print("List::Y scale ");
    scale.print();

    float button_y_spacing = (scale.y - BUTTON_Y_START) / buttons.size();
    float button_y_scale = button_y_spacing - BUTTON_SPACING / 2;
    Serial.print("List::button ratio");
    Serial.println(button_y_spacing);
    Serial.print("List::button scale");
    Serial.println(button_y_scale);

    for (size_t i = 0; i < buttons.size(); i++)
    {
        Serial.println("List::Drawing button");
        buttons[i]->draw({pos.x, BUTTON_Y_START + (button_y_spacing / 2) + (button_y_spacing)*i}, {scale.x, button_y_scale});
    }
}
void ListComponent::draw(Vec2 pos_, Vec2 scale_)
{
    pos = pos_;
    scale = scale_;
    draw();
}