#include <LCD/components/variablecomponent.h>

void VariableComponent::draw()
{
    for (size_t i = 0; i < components.size(); i++)
    {
        Serial.println("List::Drawing button");
        components[i]->draw(pos, scale);
    }
}
// void VariableComponent::draw(Vec2 pos_, Vec2 scale_)
// {
//     pos = pos_;
//     scale = scale_;
//     draw();
// }
bool VariableComponent::detectTouch(int x, int y)
{
    for (Component *b : components)
    {
        if (b->detectTouch(x, y))
        {
            Serial.println("LIST::Touch being detected at button " + b->text);
            return true;
        }
    }
    return false;
}
VariableComponent::VariableComponent(Vec2 pos_, Vec2 scale_, String text, float incrementer_, float large_incrementer_, float *variable_, Callback callback)
    : incrementer(incrementer_), large_incrementer(large_incrementer_), variable(variable_), Component(pos_, scale_)
{
    Component *list = (new ListComponent())
                          //   ->addComponent((new TextComponent(text, variable)))
                          ->addComponent((new Button("++", callback, large_incrementer)))
                          ->addComponent((new Button("+", callback, incrementer)))
                          ->addComponent((new TextComponent((text + ": "), variable)))
                          ->addComponent((new Button("-", callback, -incrementer)))
                          ->addComponent((new Button("--", callback, -large_incrementer)))
                          ->setScale(scale)
                          ->setPos(pos);

    // Component *back = (new Button("Back", back, 0))->setScale({50, 50})->setPos({100, 100});

    components.push_back(list);
}
