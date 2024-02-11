//
// Created by cZAlpha on 2/1/24.
//

// START - Imports
#include <iostream>
#include <SDL.h>
#include "Apple.h"
// STOP  - Imports

// START - Namespaces
using namespace std;
// STOP - Namespaces

// START - Global Variables
SDL_Window* window;
SDL_Renderer* renderer;
int FPS = 60;
// STOP  - Global Variables



// START - Classes
class TestSprite {
private:
    SDL_Texture* texture;
    SDL_Rect rect;
    int movementAmount = 50; // number of pixels to move by when moving
public:
    TestSprite(SDL_Renderer* renderer) {
        // Create a surface for the sprite
        SDL_Surface* surface = SDL_CreateRGBSurface(0, 10, 10, 32, 0, 0, 0, 0);
        if (surface == nullptr) {
            std::cerr << "Failed to create surface: " << SDL_GetError() << std::endl;
            return; // Returns early to stop the constructor from causing further errors
        }

        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 50, 0)); // Fill the surface with green color

        texture = SDL_CreateTextureFromSurface(renderer, surface); // Convert the surface to a texture
        if (texture == nullptr) {
            std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(surface);
            return;
        }

        // Set the rectangle position and size
        rect.x = 0;
        rect.y = 0;
        rect.w = 50;
        rect.h = 50;

        SDL_FreeSurface(surface); // Free the surface as it's no longer needed
    }

    ~TestSprite() { SDL_DestroyTexture(texture); } // Cleanup texture

    // START - Movement Functions
    void goLeft() { rect.x -= movementAmount; } // Decrements the rectangle's x value
    void goRight() { rect.x += movementAmount; } // Increments the rectangle's x value
    void goDown() { rect.y += movementAmount; } // Increments the rectangle's y value (ASSUMING: incrementing y value makes it go up)
    void goUp() { rect.y -= movementAmount; } // Decrements the rectangle's y value (ASSUMING: decrementing y value makes it go up)
    // STOP  - Movement Functions

    // START - General Purpose Functions
    void render(SDL_Renderer* renderer) { SDL_RenderCopy(renderer, texture, NULL, &rect); } // Render the texture

    // Getters
    int getX() { return rect.x; }
    int getY() { return rect.y; }
    int getW() { return rect.w; }
    int getH() { return rect.h; }
    // STOP  - General Purpose Functions
};
// STOP  - Classes

// START - Functions
int calculateMilliseconds(int desiredFPS) {
    return 1000 / desiredFPS;
}

// Need a function to ascertain whether the snake is colliding with an Apple so that you can add points
// int isCollide( object one, object two ) { Returns 0 for false, 1 for true } // Preliminary Idea

// STOP - Functions


// START - Main
int main(int argc, char* argv[]) {
    cout << "Main Function Has Started." << endl;

    // START - Init. Local Variables
    int fps = calculateMilliseconds(FPS);
    int quit = 0;
    SDL_Event event;

    int w = 800;
    int h = 600;
    int windowed = 1; // Window flag, used for toggle window/fullscreen
    int test = 1; // Test flag, used to toggle restricted movement

    int result = SDL_Init(SDL_INIT_EVERYTHING);
    if (result < 0) return -1;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL); // Current Key State (what is being pressed)
    // STOP  - Init. Local Variables

    // START - Error Checking
    Uint32 flags = SDL_WINDOW_SHOWN;
    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
    if (window == NULL) {
        cerr << "Failed to create window: " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        cerr << "Failed to create renderer: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    // STOP  - Error Checking

    // START - Sprites
    TestSprite testSprite(renderer); // Create TestSprite object
    // STOP  - Sprites

    // START - Game Loop
    while (!quit) { // game loop
        SDL_PumpEvents(); // Update the state of all keys

        if (test == 1) { // Flag for checking if movement should be unrestricted (1: Unrestricted movement, 0: Normal movement)
            // START - Unrestricted Movement Keys
            if (currentKeyStates[SDL_SCANCODE_A] && testSprite.getX() > 0) { testSprite.goLeft(); } // LEFT
            if (currentKeyStates[SDL_SCANCODE_D] && testSprite.getX() < w - testSprite.getW()) { testSprite.goRight(); } // RIGHT
            if (currentKeyStates[SDL_SCANCODE_W] && testSprite.getY() > 0) { testSprite.goUp(); }   // UP
            if (currentKeyStates[SDL_SCANCODE_S] && testSprite.getY() < h - testSprite.getH()) { testSprite.goDown(); } // DOWN
            // STOP  - Unrestricted Movement Keys
        }

        // START - System Keys
        while ( SDL_PollEvent( &event ) != 0 ) { // If an event is encountered
            switch (event.type) { // Logic Flow using switch cases
                case SDL_WINDOWEVENT_SIZE_CHANGED:  // Handles window size changing
                    w = event.window.data1;
                    h = event.window.data2;
                    SDL_RenderPresent(renderer);
                    break; // END SDL_WINDOWEVENT_SIZE_CHANGED CASE
                case SDL_QUIT: // If the quit button is clicked, exit game
                    quit = 1;
                    break; // END SDL_QUIT CASE
                case SDL_KEYUP: // If a key is pressed
                    switch (event.key.keysym.sym) { // Gets the specific key that is pressed
                        // START - System/Window Changes From Key Press
                        case SDLK_ESCAPE: // If the escape key is pressed, quit game
                            quit = 1;
                            break; // END SDLK_ESCAPE CASE
                        case SDLK_F1: // If 'F1' key is pressed, go into fullscreen mode
                            // THE FOLLOWING CODE CAUSES THE SCREEN TO BUG THE FUCK OUT (Only  n OSX)
                            windowed = !windowed;
                            if (windowed) { SDL_SetWindowFullscreen(window, SDL_FALSE); }
                            else { SDL_SetWindowFullscreen(window, SDL_TRUE); }
                            break; // END SDLK_F1 CASE
                        case SDLK_a: // If 'a' key is pressed,
                            if (testSprite.getX() > 0 && test == 0) { testSprite.goLeft(); } // LEFT
                            break;
                        case SDLK_d: // If 'd' key is pressed,
                            if (testSprite.getX() < w - testSprite.getW() && test == 0) { testSprite.goRight(); } // RIGHT
                            break;
                        case SDLK_w: // If 'w' key is pressed,
                            if (testSprite.getY() > 0 && test == 0) { testSprite.goUp(); }   // UP
                            break;
                        case SDLK_s: // If 's' key is pressed,
                            if (testSprite.getY() < h - testSprite.getH() && test == 0) { testSprite.goDown(); } // DOWN
                            break;
                        case SDLK_z: // If 'z' key is pressed,
                            if (test == 0) { test = 1; }
                            else { test = 0; }
                            break;
                        // STOP  - System/Window Changes From Key Press
                    }
                    break; // END SDL_KEYUP CASE
            } // END SWITCH CASE LOGIC FLOW
        } // END OF CHECKING FOR KEY PRESSES
        // STOP  - System Keys

        SDL_SetRenderDrawColor(renderer, 20, 200, 20, 255); // Makes the screen blue with full opacity
        SDL_RenderClear(renderer);

        // Test Sprite
        testSprite.render(renderer); // Render the sprite

        SDL_RenderPresent(renderer);
        SDL_Delay(fps); // updates every 10 ms which is
    } // END OF GAME LOOP
    // STOP  - Game Loop

    // Cleanup
    CLEANUP_AND_QUIT:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
// STOP  - Main