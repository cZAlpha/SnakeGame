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

// Overloaded constructor with width and height to meet requirements
Sprite::Sprite(int width, int height, SDL_Renderer *renderer) {
    // Initialize texture with blank surface of given dimensions
    // Initialize other variables
    std::cout << "Creating Sprite with width: " << width << ", height: " << height << std::endl;
}

    void Sprite::render(SDL_Renderer* renderer) { SDL_RenderCopy(renderer, texture, NULL, &rect); } // Render

    // Getters
    int Sprite::getX() const { return rect.x; }
    int Sprite::getY() const { return rect.y; }
    int Sprite::getW() const { return rect.w; }
    int Sprite::getH() const { return rect.h; }
    // Setters
    void Sprite::setX(int x) { rect.x = x; }
    void Sprite::setY(int y) { rect.y = y; }

    // Collision
    bool Sprite::isCollidingWith(const Sprite& sprite) const {
        SDL_Rect rectA = { rect.x, rect.y, rect.w, rect.h };
        SDL_Rect rectB = { sprite.getX(), sprite.getY(), sprite.getW(), sprite.getH() };
        return SDL_HasIntersection(&rectA, &rectB) == SDL_TRUE;
    }

    // Destructor
    Sprite::~Sprite() {
        cout << "Sprite is being destroyed" << endl; // console output
        if (texture != nullptr) { // Ensures deletion of SDL texture
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }
