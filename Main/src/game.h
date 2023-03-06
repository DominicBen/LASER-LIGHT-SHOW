
#include <gameobject.h>
// #include <iostream>
#include <vector>
#include <pointer.h>

class Game
{
private:
    /* data */
public:
    std::vector<GameObject2D> objects;
    Pointer &p = Pointer::getInstance();
    void init();
    void update();
    void draw();
    Game(/* args */);
    ~Game();
};

Game::Game(/* args */)
{
}

Game::~Game()
{
}
