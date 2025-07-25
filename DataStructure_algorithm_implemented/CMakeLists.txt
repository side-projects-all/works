cmake_minimum_required(VERSION 3.28)
project(ds_alg_impl VERSION 0.1.0 LANGUAGES C CXX)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)

set(BOOST_ROOT "D:/dev_extensions/boost_1_84_0")
set(Boost_INCLUDE_DIRS "D:/dev_extensions/boost_1_84_0")
set(Boost_LIBRARY_DIR "D:/dev_extensions/boost_1_84_0/stage/lib")
set(Boost_ARCHITECTURE "-x64")
find_package(Boost 1.84 REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

find_package(Catch2 REQUIRED PATHS "D:/dev_extensions/catch2_local/sub_build/lib/cmake/Catch2")
#[[
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.3 # v3.5.3
)


FetchContent_MakeAvailable(Catch2)
]]
enable_testing()

add_subdirectory(trees)
add_subdirectory(graph)
add_subdirectory(math)
add_subdirectory(sorting)
add_subdirectory(list)
add_subdirectory(test)

add_executable(main main.cpp)

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/trees)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/math)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sorting)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/graph)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/list)

target_link_libraries(main PRIVATE My_list Shortest_path Trie MathFuncs Sortings)
