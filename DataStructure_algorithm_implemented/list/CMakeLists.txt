add_library(My_list STATIC My_list.c)
target_link_libraries(My_list PUBLIC compiler_flags)