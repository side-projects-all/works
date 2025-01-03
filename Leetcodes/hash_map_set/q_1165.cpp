/*
There is a special keyboard with all keys in a single row.

Given a string keyboard of length 26 indicating the layout of the keyboard (indexed from 0 to 25). Initially, your finger is at index 0. To type a character, you have to move your finger to the index of the desired character. The time taken to move your finger from index i to index j is |i - j|.

You want to type a string word. Write a function to calculate how much time it takes to type it with one finger.

 

Example 1:

Input: keyboard = "abcdefghijklmnopqrstuvwxyz", word = "cba"
Output: 4
Explanation: The index moves from 0 to 2 to write 'c' then to 1 to write 'b' then to 0 again to write 'a'.
Total time = 2 + 1 + 1 = 4. 

Example 2:

Input: keyboard = "pqrstuvwxyzabcdefghijklmno", word = "leetcode"
Output: 73

 

Constraints:

    keyboard.length == 26
    keyboard contains each English lowercase letter exactly once in some order.
    1 <= word.length <= 10^4
    word[i] is an English lowercase letter.


*/

class Solution {
private:
    int better(string& keyboard, string& word) {
        int arr[26] = { 0 };

        for (int i = 0; i < keyboard.size(); ++i) {
            arr[keyboard[i] - 'a'] = i;
        }

        int prev = 0;
        int len = 0;
        for (char& c : word) {
            len += std::abs(prev - arr[c - 'a']);

            prev = arr[c - 'a'];
        }

        return len;
    }

    int naive(string& keyboard, string& word) {
        std::unordered_map<char, std::unordered_map<char, int>> m;
        std::unordered_map<char, int> begin;

        for (int i = 0; i < keyboard.size(); ++i) {
            begin[keyboard[i]] = i;
            for (int j = 0; j < keyboard.size(); ++j) {
                m[keyboard[i]][keyboard[j]] = std::abs(i - j);
            }
        }

        int len = begin[word[0]];
        for (int i = 0; i < word.size() - 1; ++i) {
            len += m[word[i]][word[i + 1]];
        }

        return len;
    }

public:
    int calculateTime(string keyboard, string word) {

        //return naive(keyboard, word);
        return better(keyboard, word);
    }
};