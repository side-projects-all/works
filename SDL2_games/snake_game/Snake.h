#pragma once
#ifndef SNAKE_H
#define SNAKE_H
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>

class Snake {
public:
  std::vector<SDL_Rect> body;
  SDL_Rect head;
  int direction;

  Snake(int x, int y);
  void move();
  void grow();
};

#endif