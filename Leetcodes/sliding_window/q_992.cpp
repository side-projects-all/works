/*
Given an integer array nums and an integer k, return the number of good subarrays of nums.

A good array is an array where the number of different integers in that array is exactly k.

    For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.

A subarray is a contiguous part of an array.

 

Example 1:

Input: nums = [1,2,1,2,3], k = 2
Output: 7
Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]

Example 2:

Input: nums = [1,2,1,3,4], k = 3
Output: 3
Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].

 

Constraints:

    1 <= nums.length <= 2 * 10^4
    1 <= nums[i], k <= nums.length


*/

class Solution {
private:
    int onePassSlidingWindow(vector<int>& nums, int k) {
        std::vector<int> distinctCnt(nums.size() + 1, 0);
        int total = 0;
        int start = 0;
        int end = 0;
        int currCnt = 0;

        while (end < nums.size()) {
            ++distinctCnt[nums[end]];
            if (distinctCnt[nums[end]] == 1) {
                --k;
            }

            if (k < 0) {
                --distinctCnt[nums[start]];
                ++start;
                ++k;
                currCnt = 0;
            }

            if (k == 0) {
                while (distinctCnt[nums[start]] > 1) {
                    --distinctCnt[nums[start]];
                    ++start;
                    ++currCnt;
                }

                total += (currCnt + 1);
            }

            ++end;
        }

        return total;
    }
    int atMostkSlidingWindow(vector<int>& nums, int k) {

        std::function<int(int)> sw = [&](int req) -> int {
            int cnt = 0;
            std::unordered_map<int, int> m;
            int start = 0;

            for (int end = 0; end < nums.size(); ++end) {
                ++m[nums[end]];

                while (m.size() > req) {

                    --m[nums[start]];
                    if (m[nums[start]] == 0) {
                        m.erase(nums[start]);
                    }

                    ++start;
                }

                cnt += end - start + 1;
            }

            return cnt;
        };

        return sw(k) - sw(k - 1);
    }
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return onePassSlidingWindow(nums, k);
        //return atMostkSlidingWindow(nums, k);
    }
};