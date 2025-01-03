add_library(Threadsafe_stack INTERFACE)
#target_include_directories(Threadsafe_stack INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
#target_sources(Threadsafe_stack INTERFACE Threadsafe_stack.h)
target_compile_features(Threadsafe_stack INTERFACE cxx_std_20)

add_library(X INTERFACE Unique_lock_swap.h)
target_compile_features(X INTERFACE cxx_std_20)

add_library(Conn_works INTERFACE Conn_works.h)
target_compile_features(Conn_works INTERFACE cxx_std_20)

add_library(Cache_data INTERFACE Cache_data.h)
target_compile_features(Cache_data INTERFACE cxx_std_20)