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

    auto playBounce = [&](GameObject2D *caller)
    {
        playFile("bounce.WAV");
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

    ball = (new GameObject2D(ballg))->setPosition({WIDTH / 2, HEIGHT / 2})->setScale({100, 100})->setColor(WHITE)->fitColliderToObject();
    leftPaddle = (new GameObject2D(floorg))->setPosition(leftPaddleOffset)->setScale(paddleSize)->setColor(player1_color)->fitColliderToObject(playBounce);
    rightPaddle = (new GameObject2D(floorg))->setPosition(rightPaddleOffset)->setScale(paddleSize)->setColor(player2_color)->fitColliderToObject(playBounce);
    player1border = (new GameObject2D(floorg))->setPosition({WIDTH / 4, HEIGHT / 2})->setScale({WIDTH / 2, HEIGHT - 1})->setColor(player1_color);
    player2border = (new GameObject2D(floorg))->setPosition({(WIDTH - WIDTH / 4), HEIGHT / 2})->setScale({WIDTH / 2 - 1, HEIGHT - 1})->setColor(player2_color);
    player1goal = (new GameObject2D(floorg))->setPosition({50, HEIGHT / 2})->setScale({25, HEIGHT - 1})->setColor(player2_color)->fitColliderToObject(player2Score);
    player2goal = (new GameObject2D(floorg))->setPosition({WIDTH - 50, HEIGHT / 2})->setScale({25, HEIGHT - 1})->setColor(player2_color)->fitColliderToObject(player1Score);

    ball->velocity = ballSpeed;
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
}
void Pong::update()
{
    if (mIsPaused)
        return;
    ControllerState player1_state = player1_input.read();
    ControllerState player2_state = player2_input.read();
    Serial.println("p1: left " + (String)player1_state.left + "right " + (String)player1_state.right + "up " + (String)player1_state.up + "down " + (String)player1_state.down);

    Serial.println("p2: left " + (String)player2_state.left + "right " + (String)player2_state.right + "up " + (String)player2_state.up + "down " + (String)player2_state.down);

    world.step(1);

    if (gameEnd == false)
    {

        // if (ball.transform.pos.y >= HEIGHT - ball.transform.scale.y)
        // { // bottom bounce
        //     ballSpeedY *= -1;
        //     playFile("bounce.WAV");
        //     delay(25);
        // }
        // if (ball.transform.pos.y <= ball.transform.scale.y)
        // { // top bounce
        //     ballSpeedY *= -1;
        //     playFile("bounce.WAV");
        //     delay(25);
        // }
        // if (ball.transform.pos.x >= rightPaddle.transform.pos.x - 4 && ball.transform.pos.y >= rightPaddle.transform.pos.y && ball.transform.pos.y <= rightPaddle.transform.pos.y + 30)
        // { // right paddle bounce
        //     ballSpeedX *= -1;
        //     playFile("bounce.WAV");
        //     delay(25);
        // }
        // if (ball.transform.pos.x <= leftPaddle.transform.pos.x + 5 && ball.transform.pos.y >= leftPaddle.transform.pos.y && ball.transform.pos.y <= leftPaddle.transform.pos.y + 30)
        // { // left paddle bounce
        //     ballSpeedX *= -1;
        //     playFile("bounce.WAV");
        //     delay(25);
        // }

        // if (ball->transform->pos.x >= WIDTH - ball->transform->scale.x)
        // { // right goal
        //     player1_score++;
        //     playFile("goal.WAV");
        //     delay(25);
        //     resetRound();
        // }
        // if (ball->transform->pos.x <= ball->transform->scale.x)
        // { // left goal
        //     player2_score++;
        //     playFile("goal.WAV");
        //     delay(25);
        //     resetRound();
        // }

        if (player1_state.up)
        {
            leftPaddle->transform->pos.y += paddleSpeed;
        }
        if (player1_state.down)
        {
            leftPaddle->transform->pos.y -= paddleSpeed;
        }
        if (player2_state.up)
        {
            rightPaddle->transform->pos.y += paddleSpeed;
        }
        if (player2_state.right)
        {
            rightPaddle->transform->pos.y -= paddleSpeed;
        }

        delay(1);
    }
    if (player1_score >= '9')
    {
        gameEnd = true;
        win("1");
    }
    if (player2_score >= '9')
    {
        gameEnd = true;
        win("2");
    }
}
void Pong::draw()
{
    world.draw();
    player1_score_display.m = Mesh(player1_score);
    player2_score_display.m = Mesh(player2_score);
    player1_score_display.draw(player1_score_transform, player1_color);
    player2_score_display.draw(player2_score_transform, player2_color);
}

void Pong::restart()
{
    player1_score = '0';
    player2_score = '0';
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
    // p.fillScreen(ILI9341_BLACK);
    // p.drawRect(WIDTH / 2, HEIGHT / 2, WIDTH, HEIGHT); // border
    // p.drawCircle(ballX, ballY, 20);                   // ball
}

void Pong::playFile(const char *filename)
{
    playWav1.play(filename);
}
