/*
Given an integer rowIndex, return the rowIndexth (0-indexed) row of the Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:

 

Example 1:

Input: rowIndex = 3
Output: [1,3,3,1]

Example 2:

Input: rowIndex = 0
Output: [1]

Example 3:

Input: rowIndex = 1
Output: [1,1]

 

Constraints:

    0 <= rowIndex <= 33

*/

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        if (rowIndex == 0) {
            return std::vector<int>(1, 1);
        }

        if (rowIndex == 1) {
            return std::vector<int>(2, 1);
        }

        std::vector<int> rowLast = getRow(rowIndex - 1);
        std::vector<int> rowNow = std::vector<int>(rowIndex + 1, 1);
        for (int i = 1; i < rowIndex; ++i) {
            rowNow[i] = rowLast[i - 1] + rowLast[i];
        }

        return rowNow;
    }
};