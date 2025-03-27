/*
Given an integer n, return all the numbers in the range [1, n] sorted in lexicographical order.

You must write an algorithm that runs in O(n) time and uses O(1) extra space. 

 

Example 1:

Input: n = 13
Output: [1,10,11,12,13,2,3,4,5,6,7,8,9]

Example 2:

Input: n = 2
Output: [1,2]

 

Constraints:

    1 <= n <= 5 * 10^4
*/

class Solution {
public:
    vector<int> lexicalOrder(int n) {
        if (n < 10) {
            std::vector<int> ans(n);
            for (int i = 1; i <= n; ++i) {
                ans[i - 1] = i;
            }

            return ans;
        }
        

        std::vector<int> ans(n);
        int num = 1;
        for (int i = 0; i < n; ++i) {
            ans[i] = num;

            if (num * 10 <= n) {
                num *= 10;

            } else {

                while (num + 1 > n || num % 10 == 9) {
                    num /= 10;
                }

                ++num;
            }
        }

        return ans;
    }
};


