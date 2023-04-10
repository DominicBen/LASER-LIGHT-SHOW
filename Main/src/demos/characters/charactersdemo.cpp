#include <demos/characters/charactersdemo.h>
CharactersDemo::CharactersDemo(/* args */)
{
}

CharactersDemo::~CharactersDemo()
{
}
void CharactersDemo::init()
{
    p.format_info.kerneling = 150;
    p.format_info.font_size = 200;
    text = (new GameObject2D(sentanceg))->setPosition({100, HEIGHT / 2})->setScale({100, 100})->setColor((Color)WHITE);
    text->is_static = true;
}
void CharactersDemo::play()
{
}

void CharactersDemo::pause()
{
}
void CharactersDemo::draw()
{
    text->draw();
}
void CharactersDemo::update()
{
}

void CharactersDemo::restart()
{
}