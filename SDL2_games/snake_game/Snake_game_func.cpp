#include "Snake_game_func.h"

bool Snake_game_func::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Snake_game_func::close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Snake_game_func::game_run(Snake& snake, Snake_Food& snake_food) {
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        handleInput(snake);
        snake.move();

        if (checkCollision(snake.head, snake_food.rect)) {
            snake.grow();
            snake_food.respawn(SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // Render objects here
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
        for (const auto& segment : snake.body) {
            SDL_RenderFillRect(renderer, &segment);
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &snake_food.rect);
        // Update screen
        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

    close();
}

void Snake_game_func::handleInput(Snake& snake) {
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_UP] && snake.direction != SDL_SCANCODE_DOWN) {
        snake.direction = SDL_SCANCODE_UP;
    }
    if (state[SDL_SCANCODE_DOWN] && snake.direction != SDL_SCANCODE_UP) {
        snake.direction = SDL_SCANCODE_DOWN;
    }
    if (state[SDL_SCANCODE_LEFT] && snake.direction != SDL_SCANCODE_RIGHT) {
        snake.direction = SDL_SCANCODE_LEFT;
    }
    if (state[SDL_SCANCODE_RIGHT] && snake.direction != SDL_SCANCODE_LEFT) {
        snake.direction = SDL_SCANCODE_RIGHT;
    }
}

bool Snake_game_func::checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return (a.x == b.x && a.y == b.y);
}


