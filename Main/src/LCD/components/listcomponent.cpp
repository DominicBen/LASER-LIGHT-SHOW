#include <LCD/components/listcomponent.h>

bool ListComponent::detectTouch(int x, int y)
{
    for (Component *b : components)
    {
        if (b->detectTouch(x, y))
        {
            Serial.println("LIST::Touch being detected at Component " + b->text);
            return true;
        }
    }
    return false;
}

void ListComponent::draw()
{

    Serial.println("List::Drawing List");
    tft.setTextSize(3);
    tft.textMode();
    tft.textEnlarge(3);
    Serial.println("List::Text size set");
    Serial.print("List::number of components being printed");
    Serial.println(components.size());
    Serial.print("List::Y scale ");
    scale.print();

    float Component_y_spacing = (scale.y) / components.size();
    float Component_y_scale = Component_y_spacing - COMPONENT_SPACING / 2;
    Serial.print("List::Component ratio");
    Serial.println(Component_y_spacing);
    Serial.print("List::Component scale");
    Serial.println(Component_y_scale);

    for (size_t i = 0; i < components.size(); i++)
    {
        Serial.println("List::Drawing Component");
        components[i]->draw({pos.x, (pos.y - (scale.y / 2)) + (Component_y_spacing / 2) + (Component_y_spacing)*i}, {scale.x, Component_y_scale});
    }
}
// void ListComponent::draw(Vec2 pos_, Vec2 scale_)
// {
//     pos = pos_;
//     scale = scale_;
//     draw();
// }