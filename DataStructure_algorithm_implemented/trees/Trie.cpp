
#include "Trie.h"

void Trie::insert(const std::string& word) {
    Node* now = &root;

    for (char c : word) {
        int i = c - 'a';

        if (now->next[i] == nullptr) {
            now->next[i] = new Node();
        }

        now = now->next[i];
    }

    now->isEnd = true;
}
    
bool Trie::search(const std::string& word) {
  if (word.empty()) {
      return false;
  }

  Node* now = &root;

  for (int j = 0; j < word.size(); ++j) {
      int i = word[j] - 'a';

      if (now->next[i] == nullptr) {
          return false;
      }

      now = now->next[i];
  }

  return now->isEnd ? true : false;
}
    
bool Trie::startsWith(const std::string& prefix) {
  if (prefix.empty()) {
      return false;
  }

  Node* now = &root;

  for (char c : prefix) {
      int i = c - 'a';

      if (now->next[i] == nullptr) {
          return false;
      }

      now = now->next[i];
  }

  return true;
}