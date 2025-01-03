add_library(Threadsafe_queue INTERFACE)
#target_include_directories(Threadsafe_stack INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
#target_sources(Threadsafe_stack INTERFACE Threadsafe_stack.h)
target_compile_features(Threadsafe_queue INTERFACE cxx_std_20)

add_library(Async_n_Future INTERFACE Async_n_Future.h)
target_compile_features(Async_n_Future INTERFACE cxx_std_20)

add_library(Packaged_task_n_Promise INTERFACE Packaged_task_n_Promise.h)
target_compile_features(Packaged_task_n_Promise INTERFACE cxx_std_20)

add_library(Latch_example INTERFACE Latch_example.h)
target_compile_features(Latch_example INTERFACE cxx_std_20)