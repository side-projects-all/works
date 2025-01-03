/*
Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

 

Example 1:

Input: nums = [3,2,3]
Output: 3

Example 2:

Input: nums = [2,2,1,1,1,2,2]
Output: 2

 

Constraints:

    n == nums.length
    1 <= n <= 5 * 10^4
    -10^9 <= nums[i] <= 10^9

*/

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int N = nums.size();
        int cnt = 1;
        int element = nums[0];

        for (int i = 1; i < N; ++i) {
            if (nums[i] == element) {
                ++cnt;
            } else {
                --cnt;

                if (cnt == 0) {
                    element = nums[i];
                    cnt = 1;
                }
            }
        }

        return element;
        /*
        
        std::unordered_map<int, int> m;

        for (int n : nums) {
            ++m[n];
        }

        int maxCnt = 0;
        int M = 0;
        for (const auto& p : m) {
            if (p.second > maxCnt && p.second > N / 2) {
                M = p.first;
            }
        }

        return M;
        */
    }
};