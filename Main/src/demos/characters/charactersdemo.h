#pragma once
#include <demos/demo.h>
#include <physics/physicsworld.h>
#include <graphics/shape.h>
#include <graphics/sentence.h>
class CharactersDemo : public Demo
{
private:
    /* data */
public:
    Graphic *sentanceg = new Sentence("abcdefghijklmnopqrstuvwxyz0123456789!?.");
    GameObject2D *text;

    CharactersDemo(/* args */);
    ~CharactersDemo();
    void play() override;
    void pause() override;
    void draw() override;
    void update() override;
    void restart() override;
    void init() override;
};
