cmake_minimum_required(VERSION 3.28)
project(Boost_funcs VERSION 0.1.0 LANGUAGES C CXX)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)

set(BOOST_ROOT "D:/dev_extensions/boost_1_84_0")
#library .a for static link; .so for dynamic link
#set(Boost_USE_STATIC_LIBS ON)
set(BOOST_INCLUDEDIR "D:/dev_extensions/boost_1_84_0")
set(BOOST_LIBRARYDIR "D:/dev_extensions/boost_1_84_0/stage/lib")
set(Boost_ARCHITECTURE "-x64")
#set(Boost_DEBUG ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

find_package(Catch2 REQUIRED PATHS "D:/dev_extensions/catch2_local/sub_build/lib/cmake/Catch2")
find_package(Boost 1.84 REQUIRED COMPONENTS program_options)
include_directories(${BOOST_INCLUDEDIR})
link_directories(${BOOST_LIBRARYDIR})


enable_testing()

add_executable(main main.cpp)

target_include_directories(main PUBLIC ${BOOST_INCLUDEDIR})
target_link_libraries(main PRIVATE Boost::program_options)

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "D:/dev_extensions/boost_1_84_0/stage/lib/libboost_program_options-mgw12-mt-d-x64-1_84.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    COMMAND_EXPAND_LISTS
  )
