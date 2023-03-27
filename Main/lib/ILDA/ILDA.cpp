#include <ILDA.h>
#include <Audio.h>

ILDA::ILDA()
{
    frames = NULL;
    num_frames = 0;
}

ILDA::~ILDA()
{
    free(frames);
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
        header.points = (header.points >> 8);
        header.total_frames = (header.total_frames >> 8);
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
                points[i].x = ((points[i].x & 0x00ff) << 8) | ((points[i].x & 0xff00) >> 8);
                points[i].y = ((points[i].y & 0x00ff) << 8) | ((points[i].y & 0xff00) >> 8);
                points[i].z = ((points[i].z & 0x00ff) << 8) | ((points[i].z & 0xff00) >> 8);
            }
            // read the next header
            file.read((uint8_t *)&header, sizeof(ILDA_Header_t));
            header.points = (header.points >> 8);
            header.total_frames = (header.total_frames >> 8);
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
