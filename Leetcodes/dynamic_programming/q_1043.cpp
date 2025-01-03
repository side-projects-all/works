/*
Given an integer array arr, partition the array into (contiguous) subarrays of length at most k. After partitioning, each subarray has their values changed to become the maximum value of that subarray.

Return the largest sum of the given array after partitioning. Test cases are generated so that the answer fits in a 32-bit integer.

 

Example 1:

Input: arr = [1,15,7,9,2,5,10], k = 3
Output: 84
Explanation: arr becomes [15,15,15,9,10,10,10]

Example 2:

Input: arr = [1,4,1,5,7,3,6,1,9,9,3], k = 4
Output: 83

Example 3:

Input: arr = [1], k = 1
Output: 1

 

Constraints:

    1 <= arr.length <= 500
    0 <= arr[i] <= 10^9
    1 <= k <= arr.length


*/

class Solution {
private:
    int iterative(vector<int>& arr, int k) {
        int N = arr.size();
        std::vector<int> mem(N + 1, 0);

        for (int i = N - 1; i > -1; --i) {

            int currMax = 0;
            int ans = 0;
            int end = std::min(N, i + k);
            for (int s = i; s < end; ++s) {
                currMax = std::max(currMax, arr[s]);
                mem[i] = std::max(mem[i], currMax * (s - i + 1) + mem[s + 1]);
            }
        }

        return mem[0];
    }
    int recursive(vector<int>& arr, int k) {
        int N = arr.size();
        std::vector<int> mem(N, -1);

        std::function<int(int)> recurr = [&](int i) -> int {
            if (i >= N) {
                return 0;
            }

            if (mem[i] != -1) {
                return mem[i];
            }

            int currMax = 0;
            int ans = 0;
            int end = std::min(N, i + k);
            for (int s = i; s < end; ++s) {
                currMax = std::max(currMax, arr[s]);
                ans = std::max(ans, currMax * (s - i + 1) + recurr(s + 1));
            }

            return mem[i] = ans;
        };

        return recurr(0);
    }
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        //return recursive(arr, k);
        
        return iterative(arr, k);
    }
};