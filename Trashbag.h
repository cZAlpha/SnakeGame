//
// Created by Noah Klaus on 2/10/2024.
//

#ifndef TRASHBAG_H
#define TRASHBAG_H

#include "Sprite.h" // Include parent class


class Trashbag : public Sprite {
private:
    const int value;
    int x;
    int y;

public:
    Trashbag();
    Trashbag(int x, int y, SDL_Renderer* renderer);
    void setLocation(int x, int y);
    void setValue(int setValue);

    Trashbag& operator+(const Trashbag& other); // Operator as per requirement

    virtual ~Trashbag();

    // Override render method
    virtual void render(SDL_Renderer* renderer) override;
};

#endif // TRASHBAG_H
