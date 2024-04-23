//
// Created by Noah Klaus on 2/10/2024.
//

#ifndef TRASHMAN_H
#define TRASHMAN_H

#include "Sprite.h" // Include parent class

class Trashman : public Sprite {
private:
    static int trash; // # of trashbags accrued by given trashman
    int x;       // X Coord
    int y;      // Y Coord

public:
    Trashman(); // Default Constructor
    Trashman(int x, int y, SDL_Renderer* renderer); // Custom Constructor

    void setTrash(int inputtedTrash); // Setter for trashbags collected
    void setLocation(int x, int y); // Setter for location
    int getTrash() const; // Getter for trash
    void incrementTrash(); // Increment length
};

#endif // TRASHMAN_H
