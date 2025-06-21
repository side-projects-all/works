#add_library(All_tricks All_tricks.cpp)
#target_link_libraries(All_tricks PUBLIC compiler_flags)

add_library(All_tricks INTERFACE All_tricks.h)
target_link_libraries(All_tricks INTERFACE cxx_std_20)

