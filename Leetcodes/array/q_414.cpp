/*
Given an integer array nums, return the third distinct maximum number in this array. If the third maximum does not exist, return the maximum number.

 

Example 1:

Input: nums = [3,2,1]
Output: 1
Explanation:
The first distinct maximum is 3.
The second distinct maximum is 2.
The third distinct maximum is 1.

Example 2:

Input: nums = [1,2]
Output: 2
Explanation:
The first distinct maximum is 2.
The second distinct maximum is 1.
The third distinct maximum does not exist, so the maximum (2) is returned instead.

Example 3:

Input: nums = [2,2,3,1]
Output: 1
Explanation:
The first distinct maximum is 3.
The second distinct maximum is 2 (both 2's are counted together since they have the same value).
The third distinct maximum is 1.

 

Constraints:

    1 <= nums.length <= 10^4
    -2^31 <= nums[i] <= 2^31 - 1

*/

class Solution {
public:
    int thirdMax(vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        //by sorting
        /*
        std::sort(nums.begin(), nums.end());
        int count = 1;

        for (int i = nums.size() - 2; i > -1; --i) {
            if (nums[i] != nums[i + 1]) {
                ++count;
            }

            if (count == 3) {
                return nums[i];
            }
        }

        return nums[nums.size() - 1];
        */

        /*
        //by heap
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;        
        std::unordered_set<int> used;

        for (int i = 0; i < nums.size(); ++i) {
            if (used.count(nums[i]) > 0) {
                continue;
            }

            if (pq.size() == 3) {
                if (nums[i] > pq.top()) {
                    used.erase(pq.top());
                    pq.pop();

                    pq.push(nums[i]);
                    used.insert(nums[i]);
                }
            } else {
                pq.push(nums[i]);
                used.insert(nums[i]);
            }
            
        }

        if (pq.size() == 2) {
            int first = pq.top();
            pq.pop();

            return std::max(first, pq.top());
        }

        //size is 1 or 3 will just return top
        return pq.top();
        */

        //by ordered set
        std::set<int> sorted;

        for (int i = 0; i < nums.size(); ++i) {
            if (sorted.count(nums[i])) {
                continue;
            }

            if (sorted.size() == 3) {
                if (*sorted.begin() < nums[i]) {
                    sorted.erase(sorted.begin());
                    sorted.insert(nums[i]);
                }
            } else {
                sorted.insert(nums[i]);
            }
        }

        if (sorted.size() == 3) {
            return *sorted.begin();
        }

        return *sorted.rbegin();
    }
};