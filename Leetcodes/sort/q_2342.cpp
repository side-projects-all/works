/*
You are given a 0-indexed array nums consisting of positive integers. You can choose two indices i and j, such that i != j, and the sum of digits of the number nums[i] is equal to that of nums[j].

Return the maximum value of nums[i] + nums[j] that you can obtain over all possible indices i and j that satisfy the conditions.

 

Example 1:

Input: nums = [18,43,36,13,7]
Output: 54
Explanation: The pairs (i, j) that satisfy the conditions are:
- (0, 2), both numbers have a sum of digits equal to 9, and their sum is 18 + 36 = 54.
- (1, 4), both numbers have a sum of digits equal to 7, and their sum is 43 + 7 = 50.
So the maximum sum that we can obtain is 54.

Example 2:

Input: nums = [10,12,19,14]
Output: -1
Explanation: There are no two numbers that satisfy the conditions, so we return -1.

 

Constraints:

    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9


*/

class Solution {
private:
    int sum_of_digits(int n) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10; 
        }

        return sum;
    }

    int by_classified_sum(vector<int>& nums, int& n) {
        std::vector<int> sum_to_n(82, -1);
        int max_sum = -1;
        
        for (int i = 0; i < n; ++i) {
            int sum = sum_of_digits(nums[i]);

            if (sum_to_n[sum] != -1) {
                
                int existed = sum_to_n[sum];
                max_sum = std::max(max_sum, existed + nums[i]);
                sum_to_n[sum] = std::max(existed, nums[i]);

            } else {
                sum_to_n[sum] = nums[i];
            }
        }

        return max_sum;
    }
    int by_sort(vector<int>& nums, int& n) {
        std::vector<std::pair<int, int>> sums(n);
        for (int i = 0; i < n; ++i) {
            sums[i] = { sum_of_digits(nums[i]), nums[i] };
        }

        std::sort(sums.begin(), sums.end());

        int max_val = -1;
        for (int i = 1; i < n; ++i) {
            if (sums[i].first == sums[i - 1].first) {
                max_val = std::max(max_val, sums[i].second + sums[i - 1].second);
            }
        }

        return max_val;
    }
public:
    int maximumSum(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return -1;
        }

        //return by_sort(nums, n);
        return by_classified_sum(nums, n);
    }
};