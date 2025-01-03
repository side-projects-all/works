cmake_minimum_required(VERSION 3.28)
project(Opencv_apps VERSION 0.1.0 LANGUAGES C CXX)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)

FIND_PACKAGE(OpenCV REQUIRED PATHS "D:/dev_extensions/opencv_dev_build/build/install")
find_package(Catch2 REQUIRED PATHS "D:/dev_extensions/catch2_local/sub_build/lib/cmake/Catch2")

enable_testing()

add_executable(main main.cpp)
message(${OpenCV_INCLUDE_DIRS})
#target_include_directories(main PUBLIC ${OpenCV_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(main ${OpenCV_LIBS})




