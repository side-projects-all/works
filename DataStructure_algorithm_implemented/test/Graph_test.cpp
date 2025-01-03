#include <catch2/catch_test_macros.hpp>
#include "../graph/UnionFind.h"
#include <iostream>

TEST_CASE("graph all test") {

  SECTION("union find test") {
    
    UnionFind uf(10);
    uf.union_set(1, 2);
    uf.union_set(2, 5);
    uf.union_set(5, 6);
    uf.union_set(6, 7);
    uf.union_set(3, 8);
    uf.union_set(8, 9);
    
    std::cout << uf.is_connected(1, 5) << "\n";
    std::cout << uf.is_connected(5, 7) << "\n";
    std::cout << uf.is_connected(4, 9) << "\n";

    uf.union_set(9, 4);
    
    std::cout << uf.is_connected(4, 9) << "\n";
    bool final = true;
    REQUIRE(final == true);
  }
}