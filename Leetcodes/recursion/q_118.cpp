/*
Given an integer numRows, return the first numRows of Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:

 

Example 1:

Input: numRows = 5
Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]

Example 2:

Input: numRows = 1
Output: [[1]]

 

Constraints:

    1 <= numRows <= 30


*/

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        //return iterative(numRows);
        result = std::vector<std::vector<int>>(numRows);
        //recursive(numRows);
        iterative2(numRows);

        return result;
    }

private:
    std::vector<std::vector<int>> result;

    void iterative2(int rows) {
        if (rows != 0) {
            result[0] = {1};
        }

        if (rows <= 1) {
            return;
        }

        for (int i = 1; i < result.size(); ++i) {

            std::vector<int> tmp(i + 1, 1);
            for (int j = 1; j < tmp.size() - 1; ++j) {
                tmp[j] = result[i - 1][j - 1] + result[i - 1][j];
            }
            
            result[i] = tmp;
        }
    }


    std::vector<int> recursive(int row) {

        //base case with 1 row, 1 col, also value is 1
        if (row == 1) {
            std::vector<int> base = std::vector<int>(1, 1);
            result[row - 1] = base;
            return base;
        }

        std::vector<int> rowLast = recursive(row - 1);
        std::vector<int> rowNow = std::vector<int>(row, 1);

        for (int i = 1; i < row - 1; ++i) {
            rowNow[i] = rowLast[i - 1] + rowLast[i];
        }
        result[row - 1] = rowNow;

        return rowNow;
    }

    std::vector<std::vector<int>> iterative(int numRows) {
        vector<vector<int>> result(numRows);
        vector<int> rowLast;
        vector<int> rowCurrent;
        
        result[0] = vector<int>(1, 1);
        
        if (numRows == 1) {
            return result;
        }
        
        result[1] = vector<int>(2, 1);
        if (numRows == 2) {
            return result;
        }
        
        for (int i = 2; i < numRows; ++i) {
            result[i] = vector<int>(i + 1, 1);
            
            for (int j = 1; j < result[i].size() - 1; ++j) {
                result[i][j] = result[i - 1][j - 1] + result[i - 1][j];
            }
        }
        
        return result;
    }
};