#include "Snake_Food.h"

Snake_Food::Snake_Food(int screenWidth, int screenHeight) {
    std::srand(std::time(nullptr));
    rect = {std::rand() % (screenWidth / 20) * 20, std::rand() % (screenHeight / 20) * 20, 20, 20};
}

void Snake_Food::respawn(int screenWidth, int screenHeight) {
    rect = {std::rand() % (screenWidth / 20) * 20, std::rand() % (screenHeight / 20) * 20, 20, 20};
}