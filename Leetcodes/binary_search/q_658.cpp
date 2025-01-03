/*
Given a sorted integer array arr, two integers k and x, return the k closest integers to x in the array. The result should also be sorted in ascending order.

An integer a is closer to x than an integer b if:

    |a - x| < |b - x|, or
    |a - x| == |b - x| and a < b

 

Example 1:

Input: arr = [1,2,3,4,5], k = 4, x = 3
Output: [1,2,3,4]

Example 2:

Input: arr = [1,2,3,4,5], k = 4, x = -1
Output: [1,2,3,4]

 

Constraints:

    1 <= k <= arr.length
    1 <= arr.length <= 10^4
    arr is sorted in ascending order.
    -10^4 <= arr[i], x <= 10^4


*/

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        std::vector<int> result;
        int N = arr.size();
        int left = 0;
        int right = N - 1;

        //edge case: arr is empty
        if (arr.empty()) {
            return result;
        }
        //edge case: k >= arr.size()
        if (k >= N) {
            return arr;
        }
        //edge case: x is equal to or smaller thatn arr[0]
        if (x <= arr[left]) {
            for (int i = 0, count = 1; i < arr.size() && count <= k; ++i, ++count) {
                result.push_back(arr[i]);
            }
            return result;
        }
        //edge case; x is equal to or larger than arr[arr.size() - 1]
        if (x >= arr[right]) {
            for (int i = arr.size() - 1, count = 1; i > -1 && count <= k; --i, ++count) {
                result.push_back(arr[i]);
            }
            std::sort(result.begin(), result.end());
            return result;
        }

        //binary search by finding left bound
        
        right = N - k;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (x - arr[mid] > arr[mid + k] - x) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        for (int i = left; i < left + k; ++i) {
            result.push_back(arr[i]);
        }

        
        //sliding window + binary search
        /*
        while (left < right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] >= x) {
                right = mid;
            
            } else {
                
                left = mid + 1;
            }
        }

        left -= 1;
        right = left + 1;

        while (right - left - 1 < k) {
            if (left == -1) {
                right += 1;
                continue;
            }

            if (right == N || std::abs(arr[left] - x) <= std::abs(arr[right] - x)) {
                left -= 1;
            } else {
                right += 1;
            }
        }

        for (int i = left + 1; i < right; ++i) {
            result.push_back(arr[i]);
        }
        */

        return result;
    }
};