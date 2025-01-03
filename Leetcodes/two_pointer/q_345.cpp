/*
Given a string s, reverse only all the vowels in the string and return it.

The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases, more than once.

 

Example 1:

Input: s = "IceCreAm"

Output: "AceCreIm"

Explanation:

The vowels in s are ['I', 'e', 'e', 'A']. On reversing the vowels, s becomes "AceCreIm".

Example 2:

Input: s = "leetcode"

Output: "leotcede"

 

Constraints:

    1 <= s.length <= 3 * 10^5
    s consist of printable ASCII characters.


*/

class Solution {
private:
    bool is_vowel(char c) {

        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || 
                c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
    }
public:
    string reverseVowels(string s) {
        int n = s.size();
        if (n == 1) {
            return s;
        }

        int b = 0;
        int e = n - 1;
        while (b < e) {

            while (b < n && !is_vowel(s[b])) {
                ++b;
            }

            while (e >= 0 && !is_vowel(s[e])) {
                --e;
            }

            if (b < e) {
                std::swap(s[b], s[e]);
                ++b;
                --e;
            }
        }

        return s;
    }
};