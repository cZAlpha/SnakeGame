//
// Created by Noah Klaus on 2/1/24.
//

// START - Imports
#include <iostream>
#include <SDL.h>
// STOP  - Imports

// START - Namespaces
using namespace std;
// STOP - Namespaces

// START - Global Variables
SDL_Window* window;
SDL_Renderer* renderer;
int FPS = 60;
// STOP  - Global Variables


// START - Functions
int calculateMilliseconds(int desiredFPS) {
    return 1000 / desiredFPS;
}
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
    int windowed = 1;

    int result = SDL_Init(SDL_INIT_EVERYTHING);
    if (result < 0) return -1;

    Uint32 flags = SDL_WINDOW_SHOWN;
    window = SDL_CreateWindow("basic window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
    // STOP  - Init. Local Variables

    if (window == NULL) goto CLEANUP_AND_QUIT;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) goto CLEANUP_AND_QUIT;

    while (!quit) { // game loop
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
                        case SDLK_ESCAPE: // If the escape key is pressed, quit game
                            quit = 1;
                            break; // END SDLK_ESCAPE CASE
                        case SDLK_F1: // If 'F1' key is pressed, go into fullscreen mode
                        // THE FOLLOWING CODE CAUSES THE SCREEN TO BUG THE FUCK OUT (Only tested on OSX)
                            windowed = !windowed;
                            if (windowed) {
                                SDL_SetWindowFullscreen(window, SDL_FALSE);
                            } else {
                                SDL_SetWindowFullscreen(window, SDL_TRUE);
                            }
                            break; // END SDLK_F1 CASE
                    }
                    break; // END SDL_KEYUP CASE
            } // END SWITCH CASE LOGIC FLOW
        } // END OF CHECKING FOR KEY PRESSES

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Makes the screen blue with full opacity
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(fps); // updates every 10 ms which is
    } // END OF GAME LOOP

    // Cleanup
    CLEANUP_AND_QUIT:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
// STOP  - Main