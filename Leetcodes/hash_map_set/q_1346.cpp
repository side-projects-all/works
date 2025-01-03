/*
Given an array arr of integers, check if there exist two indices i and j such that :

    i != j
    0 <= i, j < arr.length
    arr[i] == 2 * arr[j]

 

Example 1:

Input: arr = [10,2,5,3]
Output: true
Explanation: For i = 0 and j = 2, arr[i] == 10 == 2 * 5 == 2 * arr[j]

Example 2:

Input: arr = [3,1,7,11]
Output: false
Explanation: There is no i and j that satisfy the conditions.

 

Constraints:

    2 <= arr.length <= 500
    -10^3 <= arr[i] <= 10^3


*/

class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        std::unordered_set<int> visited;

        for (int i = 0; i < arr.size(); ++i) {
            
            if (visited.find(arr[i] * 2) != visited.end() || 
                (arr[i] % 2 == 0 && visited.find(arr[i] / 2) != visited.end())) {

                return true;
            }

            visited.insert(arr[i]);
        }

        return false;
    }
};