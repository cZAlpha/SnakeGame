//
// Created by cZAlpha on 2/10/2024.
//

#ifndef SNAKE_H
#define SNAKE_H

#include "Sprite.h" // Include parent class
#include "Apple.h" // Include Apple.h to use the Apple class

class Snake : public Sprite {
private:
    int length; // Length of snake (size)
    int x;       // X Coord
    int y;      // Y Coord

public:
    Snake(); // Default Constructor
    Snake(int len, int x, int y, SDL_Renderer* renderer); // Custom Constructor

    void setLength(int inputtedLength); // Setter for length
    void setLocation(int x, int y); // Setter for location
    int getLength() const; // Getter for length
    void incrementLength(); // Increment length
};

#endif // SNAKE_H
