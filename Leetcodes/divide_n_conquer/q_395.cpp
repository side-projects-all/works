/*
Given a string s and an integer k, return the length of the longest substring of s such that the frequency of each character in this substring is greater than or equal to k.

if no such substring exists, return 0.

 

Example 1:

Input: s = "aaabb", k = 3
Output: 3
Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.

Example 2:

Input: s = "ababbc", k = 2
Output: 5
Explanation: The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.

 

Constraints:

    1 <= s.length <= 10^4
    s consists of only lowercase English letters.
    1 <= k <= 10^5


*/

class Solution {
private:
    int by_divide_n_conquer(string& s, int k, int b, int e) {
        if (e < k) {
            return 0;
        }

        int cnt_map[26]{ 0 };
        for (int i = b; i < e; ++i) {
            ++cnt_map[s[i] - 'a'];
        }

        for (int mid = b; mid < e; ++mid) {
            if (cnt_map[s[mid] - 'a'] >= k) {
                continue;
            }

            int mid_next = mid + 1;
            while (mid_next < e && cnt_map[s[mid_next] - 'a'] < k) {
                ++mid_next;
            }

            return std::max(by_divide_n_conquer(s, k, b, mid), by_divide_n_conquer(s, k, mid_next, e));
        }

        return (e - b);
    }
    int by_sliding_window(string& s, int k) {
        int max_unique = 0;
        bool map[26]{ 0 };
        for (int i = 0; i < s.size(); ++i) {
            if (!map[s[i] - 'a']) {
                ++max_unique;
                map[s[i] - 'a'] = true;
            }
        }

        int cnt_map[26];
        int ans = 0;
        for (int curr_unique = 1; curr_unique <= max_unique; ++curr_unique) {
            
            memset(cnt_map, 0, sizeof(cnt_map));
            int b = 0;
            int e = 0;
            int i = 0;
            int unique = 0;
            int cnt_at_least_k = 0;

            while (e < s.size()) {

                if (unique <= curr_unique) {
                    i = s[e] - 'a';
                    if (cnt_map[i] == 0) {
                        ++unique;
                    }

                    ++cnt_map[i];

                    if (cnt_map[i] == k) {
                        ++cnt_at_least_k;
                    }

                    ++e;

                } else {
                    i = s[b] - 'a';

                    if (cnt_map[i] == k) {
                        --cnt_at_least_k;
                    }

                    --cnt_map[i];

                    if (cnt_map[i] == 0) {
                        --unique;
                    }

                    ++b;
                }

                if (unique == curr_unique && unique == cnt_at_least_k) {
                    ans = std::max(ans, e - b);
                }
            }
        }

        return ans;
    }
public:
    int longestSubstring(string s, int k) {
        if (k > s.size()) {
            return 0;
        }

        //return by_sliding_window(s, k);
        return by_divide_n_conquer(s, k, 0, s.size());
    }
};