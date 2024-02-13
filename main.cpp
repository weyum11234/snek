#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include <deque>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *game_window = SDL_CreateWindow("snek", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 1000, SDL_WINDOW_SHOWN);
    SDL_Renderer *game_renderer = SDL_CreateRenderer(game_window, -1, 0);
    SDL_Event e;

    enum Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };

    bool is_running = true;
    int direction = 0;

    // snake body
    SDL_Rect head{500, 500, 10, 10};
    std::deque<SDL_Rect> body;
    int size = 1;

    // apple
    SDL_Rect apple{rand() % 100 * 10, rand() % 100 * 10, 10, 10};

    // main loop
    while (is_running)
    {
        // check input
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                is_running = false;
            }
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    if (direction != DOWN)
                        direction = UP;
                    break;
                case SDLK_DOWN:
                    if (direction != UP)
                        direction = DOWN;
                    break;
                case SDLK_LEFT:
                    if (direction != RIGHT)
                        direction = LEFT;
                    break;
                case SDLK_RIGHT:
                    if (direction != LEFT)
                        direction = RIGHT;
                    break;
                }
            }
        }

        // move
        switch (direction)
        {
        case DOWN:
            head.y += 10;
            break;
        case UP:
            head.y -= 10;
            break;
        case LEFT:
            head.x -= 10;
            break;
        case RIGHT:
            head.x += 10;
            break;
        }

        // check collision with apple
        if (head.x == apple.x && head.y == apple.y)
        {
            // create new apple
            apple.x = rand() % 100 * 10;
            apple.y = rand() % 100 * 10;

            // increase body length
            size += 10;
        }

        // check collision with body
        for (size_t i = 0; i < body.size(); ++i)
        {
            if (head.x == body[i].x && head.y == body[i].y)
            {
                // reset game
                size = 1;
                head.x = 500, head.y = 500;
                direction = 0;

                // create new apple
                apple.x = rand() % 100 * 10;
                apple.y = rand() % 100 * 10;
            }
        }

        // check collision with wall
        if (head.x > 999 || head.x < 0 || head.y > 999 || head.y < 0)
        {
            // reset game
            size = 1;
            head.x = 500, head.y = 500;
            direction = 0;

            // create new apple
            apple.x = rand() % 100 * 10;
            apple.y = rand() % 100 * 10;
        }

        body.push_front(head);

        while (body.size() > size)
        {
            body.pop_back();
        }

        // clear window
        SDL_SetRenderDrawColor(game_renderer, 0, 0, 0, 255);
        SDL_RenderClear(game_renderer);

        // draw body
        SDL_SetRenderDrawColor(game_renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(game_renderer, &head);
        for (size_t i = 0; i < body.size(); ++i)
        {
            SDL_RenderFillRect(game_renderer, &body[i]);
        }
        SDL_SetRenderDrawColor(game_renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(game_renderer, &apple);

        SDL_RenderPresent(game_renderer);
        SDL_Delay(25);
    }
}