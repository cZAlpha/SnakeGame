//
// Created by Parents on 2/10/2024.
//

#ifndef APPLE_H
#define APPLE_H

#include "Sprite.h" // Include parent class

class Apple : public Sprite {
private:
    int value;
    int x;
    int y;

public:
    Apple();
    Apple(int value, int x, int y, SDL_Renderer* renderer);
    void setValue(int inputtedValue);
    void setLocation(int x, int y);
    int getValue();
    void incrementLength();
    int getX() const; // Add getter function for x coordinate
    int getY() const; // Add getter function for y coordinate
};

#endif // APPLE_H
