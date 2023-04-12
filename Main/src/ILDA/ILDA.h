#ifndef ILDA_H
#define ILDA_H

#include <SD.h>
#include <SerialFlash.h>
#include <SPI.h>
#include <vector>
#include <graphics/graphic.h>

#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 11
#define SDCARD_MISO_PIN 12
#define SDCARD_SCK_PIN 13

#pragma pack(1)
typedef struct
{
    char ilda[4];
    uint8_t reserved1[3];
    uint8_t format;
    char frame_name[8];
    char company_name[8];
    uint16_t points;
    uint16_t frame_number;
    uint16_t total_frames;
    uint8_t projector_number;
    uint8_t reserved2;
} ILDA_Header_t;
#pragma pack()

#pragma pack(1)
typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
    uint8_t status_code;
    uint8_t color;
} ILDA_Point_t;
#pragma pack()

typedef struct
{
    ILDA_Point_t *points;
    uint16_t number_points;
} ILDA_Frame_t;

typedef struct
{
    const char *filepath;
    u_int16_t framerate;

} ILDAFileInformation_t;
class ILDA : public Graphic
{
private:
    /* data */
public:
    File file;

    ILDA_Header_t header;
    ILDA_Frame_t frames;
    int num_frames;
    u_int64_t mSeekPos;
    u_int16_t mFrameRate = 30;
    u_int16_t mMinDelay = 20;
    u_int16_t mMaxDelay = 100;
    float mCalibrationFactor = 2;
    bool mPlayNext = true; // A simple bool that desides if we play the next frame;

    bool read(const char *filepath);
    bool readNextHeader();
    bool resetRead();
    void print_header(const ILDA_Header_t &header);
    void draw(Transform2D transform, Color c) override;
    void update() override;

    ILDA();
    ILDA(ILDAFileInformation_t info);
    ~ILDA();
};

#endif // !ILDA_H