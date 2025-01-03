#include <catch2/catch_test_macros.hpp>
#include "../trees/trie.h"
#include <iostream>

TEST_CASE("trees all test") {

  SECTION("trie test") {
    
    std::vector<std::string> words{ "apple", "app" };
    std::vector<bool> ans;
    Trie trie;
    trie.insert(words[0]);
    ans.push_back(trie.search(words[0]));
    ans.push_back(trie.search(words[1]));
    ans.push_back(trie.startsWith(words[1]));
    trie.insert(words[1]);
    ans.push_back(trie.search(words[1]));

    bool result[4]{ true, false, true, true};
    bool final = true;
    for (int i = 0; i < ans.size(); ++i) {
      if (result[i] != ans[i]) {
        final = false;
        break;
      }
    }

    REQUIRE(final == true);
  }
}