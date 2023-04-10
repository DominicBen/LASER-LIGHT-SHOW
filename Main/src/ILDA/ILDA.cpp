#include <ilda/ILDA.h>
#include <Audio.h>

ILDA::ILDA()
{
    frames = NULL;
    num_frames = 0;
    type = Other;
}
ILDA::ILDA(const char *filepath)
{
    frames = NULL;
    num_frames = 0;
    type = Other;
    read(filepath);
}

ILDA::~ILDA()
{
    free(frames);
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
bool ILDA::read(const char *filepath)
{
    // SPI.setMISO(SDCARD_MISO_PIN);
    // SPI.setMOSI(SDCARD_MOSI_PIN);
    // SPI.setSCK(SDCARD_SCK_PIN);

    while (!(SD.begin(BUILTIN_SDCARD)))
    {
        Serial.println("Unable to access the SD card");
        delay(500);
    }
    // open file for reading
    file = SD.open(filepath, FILE_READ);
    if (file)
    {
        file.read((uint8_t *)&header, sizeof(ILDA_Header_t));
        header.points = ntohs(header.points);
        header.total_frames = ntohs(header.total_frames);
        print_header(header);

        // allocate space for the frames
        frames = (ILDA_Frame_t *)malloc(sizeof(ILDA_Frame_t) * header.total_frames);
        num_frames = header.total_frames;
        // read in each frame
        for (int frame_idx = 0; frame_idx < header.total_frames; frame_idx++)
        {
            frames[frame_idx].number_points = header.points;
            frames[frame_idx].points = (ILDA_Point_t *)malloc(sizeof(ILDA_Point_t) * header.points);
            ILDA_Point_t *points = frames[frame_idx].points;
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
        }

        // finished();
        file.close();
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

void ILDA::draw(Transform2D transform, Color c)
{
    Serial.print("drawing ILDA with frames");
    Serial.println(num_frames);

    for (u_int16_t i = 0; i < num_frames; i++)
    {

        Serial.print("drawing frame ");
        Serial.print(i);
        Serial.print(" with points ");
        Serial.println(frames[i].number_points);
        for (u_int16_t j = 0; j < frames[i].number_points; j++)
        {
            Vec2 point = Vec2(frames[i].points[j].x, frames[i].points[j].y);

            point.mapVec(-32768, 32767, (WIDTH / 2 - 2000), (WIDTH / 2 + 2000));
            // toggles led's based on status code
            if ((frames[i].points[j].status_code & 0b01000000) == 0)
            {
                p.setColor(c);
            }
            else
            {
                p.setLed(HIGH);
            }
            p.pointTo(point);
        }

        delay(20);
    }
}