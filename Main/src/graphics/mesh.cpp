#include <graphics/mesh.h>

Mesh::Mesh(/* args */)
{
}
Mesh::Mesh(String s)
{
    if (s == "flappy")
    {
        verticies =
            {
                {-0.47, 0.31},
                {-0.68, 0.61},
                {-0.76, 0.22},
                {-0.76, -0.03},
                {-0.56, -0.28},
                {-0.25, -0.66},
                {-0.16, 0.12},
                {-0.36, -0.5},
                {-0.24, -0.63},
                {0.44, -0.63},
                {0.23, -0.5},
                {0.60, -0.5},
                {0.73, -0.26},
                {0.84, -0.13},
                {0.73, -0.03},
                {0.63, -0.03},
                {0.23, -0.03},
                {0.03, -0.27},
                {0.22, -0.27},
                {0.63, -0.67},
                {0.33, -0.35},
                {0.14, 0.66},
                {0.02, 0.46},
                {0.02, 0.19},
                {0.42, 0.33},
                {0.42, 0.18},
                {-0.17, 0.66},
                {-0.37, 0.55},

            };
        travel_order = {
            0,
            1,
            2,
            3,
            4,
            5,
            6,
            0, // off after this
            4,
            7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 10, // off
            13, 18,                                      // off
            16, 19, 20, 21, 22, 23, 17,                  // off
            24,
            25, // off
            21, 26, 27

        };
        led_info =
            {
                true,
                true,
                true,
                true,
                true,
                true,
                true,
                false,
                true,
                true,
                true,
                true,
                true,
                true,
                true,
                true,
                true,
                true,
                true,
                true,
                false,
                true,
                false,
                true,
                true,
                true,
                true,
                true,
                true,
                false,
                true,
                false,
                true,
                true};
    }
}
Mesh::Mesh(char sym)
{
    switch (sym)
    {
    case 'a':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 1},
            {0.5, 1},
            {0.5, -1},
            {-0.5, 0},
            {0.5, 0},
        };
        led_info = {
            true,
            true,
            true,
            false,
            true,
        };
        travel_order = {
            0,
            1,
            2,
            3,
            4,
            5,
        };
        break;
    }
    case 'b':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 0},
            {-0.5, 1},
            {0.3, 1},
            {0.3, 0},
            {0.5, 0},
            {0.5, -1},
        };
        led_info = {
            true,
            true,
            true,
            true,
            true,
            true,
            false,
            true,
        };
        travel_order = {
            0,
            2,
            3,
            4,
            5,
            6,
            0,
            1,
            5};
        break;
    }
    case 'c':
    {
        verticies = {
            {0.5, -1},
            {-0.5, -1},
            {-0.5, 1},
            {0.5, 1},
        };
        led_info = {
            true,
            true,
            true,
        };
        travel_order = {
            0,
            1,
            2,
            3,
        };
        break;
    }
    case 'd':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 1},
            {0.5, 0},
        };
        led_info = {
            true,
            true,
            true,
            true,
        };
        travel_order = {
            0,
            1,
            2,
            0,
        };
        break;
    }
    case 'e':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 0},
            {-0.5, 1},
            {0.5, 1},
            {0.5, -1},
            {0, 0},
        };
        led_info = {
            true,
            true,
            true,
            false,
            true};
        travel_order = {
            4,
            0,
            2,
            3,
            1,
            5,
        };
        break;
    }
    case 'f':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 0},
            {-0.5, 1},
            {0.5, 1},
            {0, 0},
        };
        led_info = {
            true,
            true,
            false,
            true,
        };
        travel_order = {
            0,
            2,
            3,
            1,
            4,
        };
        break;
    }
    case 'g':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 1},
            {0.5, 1},
            {0.5, 0},
            {0.5, -1},
            {0, 0},
        };
        led_info = {
            true,
            true,
            true,
            true,
            true,
        };
        travel_order = {
            2,
            1,
            0,
            4,
            3,
            5,
        };
        break;
    }
    case 'h':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 0},
            {-0.5, 1},
            {0.5, 1},
            {0.5, 0},
            {0.5, -1},
        };
        led_info = {
            true,
            false,
            true,
            false,
            true,
        };
        travel_order = {
            0,
            2,
            3,
            5,
            1,
            4,
        };
        break;
    }
    case 'i':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 1},
            {0, 1},
            {0.5, 1},
            {0.5, -1},
            {0, -1},
        };
        led_info = {
            true,
            false,
            true,
            false,
            true,
        };
        travel_order = {
            1,
            3,
            4,
            0,
            5,
            2,
        };
        break;
    }
    case 'j':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 1},
            {0, 1},
            {0.5, 1},
            {0, -1},
        };
        led_info = {
            true,
            false,
            true,
            true,

        };
        travel_order = {
            1,
            3,
            0,
            4,
            2,
        };
        break;
    }
    case 'k':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 0},
            {-0.5, 1},
            {0.5, 1},
            {0.5, -1},
        };
        led_info = {
            true,
            false,
            true,
            false,
            true,

        };
        travel_order = {
            0,
            2,
            1,
            3,
            1,
            4,
        };
        break;
    }
    case 'l':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 1},
            {0.5, -1},
        };
        led_info = {
            true,
            true,

        };
        travel_order = {
            2,
            0,
            1,

        };
        break;
    }
    case 'm':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 1},
            {0.5, 1},
            {0.5, -1},
            {0, 0},
        };
        led_info = {
            true,
            true,
            true,
            true,

        };
        travel_order = {
            0,
            1,
            4,
            2,
            3,
        };
        break;
    }
    case 'n':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 1},
            {0.5, 1},
            {0.5, -1},
        };
        led_info = {
            true,
            true,
            true,

        };
        travel_order = {
            0,
            1,
            3,
            2,
        };
        break;
    }
    case 'o':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 1},
            {0.5, 1},
            {0.5, -1},
        };
        led_info = {
            true,
            true,
            true,
            true,
            true

        };
        travel_order = {
            0,
            1,
            2,
            3,
            0,
        };
        break;
    }
    case 'p':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 0},
            {-0.5, 1},
            {0.5, 1},
            {0.5, 0},
        };
        led_info = {
            true,
            true,
            true,
            true,
            true,
        };
        travel_order = {
            0,
            1,
            2,
            3,
            4,
            1,
        };
        break;
    }
    case 'q':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 1},
            {0.5, 1},
            {0.5, -1},
            {0, 0},
        };
        led_info = {
            true,
            true,
            true,
            true,
            false,
            true

        };
        travel_order = {
            0,
            1,
            2,
            3,
            0,
            4,
            3,
        };
        break;
    }
    case 'r':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 0},
            {-0.5, 1},
            {0.5, 1},
            {0.5, 0},
            {0.5, -1},
        };
        led_info = {
            true,
            true,
            true,
            true,
            true,

        };
        travel_order = {
            0,
            2,
            3,
            4,
            1,
            5,
        };
        break;
    }
    case 's':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 0},
            {-0.5, 1},
            {0.5, 1},
            {0.5, 0},
            {0.5, -1},
        };
        led_info = {
            true,
            true,
            true,
            true,
            true,

        };
        travel_order = {
            3,
            2,
            1,
            4,
            5,
            0,
        };
        break;
    }
    case 't':
    {
        verticies = {
            {-0.5, 1},
            {0, 1},
            {0.5, 1},
            {0, -1},
        };
        led_info = {
            true,
            false,
            true,
        };
        travel_order = {
            0,
            2,
            1,
            3,
        };
        break;
    }
    case 'u':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 1},
            {0.5, 1},
            {0.5, -1},
        };
        led_info = {
            true,
            true,
            true,
        };
        travel_order = {
            1,
            0,
            3,
            2,
        };
        break;
    }
    case 'v':
    {
        verticies = {
            {-0.5, 1},
            {0.5, 1},
            {0, -1},
        };
        led_info = {
            true,
            true,
        };
        travel_order = {
            0,
            2,
            1,
        };

        break;
    }
    case 'w':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 1},
            {0.5, 1},
            {0.5, -1},
            {0, 0},
        };
        led_info = {
            true,
            true,
            true,
            true,

        };
        travel_order = {
            1,
            0,
            4,
            3,
            2,
        };
        break;
    }
    case 'x':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 1},
            {0.5, 1},
            {0.5, -1},
        };
        led_info = {
            true,
            false,
            true,

        };
        travel_order = {
            0,
            2,
            1,
            3,
        };
        break;
    }
    case 'y':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 1},
            {0.5, 1},
            {0, 0},
        };
        led_info = {
            true,
            false,
            true,

        };
        travel_order = {
            0,
            2,
            1,
            3,
        };
        break;
    }
    case 'z':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 1},
            {0.5, 1},
            {0.5, -1},
        };
        led_info = {
            true,
            true,
            true,

        };
        travel_order = {
            1,
            2,
            0,
            3,
        };
        break;
    }
    case '?':
    {
        verticies = {
            {-0.5, 1},
            {0.5, 1},
            {0.5, 0},
            {0, -1},
            {0, 0},
        };
        led_info = {
            true,
            true,
            true,
            true,
            false,
            true,

        };
        travel_order = {
            0,
            1,
            2,
            4,
            3,
            3,
        };
        break;
    }
    case '.':
    {
        verticies = {
            {-0.5, -1},
        };
        led_info = {
            true,

        };
        travel_order = {
            0,
            0,
        };
        break;
    }
    case ',':
    {
        verticies = {
            {0, -0.5},
            {-0.5, -1}};
        led_info = {
            true,

        };
        travel_order = {
            0,
            1,
        };
        break;
    }
    case '0':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 1},
            {0.5, 1},
            {0.5, -1},
        };
        led_info = {
            true,
            true,
            true,
            true,
            true,

        };
        travel_order = {
            0,
            1,
            2,
            3,
            0,
            2,
        };
        break;
    }
    case '1':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 1},
            {0, 1},
            {0.5, -1},
            {0, -1},
        };
        led_info = {
            true,
            true,
            true,
            true,
            true,
        };
        travel_order = {
            1,
            2,
            4,
            0,
            3,
        };
        break;
    }
    case '2':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 0},
            {-0.5, 1},
            {0.5, 1},
            {0.5, 0},
            {0.5, -1},
        };
        led_info = {
            true,
            true,
            true,
            true,
            true,
        };
        travel_order = {
            5,
            0,
            1,
            4,
            3,
            2,
        };
        break;
    }
    case '3':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 0},
            {-0.5, 1},
            {0.5, 1},
            {0.5, 0},
            {0.5, -1},
        };
        led_info = {
            true,
            true,
            true,
            true,
            true,
            true,
        };
        travel_order = {
            0,
            5,
            4,
            1,
            4,
            3,
            2,
        };
        break;
    }
    case '4':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 0},
            {-0.5, 1},
            {0.5, 1},
            {0.5, 0},
            {0.5, -1},
        };
        led_info = {
            true,
            true,
            true,
            true,
        };
        travel_order = {
            2,
            1,
            4,
            3,
            5,
        };
        break;
    }
    case '5':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 0},
            {-0.5, 1},
            {0.5, 1},
            {0.5, 0},
            {0.5, -1},
        };
        led_info = {
            true,
            true,
            true,
            true,
            true,
        };
        travel_order = {
            0,
            5,
            4,
            1,
            2,
            3,
        };
        break;
    }
    case '6':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 0},
            {-0.5, 1},
            {0.5, 1},
            {0.5, 0},
            {0.5, -1},
        };
        led_info = {
            true,
            true,
            true,
            true,
            true,
            true,
        };
        travel_order = {
            3,
            2,
            1,
            0,
            5,
            4,
            1,
        };
        break;
    }
    case '7':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 0},
            {-0.5, 1},
            {0.5, 1},
            {0.5, 0},
            {0.5, -1},
        };
        led_info = {
            true,
            true,
            true,
        };
        travel_order = {
            2,
            3,
            4,
            5,
        };
        break;
    }
    case '8':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 0},
            {-0.5, 1},
            {0.5, 1},
            {0.5, 0},
            {0.5, -1},
        };
        led_info = {
            true,
            true,
            true,
            true,
            true,
            true,
            false,
            true};
        travel_order = {
            0,
            1,
            2,
            3,
            4,
            5,
            0,
            1,
            4,
        };
        break;
    }
    case '9':
    {
        verticies = {
            {-0.5, -1},
            {-0.5, 0},
            {-0.5, 1},
            {0.5, 1},
            {0.5, 0},
            {0.5, -1},
        };
        led_info = {
            true,
            true,
            true,
            true,
        };
        travel_order = {
            4,
            1,
            2,
            3,
            5,
        };
        break;
    }
    case ' ':
    {
        break;
    }
    default:
        valid = false;
        break;
    }

    if (led_info.size() != travel_order.size() - 1)
    {
        // Serial.print("Error::Mesh::Invalid Mesh Initilization, Travel order != led_info at char (");
        // Serial.println(sym + ")");
        // exit(-1);
    }
}

Mesh::~Mesh()
{
}