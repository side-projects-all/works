/*
Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

 

Example 1:

Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.

Example 2:

Input: matrix = [["0"]]
Output: 0

Example 3:

Input: matrix = [["1"]]
Output: 1

 

Constraints:

    rows == matrix.length
    cols == matrix[i].length
    1 <= row, cols <= 200
    matrix[i][j] is '0' or '1'.


*/

class Solution {
    int byDPwithStack(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        std::function<int(std::vector<int>&)> stk = [&](std::vector<int>& heights) -> int {
            std::stack<int> s;
            s.push(-1);
            int max_area = 0;

            for (int i = 0; i < heights.size(); ++i) {
                while (s.top() != -1 && heights[s.top()] >= heights[i]) {
                    int now = s.top();
                    s.pop();
                    max_area = std::max(max_area, heights[now] * (i - s.top() - 1));
                    
                }

                s.push(i);
            }

            while (s.top() != -1) {
                int now = s.top();
                s.pop();
                int area = heights[now] * (heights.size() - s.top() - 1);
                max_area = std::max(max_area, area);
            }

            return max_area;
        };

        int maxArea = 0;
        std::vector<int> mem(cols);
        
        for (int i = 0; i < matrix.size(); ++i) { 
            for (int j = 0; j < matrix[0].size(); ++j) {
                mem[j] = (matrix[i][j] == '1' ? mem[j] + 1 : 0);
            }

            maxArea = std::max(maxArea, stk(mem));
        }

        return maxArea;
    }
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        return byDPwithStack(matrix);
    }
};