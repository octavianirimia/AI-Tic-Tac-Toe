#include <SDL.h>

#include "./configuration.h"
#include <stdio.h>



void render_grid (SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    for (unsigned short i = 1; i < 3; i ++)
    {
        SDL_RenderDrawLine(renderer,
                           i * CELL_WIDTH, 0,
                           i * CELL_WIDTH , WINDOW_HEIGHT);
        
        SDL_RenderDrawLine(renderer,
                           0, i * CELL_HEIGHT,
                           WINDOW_WIDTH, i * CELL_HEIGHT);
    }
}



void render_X (SDL_Renderer *renderer, short row, short column)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    SDL_RenderDrawLine(renderer,
                       10 + column * CELL_WIDTH, 10 + row * CELL_HEIGHT,
                       (column + 1) * CELL_WIDTH - 10, (row + 1) * CELL_HEIGHT - 10);

    SDL_RenderDrawLine(renderer,
                       10 + column * CELL_WIDTH, (row + 1) * CELL_HEIGHT - 10,
                       (column + 1) * CELL_WIDTH - 10, 10 + row * CELL_HEIGHT);
}



void render_O (SDL_Renderer* renderer, unsigned short row, unsigned short column)
{
    short center_x = CELL_WIDTH * (column + 0.5);
    short center_y = CELL_HEIGHT * (row + 0.5);
    short radius = CELL_WIDTH / 2 - 10;
    short x = radius - 1;
    short y = 0;
    short tx = 1;
    short ty = 1;
    short error = tx - radius * 2;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

    while (x >= y)
    {
        // Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, center_x + x, center_y - y);
        SDL_RenderDrawPoint(renderer, center_x + x, center_y + y);
        SDL_RenderDrawPoint(renderer, center_x - x, center_y - y);
        SDL_RenderDrawPoint(renderer, center_x - x, center_y + y);
        SDL_RenderDrawPoint(renderer, center_x + y, center_y - x);
        SDL_RenderDrawPoint(renderer, center_x + y, center_y + x);
        SDL_RenderDrawPoint(renderer, center_x - y, center_y - x);
        SDL_RenderDrawPoint(renderer, center_x - y, center_y + x);

        if (error <= 0)
        {
            y++;
            error += ty;
            ty += 2;
        }

        else
        {
            x--;
            tx += 2;
            error += tx - radius * 2;
        }
    }
}



void render_board (SDL_Renderer *renderer, char board[3][3])
{
    for (unsigned short row = 0; row < 3; row ++)
        for (unsigned short column = 0; column < 3; column ++)
            if (board[row][column] == 'X')
                render_X (renderer, row, column);
            
            else if (board[row][column] == 'O')
                render_O (renderer, row, column);
}



void render (SDL_Renderer *renderer, char board[3][3])
{
    SDL_SetRenderDrawColor (renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear (renderer);

    render_grid(renderer);
    render_board (renderer, board);

    SDL_RenderPresent (renderer);
}