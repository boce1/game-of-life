#include "cell.hpp"

cell::cell(int row_grid, int col_grid, int width)
{
    row = row_grid;
    column = col_grid;
    rect.x = column * width;
    rect.y = row * width;
    rect.w = width;
    rect.h = width;
    alive = false;
}

cell::draw(SDL_Renderer* renderer, const int &red, const int &green, const int &blue)
{
    if(alive)
    {
        SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}