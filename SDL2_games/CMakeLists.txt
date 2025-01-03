cmake_minimum_required(VERSION 3.28)
project(sdl2_games VERSION 0.1.0 LANGUAGES C CXX)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

find_package(SDL2 REQUIRED PATHS "D:/dev_extensions/SDL2-2.30.5/x86_64-w64-mingw32")
find_package(Catch2 REQUIRED PATHS "D:/dev_extensions/catch2_local/sub_build/lib/cmake/Catch2")

enable_testing()
add_subdirectory(snake_game)
add_executable(main main.cpp)

target_include_directories(main PUBLIC ${SDL2_INCLUDE_DIRS} PRIVATE ../snake_game)
target_link_libraries(main PRIVATE ${SDL2_LIBRARIES} snake_game_func snake snake_food)

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "D:/dev_extensions/SDL2-2.30.5/x86_64-w64-mingw32/bin/SDL2.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    COMMAND_EXPAND_LISTS
  )


