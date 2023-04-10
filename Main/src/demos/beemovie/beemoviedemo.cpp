#include <demos/beemovie/beemoviedemo.h>

BeeMovieDemo::BeeMovieDemo(/* args */)
{
}

BeeMovieDemo::~BeeMovieDemo()
{
}
void BeeMovieDemo::init()
{

    while (!(SD.begin(BUILTIN_SDCARD)))
    {
        Serial.println("Unable to access the SD card");
        delay(500);
    }
    // open file for reading
    file = SD.open("beemoviescript.txt", FILE_READ);
    for (size_t i = 0; i < 100; i++)

    {
        String line = file.readStringUntil('\n').toLowerCase();
        mWords.push_back((new GameObject2D(new Sentence(line.c_str())))->setPosition({300, HEIGHT / 2})->setScale({100, 100})->setColor((Color)WHITE));
        int curLine = mWords.size();
        Serial.print("Reading beemovie script line ");
        Serial.println(curLine);
    }

    p.format_info.kerneling = 100;
    p.format_info.font_size = 200;
}

void BeeMovieDemo::play()
{
}

void BeeMovieDemo::pause()
{
}
void BeeMovieDemo::draw()
{
    u_int64_t cycleTime = 3000;

    if (millis() > cycleTime + mLastScreenTime)
    {
        mLastScreenTime = millis();
        mCurrentScreen++;
    }
    if ((mCurrentScreen - 1) >= mWords.size())
    {
        mCurrentScreen = 1;
    }
    mWords[mCurrentScreen - 1]->draw();
}
void BeeMovieDemo::update()
{

    // text->setRotation(text->transform->rot + Vec3({0, 1, 0}));
}

void BeeMovieDemo::restart()
{
}