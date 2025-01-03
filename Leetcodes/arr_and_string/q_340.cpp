/*
Given a string s and an integer k, return the length of the longest
substring
of s that contains at most k distinct characters.

 

Example 1:

Input: s = "eceba", k = 2
Output: 3
Explanation: The substring is "ece" with length 3.

Example 2:

Input: s = "aa", k = 1
Output: 2
Explanation: The substring is "aa" with length 2.

 

Constraints:

    1 <= s.length <= 5 * 10^4
    0 <= k <= 50


*/

class Solution {

private:
    int onlySlidingWindow(string& s, int k) {
        //corner case
        if (s.size() < k) {
            return s.size();
        }

        int left = 0;
        int right = 0;
        int max_len = k;
        std::map<char, int> map;

        while (right < s.size()) {

            map[s[right]] = right;
            ++right;

            if (map.size() > k) {
                int del_index = 50001;

                //delete the minimum
                for (std::pair<char, int> p : map) {
                    del_index = std::min(del_index, p.second);
                }

                map.erase(s[del_index]);
                left = del_index + 1;
            }

            max_len = std::max(max_len, right - left);
        }

        return max_len;
    }

public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        return onlySlidingWindow(s, k);
    }
};