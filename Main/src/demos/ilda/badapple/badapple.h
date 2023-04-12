#pragma once
#include <demos/demo.h>
#include <graphics/graphic.h>

class BadAppleDemo : public Demo
{
private:
    /* data */
public:
    // int a is our current file
    GameObject2D *cube;

    // Audio
    AudioPlaySdWav playWav1;     // xy=88,55
    AudioOutputI2S2 audioOutput; // xy=280,79
    AudioConnection patchCord1 = AudioConnection(playWav1, 0, audioOutput, 0);
    AudioConnection patchCord2 = AudioConnection(playWav1, 1, audioOutput, 1);

    BadAppleDemo(/* args */);
    ~BadAppleDemo();

    void draw() override;
    void update() override;
    void restart() override;
    void init() override;
    void setA(float val) override
    {
    }
    void setB(float val) override
    {
    }
    void setC(float val) override
    {
    }
};