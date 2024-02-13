//
// Created by Noah Klaus on 2/12/24.
//

// START - Includes
#include <iostream>
#include "Sprite.h" // Header
#include <SDL.h>    // SDL2
// STOP  - Includes

// START - Namespaces
using namespace std;
// STOP - Namespaces

// Sprite Class
Sprite::Sprite() {
    // Initialize texture and rect pointers to nullptr
    texture = nullptr;
    // Initialize rect to zeros
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
    id = std::rand();
    // Default, nothing
}

Sprite::Sprite(const char* imagePath, SDL_Renderer* renderer) {
    // Load image as texture ; Check for null pointer -> Log error
    SDL_Surface* surface = SDL_LoadBMP(imagePath);
    if (surface == nullptr) {
        cerr << "Failed to load image: " << SDL_GetError() << endl;
        return;
    }
    // Create texture for sprite surface ; Check for null pointer -> Log error
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        cerr << "Failed to create texture: " << SDL_GetError() << endl;
        SDL_FreeSurface(surface);
        return;
    }

    // Ascertain the width and height of BMP file from 'imagePath' in args
    int BMPwidth = surface->w;
    int BMPheight = surface->h;
    // Set the rectangle position and size
    rect.x = 0;
    rect.y = 0;
    rect.w = BMPwidth;
    rect.h = BMPheight;

    SDL_FreeSurface(surface);
} // Custom Constructor, takes args of img path as char*

    void Sprite::render(SDL_Renderer* renderer) { SDL_RenderCopy(renderer, texture, NULL, &rect); } // Render

    // Getters
    int Sprite::getX() { return rect.x; }
    int Sprite::getY() { return rect.y; }
    int Sprite::getW() { return rect.w; }
    int Sprite::getH() { return rect.h; }
