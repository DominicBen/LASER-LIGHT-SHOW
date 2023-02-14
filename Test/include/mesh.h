#ifndef MESH_H
#define MESH_H
#include <Arduino.h>
#include <transform.h>
#include <vector>

class Mesh
{
private:
public:
    std::vector<Vec2> verticies;
    std::vector<boolean> led_info;
    std::vector<uint16_t> travel_order;
    bool valid = true;
    Mesh(/* args */);
    Mesh(char sym);
    ~Mesh();
};

Mesh::Mesh(/* args */)
{
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
        Serial.println("Error::Mesh::Invalid Mesh Initilization, Travel order != led_info");
        // exit(-1);
    }
}

Mesh::~Mesh()
{
}

#endif // !MESH_H
