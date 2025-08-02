/*
Given an integer array arr, return the number of distinct bitwise ORs of all the non-empty subarrays of arr.

The bitwise OR of a subarray is the bitwise OR of each integer in the subarray. The bitwise OR of a subarray of one integer is that integer.

A subarray is a contiguous non-empty sequence of elements within an array.

 

Example 1:

Input: arr = [0]
Output: 1
Explanation: There is only one possible result: 0.

Example 2:

Input: arr = [1,1,2]
Output: 3
Explanation: The possible subarrays are [1], [1], [2], [1, 1], [1, 2], [1, 1, 2].
These yield the results 1, 1, 2, 1, 3, 3.
There are 3 unique values, so the answer is 3.

Example 3:

Input: arr = [1,2,4]
Output: 6
Explanation: The possible results are 1, 2, 3, 4, 6, and 7.

 

Constraints:

    1 <= arr.length <= 5 * 10^4
    0 <= arr[i] <= 10^9


*/

class Solution {
private:
    int by_iterative_dp_better(vector<int>& arr) {
        std::unordered_set<int> s;
        for(int i = 0;i < arr.size(); ++i) {
           int j = i - 1;
           int x = 0;
           int y = arr[i];
           s.insert(y);

           while(j >= 0 && x != y) {
               x |= arr[j];
               y |= arr[j];
               s.insert(y);
               --j;
           }
        }
        return s.size();
    }
    int by_iterative_dp(vector<int>& arr) {
        std::unordered_set<int> ans;      
        std::unordered_set<int> cur;      // OR results ending at previous index

        for (int x : arr) {
            std::unordered_set<int> next;
            // 1) subarray consisting of x alone
            next.insert(x);

            // 2) extend all subarrays that ended at the prior element
            for (int y : cur) {
                next.insert(y | x);
            }

            // 3) merge into global set
            for (int v : next) {
                ans.insert(v);
            }
            // prepare for the next iteration
            cur.swap(next);
        }
        return ans.size();
    }
public:
    int subarrayBitwiseORs(vector<int>& arr) {
        return by_iterative_dp(arr);
        //return by_iterative_dp_better(arr);
    }
};