#include <iostream>
#include <vector>
#include "trie.h"
#include "MathFuncs.h"
#include <numeric>
#include "Sortings.h"
#include "Shortest_path.h"

int main() {

  Shortest_path sp;
  std::cout << "this city: " << sp.findTheCity() << "\n";

  /*
  MathFuncs mfs;
  int val = 77;
  bool r = mfs.only_has_3_factors(val);
  std::cout << r << "\n";
  
  Sortings sortings;
  std::vector<int> arr{4, 5, 1, 3, 7};
  sortings.insertion_sort(arr, false);
  //sortings.merge_sort(arr, 0, 4);
  //sortings.quick_sort(arr, 0, 4);
  //sortings.heap_sort(arr);
  sortings.show_vals(arr);
  */

  /*
  std::vector<std::string> words{ "apple", "app" };
  std::vector<bool> ans;
  Trie trie;
  trie.insert(words[0]);
  ans.push_back(trie.search(words[0]));
  ans.push_back(trie.search(words[1]));
  ans.push_back(trie.startsWith(words[1]));
  trie.insert(words[1]);
  ans.push_back(trie.search(words[1]));

  for (bool b : ans) {
    std::cout << b << " ";
  }
  */
  
  
  return 0;
}