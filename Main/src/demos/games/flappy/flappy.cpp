#include <demos/games/flappy/flappy.h>

void Flappy::init()
{
    AudioMemory(250);

    if (!(SD.begin(BUILTIN_SDCARD)))
    {
        // stop here, but print a message repetitively
        while (1)
        {
            Serial.println("Unable to access the SD card");
            delay(500);
        }
    }

    Graphic *ballg = new Shape(Graphic::Circle);
    Graphic *floorg = new Shape(Graphic::Rectangle);

    auto player1Death = [&](GameObject2D *caller)
    {
        player1->velocity = {0, 0};
        if (!mIsPlayer1Dead)
        {
            playFile("sound/sfx_hit.WAV");
            mIsPlayer1Dead = true;
            // player1->mIsGravity = false;
        }
    };
    auto player2Death = [&](GameObject2D *caller)
    {
        player2->velocity = {0, 0};
        if (!mIsPlayer2Dead)
        {
            playFile("sound/sfx_hit.WAV");
            mIsPlayer2Dead = true;
            // player2->mIsGravity = false;
        }
    };
    auto onPipeHit = [&](GameObject2D *caller)
    {
        playFile("sound/sfx_hit.WAV");
    };
    auto player1Score = [&](GameObject2D *caller)
    {
        player1_score++;
        Serial.println("PLAYER 1 SCORED");
        playFile("goal.WAV");
        delay(25);
        restartRound();
    };
    auto player2Score = [&](GameObject2D *caller)
    {
        player2_score++;
        Serial.println("PLAYER 2 SCORED");
        playFile("goal.WAV");
        delay(25);
        restartRound();
    };

    player1 = (new GameObject2D(ballg))->setPosition({WIDTH / 2 - 200, HEIGHT / 2})->setScale({100, 100})->setColor(WHITE)->fitColliderToObject(player1Death);
    player2 = (new GameObject2D(ballg))->setPosition({WIDTH / 2 + 200, HEIGHT / 2})->setScale({100, 100})->setColor(WHITE)->fitColliderToObject(player2Death);

    ground = (new GameObject2D(floorg))->setPosition({WIDTH / 2, 100})->setScale({WIDTH - 2, 50})->setColor(player1_color)->fitColliderToObject();
    pipeTop = (new GameObject2D(floorg))->setPosition({WIDTH - 200, HEIGHT * 3 / 4})->setScale({100, HEIGHT / 4})->setColor(GREEN)->fitColliderToObject(onPipeHit);
    pipeBot = (new GameObject2D(floorg))->setPosition({WIDTH - 200, HEIGHT * 1 / 4})->setScale({100, HEIGHT / 4})->setColor(GREEN)->fitColliderToObject(onPipeHit);

    pipeTop->mIsDynamic = false;
    pipeBot->mIsDynamic = false;

    player1->mIsDynamic = true;
    player1->mIsGravity = true;
    player2->mIsDynamic = true;
    player2->mIsGravity = true;

    ground->mIsDynamic = false;

    Serial.println("Filling game vector");

    world.addObject(player1);
    world.addObject(player2);
    world.addObject(ground);
    world.addObject(pipeTop);
    world.addObject(pipeBot);

    world.addSolver(&solver1);
    world.mHasBorder = false;
    // world.addSolver(&solver2);
}
void Flappy::resetPipe()
{
    pipeTop->setPosition({WIDTH - 200, HEIGHT * 3 / 4});
    pipeBot->setPosition({WIDTH - 200, HEIGHT * 1 / 4});
}
void Flappy::update()
{
    if (mIsPaused)
        return;
    ControllerState player1_state = player1_input.read();
    ControllerState player2_state = player2_input.read();

    if (gameEnd == false)

    {

        if ((player1_state.upIsPressed || player1_state.downIsPressed || player1_state.leftIsPressed || player1_state.rightIsPressed) && player1_state.isValid)
        {
            Serial.println("p1: left " + (String)player1_state.left + "right " + (String)player1_state.right + "up " + (String)player1_state.up + "down " + (String)player1_state.down);
            playFile("sound/sfx_wing.wav");
            player1->force += Vec2(0, 1) * 2 * mJumpStrength * player1->mass;
        }
        if ((player2_state.upIsPressed || player2_state.downIsPressed || player2_state.leftIsPressed || player2_state.rightIsPressed) && player2_state.isValid)
        {
            Serial.println("p2: left " + (String)player2_state.left + "right " + (String)player2_state.right + "up " + (String)player2_state.up + "down " + (String)player2_state.down);
            playFile("sound/sfx_wing.wav");
            player2->force += Vec2(0, 1) * 2 * mJumpStrength * player2->mass;
        }

        pipeTop->transform->pos += {-mPipeSpeed, 0};
        pipeBot->transform->pos += {-mPipeSpeed, 0};
        if (pipeTop->transform->pos.x < 0 || pipeBot->transform->pos.x < 0)
        {
            resetPipe();
        }
    }

    // if (player1_score >= '9')
    // {
    //     gameEnd = true;
    //     win("1");
    // }
    // if (player2_score >= '9')
    // {
    //     gameEnd = true;
    //     win("2");
    // }
    world.step(1);
}
void Flappy::draw()
{
    world.draw();
    player1_score_display.m = Mesh(player1_score);
    player2_score_display.m = Mesh(player2_score);
    player1_score_display.draw(player1_score_transform, player1_color);
    player2_score_display.draw(player2_score_transform, player2_color);
}

void Flappy::restart()
{
    player1_score = '0';
    player2_score = '0';
    restartRound();
}

void Flappy::win(std::string winner)
{
    playFile("victory.WAV");
    for (size_t i = 0; i < 350; i++)
    {
        Transform2D tran;
        tran.setPosition({250, HEIGHT / 2}).setScale({500, 250});
        Sentence("player " + winner + " wins").draw(tran, WHITE);
    }
    restart();
}

void Flappy::restartRound()
{
    // ball
}

void Flappy::playFile(const char *filename)
{
    playWav1.play(filename);
}
