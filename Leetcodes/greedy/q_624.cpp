/*
You are given m arrays, where each array is sorted in ascending order.

You can pick up two integers from two different arrays (each array picks one) and calculate the distance. We define the distance between two integers a and b to be their absolute difference |a - b|.

Return the maximum distance.

 

Example 1:

Input: arrays = [[1,2,3],[4,5],[1,2,3]]
Output: 4
Explanation: One way to reach the maximum distance 4 is to pick 1 in the first or third array and pick 5 in the second array.

Example 2:

Input: arrays = [[1],[1]]
Output: 0

 

Constraints:

    m == arrays.length
    2 <= m <= 10^5
    1 <= arrays[i].length <= 500
    -10^4 <= arrays[i][j] <= 10^4
    arrays[i] is sorted in ascending order.
    There will be at most 105 integers in all the arrays.


*/

class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        int min = arrays[0][0];
        int max = arrays[0][arrays[0].size() - 1];
        int result = 0;

        for (int i = 1; i < arrays.size(); ++i) {
            int last = arrays[i].size() - 1;
            result = std::max(result, std::max(std::abs(arrays[i][last] - min), std::abs(max - arrays[i][0])));

            min = std::min(min, arrays[i][0]);
            max = std::max(max, arrays[i][last]);
        }

        return result;
    }
};