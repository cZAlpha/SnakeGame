//
// Created by Noah Klaus on 2/10/2024.
//

#include "Trashman.h"
#include "Sprite.h"
#include <SDL.h>

int Trashman::trash = 0; // Define the static member variable trash

Trashman::Trashman() : Sprite() { // Default constructor
    trash = 0;
    x = 0;
    y = 0;
}

Trashman::Trashman(int x, int y, SDL_Renderer* renderer) : Sprite("/Users/nbklaus21/CLionProjects/SnakeGame/Assets/trashman_sprite.bmp", renderer) { // Full custom constructor
    this->setX(x);
    this->setY(y);
}

    void Trashman::setTrash(int inputtedTrash) {
        if (inputtedTrash >= 1) {
            trash = inputtedTrash;
        }
    }

    void Trashman::setLocation(int x, int y) {
        this->setX(x);
        this->setY(y);
    }

    int Trashman::getTrash() const {
        return trash;
    }

    void Trashman::incrementTrash() {
        trash++;
    }

