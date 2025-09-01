/*
Given two binary strings a and b, return their sum as a binary string.

 

Example 1:

Input: a = "11", b = "1"
Output: "100"

Example 2:

Input: a = "1010", b = "1011"
Output: "10101"

 

Constraints:

    1 <= a.length, b.length <= 10^4
    a and b consist only of '0' or '1' characters.
    Each string does not contain leading zeros except for the zero itself.




*/

class Solution {
public:
    string addBinary(string a, string b) {
        std::string ans;
        int ai = a.size() - 1;
        int bi = b.size() - 1;
        int carry = 0;

        while (ai >= 0 || bi >= 0 || carry) {

            if (ai >= 0) {
                carry += a[ai] - '0';
                --ai;
            }

            if (bi >= 0) {
                carry += b[bi] - '0';
                --bi;
            }

            ans.push_back((carry % 2) + '0');
            carry /= 2;
        }

        std::reverse(ans.begin(), ans.end());

        return ans;
    }
};