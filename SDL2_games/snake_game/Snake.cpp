#include "Snake.h"

Snake::Snake(int x, int y) {
    head = {x, y, 20, 20};
    body.push_back(head);
    direction = SDL_SCANCODE_RIGHT;
}

void Snake::move() {
    SDL_Rect newHead = head;
    switch (direction) {
        case SDL_SCANCODE_UP: newHead.y -= 20; break;
        case SDL_SCANCODE_DOWN: newHead.y += 20; break;
        case SDL_SCANCODE_LEFT: newHead.x -= 20; break;
        case SDL_SCANCODE_RIGHT: newHead.x += 20; break;
    }
    body.insert(body.begin(), newHead);
    head = newHead;
    body.pop_back();
}

void Snake::grow() {
    SDL_Rect newHead = head;
    switch (direction) {
        case SDL_SCANCODE_UP: newHead.y -= 20; break;
        case SDL_SCANCODE_DOWN: newHead.y += 20; break;
        case SDL_SCANCODE_LEFT: newHead.x -= 20; break;
        case SDL_SCANCODE_RIGHT: newHead.x += 20; break;
    }
    body.insert(body.begin(), newHead);
    head = newHead;
}