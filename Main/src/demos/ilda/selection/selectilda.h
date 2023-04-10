#pragma once
#include <demos/demo.h>
#include <physics/physicsworld.h>
#include <graphics/shape.h>
#include <ILDA/ILDA.h>
static const ILDAFileInformation_t files[] = {
    {"cube.ild", 15},
    {"money.ild", 15},   // rk
    {"wall.ild", 15},    // ork
    {"tunnel.ild", 15},  // ork
    {"nasa.ild", 30},    // ork
    {"wheel.ild", 15},   // ork
    {"tunnel2.ild", 15}, //
    {"land.ild", 15},    //
    {"Enterprise2.ild", 15},
    {"LemmTumble.ild", 15}, //  Is moon rover
    {"Xwing.ild", 15},      //
    {"Vader.ild", 15},      //
    {"badapple2.ild", 30},

};
class ILDADemo : public Demo
{
private:
    /* data */
public:
    u_int16_t mNumFiles = sizeof(files) / sizeof(files[0]);
    // int a is our current file
    std::vector<ILDA *> mILDAFiles;
    GameObject2D *cube;

    ILDADemo(/* args */);
    ~ILDADemo();

    void draw() override;
    void update() override;
    void restart() override;
    void init() override;
    void setA(float val) override
    {
        a = (int)val % mNumFiles;
        if (a < 0)
            a = mNumFiles - a;
        cube->changeGraphic(new ILDA(files[(int)a]));
    }
    void setB(float val) override
    {
    }
    void setC(float val) override
    {
    }
};