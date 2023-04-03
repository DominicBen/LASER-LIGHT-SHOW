#pragma once
#include <demos/demo.h>
#include <physicsworld.h>
#include <shape.h>
#include <sentence.h>
#include <color.h>
class TextDemo : public Demo
{
private:
    /* data */
public:
    Graphic *sentanceg = new Sentence("hello world");
    GameObject2D *text;

    TextDemo(/* args */);
    ~TextDemo();
    void play() override;
    void pause() override;
    void draw() override;
    void update() override;
    void restart() override;
    void init() override;
};

TextDemo::TextDemo(/* args */)
{
}

TextDemo::~TextDemo()
{
}
void TextDemo::init()
{
    p.format_info.kerneling = 300;
    p.format_info.font_size = 400;
    text = (new GameObject2D(sentanceg))->setPosition({300, HEIGHT / 2})->setScale({100, 100})->setColor((Color)WHITE)->fitColliderToObject();
    text->is_static = true;
}
void TextDemo::play()
{
}

void TextDemo::pause()
{
}
void TextDemo::draw()
{
    text->draw();
}
void TextDemo::update()
{

    // text->setRotation(text->transform->rot + Vec3({0, 1, 0}));
}

void TextDemo::restart()
{
}