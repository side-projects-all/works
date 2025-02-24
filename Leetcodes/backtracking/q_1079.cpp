/*
You have n  tiles, where each tile has one letter tiles[i] printed on it.

Return the number of possible non-empty sequences of letters you can make using the letters printed on those tiles.

 

Example 1:

Input: tiles = "AAB"
Output: 8
Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA".

Example 2:

Input: tiles = "AAABBC"
Output: 188

Example 3:

Input: tiles = "V"
Output: 1

 

Constraints:

    1 <= tiles.length <= 7
    tiles consists of uppercase English letters.


*/

class Solution {
private:
    void recursive(std::unordered_map<char, int>& cnts, int& total) {
        
        for (auto& cnt : cnts) {
            if (cnt.second > 0) {
                --cnt.second;

                ++total;
                recursive(cnts, total);
                ++cnt.second;
            }
        }
    }
    int by_back_tracking(string& tiles) {
        std::unordered_map<char, int> cnts;
        for (int i = 0; i < tiles.size(); ++i) {
            ++cnts[tiles[i]];
        }

        int total = 0;
        recursive(cnts, total);

        return total;
    }
public:
    int numTilePossibilities(string tiles) {
        return by_back_tracking(tiles);
    }
};