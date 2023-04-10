
#include <gameobject.h>
// #include <iostream>
#include <vector>
#include <pointer.h>

class Game
{
private:
    /* data */

public:
    Pointer &p = Pointer::getInstance();

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    Game(/* args */);
    ~Game();
};

Game::Game(/* args */)
{
}

Game::~Game()
{
}
