/*
You are given two integer arrays nums1 and nums2 of lengths m and n respectively. nums1 and nums2 represent the digits of two numbers. You are also given an integer k.

Create the maximum number of length k <= m + n from digits of the two numbers. The relative order of the digits from the same array must be preserved.

Return an array of the k digits representing the answer.

 

Example 1:

Input: nums1 = [3,4,6,5], nums2 = [9,1,2,5,8,3], k = 5
Output: [9,8,6,5,3]

Example 2:

Input: nums1 = [6,7], nums2 = [6,0,4], k = 5
Output: [6,7,6,0,4]

Example 3:

Input: nums1 = [3,9], nums2 = [8,9], k = 3
Output: [9,8,9]

 

Constraints:

    m == nums1.length
    n == nums2.length
    1 <= m, n <= 500
    0 <= nums1[i], nums2[i] <= 9
    1 <= k <= m + n


*/

class Solution {
public:
    
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        int m = nums2.size();

        std::vector<int> ans(k);       
        for (int len_n1 = std::max(0, k - m); len_n1 <= k && len_n1 <= n; ++len_n1) {
            std::vector<int> a1 = max_arr(nums1, len_n1);
            std::vector<int> a2 = max_arr(nums2, k - len_n1);
            std::vector<int> candidate = merge_arr(a1, a2, k);

            if (greater_arr(candidate, 0, ans, 0)) {
                ans = candidate;
            }
        }

        return ans;
    }
private:
    std::vector<int> max_arr(std::vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans(k);

        for (int i = 0, j = 0; i < n; ++i) {
            while (n - i + j > k && j > 0 && ans[j - 1] < nums[i]) {
                j--;
            }

            if (j < k) {
                ans[j] = nums[i];
                ++j;
            } 
        }

        return ans;
    }
    
    std::vector<int> merge_arr(std::vector<int>& nums1, std::vector<int>& nums2, int k) {
        std::vector<int> ans(k);

        for (int i = 0, j = 0, r = 0; r < k; ++r) {
            ans[r] = greater_arr(nums1, i, nums2, j) ? nums1[i++] : nums2[j++];
        }
            
        return ans;
    }

    bool greater_arr(std::vector<int>&nums1, int i, std::vector<int>&nums2, int j) {

        while (i < nums1.size() && j < nums2.size() && nums1[i] == nums2[j]) {
            ++i;
            ++j;
        }
        return j == nums2.size() || (i < nums1.size() && nums1[i] > nums2[j]);
    }
};