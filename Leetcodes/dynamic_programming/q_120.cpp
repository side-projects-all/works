/*
Given a triangle array, return the minimum path sum from top to bottom.

For each step, you may move to an adjacent number of the row below. More formally, if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.

 

Example 1:

Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).

Example 2:

Input: triangle = [[-10]]
Output: -10

 

Constraints:

    1 <= triangle.length <= 200
    triangle[0].length == 1
    triangle[i].length == triangle[i - 1].length + 1
    -104 <= triangle[i][j] <= 104

 
Follow up: Could you do this using only O(n) extra space, where n is the total number of rows in the triangle?
*/

class Solution {
private:
    int by_iterative_dp(vector<vector<int>>& triangle) {
        int rows = triangle.size();
        if (rows == 1) {
            return triangle[0][0];
        }

        int cols = triangle[rows - 1].size();

        std::vector<int> prev(cols);
        prev[0] = triangle[1][0] + triangle[0][0];
        prev[1] = triangle[1][1] + triangle[0][0];

        for (int r = 2; r < rows; ++r) {

            int len = triangle[r].size();
            int top_left = prev[0];
            int top = prev[1];
            prev[0] = triangle[r][0] + prev[0];
            prev[len - 1] = triangle[r][len - 1] + prev[len - 2];

            for (int c = 1; c < len - 1; ++c) {
                prev[c] = triangle[r][c] + std::min(top_left, top);
                top_left = top;
                top = prev[c + 1];
            }
        }

        int min = INT_MAX;
        for (int i = 0; i < cols; ++i) {
            min = std::min(min, prev[i]);
        }

        return min;
    }
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        return by_iterative_dp(triangle);
    }
};