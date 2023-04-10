#ifndef MESH_H
#define MESH_H
#include <Arduino.h>
#include <dataobjects/transform.h>
#include <vector>

class Mesh
{
private:
public:
    /// @brief A collection of vertices in the range of x= { -1 , 1 } y = { -1 , 1 }
    /// These vertices are use to represent points and corners of any given object
    /// Example) A square would have 4 vertices.
    std::vector<Vec2> verticies;
    /// @brief A collection of bools, detailing when a led should be on or off
    std::vector<boolean> led_info;
    /// @brief A collection of indexes, detailing what order should the laser travel the vertices
    /// Example, A square would travel to 0->1->2->3->0
    std::vector<uint16_t> travel_order;
    /// @brief Is the current symbol holding a value?
    bool valid = true;

    Mesh(/* args */);
    /// @brief Takes in a character, and fills the class instance with the Mesh data for that character
    /// currently supports A-Z
    /// @param sym
    Mesh(char sym);
    ~Mesh();
};

#endif // !MESH_H
