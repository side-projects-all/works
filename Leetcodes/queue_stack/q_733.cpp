/*
An image is represented by an m x n integer grid image where image[i][j] represents the pixel value of the image.

You are also given three integers sr, sc, and color. You should perform a flood fill on the image starting from the pixel image[sr][sc].

To perform a flood fill, consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color), and so on. Replace the color of all of the aforementioned pixels with color.

Return the modified image after performing the flood fill.

 

Example 1:

Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, color = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation: From the center of the image with position (sr, sc) = (1, 1) (i.e., the red pixel), all pixels connected by a path of the same color as the starting pixel (i.e., the blue pixels) are colored with the new color.
Note the bottom corner is not colored 2, because it is not 4-directionally connected to the starting pixel.

Example 2:

Input: image = [[0,0,0],[0,0,0]], sr = 0, sc = 0, color = 0
Output: [[0,0,0],[0,0,0]]
Explanation: The starting pixel is already colored 0, so no changes are made to the image.

 

Constraints:

    m == image.length
    n == image[i].length
    1 <= m, n <= 50
    0 <= image[i][j], color < 2^16
    0 <= sr < m
    0 <= sc < n


*/

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        p_img = image;
        old_color = image[sr][sc];
        new_color = color;
        col_len = p_img[0].size();
        row_len = p_img.size();
        
        if (old_color != new_color) {
            dfs(sr, sc);
        }
        
        return p_img;
    }

private:
    std::vector<std::vector<int>> p_img;
    int old_color;
    int new_color;
    int col_len;
    int row_len;
    
    void dfs(int r, int c) {
        if (p_img[r][c] == old_color) {
            //because color already be changed here, it just like cached the position
            p_img[r][c] = new_color;
            
            //bottom
            if (r >= 1) {
                dfs(r - 1, c);
            }
            
            //left
            if (c >= 1) {
                dfs(r, c - 1);
            }
            
            //top
            if (r + 1 < row_len) {
                dfs(r + 1, c);
            }
            
            //right
            if (c + 1 < col_len) {
                dfs(r , c + 1);
            }
            
        }
    }
};