/*
A row-sorted binary matrix means that all elements are 0 or 1 and each row of the matrix is sorted in non-decreasing order.

Given a row-sorted binary matrix binaryMatrix, return the index (0-indexed) of the leftmost column with a 1 in it. If such an index does not exist, return -1.

You can't access the Binary Matrix directly. You may only access the matrix using a BinaryMatrix interface:

    BinaryMatrix.get(row, col) returns the element of the matrix at index (row, col) (0-indexed).
    BinaryMatrix.dimensions() returns the dimensions of the matrix as a list of 2 elements [rows, cols], which means the matrix is rows x cols.

Submissions making more than 1000 calls to BinaryMatrix.get will be judged Wrong Answer. Also, any solutions that attempt to circumvent the judge will result in disqualification.

For custom testing purposes, the input will be the entire binary matrix mat. You will not have access to the binary matrix directly.

 

Example 1:

Input: mat = [[0,0],[1,1]]
Output: 0

Example 2:

Input: mat = [[0,0],[0,1]]
Output: 1

Example 3:

Input: mat = [[0,0],[0,0]]
Output: -1

 

Constraints:

    rows == mat.length
    cols == mat[i].length
    1 <= rows, cols <= 100
    mat[i][j] is either 0 or 1.
    mat[i] is sorted in non-decreasing order.


*/

/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int row, int col);
 *     vector<int> dimensions();
 * };
 */

class Solution {
public:
    int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        std::vector<int> dim = binaryMatrix.dimensions();

        int leftMost = dim[1];
        for (int r = 0; r < dim[0]; ++r) {
            int left = 0;
            int right = dim[1] - 1;

            while (left <= right) {
                int mid = left + (right - left) / 2;

                if (binaryMatrix.get(r, mid) == 1) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }

            if (left != dim[1]) {
                leftMost = std::min(leftMost, left);
            }
            
        }

        return leftMost == dim[1] ? -1 : leftMost;
    }
};