/*
Given a string s, return the length of the longest
substring
that contains at most two distinct characters.

 

Example 1:

Input: s = "eceba"
Output: 3
Explanation: The substring is "ece" which its length is 3.

Example 2:

Input: s = "ccaabbb"
Output: 5
Explanation: The substring is "aabbb" which its length is 5.

 

Constraints:

    1 <= s.length <= 10^5
    s consists of English letters.


*/

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        //corner case
        if (s.size() < 3) {
            return s.size();
        }

        return by_vector(s);
        //return by_map(s);
    }

private:
    int by_vector(string& s) {
        int left = 0;
        int right = 0;
        std::vector<int> cnts(128);
        int len = 0;
        int char_cnt = 0;

        while (right < s.size()) {

            if (cnts[s[right]] == 0) {
                ++char_cnt;
            }

            ++cnts[s[right]];
            
            while (char_cnt > 2) {
                if (cnts[s[left]] == 1) {
                    --char_cnt;
                }

                --cnts[s[left]];
                ++left;
            }

            len = std::max(len, right - left + 1);
            ++right;
        }

        return len;
    }
    int by_map(string& s) {
        int left = 0;
        int right = 0;
        std::map<char, int> map;
        int max_len = 2;

        while (right < s.size()) {
        
            //here we update position of latest character
            map[s[right]] = right;
            ++right;

            if (map.size() == 3) {
                int indexToDel = 100001;

                //loop the map to find minimum index
                for (std::pair<char, int> e : map) {
                    indexToDel = std::min(indexToDel, e.second);
                }

                map.erase(s[indexToDel]);
                left = indexToDel + 1;
            }

            max_len = std::max(max_len, right - left);
        }

        return max_len;
    }
};