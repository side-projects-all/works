/*
Given an integer array nums and an integer k, you are asked to construct the array ans of size n-k+1 where ans[i] is the number of distinct numbers in the subarray nums[i:i+k-1] = [nums[i], nums[i+1], ..., nums[i+k-1]].

Return the array ans.

 

Example 1:

Input: nums = [1,2,3,2,2,1,3], k = 3
Output: [3,2,2,2,3]
Explanation: The number of distinct elements in each subarray goes as follows:
- nums[0:2] = [1,2,3] so ans[0] = 3
- nums[1:3] = [2,3,2] so ans[1] = 2
- nums[2:4] = [3,2,2] so ans[2] = 2
- nums[3:5] = [2,2,1] so ans[3] = 2
- nums[4:6] = [2,1,3] so ans[4] = 3

Example 2:

Input: nums = [1,1,1,1,2,3,4], k = 4
Output: [1,2,3,4]
Explanation: The number of distinct elements in each subarray goes as follows:
- nums[0:3] = [1,1,1,1] so ans[0] = 1
- nums[1:4] = [1,1,1,2] so ans[1] = 2
- nums[2:5] = [1,1,2,3] so ans[2] = 3
- nums[3:6] = [1,2,3,4] so ans[3] = 4

 

Constraints:

    1 <= k <= nums.length <= 10^5
    1 <= nums[i] <= 10^5

*/

class Solution {
private:
    vector<int> by_counting_array(vector<int>& nums, int& k, int& n) {
        //still sliding window concept, but couting
        int max_num = *std::max_element(nums.begin(), nums.end());
        std::vector<int> freq(max_num + 1);

        int distinct = 0;
        std::vector<int> ans(n - k + 1);

        for (int i = 0; i < k; ++i) {
            ++freq[nums[i]];

            if (freq[nums[i]] == 1) {
                ++distinct;
            }
        }
        ans[0] = distinct;

        for (int i = 1; i <= n - k; ++i) {
            ++freq[nums[i + k - 1]];

            if (freq[nums[i + k - 1]] == 1) {
                ++distinct;
            }

            --freq[nums[i - 1]];
            if (freq[nums[i - 1]] == 0) {
                --distinct;
            }

            ans[i] = distinct;
        }

        return ans;
    }
    vector<int> by_simple_sliding_window(vector<int>& nums, int& k, int& n) {
        std::vector<int> ans(n - k + 1);
        std::unordered_map<int, int> window;

        for(int i = 0; i < k; ++i) {
            ++window[nums[i]];
        }

        ans[0] = window.size();

        for (int i = 1; i <= n - k; ++i) {
            --window[nums[i - 1]];
            ++window[nums[i + k - 1]];

            if (window[nums[i - 1]] == 0) {
                window.erase(nums[i - 1]);
            }
            ans[i] = window.size();
        }

        return ans;
    }
public:
    vector<int> distinctNumbers(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 1) {
            return {1};
        }

        if (k == 1) {
            return std::vector<int>(n, 1);
        }
        
        //return by_simple_sliding_window(nums, k, n);
        return by_counting_array(nums, k, n);
    }
};