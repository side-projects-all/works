/*
Your task is to calculate ab mod 1337 where a is a positive integer and b is an extremely large positive integer given in the form of an array.

 

Example 1:

Input: a = 2, b = [3]
Output: 8

Example 2:

Input: a = 2, b = [1,0]
Output: 1024

Example 3:

Input: a = 1, b = [4,3,3,8,5,2]
Output: 1

 

Constraints:

    1 <= a <= 2^31 - 1
    1 <= b.length <= 2000
    0 <= b[i] <= 9
    b does not contain leading zeros.


*/

class Solution {
private:
    int by_one_digit(int a, int b) {
        a %= 1337;
        int ans = 1;
        for (int i = 0; i < b; ++i) {
            ans *= a;
            ans %= 1337;
        }

        return ans;
    }
public:
    int superPow(int a, vector<int>& b) {
        int num = 1;
        int tmp = 0;
        int ans = 0;

        for (int i = 0; i < b.size(); ++i) {
            tmp = by_one_digit(a, b[i]);
            tmp *= num;
            tmp %= 1337;

            ans = tmp;
            tmp = by_one_digit(tmp, 10);
            num = tmp;
        }

        return ans;
    }
};