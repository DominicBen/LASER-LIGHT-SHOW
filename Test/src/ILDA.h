// #include <SD.h>
// #include <SerialFlash.h>
// #include <SPI.h>
// #define SDCARD_CS_PIN 10
// #define SDCARD_MOSI_PIN 11
// #define SDCARD_MISO_PIN 12
// #define SDCARD_SCK_PIN 13

// class ILDA
// {
// private:
//     /* data */
// public:
//     File file;
//     char buf[20];
//     ILDA(/* args */);
//     ~ILDA();
// };

// ILDA::ILDA(/* args */)
// {
//     SPI.setMISO(SDCARD_MISO_PIN);
//     SPI.setMOSI(SDCARD_MOSI_PIN);
//     SPI.setSCK(SDCARD_SCK_PIN);
//     if (!(SD.begin(SDCARD_CS_PIN)))
//     {
//         // stop here, but print a message repetitively
//         while (1)
//         {
//             Serial.println("Unable to access the SD card");
//             delay(500);
//         }
//     }
//     // open file for reading
//     file = SD.open("cube.ild", FILE_READ);
//     if (file)
//     {
//         int rlen = file.available();
//         char ch = file.read();    // read the first character
//         file.read(buf, rlen - 1); // read the remaining to buffer

//         Serial.print(ch);
//         Serial.print(buf);

//         file.close();
//     }
//     else
//     {
//         Serial.print(F("SD Card: error on opening file"));
//     }
// }

// ILDA::~ILDA()
// {
// }
