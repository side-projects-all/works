/*
Given an array of integers arr, return true if and only if it is a valid mountain array.

Recall that arr is a mountain array if and only if:

    arr.length >= 3
    There exists some i with 0 < i < arr.length - 1 such that:
        arr[0] < arr[1] < ... < arr[i - 1] < arr[i] 
        arr[i] > arr[i + 1] > ... > arr[arr.length - 1]

 

Example 1:

Input: arr = [2,1]
Output: false

Example 2:

Input: arr = [3,5,5]
Output: false

Example 3:

Input: arr = [0,3,2,1]
Output: true

 

Constraints:

    1 <= arr.length <= 10^4
    0 <= arr[i] <= 10^4


*/

class Solution {
private:

public:
    bool validMountainArray(vector<int>& arr) {
        //marginal case
        if (arr.size() == 1) {
            return false;
        }

        int len = arr.size();
        int i = 0;

        while (i + 1 < len && arr[i] < arr[i + 1]) {
            ++i;
        }
        
        if (i == arr.size() - 1 || i == 0) {
            return false;
        }

        while (i + 1 < len && arr[i] > arr[i + 1]) {
            ++i;
        }

        return i == len - 1;
    }
};