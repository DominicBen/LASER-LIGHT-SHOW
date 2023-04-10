#pragma once
#include <demos/demo.h>
#include <physics/physicsworld.h>
#include <graphics/shape.h>
#include <graphics/sentence.h>
#include <color.h>
#include <vector>

#include <SD.h>
#include <SerialFlash.h>
class BeeMovieDemo : public Demo
{
private:
    /* data */
public:
    File file;
    std::vector<GameObject2D *> mWords;

    u_int64_t cycleTime = 3000;

    u_int64_t mLastScreenTime = 0;
    u_int32_t mCurrentScreen = 0;

    BeeMovieDemo(/* args */);
    ~BeeMovieDemo();
    void play() override;
    void pause() override;
    void draw() override;
    void update() override;
    void restart() override;
    void init() override;
};