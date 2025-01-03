/*
Given an integer array nums, return the number of reverse pairs in the array.

A reverse pair is a pair (i, j) where:

    0 <= i < j < nums.length and
    nums[i] > 2 * nums[j].

 

Example 1:

Input: nums = [1,3,2,3,1]
Output: 2
Explanation: The reverse pairs are:
(1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
(3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1

Example 2:

Input: nums = [2,4,3,5,1]
Output: 3
Explanation: The reverse pairs are:
(1, 4) --> nums[1] = 4, nums[4] = 1, 4 > 2 * 1
(2, 4) --> nums[2] = 3, nums[4] = 1, 3 > 2 * 1
(3, 4) --> nums[3] = 5, nums[4] = 1, 5 > 2 * 1

 

Constraints:

    1 <= nums.length <= 5 * 10^4
    -2^31 <= nums[i] <= 2^31 - 1


*/


class Solution {
private:
    int mergeSort(std::vector<int>& nums, int left, int right) {
        if (left >= right) {
            return 0;
        }
        int mid = left + (right - left) / 2;
        int count = mergeSort(nums, left, mid) + mergeSort(nums, mid + 1, right);

        // Count the reverse pairs
        int j = mid + 1;
        for (int i = left; i <= mid; ++i) {
            while (j <= right && nums[i] > 2LL * nums[j]) {
                j++;
            }
            count += j - (mid + 1);
        }

        // Merge the two halves
        merge(nums, left, mid, right);
        return count;
    }

    void merge(std::vector<int>& nums, int left, int mid, int right) {
        std::vector<int> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right) {
            if (nums[i] <= nums[j]) {
                temp[k++] = nums[i++];
            } else {
                temp[k++] = nums[j++];
            }
        }

        while (i <= mid) {
            temp[k++] = nums[i++];
        }
        while (j <= right) {
            temp[k++] = nums[j++];
        }
        for (int i = left; i <= right; ++i) {
            nums[i] = temp[i - left];
        }
    }

    void update(std::vector<int>& BIT, int index, int val) {
        while (index > 0) {
            BIT[index] += val;
            index -= index & (-index);
        }
    }

    int query(std::vector<int>& BIT, int index) {
        int sum = 0;
        while (index < BIT.size()) {
            sum += BIT[index];
            index += index & (-index);
        }
        return sum;
    }

    int by_fenwick_tree(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> nums_copy(nums);

        std::sort(nums_copy.begin(), nums_copy.end());

        std::vector<int> BITS(n + 1, 0);
        int count = 0;
        for (int i = 0; i < n; i++) {
            count += query(BITS, std::lower_bound(nums_copy.begin(), nums_copy.end(), 2LL * nums[i] + 1) - nums_copy.begin() + 1);
            update(BITS, std::lower_bound(nums_copy.begin(), nums_copy.end(), nums[i]) - nums_copy.begin() + 1, 1);
        }
        return count;
    }

public:
    int reversePairs(std::vector<int>& nums) {

        //return mergeSort(nums, 0, nums.size() - 1);
        return by_fenwick_tree(nums);
    }
};

