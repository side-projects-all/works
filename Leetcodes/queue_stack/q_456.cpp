/*
Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].

Return true if there is a 132 pattern in nums, otherwise, return false.

 

Example 1:

Input: nums = [1,2,3,4]
Output: false
Explanation: There is no 132 pattern in the sequence.

Example 2:

Input: nums = [3,1,4,2]
Output: true
Explanation: There is a 132 pattern in the sequence: [1, 4, 2].

Example 3:

Input: nums = [-1,3,2,0]
Output: true
Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].

 

Constraints:

    n == nums.length
    1 <= n <= 2 * 10^5
    -10^9 <= nums[i] <= 10^9


*/

class Solution {
private:
    bool by_binary_search(vector<int>& nums) {
        int n = nums.size();
        std::vector<int> min_arr(n);
        min_arr[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            min_arr[i] = std::min(min_arr[i - 1], nums[i]);
        }

        int k = n;
        for (std::size_t j = n - 1; j > 0; --j) {
            if (nums[j] <= min_arr[j]) {
                continue;
            }

            auto it = std::lower_bound(nums.begin() + k, nums.end(), min_arr[j] + 1);
            k = it - nums.begin();
            if (k < n && nums[k] < nums[j]) {
                return true;
            }

            nums[--k] = nums[j];
        }

        return false;
    }
    bool by_stack(vector<int>& nums) {
        int n = nums.size();
        std::vector<int> min_arr(n);
        min_arr[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            min_arr[i] = std::min(min_arr[i - 1], nums[i]);
        }

        std::stack<int> stack;  //it stores all k!!
        for (int j = n - 1; j > 0; --j) {
            if (nums[j] <= min_arr[j]) {
                continue;
            }

            while (!stack.empty() && stack.top() <= min_arr[j]) {
                stack.pop();
            }

            if (!stack.empty() && stack.top() < nums[j]) {
                return true;
            }

            stack.push(nums[j]);
        } 

        return false;
    }
public:
    bool find132pattern(vector<int>& nums) {
        //return by_stack(nums);
        return by_binary_search(nums);
    }
};