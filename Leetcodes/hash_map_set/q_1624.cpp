/*
Given a string s, return the length of the longest substring between two equal characters, excluding the two characters. If there is no such substring return -1.

A substring is a contiguous sequence of characters within a string.

 

Example 1:

Input: s = "aa"
Output: 0
Explanation: The optimal substring here is an empty substring between the two 'a's.

Example 2:

Input: s = "abca"
Output: 2
Explanation: The optimal substring here is "bc".

Example 3:

Input: s = "cbzxy"
Output: -1
Explanation: There are no characters that appear twice in s.

 

Constraints:

    1 <= s.length <= 300
    s contains only lowercase English letters.


*/

class Solution {
private:
    int byMap(std::string& s) {
        std::unordered_map<char, int> m;

        int ans = -1;

        for (int i = 0; i < s.size(); ++i) {
            if (m.find(s[i]) != m.end()) {
                ans = std:: max(ans, i - m[s[i]] - 1);
            } else {
                m[s[i]] = i;
            }
        }

        return ans;
    }
    int recursive(std::string& s, int left, int right, std::vector<std::vector<int>>& mem) {
        //base case
        if (left == right) {
            return -1;
        }

        if (mem[left][right] != -1) {
            return mem[left][right];
        }

        int len = 0;
        if (s[left] == s[right]) {
            len = right - left - 1;
        } else {
            len = std::max(recursive(s, left + 1, right, mem), 
                            recursive(s, left, right - 1, mem));
        }

        mem[left][right] = len;

        return len;
    }
public:
    int maxLengthBetweenEqualCharacters(string s) {
        //int N = s.size();
        //std::vector<std::vector<int>> mem(N, std::vector<int>(N, -1));

        //return recursive(s, 0, N - 1, mem);

        return byMap(s);
    }
};