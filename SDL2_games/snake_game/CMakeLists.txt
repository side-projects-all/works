
add_library(snake_game_func Snake_game_func.cpp)
target_include_directories(snake_game_func PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(snake_game_func PRIVATE ${SDL2_LIBRARIES})

add_library(snake Snake.cpp)
target_include_directories(snake PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(snake PRIVATE ${SDL2_LIBRARIES})

add_library(snake_food Snake_food.cpp)
target_include_directories(snake_food PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(snake_food PRIVATE ${SDL2_LIBRARIES})


