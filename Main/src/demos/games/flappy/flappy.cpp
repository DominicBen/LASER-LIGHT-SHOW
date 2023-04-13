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

    Graphic *ballg = new Char("flappy");
    ballg->type = Graphic::SmallCircle;
    // Graphic *ballg = new Shape(Graphic::Circle);
    Graphic *floorg = new Shape(Graphic::Rectangle);

    auto player1Collide = [&](GameObject2D *caller, GameObject2D *other)
    {
        if (gameEnd)
            return;
        if (!mIsPlayer1Dead && other->mID == "pipe")
        {
            player1->velocity = {0, 0};
            Serial.println("detected collision player1 on object" + other->mID);
            playFile("sound/sfx_hit.WAV");
            mIsPlayer1Dead = true;
        }
        else if (other->mID == "goal")
        {
            if (millis() > mPlayer1LastScore + mScoreCooldown)
            {
                mPlayer1LastScore = millis();
                player1Score();
            }
        }
        else
        {
            player1->velocity = {0, 0};
        }
    };
    auto player2Collide = [&](GameObject2D *caller, GameObject2D *other)
    {
        if (gameEnd)
            return;
        if (!mIsPlayer2Dead && other->mID == "pipe")
        {
            player2->velocity = {0, 0};
            Serial.println("detected collision player2 on object" + other->mID);
            playFile("sound/sfx_hit.WAV");
            mIsPlayer2Dead = true;
        }
        else if (other->mID == "goal")
        {
            if (millis() > mPlayer2LastScore + mScoreCooldown)
            {
                mPlayer2LastScore = millis();
                player2Score();
            }
        }
        else
        {
            player2->velocity = {0, 0};
        }
    };
    auto onPipeHit = [&](GameObject2D *caller, GameObject2D *other) {
    };

    player1 = (new GameObject2D(ballg, "player1"))->setScale({100, 100})->setColor(WHITE)->fitColliderToObject(player1Collide);
    player2 = (new GameObject2D(ballg, "player2"))->setScale({100, 100})->setColor(WHITE)->fitColliderToObject(player2Collide);
    resetPlayers();
    pipeTop = (new GameObject2D(floorg, "pipe"))->setColor(GREEN)->fitColliderToObject();
    pipeBot = (new GameObject2D(floorg, "pipe"))->setColor(GREEN)->fitColliderToObject();
    pipeGoal = (new GameObject2D(floorg, "goal"))->setColor(BLUE)->fitColliderToObject();

    resetPipe();
    ground = (new GameObject2D(floorg, "floor"))->setPosition({WIDTH / 2, 100})->setScale({WIDTH - 2, 100})->setColor(GREEN)->fitColliderToObject();
    ceiling = (new GameObject2D(floorg, "floor"))->setPosition({WIDTH / 2, HEIGHT - 100})->setScale({WIDTH - 2, 100})->setColor(GREEN)->fitColliderToObject();

    player1FinalScore = (new GameObject2D(new Sentence(String(mPlayer1Score).c_str())))->setScale({300, 300})->setPosition({WIDTH / 2 - 400, 0})->setColor(GREEN);
    player2FinalScore = (new GameObject2D(new Sentence(String(mPlayer2Score).c_str())))->setScale({300, 300})->setPosition({WIDTH / 2 + 400, 0})->setColor(GREEN);
    player1FinalScore->mIsDrawn = false;
    player2FinalScore->mIsDrawn = false;
    player1FinalScore->mIsDynamic = false;
    player2FinalScore->mIsDynamic = false;
    pipeTop->mIsDynamic = false;
    pipeBot->mIsDynamic = false;
    pipeGoal->mIsDrawn = false;
    pipeBot->mIsDrawn = true;
    pipeTop->mIsDrawn = true;

    pipeGoal->mIsDynamic = false;

    pipeGoal->mIsTrigger = true;

    player1->mIsDynamic = true;
    player1->mIsGravity = true;
    player2->mIsDynamic = true;
    player2->mIsGravity = true;

    ground->mIsDynamic = false;
    ceiling->mIsDynamic = false;
    ceiling->mIsDrawn = false;

    Serial.println("Filling game vector");

    world.addObject(player1);
    world.addObject(player2);
    world.addObject(ground);
    world.addObject(pipeTop);
    world.addObject(pipeBot);
    world.addObject(pipeGoal);

    world.addObject(player1FinalScore);
    world.addObject(player2FinalScore);

    world.addSolver(&solver1);
    world.mHasBorder = true;
    world.mWorldBounderiesBounce = false;
    // world.addSolver(&solver2);
}
void Flappy::resetPipe()
{
    int rand = random(mGoalRange + 1) - mGoalRange / 2;
    pipeGoal->setPosition({mPipeSpawnPoint, rand + HEIGHT / 2});
    pipeGoal->setScale({mPipeThickness, mGoalSize});
    Vec2 temp = {mPipeThickness, (HEIGHT - (pipeGoal->transform->pos.y + pipeGoal->transform->scale.y / 2)) - 30};
    temp.print();
    pipeTop->setScale(temp);
    pipeBot->setScale({mPipeThickness, pipeGoal->transform->pos.y - pipeGoal->transform->scale.y / 2});
    pipeTop->setPosition({mPipeSpawnPoint, HEIGHT - (pipeTop->transform->scale.y / 2) - 2});
    pipeBot->setPosition({mPipeSpawnPoint, pipeBot->transform->scale.y / 2});
    pipeTop->fitColliderToObject();
    pipeBot->fitColliderToObject();
    pipeGoal->fitColliderToObject();
}
void Flappy::resetPlayers()
{
    player1->setPosition({WIDTH / 2 - 200, HEIGHT / 2});
    player2->setPosition({WIDTH / 2 + 200, HEIGHT / 2});
    player1->velocity = {0, 0};
    player2->velocity = {0, 0};

    mPlayer1Score = 0;
    mPlayer2Score = 0;
    mIsPlayer2Dead = false;
    mIsPlayer1Dead = false;
    player1FinalScore->mIsDrawn = false;
    player2FinalScore->mIsDrawn = false;
    player1->mIsGravity = true;
    player2->mIsGravity = true;
}

