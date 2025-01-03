/*
Given a string s and an integer k, rearrange s such that the same characters are at least distance k from each other. If it is not possible to rearrange the string, return an empty string "".

 

Example 1:

Input: s = "aabbcc", k = 3
Output: "abcabc"
Explanation: The same letters are at least a distance of 3 from each other.

Example 2:

Input: s = "aaabc", k = 3
Output: ""
Explanation: It is not possible to rearrange the string.

Example 3:

Input: s = "aaadbbcc", k = 2
Output: "abacabcd"
Explanation: The same letters are at least a distance of 2 from each other.

 

Constraints:

    1 <= s.length <= 3 * 10^5
    s consists of only lowercase English letters.
    0 <= k <= s.length


*/

class Solution {
public:
    string rearrangeString(string s, int k) {
        int freq[26] = { 0 };

        for (int i = 0; i < s.size(); ++i) {
            ++freq[s[i] - 'a'];
        }

        std::priority_queue<std::pair<int, int>> pq;
        for (int i = 0; i < 26; ++i) {
            if (freq[i]) {
                pq.push({freq[i], i});
            }
        }

        std::string ans("");
        std::queue<std::pair<int, int>> q;

        while (ans.size() != s.size()) {
            int index = ans.size();

            if (!q.empty() && (index - q.front().first) >= k) {
                std::pair<int, int> p = q.front();
                q.pop();
                pq.push({freq[p.second], p.second});
            }

            if (pq.empty()) {
                return "";
            }

            int currLetter = pq.top().second;
            pq.pop();

            ans += (currLetter + 'a');

            --freq[currLetter];
            if (freq[currLetter] > 0) {
                q.push({index, currLetter});
            }
        }

        return ans;
    }
};