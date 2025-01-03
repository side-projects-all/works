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
        if (num1 == "0" || num2 == "0") {
          return "0";
        }

        std::reverse(num1.begin(), num1.end());
        std::reverse(num2.begin(), num2.end());

        int N = num1.size() + num2.size();
        std::string ans(N, '0');

        for (int p2 = 0; p2 < num2.size(); ++p2) {
          int d2 = num2[p2] - '0';

          for (int p1 = 0; p1 < num1.size(); ++p1) {
            int d1 = num1[p1] - '0';
            int numZeros = p1 + p2; //this is the important step!

            //this is the largest digit in previous operation, 
            //and it will be used for carry
            int carryFromPrev = ans[numZeros] - '0';
            int multi = d1 * d2 + carryFromPrev;

            ans[numZeros] = (multi % 10) + '0';

             ans[numZeros + 1] += (multi / 10);
          }
        }

        if (ans.back() == '0') {
          ans.pop_back();
        }

        std::reverse(ans.begin(), ans.end());

        return ans;
    }
};