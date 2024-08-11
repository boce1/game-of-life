#ifndef CELL_H
#define CELL_H

#include <SDL2/SDL.h>

class cell
{
    public:
        int row, column;
        bool alive;
        SDL_Rect rect;

        cell(int row_grid, int col_grid, int width);
        draw(SDL_Renderer* renderer, const int &red, const int &green, const int &blue);
};

#endif // CELL_H