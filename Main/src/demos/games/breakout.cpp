#include <demos/games/breakout.h>

void Breakout::init()
{
    AudioMemory(250);
    gameEnd = false;
    if (!(SD.begin(BUILTIN_SDCARD)))
    {
        // stop here, but print a message repetitively
        while (1)
        {
            Serial.println("Unable to access the SD card");
            //delay(500);
        }
    }
    Graphic *ballg = new Shape(Graphic::Circle);
    Graphic *floorg = new Shape(Graphic::Rectangle);


    auto deleteBrick = [&](GameObject2D * caller)
    {
        if(caller != NULL)
            caller->mMarkedForDeletion = true;
        playFile("glassBreak.WAV");
    };

    auto playBounce = [&](GameObject2D *caller)
    {
        playFile("bounce.WAV");
    };

    auto gameOver = [&](GameObject2D *caller)
    {
        lose();
        gameEnd = true;
    };


    ball = (new GameObject2D(ballg))->setPosition({WIDTH / 2, 500})->setScale({100, 100})->setColor(WHITE)->fitColliderToObject();
    Paddle = (new GameObject2D(floorg))->setPosition(PaddleOffset)->setScale(paddleSize)->setColor(player1_color)->fitColliderToObject(playBounce);
    border = (new GameObject2D(floorg))->setPosition({WIDTH/2, HEIGHT/2})->setScale({WIDTH-1, HEIGHT-1})->setColor(player1_color)->fitColliderToObject(playBounce);
    ground = (new GameObject2D(floorg))->setPosition({HEIGHT / 2,50})->setScale({WIDTH - 1,25})->setColor(player1_color)->fitColliderToObject(gameOver);
    brick11 = (new GameObject2D(floorg))->setPosition(brickA)->setScale(brickSize)->setColor(topBricks)->fitColliderToObject(deleteBrick);
    brick12 = (new GameObject2D(floorg))->setPosition(brickB)->setScale(brickSize)->setColor(topBricks)->fitColliderToObject(deleteBrick);
    brick13 = (new GameObject2D(floorg))->setPosition(brickC)->setScale(brickSize)->setColor(topBricks)->fitColliderToObject(deleteBrick);
    brick14 = (new GameObject2D(floorg))->setPosition(brickD)->setScale(brickSize)->setColor(topBricks)->fitColliderToObject(deleteBrick);
    brick15 = (new GameObject2D(floorg))->setPosition(brickE)->setScale(brickSize)->setColor(topBricks)->fitColliderToObject(deleteBrick);
    brick21 = (new GameObject2D(floorg))->setPosition(brickF)->setScale(brickSize)->setColor(middleBricks)->fitColliderToObject(deleteBrick);
    brick22 = (new GameObject2D(floorg))->setPosition(brickG)->setScale(brickSize)->setColor(middleBricks)->fitColliderToObject(deleteBrick);
    brick23 = (new GameObject2D(floorg))->setPosition(brickH)->setScale(brickSize)->setColor(middleBricks)->fitColliderToObject(deleteBrick);
    brick24 = (new GameObject2D(floorg))->setPosition(brickI)->setScale(brickSize)->setColor(middleBricks)->fitColliderToObject(deleteBrick);
    brick25 = (new GameObject2D(floorg))->setPosition(brickJ)->setScale(brickSize)->setColor(middleBricks)->fitColliderToObject(deleteBrick);
    brick26 = (new GameObject2D(floorg))->setPosition(brickK)->setScale(brickSize)->setColor(middleBricks)->fitColliderToObject(deleteBrick);
    brick31 = (new GameObject2D(floorg))->setPosition(brickL)->setScale(brickSize)->setColor(bottomBricks)->fitColliderToObject(deleteBrick);
    brick32 = (new GameObject2D(floorg))->setPosition(brickM)->setScale(brickSize)->setColor(bottomBricks)->fitColliderToObject(deleteBrick);
    brick33 = (new GameObject2D(floorg))->setPosition(brickN)->setScale(brickSize)->setColor(bottomBricks)->fitColliderToObject(deleteBrick);
    brick34 = (new GameObject2D(floorg))->setPosition(brickO)->setScale(brickSize)->setColor(bottomBricks)->fitColliderToObject(deleteBrick);
    brick35 = (new GameObject2D(floorg))->setPosition(brickP)->setScale(brickSize)->setColor(bottomBricks)->fitColliderToObject(deleteBrick);

    ball->velocity = ballSpeed;
    ball->mIsDynamic = true;
    ball->mIsGravity = false;
    Paddle->mIsDynamic = false;

    border->mIsDynamic = false;
    ground->mIsTrigger = true;
    ground->mIsDynamic = false;
    ground->mIsDrawn = false;

    brick11->mIsDynamic = false;
    brick12->mIsDynamic = false;
    brick13->mIsDynamic = false;
    brick14->mIsDynamic = false;
    brick15->mIsDynamic = false;
    brick21->mIsDynamic = false;
    brick22->mIsDynamic = false;
    brick23->mIsDynamic = false;
    brick24->mIsDynamic = false;
    brick25->mIsDynamic = false;
    brick26->mIsDynamic = false;
    brick31->mIsDynamic = false;
    brick32->mIsDynamic = false;
    brick33->mIsDynamic = false;
    brick34->mIsDynamic = false;
    brick35->mIsDynamic = false;

    world.addObject(ball);
    world.addObject(Paddle);
    world.addObject(border);
    world.addObject(ground);

    world.addObject(brick11);
    world.addObject(brick12);
    world.addObject(brick13);
    world.addObject(brick14);
    world.addObject(brick15);
    world.addObject(brick21);
    world.addObject(brick22);
    world.addObject(brick23);
    world.addObject(brick24);
    world.addObject(brick25);
    world.addObject(brick26);
    world.addObject(brick31);
    world.addObject(brick32);
    world.addObject(brick33);
    world.addObject(brick34);
    world.addObject(brick35);

    world.addSolver(&solver1);
    world.addSolver(&solver2);
}

void Breakout::update()
{
    Serial.println("Breakout::updating");

     if (mIsPaused){
        return;
     }
    ControllerState player1_state = player1_input.read();
    Serial.println("p1: left " + (String)player1_state.left + "right " + (String)player1_state.right + "up " + (String)player1_state.up + "down " + (String)player1_state.down);

    //gameEnd = false;
    if (gameEnd == false)
    {
    world.step(1);

        if (player1_state.right)
        {
            Paddle->transform->pos.x += paddleSpeed;
        }
        if (player1_state.left)
        {
            Paddle->transform->pos.x -= paddleSpeed;
        }

        delay(1);
    }
    world.cleanUpWorld();
}

void Breakout::draw()
{
    Serial.println("Breakout::drawing");
    world.draw();
}

void Breakout::restart()
{

    world.reset();
   restartRound();

}

void Breakout::win()
{
    playFile("victory.WAV");
    for (size_t i = 0; i < 350; i++)
    {
        Transform2D tran;
        tran.setPosition({250, HEIGHT / 2}).setScale({500, 250});
        Sentence("you win").draw(tran, WHITE);
    }
    restart();
}

void Breakout::lose(){
    playFile("gameOver.WAV");
    for (size_t i = 0; i < 350; i++)
    {
        Transform2D tran;
        tran.setPosition({250, HEIGHT / 2}).setScale({300, 250});
        Sentence("game over").draw(tran, WHITE);
    }
    restart();
}

void Breakout::restartRound()
{

   init();

}

void Breakout::playFile(const char *filename)
{
    playWav1.play(filename);
}
