/*
Given an integer array nums of size n, return the minimum number of moves required to make all array elements equal.

In one move, you can increment n - 1 elements of the array by 1.

 

Example 1:

Input: nums = [1,2,3]
Output: 3
Explanation: Only three moves are needed (remember each move increments two elements):
[1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]

Example 2:

Input: nums = [1,1,1]
Output: 0

 

Constraints:

    n == nums.length
    1 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9
    The answer is guaranteed to fit in a 32-bit integer.


*/

class Solution {
public:
    int minMoves(vector<int>& nums) {
        //return by_math(nums);
        return by_sort(nums);
    }
private:
    int by_sort(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int cnt = 0;
        for (int i = nums.size() - 1; i > 0; --i) {
            cnt += nums[i] - nums[0];
        }

        return cnt;
    }
    int by_math(vector<int>& nums) {
        int moves = 0;
        int min = INT_MAX;
        for (int n : nums) {
            moves += n;
            min = std::min(min, n);
        }

        return moves - min * nums.size();
    }
};