#pragma once
#include <demos/demo.h>
#include <physics/physicsworld.h>
#include <graphics/shape.h>
#include <ILDA/ILDA.h>
static const char *files[] = {
    "cube.ild",        // works
    "money.ild",       // kinda work
    "wall.ild",        // doesnt work
    "tunnel.ild",      // doesnt work
    "nasa.ild",        // doesnt work
    "magic.ild",       // doesnt wark
    "wheel.ild",       // doesnt work
    "tunnel2.ild",     // doesnt work
    "land.ild",        // doesnt work
    "Enterprise2.ild", // 9
    "LemmTumble.ild",  // 10
    "Xwing.ild",       // 11
    "Vader.ild",

};
class Cube3D : public Demo
{
private:
    /* data */
public:
    Graphic *cubeg = new ILDA("LemmTumble.ild");

    GameObject2D *cube;

    Cube3D(/* args */);
    ~Cube3D();
    void play() override;
    void pause() override;
    void draw() override;
    void update() override;
    void restart() override;
    void init() override;
};