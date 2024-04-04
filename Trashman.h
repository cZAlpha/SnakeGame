//
// Created by cZAlpha on 2/10/2024.
//

#ifndef SNAKE_H
#define SNAKE_H

#include "Sprite.h" // Include parent class
#include "Trashbag.h" // Include Trashbag.h to use the Trashbag class

class Trashman : public Sprite {
private:
    int length; // Length of snake (size)
    int x;       // X Coord
    int y;      // Y Coord

public:
    Trashman(); // Default Constructor
    Trashman(int x, int y, SDL_Renderer* renderer); // Custom Constructor

    void setLength(int inputtedLength); // Setter for length
    void setLocation(int x, int y); // Setter for location
    int getLength() const; // Getter for length
    void incrementLength(); // Increment length
};

#endif // SNAKE_H
