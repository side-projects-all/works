/*
You are given a license key represented as a string s that consists of only alphanumeric characters and dashes. The string is separated into n + 1 groups by n dashes. You are also given an integer k.

We want to reformat the string s such that each group contains exactly k characters, except for the first group, which could be shorter than k but still must contain at least one character. Furthermore, there must be a dash inserted between two groups, and you should convert all lowercase letters to uppercase.

Return the reformatted license key.

 

Example 1:

Input: s = "5F3Z-2e-9-w", k = 4
Output: "5F3Z-2E9W"
Explanation: The string s has been split into two parts, each part has 4 characters.
Note that the two extra dashes are not needed and can be removed.

Example 2:

Input: s = "2-5g-3-J", k = 2
Output: "2-5G-3J"
Explanation: The string s has been split into three parts, each part has 2 characters except the first part as it could be shorter as mentioned above.

 

Constraints:

    1 <= s.length <= 10^5
    s consists of English letters, digits, and dashes '-'.
    1 <= k <= 10^4


*/

class Solution {
public:
    string licenseKeyFormatting(string s, int k) {

        //from right to left
        std::string no_dash;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] != '-') {
                no_dash += std::toupper(s[i]);
            }
        }

        if (no_dash.size() <= k) {
            return no_dash;
        }

        std::string ans;
        int cnt = 0;
        for (int i = no_dash.size() - 1; i >= 0;) {

            while (i >= 0 && cnt < k) {
                ans += no_dash[i];
                ++cnt;
                --i;
            }

            if (i >= 0) {
                ans += '-';
                cnt = 0;
            }
        }

        std::reverse(ans.begin(), ans.end());
        return ans;
        
        /* from left to right
        int total = 0;    //all non '-' chars
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] != '-') {
                ++total;
            }
        }

        std::string ans;
        //set first group size
        int first_group = (total % k) ? total % k : k;  
        int i = 0;
        int cnt = 0;

        //set first group substring
        while (i < s.size()) {
            if (cnt == first_group) {
                cnt = 0;
                break;
            }

            if (s[i] != '-') {
                ++cnt;
                ans += std::toupper(s[i]);
            }

            ++i;
        }

        //corner case k > s.size()
        if (i >= s.size()) {
            return ans;
        }

        ans += '-';
        while (i < s.size()) {
            if (s[i] != '-') {

                if (cnt == k) {
                    ans += '-';
                    cnt = 0;
                }

                ans += std::toupper(s[i]);
                ++cnt;
            }

            ++i;
        }

        return ans;
        */
    }
};