/*
Given a binary array nums and an integer goal, return the number of non-empty subarrays with a sum goal.

A subarray is a contiguous part of the array.

 

Example 1:

Input: nums = [1,0,1,0,1], goal = 2
Output: 4
Explanation: The 4 subarrays are bolded and underlined below:
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]

Example 2:

Input: nums = [0,0,0,0,0], goal = 0
Output: 15

 

Constraints:

    1 <= nums.length <= 3 * 10^4
    nums[i] is either 0 or 1.
    0 <= goal <= nums.length

*/

class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int N = nums.size();

        //corner case
        if (N == 1) {
            return nums[0] == goal ? 0 : 1;
        }

        std::function<int(int)> sw = [&](int goal) -> int {
            int cnt = 0;
            int begin = 0;
            int sum = 0;

            for (int end = 0; end < N; ++end) {
                sum += nums[end];

                while (begin <= end && sum > goal) {
                    sum -= nums[begin];
                    ++begin;
                }

                cnt += end - begin + 1;
            }

            return cnt;
        };

        return sw(goal) - sw(goal - 1);
        //TLE
        /*
        for (int s = 0; s < N; ++s) {

            int sum = 0;
            for (int e = s; e < N; ++e) {
                
                sum += nums[e];

                if (sum > goal) {
                    break;
                } else if (sum == goal) {
                    ++cnt;
                }
            }
        }

        return cnt;
        */       
    }
};