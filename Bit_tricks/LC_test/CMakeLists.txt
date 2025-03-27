#add_library(Lc_questions Lc_questions.cpp)
#target_link_libraries(Lc_questions PUBLIC compiler_flags)

add_library(Solution INTERFACE Solution.h)
target_link_libraries(Solution INTERFACE cxx_std_20)

