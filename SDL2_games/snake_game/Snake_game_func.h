#pragma once
#ifndef SNAKE_GAME_FUNC_H
#define SNAKE_GAME_FUNC_H
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "Snake.h"
#include "Snake_Food.h"

class Snake_game_func final {
public:
  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 480;
  
  Snake_game_func() {
  }

  bool init();
  void close();
  void game_run(Snake& snake, Snake_Food& snake_food);
  void handleInput(Snake& snake);
  bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
private:
  
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
};

#endif