void Flappy::player1Score()
{
    mPlayer1Score++;
    Serial.println("PLAYER 1 SCORED");
    playFile("sound/sfx_point.WAV");
}

void Flappy::player2Score()
{
    mPlayer2Score++;
    Serial.println("PLAYER 2 SCORED");
    playFile("sound/sfx_point.WAV");
}
void Flappy::update()
{
    // Serial.println("Player 1 pos" + (String)player1->transform->pos.y);
    if (mIsPaused)
        return;
    ControllerState player1_state = player1_input.read();
    ControllerState player2_state = player2_input.read();

    if (gameEnd == false)
    {
        if (mIsPlayer2Dead && mIsPlayer1Dead)
        {
            gameOver();
        }
        if ((player1_state.upIsPressed || player1_state.downIsPressed || player1_state.leftIsPressed || player1_state.rightIsPressed) && player1_state.isValid && !mIsPlayer1Dead)
        {
            Serial.println("p1: left " + (String)player1_state.left + "right " + (String)player1_state.right + "up " + (String)player1_state.up + "down " + (String)player1_state.down);
            if (millis() > mPlayer1LastScore + mScoreCooldown)
                playFile("sound/sfx_wing.wav");
            player1->force += Vec2(0, 1) * 2 * mJumpStrength * player1->mass;
        }
        if ((player2_state.upIsPressed || player2_state.downIsPressed || player2_state.leftIsPressed || player2_state.rightIsPressed) && player2_state.isValid && !mIsPlayer2Dead)
        {
            Serial.println("p2: left " + (String)player2_state.left + "right " + (String)player2_state.right + "up " + (String)player2_state.up + "down " + (String)player2_state.down);
            if (millis() > mPlayer2LastScore + mScoreCooldown)
                playFile("sound/sfx_wing.wav");
            player2->force += Vec2(0, 1) * 2 * mJumpStrength * player2->mass;
        }

        pipeTop->transform->pos += {-mPipeSpeed, 0};
        pipeBot->transform->pos += {-mPipeSpeed, 0};
        pipeGoal->transform->pos += {-mPipeSpeed, 0};

        if (pipeTop->transform->pos.x < 0 - mPipeThickness || pipeBot->transform->pos.x < 0 - mPipeThickness)
        {
            resetPipe();
        }
    }
    else
    {

        if ((player1_state.upIsPressed || player1_state.downIsPressed || player1_state.leftIsPressed || player1_state.rightIsPressed) && player1_state.isValid)
        {
            restart();
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
    displayScore();
    // mPlayer1ScoreDisplay.m = Mesh(mPlayer1Score);
    // mPlayer2ScoreDisplay.m = Mesh(mPlayer2Score);
    // mPlayer1ScoreDisplay.draw(mPlayer1ScoreTransform, mPlayer1Color);
    // mPlayer2ScoreDisplay.draw(mPlayer2ScoreTransform, mPlayer2Color);
}

void Flappy::restart()
{
    resetPipe();
    resetPlayers();

    gameEnd = false;
}

void Flappy::gameOver()
{
    gameEnd = true;
    gameEndTime = millis();
    playFile("sound/sfx_die.WAV");
    player1FinalScore->changeGraphic(new Sentence(String(mPlayer1Score).c_str()));
    player2FinalScore->changeGraphic(new Sentence(String(mPlayer2Score).c_str()));
    player1FinalScore->mIsDrawn = true;
    player2FinalScore->mIsDrawn = true;
    player1->mIsGravity = false;
    player2->mIsGravity = false;
}

void Flappy::displayScore()
{
    if (gameEnd)
    {
        Vec2 start = {0, 0};
        Vec2 end = {0, HEIGHT * 3 / 4};
        Vec2 lerp = player1FinalScore->transform->pos.lerp(start, end, 2000, millis() - gameEndTime);
        // Serial.println(lerp.y);
        player1FinalScore->transform->pos.y = lerp.y;
        player2FinalScore->transform->pos.y = lerp.y;
    }
}

void Flappy::playFile(const char *filename)
{
    playWav1.play(filename);
}
