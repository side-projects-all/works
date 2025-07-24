/*
We know that 4 and 7 are lucky digits. Also, a number is called lucky if it contains only lucky digits.

You are given an integer k, return the kth lucky number represented as a string.

 

Example 1:

Input: k = 4
Output: "47"
Explanation: The first lucky number is 4, the second one is 7, the third one is 44 and the fourth one is 47.

Example 2:

Input: k = 10
Output: "477"
Explanation: Here are lucky numbers sorted in increasing order:
4, 7, 44, 47, 74, 77, 444, 447, 474, 477. So the 10th lucky number is 477.

Example 3:

Input: k = 1000
Output: "777747447"
Explanation: It can be shown that the 1000th lucky number is 777747447.

 

Constraints:

    1 <= k <= 10^9


*/

class Solution {
private:
    std::string opt_bits_manipulation(int k) {
        k = k + 1;
        int digits = std::log2(k);
        std::string ans(digits, ' ');
        
        while (k > 1) {
            --digits;
            ans[digits] = ((k & 1) ? '7' : '4');
            k >>= 1;
        }

        return ans;
    }
    std::string bits_manipulation(int k) {
        k = k + 1;

        std::string ans;
        while (k > 1) {
            ans.insert(0, (k & 1) ? "7" : "4");
            k >>= 1;
        }

        return ans;
    }
    std::string counting_digits(int k) {
        if (k == 1) {
            return "4";
        }

        if (k == 2) {
            return "7";
        }

       int c = 0;
       int num_cnt = 0;
       while (num_cnt < k) {
            ++c;
            num_cnt += std::pow(2, c);
       }

       int x = k - 1 - (num_cnt - std::pow(2, c));
       std::string ans;
       for (int i = 0; i < c; ++i) {

            if (x % 2 == 1) {
                ans.insert(0, "7");
            } else {
                ans.insert(0, "4");
            }

            x /= 2;
       }

        return ans;
    }
public:
    string kthLuckyNumber(int k) {
        //return counting_digits(k);
        //return bits_manipulation(k);
        return opt_bits_manipulation(k);
    }
};