/*
Given an integer array arr and an integer difference, return the length of the longest subsequence in arr which is an arithmetic sequence such that the difference between adjacent elements in the subsequence equals difference.

A subsequence is a sequence that can be derived from arr by deleting some or no elements without changing the order of the remaining elements.

 

Example 1:

Input: arr = [1,2,3,4], difference = 1
Output: 4
Explanation: The longest arithmetic subsequence is [1,2,3,4].

Example 2:

Input: arr = [1,3,5,7], difference = 1
Output: 1
Explanation: The longest arithmetic subsequence is any single element.

Example 3:

Input: arr = [1,5,7,8,5,3,4,2,1], difference = -2
Output: 4
Explanation: The longest arithmetic subsequence is [7,5,3,1].

 

Constraints:

    1 <= arr.length <= 10^5
    -10^4 <= arr[i], difference <= 10^4


*/

class Solution {
private:
    int iterative(std::vector<int>& arr, int difference) {
        int n = arr.size();
        if (n == 1) {
            return 1;
        }

        std::vector<int> dp(20001);
        int max_len = 0;
        for (int i = 0; i < n; ++i) {

            int prev = arr[i] + 10000 - diff;
            if (prev >= 0 && prev <= 20000 && dp[prev] > 0) {
                dp[prev + diff] = 1 + dp[prev];

            } else {
                dp[prev + diff] = 1;
            }

            max_len = std::max(max_len, dp[prev + diff]);
        }

        return max_len;
        /*
        int N = arr.size();
        std::unordered_map<int, int> mem;   //key: arr[i], value: len

        int max = 1;
        for (int i = 0; i < N; ++i) {
            
            if (mem.find(arr[i] - difference) != mem.end()) {
                mem[arr[i]] = 1 + mem[arr[i] - difference];

            } else {

                mem[arr[i]] = 1;
            }
            
            max = std::max(max, mem[arr[i]]);
        }

        return max;
        */
    }
    int recursive(std::vector<int>& arr, int difference) {
        int N = arr.size();

        //TLE by using the method of longest increasing sequence
        std::vector<int> mem(N, -100001);
        
        std::function<int(int)> recurr = [&](int k) -> int {

            if (mem[k] != -100001) {
                return mem[k];
            }

            mem[k] = 1;
            for (int j = 0; j < k; ++j) {
                if (arr[k] - difference == arr[j]) {
                    mem[k] = std::max(mem[k], 1 + recurr(j));
                }
            }
            
            return mem[k];
        };

        int max = 1;
        for (int i = 0; i < N; ++i) {
            max = std::max(max, recurr(i));
        }
        
        return max;
    }
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        
        //return recursive(arr, difference);
        return iterative(arr, difference);
    }
};