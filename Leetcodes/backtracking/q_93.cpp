/*
A valid IP address consists of exactly four integers separated by single dots. Each integer is between 0 and 255 (inclusive) and cannot have leading zeros.

    For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, but "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses.

Given a string s containing only digits, return all possible valid IP addresses that can be formed by inserting dots into s. You are not allowed to reorder or remove any digits in s. You may return the valid IP addresses in any order.

 

Example 1:

Input: s = "25525511135"
Output: ["255.255.11.135","255.255.111.35"]

Example 2:

Input: s = "0000"
Output: ["0.0.0.0"]

Example 3:

Input: s = "101023"
Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]

 

Constraints:

    1 <= s.length <= 20
    s consists of digits only.


*/

class Solution {
private:
    std::vector<std::string> backtracking(std::string& s) {
        std::vector<std::string> ans;
        std::string curr;

        //part: 1, 2, 3, 4
        std::function<void(int, int)> bt = [&](int now, int part) {

            if (part == 5) {
                if (now < s.size()) {
                    return;
                }

                curr.pop_back();
                ans.push_back(curr);
                return;
            }

            std::string pre = curr;
            for (int len = 1; len <= 3; ++len) {
                //pass if over the size of s
                if (now + len > s.size()) {
                    break;
                }
                std::string tmp = s.substr(now, len);
                //no leading zero
                if (tmp[0] == '0' && tmp.size() > 1) {
                    continue;
                }

                int val = std::stoi(tmp, 0);
                if (val >= 0 && val <= 255) {
                    curr += tmp + ".";
                    bt(now + len, part + 1);
                    curr = pre;
                }
            }
        };

        bt(0, 1);
        return ans;
    }
public:
    vector<string> restoreIpAddresses(string s) {
        return backtracking(s);
    }
};