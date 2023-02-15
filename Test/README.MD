# Laser Light Show Source Code

## Team Members

* Dominic Benintendi

## Explanation

This github directory contains the source code for the Laser Lightshow Project

This project focuses on created a laser that is controlled by a microcontroller. This laser can change the Xdim and Ydim of the laser, and turning it on and off

Our end goal is to display the classic Atari game "PONG" using this laser, and allow two players to interact with the game, realtime.


## IDE

We are using PlatformIO as our development IDE 
The PlatformIO directory can be found in the /TEST/ Folder
This IDE natively support Teensy boards

## Microcontroller

The code is being loaded onto a Teensy4.1

## Code Structure

* src
  * Pointer.h : Singleton class for controlling the laser and galvos
  * transform.h: Data class that hold information about an objects location, size, and rotation in 2d/3d Space
  * symbol.h : Data class that holds a mesh, along a transform
  * mesh.h : Data class that holds vertex data for printing characters
  * sentence.h : Data class that hold a collection of symbols for printing
  * shape.h : Data class for basic shapes
  * vec.h : Data class for 2d/3d Vectors, usually used to represent cordinantes
  * utils.h : Utility files with helpful functions
* lib : Folder for holding header files
* include : folder for holding 3rd party libraries
* test : folder for holding test files
* .vscode : vscode config data

## Getting Started

### Instillation

1. Install github repo onto computers
2. Install PlatformIO on VSCODE
   1. This will take some time, as PlatformIO is several Gigabytes
3. When finished installing, Press the PlatformIO icon on the left side of the VSCODE terminal, and press PIO Home/Open
4. After this, select Open Project, and navigate to the /TEST/ directory
5. Happy coding!
