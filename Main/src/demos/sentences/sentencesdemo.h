#pragma once
#include <demos/demo.h>
#include <physics/physicsworld.h>
#include <graphics/shape.h>
#include <graphics/sentence.h>
#include <color.h>
class SentencesDemo : public Demo
{
private:
    /* data */
public:
    GameObject2D *text1;
    GameObject2D *text2;
    GameObject2D *text3;
    u_int16_t mScreenOneTime = 3 * 1000;
    u_int16_t mScreenTwoTime = 3 * 1000;
    u_int16_t mScreenThreeTime = 1 * 1000;

    SentencesDemo(/* args */);
    ~SentencesDemo();

    void draw() override;
    void update() override;
    void restart() override;
    void init() override;
};