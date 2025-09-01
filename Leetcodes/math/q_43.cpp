/*
Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also represented as a string.

Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.

 

Example 1:

Input: num1 = "2", num2 = "3"
Output: "6"

Example 2:

Input: num1 = "123", num2 = "456"
Output: "56088"

 

Constraints:

    1 <= num1.length, num2.length <= 200
    num1 and num2 consist of digits only.
    Both num1 and num2 do not contain any leading zero, except the number 0 itself.


*/

class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";

        int n1 = num1.size();
        int n2 = num2.size();
        std::string ans(n1 + n2, '0');

        for (int p2 = n2 - 1; p2 >= 0; --p2) {
          int d2 = num2[p2] - '0';

          for (int p1 = n1 - 1; p1 >= 0; --p1) {
            int d1 = num1[p1] - '0';
            int pos = p1 + p2 + 1; 

            int prev_carry = ans[pos] - '0';
            int multi = d1 * d2 + prev_carry;

            ans[pos] = (multi % 10) + '0';

            ans[pos - 1] += (multi / 10);   //put carry
          }
        }

        if (ans[0] == '0') {
            ans = ans.erase(0, 1);
        }

        return ans;
    }
};