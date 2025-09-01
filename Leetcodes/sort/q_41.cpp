/*
Given an unsorted integer array nums. Return the smallest positive integer that is not present in nums.

You must implement an algorithm that runs in O(n) time and uses O(1) auxiliary space.

 

Example 1:

Input: nums = [1,2,0]
Output: 3
Explanation: The numbers in the range [1,2] are all in the array.

Example 2:

Input: nums = [3,4,-1,1]
Output: 2
Explanation: 1 is in the array but 2 is missing.

Example 3:

Input: nums = [7,8,9,11,12]
Output: 1
Explanation: The smallest positive integer 1 is missing.

 

Constraints:

    1 <= nums.length <= 10^5
    -2^31 <= nums[i] <= 2^31 - 1


*/

class Solution {
private:
    int byCycleSort(vector<int>& nums) {
        
        int N = nums.size();
        int i = 0;
        while (i < N) {

            if (nums[i] > 0 && nums[i] <= N && nums[nums[i] - 1] != nums[i]) {
                int tmp =  nums[nums[i] - 1];
                nums[nums[i] - 1] = nums[i];
                nums[i] = tmp;
            } else {
                ++i;
            }
        }

        for (int i = 0; i < N; ++i) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }

        return N + 1;
    }
    int byHashKey(vector<int>& nums) {
        int N = nums.size();
        bool containOne = false;

        //by hash key
        for (int i = 0; i < N; ++i) {
            
            if (nums[i] == 1) {
                containOne = true;
            }
            if (nums[i] <= 0 || nums[i] > N) {
                nums[i] = 1;
            }

        }

        if (!containOne) {
            return 1;
        }

        for (int i = 0; i < N; ++i) {
            int val = std::abs(nums[i]);

            if (val == N) {
                nums[0] = -std::abs(nums[0]);
            } else {
                nums[val] = -std::abs(nums[val]);
            }   
        }

        for (int i = 1; i < N; ++i) {
            if (nums[i] > 0) {
                return i;
            }
        }

        if (nums[0] > 0) {
            return N;
        }

        return N + 1;
    }
public:
    int firstMissingPositive(vector<int>& nums) {
        //return byHashKey(nums);
        return byCycleSort(nums);
    }
};