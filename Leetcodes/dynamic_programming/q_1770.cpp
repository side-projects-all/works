/*
You are given two integer arrays nums and multipliers of size n and m respectively, where n >= m. The arrays are 1-indexed.

You begin with a score of 0. You want to perform exactly m operations. On the ith operation (1-indexed), you will:

    Choose one integer x from either the start or the end of the array nums.
    Add multipliers[i] * x to your score.
    Remove x from the array nums.

Return the maximum score after performing m operations.

ex1:
Input: nums = [1,2,3], multipliers = [3,2,1]
Output: 14
Explanation: An optimal solution is as follows:
- Choose from the end, [1,2,3], adding 3 * 3 = 9 to the score.
- Choose from the end, [1,2], adding 2 * 2 = 4 to the score.
- Choose from the end, [1], adding 1 * 1 = 1 to the score.
The total score is 9 + 4 + 1 = 14.

ex2:
Input: nums = [-5,-3,-3,-2,7,1], multipliers = [-10,-5,3,4,6]
Output: 102
Explanation: An optimal solution is as follows:
- Choose from the start, [-5,-3,-3,-2,7,1], adding -5 * -10 = 50 to the score.
- Choose from the start, [-3,-3,-2,7,1], adding -3 * -5 = 15 to the score.
- Choose from the start, [-3,-2,7,1], adding -3 * 3 = -9 to the score.
- Choose from the end, [-2,7,1], adding 1 * 4 = 4 to the score.
- Choose from the end, [-2,7], adding 7 * 6 = 42 to the score. 
The total score is 50 + 15 - 9 + 4 + 42 = 102.

*/

class Solution {
private:
    int recursive(vector<int>& nums, vector<int>& multipliers, 
                    std::vector<std::vector<int>>& mem, int left, int right, int m_i) {

        //base case
        if (m_i == multipliers.size()) {
            return 0;
        }

        if (mem[m_i][left] != -1) {
            return mem[m_i][left];
        }

        int m_val = multipliers[m_i];
        int left_val = nums[left] * m_val;
        int right_val = nums[right] * m_val;
        mem[m_i][left] = std::max(left_val + recursive(nums, multipliers, mem, left + 1, right, m_i + 1), 
                                        right_val + recursive(nums, multipliers, mem, left, right - 1, m_i + 1));

        return mem[m_i][left];
    }
public:
    int maximumScore(vector<int>& nums, vector<int>& multipliers) {
        int len_n = nums.size();
        int len_m = multipliers.size();
        std::vector<std::vector<int>> mem(len_m, std::vector<int>(len_n, -1));

        return recursive(nums, multipliers, mem, 0, len_n - 1, 0);
    }
};