#include <demos/ilda/badapple/badapple.h>

BadAppleDemo::BadAppleDemo(/* args */)
{
}

BadAppleDemo::~BadAppleDemo()
{
}
void BadAppleDemo::init()
{
    AudioMemory(8);
    a = 0;
    cube = (new GameObject2D(new ILDA({"badapple2.ild", 30})))->setPosition({WIDTH / 2, HEIGHT / 2})->setScale({4000, 4000})->setColor((Color)WHITE);
    cube->mIsDynamic = false;
    playWav1.play("badapple.wav");
}

void BadAppleDemo::draw()
{

    cube->draw();
}
void BadAppleDemo::update()
{
    if (!mIsPaused)
        cube->update();
    // cube->setRotation(cube->transform->rot + Vec3({PI / 1000, PI / 1000, 0}));
}

void BadAppleDemo::restart()
{
    delete cube;
    init();
}