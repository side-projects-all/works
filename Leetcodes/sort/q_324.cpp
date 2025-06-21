/*
Given an integer array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

You may assume the input array always has a valid answer.

 

Example 1:

Input: nums = [1,5,1,1,6,4]
Output: [1,6,1,5,1,4]
Explanation: [1,4,1,5,1,6] is also accepted.

Example 2:

Input: nums = [1,3,2,2,3,1]
Output: [2,3,1,3,1,2]

 

Constraints:

    1 <= nums.length <= 5 * 10^4
    0 <= nums[i] <= 5000
    It is guaranteed that there will be an answer for the given input nums.

 
Follow Up: Can you do it in O(n) time and/or in-place with O(1) extra space?
*/

class Solution {
private:
    void by_sort(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return;
        }

        std::vector<int> sorted{ nums.begin(), nums.end() };
        std::sort(sorted.begin(), sorted.end());

        int left = (n - 1) / 2;
        int right = n - 1;

        for (int i = 0; i < n; ++i) {
            nums[i] = (i % 2 == 0) ? sorted[left--] : sorted[right--];
        }
    }

    void by_counting_sort(vector<int>& nums) {
        int max_e = *std::max_element(nums.begin(), nums.end());
        std::vector<int> sorted(max_e + 1);

        for (int i = 0; i < nums.size(); ++i) {
            ++sorted[nums[i]];
        }

        int j = max_e;
        for (int i = 1; i < nums.size(); i += 2) {
            while (sorted[j] == 0) {
                --j;
            }

            nums[i] = j;
            --sorted[j];
        }

        for (int i = 0; i < nums.size(); i += 2) {
            while (sorted[j] == 0) {
                --j;
            }

            nums[i] = j;
            --sorted[j];
        }
    }
public:
    void wiggleSort(vector<int>& nums) {
        //by_sort(nums);
        by_counting_sort(nums);
    }
};