/*
Given an array of integers nums and a positive integer k, check whether it is possible to divide this array into sets of k consecutive numbers.

Return true if it is possible. Otherwise, return false.

 

Example 1:

Input: nums = [1,2,3,3,4,4,5,6], k = 4
Output: true
Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].

Example 2:

Input: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
Output: true
Explanation: Array can be divided into [1,2,3] , [2,3,4] , [3,4,5] and [9,10,11].

Example 3:

Input: nums = [1,2,3,4], k = 3
Output: false
Explanation: Each array should be divided in subarrays of size 3.

 

Constraints:

    1 <= k <= nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

class Solution {
private:
    bool byPQ(vector<int>& nums, int k) {
        int N = nums.size();
        if (N < k || N % k != 0) {
            return false;
        }

        
        std::unordered_map<int, int> m;
        for (int v : nums) {
            ++m[v];
        }

        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
        for (const auto& p : m) {
            pq.push(p.first);
        }

        //tmp to store current values that are poped
        int groups = N / k;
        std::vector<int> tmp;
        while (!pq.empty()) {

            int first = pq.top();
            if (m[first] == 0) {
                pq.pop();
                m.erase(first);
                continue;
            }

            --m[first];
            int cnt = k - 1;
            while (cnt > 0) {
                if (m[first + 1]) {
                    --cnt;
                    --m[first + 1];
                    ++first;
                } else {
                    return false;
                }
            }
        }

        return true;
    }
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        return byPQ(nums, k);
    }
};