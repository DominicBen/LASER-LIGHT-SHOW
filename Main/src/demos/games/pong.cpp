#include <demos/games/pong.h>

void Pong::init()
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

    auto playBounce = [&](GameObject2D *caller, GameObject2D *other)
    {
        playFile("bounce.WAV");
        mMaxBallSpeed += mDifficultyScaling;
        other->velocity += caller->velocity / 4;
        other->velocity = other->velocity * (mMaxBallSpeed / other->velocity.magnitude());
    };
    auto player1Score = [&](GameObject2D *caller, GameObject2D *other)
    {
        mPlayer1Score++;
        Serial.println("PLAYER 1 SCORED");
        playFile("goal.WAV");
        delay(25);
        restartRound();
    };
    auto player2Score = [&](GameObject2D *caller, GameObject2D *other)
    {
        mPlayer2Score++;
        Serial.println("PLAYER 2 SCORED");
        playFile("goal.WAV");
        delay(25);
        restartRound();
    };

    ball = (new GameObject2D(ballg))->setPosition({WIDTH / 2, HEIGHT / 2})->setScale({100, 100})->setColor(WHITE)->fitColliderToObject();
    leftPaddle = (new GameObject2D(floorg))->setPosition(leftPaddleOffset)->setScale(paddleSize)->setColor(mPlayer1Color)->fitColliderToObject(playBounce);
    rightPaddle = (new GameObject2D(floorg))->setPosition(rightPaddleOffset)->setScale(paddleSize)->setColor(mPlayer2Color)->fitColliderToObject(playBounce);
    player1border = (new GameObject2D(floorg))->setPosition({WIDTH / 4, HEIGHT / 2})->setScale({WIDTH / 2, HEIGHT - 1})->setColor(mPlayer1Color);
    player2border = (new GameObject2D(floorg))->setPosition({(WIDTH - WIDTH / 4), HEIGHT / 2})->setScale({WIDTH / 2 - 1, HEIGHT - 1})->setColor(mPlayer2Color);
    player1goal = (new GameObject2D(floorg))->setPosition({50, HEIGHT / 2})->setScale({25, HEIGHT - 1})->setColor(mPlayer2Color)->fitColliderToObject(player2Score);
    player2goal = (new GameObject2D(floorg))->setPosition({WIDTH - 50, HEIGHT / 2})->setScale({25, HEIGHT - 1})->setColor(mPlayer2Color)->fitColliderToObject(player1Score);

    ball->mIsDynamic = true;
    ball->mIsGravity = false;

    leftPaddle->mIsDynamic = false;
    rightPaddle->mIsDynamic = false;
    player1border->mIsDynamic = false;
    player2border->mIsDynamic = false;

    player1goal->mIsTrigger = true;
    player1goal->mIsDynamic = false;
    player1goal->mIsDrawn = false;

    player2goal->mIsTrigger = true;
    player2goal->mIsDynamic = false;
    player2goal->mIsDrawn = false;

    Serial.println("Filling game vector");

    world.addObject(ball);
    world.addObject(leftPaddle);
    world.addObject(rightPaddle);
    world.addObject(player1border);
    world.addObject(player2border);
    world.addObject(player1goal);
    world.addObject(player2goal);

    world.addSolver(&solver1);
    world.addSolver(&solver2);
    restartRound();
}
void Pong::update()
{
    if (mIsPaused)
        return;
    ControllerState player1_state = player1_input.read();
    ControllerState player2_state = player2_input.read();
    if (player1_state.isValid)
        Serial.println("p1: left " + (String)player1_state.left + "right " + (String)player1_state.right + "up " + (String)player1_state.up + "down " + (String)player1_state.down + "x " + (String)player1_state.xdim + "y " + (String)player1_state.ydim);
    if (player2_state.isValid)
        Serial.println("p2: left " + (String)player2_state.left + "right " + (String)player2_state.right + "up " + (String)player2_state.up + "down " + (String)player2_state.down + "x " + (String)player2_state.xdim + "y " + (String)player2_state.ydim);

    if (gameEnd == false)
    {

        // if (player1_state.upIsPressed)
        // {
        //     leftPaddle->transform->pos.y += paddleSpeed;
        // }
        // if (player1_state.downIsPressed)
        // {
        //     leftPaddle->transform->pos.y -= paddleSpeed;
        // }
        // if (player2_state.upIsPressed)
        // {
        //     rightPaddle->transform->pos.y += paddleSpeed;
        // }
        // if (player2_state.downIsPressed)
        // {
        //     rightPaddle->transform->pos.y -= paddleSpeed;
        // }
        if (player1_state.isValid)
        {
            leftPaddle->velocity.y = (player1_state.ydim - 512) * -mPaddleSpeed / 100;
        }
        if (player2_state.isValid)
        {
            rightPaddle->velocity.y = (player2_state.ydim - 512) * -mPaddleSpeed / 100;
        }

        if (mPlayer1Score >= '9')
        {
            gameEnd = true;
            win("1");
        }
        if (mPlayer2Score >= '9')
        {
            gameEnd = true;
            win("2");
        }
    }
    world.step(1);
}
void Pong::draw()
{
    world.draw();
    mPlayer1ScoreDisplay.m = Mesh(mPlayer1Score);
    mPlayer2ScoreDisplay.m = Mesh(mPlayer2Score);
    mPlayer1ScoreDisplay.draw(mPlayer1ScoreTransform, mPlayer1Color);
    mPlayer2ScoreDisplay.draw(mPlayer2ScoreTransform, mPlayer2Color);
}

void Pong::restart()
{
    mPlayer1Score = '0';
    mPlayer2Score = '0';
    gameEnd = false;
    restartRound();
}

void Pong::win(std::string winner)
{
    playFile("victory.WAV");
    // playFile("badapplef6.MP3");
    for (size_t i = 0; i < 350; i++)
    {
        Transform2D tran;
        tran.setPosition({250, HEIGHT / 2}).setScale({500, 250});
        Sentence("player " + winner + " wins").draw(tran, WHITE);
    }
    restart();
}

void Pong::restartRound()
{
    int range = 300;
    // gives value between -range/2 to range/2
    range = random(range) - range / 2;
    ball->transform->pos.x = WIDTH / 2 + range;
    ball->transform->pos.y = HEIGHT / 2 + range;
    mMaxBallSpeed = mStartingMaxSpeed;
    ball->velocity = {-mMaxBallSpeed, 0};
    // p.fillScreen(ILI9341_BLACK);
    // p.drawRect(WIDTH / 2, HEIGHT / 2, WIDTH, HEIGHT); // border
    // p.drawCircle(ballX, ballY, 20);                   // ball
}

void Pong::playFile(const char *filename)
{
    playWav1.play(filename);
}
