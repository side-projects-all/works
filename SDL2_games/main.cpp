/*
#include <SDL2/SDL.h>
#include <iostream>
*/
#include "snake_game/Snake_game_func.h"
#include "snake_game/Snake.h"
#include "snake_game/Snake_Food.h"


int main(int argc, char *argv[]) {
  Snake_game_func sgf;
  Snake snake(sgf.SCREEN_WIDTH / 2, sgf.SCREEN_HEIGHT / 2);
  Snake_Food snake_food(sgf.SCREEN_WIDTH, sgf.SCREEN_HEIGHT);
  sgf.init();
  if (!sgf.init()) {
      std::cerr << "Failed to initialize!" << "\n";
      return -1;
  }

  sgf.game_run(snake, snake_food);

  //std::cout << "hi world\n";

  /*
  const int W = 800;
  const int H = 600;

  //The window we'll be rendering to
  SDL_Window* window = nullptr;
  
  //The surface contained by the window
  SDL_Surface* screenSurface = nullptr;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";

  } else {
    //Create window
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);

    if(window == nullptr) {
      std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";

    } else {
      //Get window surface
      screenSurface = SDL_GetWindowSurface( window );

      //Fill the surface white
      SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
      
      //Update the surface
      SDL_UpdateWindowSurface( window );

      //Hack to get window to stay up
      SDL_Event e; 
      bool quit = false; 
      while(quit == false) { 
        while(SDL_PollEvent( &e )) { 
          if(e.type == SDL_QUIT) {
            quit = true;
          }
        } 
      }
    }
  }

  //Destroy window
  SDL_DestroyWindow( window );

  //Quit SDL subsystems
  SDL_Quit();
  */

  

  return 0;
}