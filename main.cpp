#include <iostream>
#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include "cell.hpp"

const int WIDTH = 800;
const int HEIGHT = WIDTH;
const int TARGET_FPS = 60;
const int FRAME_DURATION_MS = 1000 / TARGET_FPS;

void draw(SDL_Renderer *renderer, std::vector<cell> cells);
void drawGrid(SDL_Renderer *renderer, const int &cellNum, const int &cellWidth);
void changeStateCell(SDL_Event &event, const int &mouse_x, const int &mouse_y, const int &cellWidth, const int &numRow, std::vector<cell> &cells);
void cellLife(std::vector<cell> &cells, const int &numRow, const bool &simulationFlag);
void toggleSimulation(SDL_Event &event, bool &flag);
void updateScale(std::vector<cell> &cells, int &cellNumRow, int &cellWidth);
void changeScale(SDL_Event &event, std::vector<cell> &cells, int &cellNumRow, int &cellWidth);
void changeSpeed(SDL_Event &event, int &speedCoef);

int main(int argc, char* argv[]) 
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Game of life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if(window == NULL) 
    {
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer == NULL)
    {
        return 1;
    }

    int cellNumRow = 20;
    int cellWidth;
    std::vector<cell> cells;
    updateScale(cells, cellNumRow, cellWidth);


    bool running = true;

    SDL_Event event;

    Uint64 nowTicks = SDL_GetPerformanceCounter();
    Uint64 lastTicks = 0;
    double deltaTime = 0;
    int delayCoef = 4;

    bool simulationFlag = false;

    int mouse_x, mouse_y; 
    while(running)
    {
        lastTicks = nowTicks;
        nowTicks = SDL_GetPerformanceCounter();
        deltaTime = (double)((nowTicks - lastTicks)*1000 / (double)SDL_GetPerformanceFrequency());
        int delay = FRAME_DURATION_MS - (int)deltaTime;
        if (delay > 0) 
        {
            SDL_Delay(delay * delayCoef);
        }    
        std::cout << delayCoef << "\n";
        SDL_GetMouseState(&mouse_x, &mouse_y);

        draw(renderer, cells);
        cellLife(cells, cellNumRow, simulationFlag);
        if(SDL_PollEvent(&event)) 
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }
            changeStateCell(event, mouse_x, mouse_y, cellWidth, cellNumRow, cells);
            toggleSimulation(event, simulationFlag);
            changeScale(event, cells, cellNumRow, cellWidth);
            changeSpeed(event, delayCoef);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void draw(SDL_Renderer *renderer, std::vector<cell> cells)
{
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);
    for(int i = 0; i < cells.size(); i++)
    {
        cells[i].draw(renderer, 150, 150, 255);
    }
    drawGrid(renderer, cells.size(), cells[0].rect.w);
    SDL_RenderPresent(renderer);
}

void drawGrid(SDL_Renderer *renderer, const int &cellNum, const int &cellWidth)
{
    for(int i = 0; i <= cellNum; i++)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawLine(renderer, 0, i * cellWidth, WIDTH, i * cellWidth);
        SDL_RenderDrawLine(renderer, i * cellWidth, 0, i * cellWidth, HEIGHT);
    }
}

void changeStateCell(SDL_Event &event, const int &mouse_x, const int &mouse_y, const int &cellWidth, const int &numRow, std::vector<cell> &cells)
{
    if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        int row, col, index;
        row = mouse_y / cellWidth;
        col = mouse_x / cellWidth;
        index = row * numRow + col;

        cells[index].alive = !cells[index].alive;
    }
}

void cellLife(std::vector<cell> &cells, const int &numRow, const bool &simulationFlag)
{
    if(simulationFlag)
    {
        std::vector<int> indexRemove;
        std::vector<int> indexAdd;
        int neighbours = 0;
        for(int i = 0; i < cells.size(); i++)
        {
            neighbours = 0;
            if(cells[i].row > 0)
            {
                if(cells[i - numRow].alive) // up neighbour
                {
                    neighbours++;
                }
                if(cells[i].column > 0 && cells[i - numRow - 1].alive) // up left neighbour
                {
                    neighbours++;
                }
                if(cells[i].column < numRow - 1 && cells[i - numRow + 1].alive) // up right neighbour
                {
                    neighbours++;
                }
            }
            if(cells[i].column > 0)
            {
                if(cells[i - 1].alive) // left neighbour
                {
                    neighbours++;
                }
                if(cells[i].row < numRow - 1 && cells[i + numRow - 1].alive) // down left neighbour
                {
                    neighbours++;
                }
            }
            if(cells[i].row < numRow - 1)
            {
                if(cells[i + numRow].alive) // down neighbour
                {
                    neighbours++;
                }
                if(cells[i].column < numRow - 1 && cells[i + numRow + 1].alive) // down left neighbour
                {
                    neighbours++;
                }
            }
            if(cells[i].column < numRow - 1)
            {
                if(cells[i + 1].alive) // right neighbour
                {
                    neighbours++;
                }
            }

            if(cells[i].alive && (neighbours <= 1 || neighbours >= 4))
            {
                indexRemove.push_back(i);
            }else if(!cells[i].alive && neighbours == 3)
            {
                indexAdd.push_back(i);
            }
        }

        for(int i : indexRemove)
        {
            cells[i].alive = false;
        }

        for(int i : indexAdd)
        {
            cells[i].alive = true;
        }

        indexRemove.clear();
        indexAdd.clear();
    }
}

void toggleSimulation(SDL_Event &event, bool &simulationFlag)
{
    if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT)
    {
        simulationFlag = !simulationFlag;
    }
}

void updateScale(std::vector<cell> &cells, int &cellNumRow, int &cellWidth)
{
    cells.clear();
    cellWidth = WIDTH / cellNumRow;

    for(int i = 0; i < cellNumRow * cellNumRow; i++)
    {
        int row = i / cellNumRow;
        int col = i % cellNumRow;

        cells.push_back(cell(row, col, cellWidth));
    }
}

void changeScale(SDL_Event &event, std::vector<cell> &cells, int &cellNumRow, int &cellWidth)
{
    if(event.type == SDL_MOUSEWHEEL)
    {
        if(event.wheel.y > 0 && cellNumRow > 10)
        {
            cellNumRow /= 2;
            updateScale(cells, cellNumRow, cellWidth);
        }
        else if(event.wheel.y < 0 && cellNumRow < 80)
        {
            cellNumRow *= 2;
            updateScale(cells, cellNumRow, cellWidth);
        }
    }
}

void changeSpeed(SDL_Event &event, int &speedCoef)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym) {
            case SDLK_1:
                speedCoef = 7;
                break;
            case SDLK_2:
                speedCoef = 5;
                break;
            case SDLK_3:
                speedCoef = 3;
                break;
            case SDLK_4:
                speedCoef = 1;
                break;
            default:
                break;
        }   
    }
}


