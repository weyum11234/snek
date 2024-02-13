#include <SDL2/SDL.h>
#include <iostream>

// start SDL and create window
// returns true upon successful completion
bool init();

// cleanup
void close();

// render window
SDL_Window *gWindow = NULL;

// window surface
SDL_Surface *gScreenSurface = NULL;

// window dimensions
int SCREEN_WIDTH = 500;
int SCREEN_HEIGHT = 500;

int main()
{
    init();
    SDL_Event e;
    bool quit = false;
    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }
    }
}

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "sdl could not initialize, error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("snek", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            std::cerr << "could not create window, error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}