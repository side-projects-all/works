/*

*/

class Solution {
private:
    struct TrieNode {
        std::vector<int> wordIndex;
        TrieNode* children[26];

        TrieNode() {
            for (auto& child : children) {
                child = nullptr;
            }
        }
    };

    TrieNode* root;

    void createTrie(vector<string>& words) {

        root = new TrieNode();
        TrieNode* now;

        for (int index = 0; index < words.size(); ++index) {

            now = root;
            for (char c : words[index]) {
                int i = c - 'a';
                if (now->children[i] == nullptr) {
                    now->children[i] = new TrieNode();
                }

                now = now->children[i];
                //we record every row index here!!
                //because of the symmetry of wordSquare, 
                //the letter will appear in the same number of column and row
                now->wordIndex.push_back(index);    
            }
        }
    }

    //based on the constraints
    int totalSteps = 0;

    //the first parameter starts from 1 because we do not need the value on diagonal
    //the second parameter is for temprarily storring the possible answer
    void backtracking(int step, std::vector<std::string>& wordSquare, std::vector<string>& words, 
                        std::vector<std::vector<std::string>>& result) {
        
        if (step == totalSteps) {
            result.push_back(wordSquare);
            return;
        }

        std::string prefix = "";
        for (std::string& w : wordSquare) {
            prefix += w[step];
        }

        //find in trie
        //if we could loop through all prefix letters, 
        //now will be assigned to it children[i], 
        //so if now were not nullptr, we just get its index list
        TrieNode* now = root;
        for (char c : prefix) {
            int i = c - 'a';

            if (now->children[i] == nullptr) {
                now = nullptr;
                break;
            } 
            now = now->children[i];
        }

        std::vector<int> indices;
        if (now != nullptr) {
            indices = now->wordIndex;
        }

        //backtracking recursion
        for (int i : indices) {
            wordSquare.push_back(words[i]);
            backtracking(step + 1, wordSquare, words, result);
            wordSquare.pop_back();
        }
    }

public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        //set the total steps size by the string size
        totalSteps = words[0].size();
        std::vector<std::vector<string>> result;

        createTrie(words);

        for (auto word : words) {
            std::vector<std::string> wordSquare;
            wordSquare.push_back(word);
            backtracking(1, wordSquare, words, result);
        }
        
        return result;
    }
};