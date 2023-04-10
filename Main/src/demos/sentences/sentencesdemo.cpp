#include <demos/sentences/sentencesdemo.h>

SentencesDemo::SentencesDemo(/* args */)
{
}

SentencesDemo::~SentencesDemo()
{
}
void SentencesDemo::init()
{
    p.format_info.kerneling = 150;
    p.format_info.font_size = 300;
    text1 = (new GameObject2D(new Sentence("hello world")))->setPosition({300, HEIGHT / 2})->setScale({100, 100})->setColor((Color)RAINBOW);
    text2 = (new GameObject2D(new Sentence("3.141592653589793238462643383279502884197")))->setPosition({300, HEIGHT / 2})->setScale({100, 100})->setColor((Color)WHITE);
    text3 = (new GameObject2D(new Sentence("what the dog doin?")))->setPosition({300, HEIGHT / 2})->setScale({100, 100})->setColor((Color)WHITE);
}
void SentencesDemo::play()
{
}

void SentencesDemo::pause()
{
}
void SentencesDemo::draw()
{
    u_int64_t cycleTime = mScreenOneTime + mScreenTwoTime + mScreenThreeTime;
    if (millis() % cycleTime < mScreenOneTime)
        text1->draw();
    else if (millis() % cycleTime < mScreenOneTime + mScreenTwoTime)
        text2->draw();
    else
        text3->draw();
}
void SentencesDemo::update()
{

    // text->setRotation(text->transform->rot + Vec3({0, 1, 0}));
}

void SentencesDemo::restart()
{
}