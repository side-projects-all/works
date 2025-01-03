/*
In some array arr, the values were in arithmetic progression: the values arr[i + 1] - arr[i] are all equal for every 0 <= i < arr.length - 1.

A value from arr was removed that was not the first or last value in the array.

Given arr, return the removed value.

 

Example 1:

Input: arr = [5,7,11,13]
Output: 9
Explanation: The previous array was [5,7,9,11,13].

Example 2:

Input: arr = [15,13,12]
Output: 14
Explanation: The previous array was [15,14,13,12].

 

Constraints:

    3 <= arr.length <= 1000
    0 <= arr[i] <= 10^5
    The given array is guaranteed to be a valid array.


*/

class Solution {
private:
    int byBs(vector<int>& arr) {

        int N = arr.size();
        int left = 0;
        int right = N - 1;
        int diff = (arr[right] - arr[0]) / N;
        int target = 0;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] == arr.front() + mid * diff) {
                left = mid + 1;
                
            } else {
                right = mid;
            }
        }

        return arr.front() + left * diff;
    }

    int naive(vector<int>& arr) {
        int firstDiff = arr[1] - arr[0];

        for (int i = 2; i < arr.size(); ++i) {
            int diff = arr[i] - arr[i - 1];

            if (firstDiff != diff) {
                if (std::abs(firstDiff) > std::abs(diff)) {
                    return arr[1] - diff;
                } else {
                    return arr[i] - firstDiff;
                }
            }
        }

        return arr[0];
    }
public:
    int missingNumber(vector<int>& arr) {

        //return naive(arr);
        return byBs(arr);
    }
};