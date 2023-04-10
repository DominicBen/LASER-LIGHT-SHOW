#include <ilda/ILDA.h>
#include <Audio.h>
#include <MemoryFree.h>

ILDA::ILDA()
{
    num_frames = 0;
    type = Other;
}
ILDA::ILDA(ILDAFileInformation_t info)
{
    num_frames = 0;
    mFrameRate = info.framerate;
    type = Other;
    read(info.filepath);
}

ILDA::~ILDA()
{
    free(frames.points);

    file.close();
}
uint16_t ntohs(uint16_t netshort)
{
    // Create a variable to hold the result in host byte order
    uint16_t hostshort = 0;
    // Copy the two bytes from network byte order to host byte order
    hostshort |= (netshort & 0x00FF) << 8;
    hostshort |= (netshort & 0xFF00) >> 8;
    // Return the result
    return hostshort;
}
bool ILDA::resetRead()
{
    if (file)
    {
        file.seek(0, SeekSet);
        file.read((uint8_t *)&header, sizeof(ILDA_Header_t));
        header.points = ntohs(header.points);
        header.total_frames = ntohs(header.total_frames);
        print_header(header);

        // allocate space for the frames
        // frames = (ILDA_Frame_t *)malloc(sizeof(ILDA_Frame_t) * 1);
        num_frames = header.total_frames;
        frames.points = NULL;
        frames.number_points = 0;

        mSeekPos = file.position();
    }
    else
    {
        Serial.print(F("SD Card: error on opening file"));
    }
    return true;
}
bool ILDA::read(const char *filepath)
{

    while (!(SD.begin(BUILTIN_SDCARD)))
    {
        Serial.println("Unable to access the SD card");
        delay(500);
    }
    // open file for reading
    file = SD.open(filepath, FILE_READ);
    if (file)
    {
        resetRead();
    }
    else
    {
        Serial.print(F("SD Card: error on opening file"));
    }
    return true;
}
bool ILDA::readNextHeader()
{
    if (file)
    {

        frames.number_points = header.points;

        // Serial.print("Free memory ");
        // Serial.println(freeMemory());
        void *ptr = malloc(sizeof(ILDA_Point_t) * header.points);
        if (ptr == nullptr)
        {
            Serial.println("out of memory");
            while (1)
                ;
        }
        frames.points = (ILDA_Point_t *)ptr;
        ILDA_Point_t *points = frames.points;
        for (int i = 0; i < header.points; i++)
        {
            file.read((uint8_t *)(&points[i]), sizeof(ILDA_Point_t));
            points[i].x = ntohs(points[i].x);
            points[i].y = ntohs(points[i].y);
            points[i].z = ntohs(points[i].z);
        }
        // read the next header
        file.read((uint8_t *)&header, sizeof(ILDA_Header_t));
        header.points = ntohs(header.points);
        header.total_frames = ntohs(header.total_frames);
        // free(points);
    }
    else
    {
        Serial.print(F("SD Card: error on opening file"));
    }
    return true;
}

void ILDA::print_header(const ILDA_Header_t &header)
{
    char tmp[100];
    strncpy(tmp, header.ilda, 4);
    tmp[5] = '\0';
    Serial.print("Header:");
    Serial.println(tmp);

    Serial.print("Format Code:");
    Serial.println(header.format);

    strncpy(tmp, header.frame_name, 8);
    tmp[8] = '\0';
    Serial.print("Frame Name:");
    Serial.println(tmp);

    strncpy(tmp, header.company_name, 8);
    tmp[8] = '\0';
    Serial.print("Company Name:");
    Serial.println(tmp);

    Serial.print("Number points:");
    Serial.println(header.points);

    Serial.print("Number frames:");
    Serial.println(header.total_frames);
}

void ILDA::update()
{
    mPlayNext = true;
}

void ILDA::draw(Transform2D transform, Color c)
{

    if (file.available())
    {
        if (mPlayNext)
        {
            if (frames.points != NULL)
            {
                free(frames.points);
            }
            readNextHeader();
        }
        mPlayNext = false;
        Serial.print("ILDA::drawing frame with points");
        Serial.println(frames.number_points);
        if (mFrameRate != 0)
        {
            p.mMinDelay = 1000000 / mFrameRate / frames.number_points;
            p.mMinDelay /= mCalibrationFactor;
            p.mMaxDelay = p.mMinDelay;
            Serial.print("ILDA::setting delay to ");
            Serial.println(p.mMinDelay);
        }
        uint32_t startTime = millis();
        float maxFrameTime = 1000 / (mFrameRate + 1.0);

        for (u_int16_t j = 0; j < frames.number_points; j++)
        {
            Vec2 point = Vec2(frames.points[j].x, frames.points[j].y);

            point.mapX(-32768, 32767, -transform.scale.x / 2, transform.scale.x / 2);
            point.mapY(-32768, 32767, -transform.scale.y / 2, transform.scale.y / 2);
            // toggles led's based on status code
            if ((frames.points[j].status_code & 0b01000000) == 0)
            {
                p.setColor(c);
            }
            else
            {
                p.setLed(HIGH);
            }
            point = point + transform.pos;
            p.pointTo(point);
        }
        uint32_t endTime = millis();
        uint32_t totalTime = endTime - startTime;
        if (totalTime > maxFrameTime)
        {
            Serial.print("ILDA::WARNING, PREFORMING UNDER EXPECATIONS Expected a delay of");
            Serial.println(maxFrameTime);
            mCalibrationFactor *= 1.05;
            Serial.print("ILDA::That frame took this many milliseonds to print: ");
            Serial.println(totalTime);
        }
        else
        {
            if (frames.number_points > 10)
                mCalibrationFactor *= 0.95;
            delay(maxFrameTime - totalTime);
            Serial.print("ILDA::NOTICE delaying for extra milliseconds");
            Serial.println(maxFrameTime - totalTime);
        }

        // delay(20);
        // free(frames.points);

        p.resetDelay();
    }
    else
    {
        resetRead();
    }
}