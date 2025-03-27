/*
You are given a string word and a non-negative integer k.

Return the total number of

of word that contain every vowel ('a', 'e', 'i', 'o', and 'u') at least once and exactly k consonants.

 

Example 1:

Input: word = "aeioqq", k = 1

Output: 0

Explanation:

There is no substring with every vowel.

Example 2:

Input: word = "aeiou", k = 0

Output: 1

Explanation:

The only substring with every vowel and zero consonants is word[0..4], which is "aeiou".

Example 3:

Input: word = "ieaouqqieaouqq", k = 1

Output: 3

Explanation:

The substrings with every vowel and one consonant are:

    word[0..5], which is "ieaouq".
    word[6..11], which is "qieaou".
    word[7..12], which is "ieaouq".

 

Constraints:

    5 <= word.length <= 2 * 10^5
    word consists only of lowercase English letters.
    0 <= k <= word.length - 5

*/

class Solution {
private:
    bool is_vowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
    
    long by_sliding_window(string& word, int& k) {
        int n = word.size();
        long ans = 0;
        int b = 0;
        int e = 0;
        std::unordered_map<char, int> vowel_cnt;
        int cons = 0;   //consonants

        std::vector<int> next_cons(n);
        int next_con = n;
        for (int i = n - 1; i >= 0; i--) {
            next_cons[i] = next_con;
            if (!is_vowel(word[i])) {
                next_con = i;
            }
        }

        while (e < n) {
            char new_ch = word[e];

            if (is_vowel(new_ch)) {
                ++vowel_cnt[new_ch];

            } else {
                cons++;
            }

            while (cons > k) {
                char begin_ch = word[b];

                if (is_vowel(begin_ch)) {

                    --vowel_cnt[begin_ch];
                    if (vowel_cnt[begin_ch] == 0) {

                        vowel_cnt.erase(begin_ch);
                    }
                } else {
                    --cons;
                }
                ++b;
            }

            //the most important part, how this sliding window speed up!
            while (b < n && vowel_cnt.size() == 5 && cons == k) {

                ans += next_cons[e] - e;
                char begin_ch = word[b];

                if (is_vowel(begin_ch)) {
                    --vowel_cnt[begin_ch];

                    if (vowel_cnt[begin_ch] == 0) {
                        vowel_cnt.erase(begin_ch);
                    }
                } else {
                    --cons;
                }

                ++b;
            }
            
            ++e;
        }

        return ans;
    }

public:
    long countOfSubstrings(string word, int k) {
        return by_sliding_window(word, k);
    }
};