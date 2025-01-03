/*
You are given a string s and an array of strings words. All the strings of words are of the same length.

A concatenated substring in s is a substring that contains all the strings of any permutation of words concatenated.

    For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated strings. "acdbef" is not a concatenated substring because it is not the concatenation of any permutation of words.

Return the starting indices of all the concatenated substrings in s. You can return the answer in any order.

 

Example 1:

Input: s = "barfoothefoobarman", words = ["foo","bar"]
Output: [0,9]
Explanation: Since words.length == 2 and words[i].length == 3, the concatenated substring has to be of length 6.
The substring starting at 0 is "barfoo". It is the concatenation of ["bar","foo"] which is a permutation of words.
The substring starting at 9 is "foobar". It is the concatenation of ["foo","bar"] which is a permutation of words.
The output order does not matter. Returning [9,0] is fine too.

Example 2:

Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
Output: []
Explanation: Since words.length == 4 and words[i].length == 4, the concatenated substring has to be of length 16.
There is no substring of length 16 in s that is equal to the concatenation of any permutation of words.
We return an empty array.

Example 3:

Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
Output: [6,9,12]
Explanation: Since words.length == 3 and words[i].length == 3, the concatenated substring has to be of length 9.
The substring starting at 6 is "foobarthe". It is the concatenation of ["foo","bar","the"] which is a permutation of words.
The substring starting at 9 is "barthefoo". It is the concatenation of ["bar","the","foo"] which is a permutation of words.
The substring starting at 12 is "thefoobar". It is the concatenation of ["the","foo","bar"] which is a permutation of words.

 

Constraints:

    1 <= s.length <= 10^4
    1 <= words.length <= 5000
    1 <= words[i].length <= 30
    s and words[i] consist of lowercase English letters.


*/

class Solution {
private:
    vector<int> slidingWindow(string& s, vector<string>& words) {
        std::unordered_map<std::string, int> m;
        std::size_t S = s.size();
        std::size_t N = words.size();
        std::size_t M = words[0].size();
        std::size_t subs_size = N * M;
        std::vector<int> ans;

        if (M > S) {
            return ans;
        }

        for (std::string& w : words) {
            ++m[w];
        }

        std::unordered_map<std::string, int> wordsFound;
        for (std::size_t i = 0; i < M; ++i) {
            int wordsUsed = 0;
            bool excessWord = false;
            //std::unordered_map<std::string, int> wordsFound;
            int left = i;

            for (std::size_t right = left; right <= S - M; right += M) {

                std::string sub = s.substr(right, M);
                if (m.find(sub) == m.end()) {
                    wordsFound.clear();
                    wordsUsed = 0;
                    excessWord = false;
                    left = right + M;

                } else {

                    //this part is used to move left pointer
                    while (right - left == subs_size || excessWord) {
                        std::string leftMost = s.substr(left, M);
                        left += M;
                        --wordsFound[leftMost];

                        //if (wordsFound[leftMost] >= m[leftMost]) {    //use ==
                        if (wordsFound[leftMost] >= m[leftMost]) {
                            excessWord = false;
                        } else {
                            --wordsUsed;
                        }
                    }

                    ++wordsFound[sub];
                    if (wordsFound[sub] <= m[sub]) {
                        ++wordsUsed;
                    } else {
                        excessWord = true;
                    }

                    if (wordsUsed == N && !excessWord) {
                        ans.push_back(left);
                    }
                }
            }

            wordsFound.clear();
        }
        return ans;
    }
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        return slidingWindow(s, words);
    }
};