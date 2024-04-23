//
// Created by Noah Klaus on 2/10/2024.
//

#ifndef TRASHMAN_H
#define TRASHMAN_H

#include "Sprite.h" // Include parent class

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

#endif // TRASHMAN_H
