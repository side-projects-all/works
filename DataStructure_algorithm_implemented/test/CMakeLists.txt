#these lines are necessary
include(CTest)
include(Catch)

add_executable(Trees_test Trees_test.cpp)
target_include_directories(Trees_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../trees)
target_link_libraries(Trees_test PRIVATE Trie PRIVATE Catch2::Catch2WithMain PUBLIC compiler_flags)

add_executable(Graph_test Graph_test.cpp)
target_include_directories(Graph_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../graph)
target_link_libraries(Graph_test PRIVATE UnionFind PRIVATE Catch2::Catch2WithMain PUBLIC compiler_flags)

catch_discover_tests(Trees_test)
catch_discover_tests(Graph_test)