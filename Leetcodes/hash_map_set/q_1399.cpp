/*
You are given an integer n.

Each number from 1 to n is grouped according to the sum of its digits.

Return the number of groups that have the largest size.

 

Example 1:

Input: n = 13
Output: 4
Explanation: There are 9 groups in total, they are grouped according sum of its digits of numbers from 1 to 13:
[1,10], [2,11], [3,12], [4,13], [5], [6], [7], [8], [9].
There are 4 groups with largest size.

Example 2:

Input: n = 2
Output: 2
Explanation: There are 2 groups [1], [2] of size 1.

 

Constraints:

    1 <= n <= 10^4


*/

class Solution {
public:
    int countLargestGroup(int n) {
        std::vector<int> groups(37);
        int max_size = 0;
        for (int i = 1; i <= n; ++i) {

            int val = i;
            int sum = 0;
            while (val > 0) {
                sum += val % 10;
                val /= 10;
            }

            ++groups[sum];
            max_size = std::max(max_size, groups[sum]);
        }

        int cnt = 0;
        for (int i = 0; i < 37; ++i) {
            if (groups[i] == max_size) {
                ++cnt;
            }
        }

        return cnt;
    }
};