//
// Created by Noah Klaus on 2/10/2024.
//

#include "Trashbag.h"
#include "Sprite.h"
#include <SDL.h>
#include <iostream>

using namespace std;

Trashbag::Trashbag(): value(1), x(0), y(0) {
}

Trashbag::Trashbag(int x, int y, SDL_Renderer* renderer) : Sprite("/Users/nbklaus21/CLionProjects/SnakeGame/Assets/trashbag_sprite.bmp", renderer), value(1) {
    this->setX(x);
    this->setY(y);
}

    void Trashbag::setLocation(int x, int y) {
        this->setX(x);
        this->setY(y);
    }

    Trashbag& Trashbag::operator+(const Trashbag& other) {
        // Perform addition operation here if needed
        return *this; // Return the first Trashbag
    }

    void Trashbag::render(SDL_Renderer* renderer) {
        // Custom rendering for Trashbag...
        Sprite::render(renderer); // Call base class render method
    }

Trashbag::~Trashbag() {
    // Destructor
    cout << "Trashbag is being destroyed" << endl;
}
