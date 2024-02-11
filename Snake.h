//
// Created by cZAlpha on 2/10/2024.
//

#ifndef SNAKE_H
#define SNAKE_H

#include "Apple.h" // Include Apple.h to use the Apple class

class Snake {
private:
    int length; // Length of snake (size)
    int x;       // X Coord
    int y;      // Y Coord

public:
    Snake(); // Default Constructor
    Snake(int len, int x, int y); // Custom Constructor
    void setLength(int inputtedLength); // Setter for length
    void setLocation(int x, int y); // Setter for location
    int getLength() const; // Getter for length
    void incrementLength(); // Increment length
    int getLocation() const; // Getter for x
    int getY() const; // Getter for y
    bool isCollidingWith(const Apple& apple) const; // Returns true if colliding, false if not
};

#endif // SNAKE_H
