/*
Given an m x n picture consisting of black 'B' and white 'W' pixels, return the number of black lonely pixels.

A black lonely pixel is a character 'B' that located at a specific position where the same row and same column don't have any other black pixels.

 

Example 1:

Input: picture = [["W","W","B"],["W","B","W"],["B","W","W"]]
Output: 3
Explanation: All the three 'B's are black lonely pixels.

Example 2:

Input: picture = [["B","B","B"],["B","B","W"],["B","B","B"]]
Output: 0

 

Constraints:

    m == picture.length
    n == picture[i].length
    1 <= m, n <= 500
    picture[i][j] is 'W' or 'B'.


*/

class Solution {
public:
    int findLonelyPixel(vector<vector<char>>& picture) {
        
        int rows = picture.size();
        int cols = picture[0].size();
        std::vector<int> row_bk(rows, 0);
        std::vector<int> col_bk(cols, 0);

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (picture[r][c] == 'B') {
                    ++row_bk[r];
                    ++col_bk[c];
                }
            }
        }

        int cnt = 0;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (picture[r][c] == 'B' && row_bk[r] == 1 && col_bk[c] == 1) {
                    ++cnt;
                }
            }
        }

        return cnt;
    }
};