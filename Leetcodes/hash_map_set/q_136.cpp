/*
Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.

You must implement a solution with a linear runtime complexity and use only constant extra space.

 

Example 1:

Input: nums = [2,2,1]
Output: 1

Example 2:

Input: nums = [4,1,2,1,2]
Output: 4

Example 3:

Input: nums = [1]
Output: 1

 

Constraints:

    1 <= nums.length <= 3 * 10^4
    -3 * 10^4 <= nums[i] <= 3 * 10^4
    Each element in the array appears twice except for one element which appears only once.


*/

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        /*  using hash set with erase
        std::unordered_set<int> myHash;
        
        for (auto num : nums) {
            if (myHash.find(num) != myHash.end()) {
                myHash.erase(num);
            } else {
                myHash.insert(num);
            }
        }
        
        return *(myHash.begin());
        */
        
        /* using hash set only insert 
        std::unordered_set<int> myHash;
        int sum_set = 0;
        int sum_nums = 0;
        
        for (auto num : nums) {
            if (myHash.find(num) == myHash.end()) {
                myHash.insert(num);
                sum_set += num;
            }
            
            sum_nums += num;
        }
        
        return 2 * sum_set - sum_nums;
        */
        
        /* using XOR */
        int a = 0;
        for (auto num : nums) {
            a ^= num;
        }
        
        return a;
    }
};