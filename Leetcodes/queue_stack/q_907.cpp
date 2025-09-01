/*
Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 109 + 7.

 

Example 1:

Input: arr = [3,1,2,4]
Output: 17
Explanation: 
Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]. 
Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
Sum is 17.

Example 2:

Input: arr = [11,81,94,43,3]
Output: 444

 

Constraints:

    1 <= arr.length <= 3 * 10^4
    1 <= arr[i] <= 3 * 10^4


*/

class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        std::stack<int> stack;
        int sum = 0;

        for (int i = 0; i <= n; ++i) {
            while (!stack.empty() && (i == n || arr[stack.top()] >= arr[i])) {
                int mid = stack.top();
                stack.pop();
                int left = mid - (stack.empty() ? -1 : stack.top());
                int right = i - mid;

                sum = ((long)sum + ((long)arr[mid] * left * right) % 1'000'000'007) % 1'000'000'007;
            }

            stack.push(i);
        }

        return sum;
    }
};