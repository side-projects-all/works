/*
Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.

The distance between two adjacent cells is 1.

 

Example 1:

Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
Output: [[0,0,0],[0,1,0],[0,0,0]]

Example 2:

Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
Output: [[0,0,0],[0,1,0],[1,2,1]]

 

Constraints:

    m == mat.length
    n == mat[i].length
    1 <= m, n <= 10^4
    1 <= m * n <= 10^4
    mat[i][j] is either 0 or 1.
    There is at least one 0 in mat.



*/

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int rows = mat.size();
        
        if (rows == 0) {
            return mat;
        }
        
        int cols = mat[0].size();
        std::vector<std::vector<int>> distance(rows, 
                                               std::vector<int>(cols, 
                                                                std::numeric_limits<int>::max() - 100000));
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (mat[i][j] == 0) {
                    distance[i][j] = 0;
                    
                } else {
                    if (i > 0) {
                        //compare with its top
                        distance[i][j] = std::min(distance[i][j], distance[i - 1][j] + 1);
                    } 
                    
                    if (j > 0) {
                        //compare with its left
                        distance[i][j] = std::min(distance[i][j], distance[i][j - 1] + 1);
                    }
                }
            }
        }
        
        for (int i = rows - 1; i > -1 ; --i) {
            for (int j = cols - 1; j > -1 ; --j) {
                if (i < rows - 1) {
                    //compare with its bottom
                    distance[i][j] = std::min(distance[i][j], distance[i + 1][j] + 1);
                } 

                if (j < cols - 1) {
                    //compare with its righ
                    distance[i][j] = std::min(distance[i][j], distance[i][j + 1] + 1);
                }
            }
        }
        
        return distance;
    }
};