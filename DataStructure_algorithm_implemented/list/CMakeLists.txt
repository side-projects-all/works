add_library(t_list STATIC t_list.c)
target_link_libraries(t_list PUBLIC compiler_flags)
add_library(sort_test STATIC sort_test.c)
target_link_libraries(sort_test PUBLIC compiler_flags)