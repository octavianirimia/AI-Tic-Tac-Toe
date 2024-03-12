#include <stdio.h>

#include <SDL.h>

#include "./configuration.h"
#include "./graphics.h"
#include "./logic.h"



int main(void)
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    char game_is_running = 't';

    unsigned short x_move[2], o_move[2];

    char board[3][3] = {{' ', ' ', ' '},
                        {' ', ' ', ' '},
                        {' ', ' ', ' '}};

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL could not be initialized: %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    window = SDL_CreateWindow("Tic Tac Toe",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH,
                              WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (window == NULL)
    {
        fprintf(stderr, "Window could not be created: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        fprintf(stderr, "Renderer could not be created: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    render(renderer, board);

    while (game_is_running == 't')
    {
        SDL_Event event;

        // Event loop
        while (SDL_PollEvent(&event))
        {
            // Handle events
            if (event.type == SDL_QUIT)
                game_is_running = 'f';
            
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                x_move[0] = (short)(event.button.y / CELL_HEIGHT);
                x_move[1] = (short)(event.button.x / CELL_WIDTH);

                unsigned short result = logic (board, x_move, o_move);

                render (renderer, board);

                if (result == 0)
                {
                    printf("You won!\n\n");
                    game_is_running = 'f';
                }
                
                else if (result == 1)
                {
                    printf("You lost!\n\n");
                    game_is_running = 'f';
                }
                
                else if (result == 2)
                {
                    printf("Draw!\n\n");
                    game_is_running = 'f';
                }
            }
            
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}