/*
You are given a string s consisting of the characters 'a', 'b', and 'c' and a non-negative integer k. Each minute, you may take either the leftmost character of s, or the rightmost character of s.

Return the minimum number of minutes needed for you to take at least k of each character, or return -1 if it is not possible to take k of each character.

 

Example 1:

Input: s = "aabaaaacaabc", k = 2
Output: 8
Explanation: 
Take three characters from the left of s. You now have two 'a' characters, and one 'b' character.
Take five characters from the right of s. You now have four 'a' characters, two 'b' characters, and two 'c' characters.
A total of 3 + 5 = 8 minutes is needed.
It can be proven that 8 is the minimum number of minutes needed.

Example 2:

Input: s = "a", k = 1
Output: -1
Explanation: It is not possible to take one 'b' or 'c' so return -1.

 

Constraints:

    1 <= s.length <= 10^5
    s consists of only the letters 'a', 'b', and 'c'.
    0 <= k <= s.length


*/

class Solution {
public:
    int takeCharacters(string s, int k) {
        std::vector<int> count(3, 0);
        int n = s.size();

        for (char c : s) {
            count[c - 'a']++;
        }

        for (int i = 0; i < 3; i++) {
            if (count[i] < k) return -1;
        }

        std::vector<int> window(3, 0);
        int l = 0;
        int max_window = 0;

        //find the longest window that leaves k of each character outside!!
        for (int r = 0; r < n; ++r) {
            ++window[s[r] - 'a'];

            //shrink window if we take too many characters
            while (l <= r &&
                   (count[0] - window[0] < k || count[1] - window[1] < k || count[2] - window[2] < k)) {

                --window[s[l] - 'a'];
                ++l;
            }

            max_window = max(max_window, r - l + 1);
        }

        return n - max_window;
    }
};