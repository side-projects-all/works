#pragma once
#ifndef SNAKE_FOOD_H
#define SNAKE_FOOD_H
#include <SDL2/SDL.h>
#include <vector>
#include <cstdlib>
#include <ctime>

class Snake_Food {
public:
    SDL_Rect rect;

    Snake_Food(int screenWidth, int screenHeight);
    void respawn(int screenWidth, int screenHeight);
};
#endif