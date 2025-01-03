/*
Given three integer arrays arr1, arr2 and arr3 sorted in strictly increasing order, return a sorted array of only the integers that appeared in all three arrays.

 

Example 1:

Input: arr1 = [1,2,3,4,5], arr2 = [1,2,5,7,9], arr3 = [1,3,4,5,8]
Output: [1,5]
Explanation: Only 1 and 5 appeared in the three arrays.

Example 2:

Input: arr1 = [197,418,523,876,1356], arr2 = [501,880,1593,1710,1870], arr3 = [521,682,1337,1395,1764]
Output: []

 

Constraints:

    1 <= arr1.length, arr2.length, arr3.length <= 1000
    1 <= arr1[i], arr2[i], arr3[i] <= 2000


*/

class Solution {
public:
    vector<int> arraysIntersection(vector<int>& arr1, vector<int>& arr2, vector<int>& arr3) {
        std::vector<int> result;

        int p1 = 0;
        int p2 = 0;
        int p3 = 0;
        while (p1 < arr1.size() && p2 < arr2.size() && p3 < arr3.size()) {

            if (arr1[p1] == arr2[p2] && arr2[p2] == arr3[p3]) {
                result.push_back(arr1[p1]);
                ++p1;
                ++p2;
                ++p3;
            } else {
                if (arr1[p1] < arr2[p2] ) {
                    ++p1;
                    
                } else if (arr2[p2] < arr3[p3]) {

                    ++p2;
                } else {
                    
                    ++p3;
                }
            }
        }

        return result;
    }
};