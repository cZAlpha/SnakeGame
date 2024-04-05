//
// Created by Parents on 2/10/2024.
//

#ifndef APPLE_H
#define APPLE_H

#include "Sprite.h" // Include parent class

class Trashbag : public Sprite {
private:
    int value;
    int x;
    int y;

public:
    Trashbag();
    Trashbag(int x, int y, SDL_Renderer* renderer);
    void setLocation(int x, int y);
    void incrementLength();
};

#endif // APPLE_H
