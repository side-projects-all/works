cmake_minimum_required(VERSION 3.28)
project(Bit_tricks VERSION 0.1.0 LANGUAGES C CXX)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

find_package(Catch2 REQUIRED PATHS "D:/dev_extensions/catch2_local/sub_build/lib/cmake/Catch2")

enable_testing()
add_subdirectory(tricks)
add_subdirectory(LC_test)
add_executable(main main.cpp)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tricks)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/LC_test)
target_link_libraries(main PRIVATE All_tricks Lc_questions)




