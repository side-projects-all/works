/*
You are given an m x n binary matrix image where 0 represents a white pixel and 1 represents a black pixel.

The black pixels are connected (i.e., there is only one black region). Pixels are connected horizontally and vertically.

Given two integers x and y that represents the location of one of the black pixels, return the area of the smallest (axis-aligned) rectangle that encloses all black pixels.

You must write an algorithm with less than O(mn) runtime complexity

 

Example 1:

Input: image = [["0","0","1","0"],["0","1","1","0"],["0","1","0","0"]], x = 0, y = 2
Output: 6

Example 2:

Input: image = [["1"]], x = 0, y = 0
Output: 1

 

Constraints:

    m == image.length
    n == image[i].length
    1 <= m, n <= 100
    image[i][j] is either '0' or '1'.
    0 <= x < m
    0 <= y < n
    image[x][y] == '1'.
    The black pixels in the image only form one component.


*/

class Solution {
private:
    int by_binary_search_cols(vector<vector<char>>& image, int b, int e, int top, int bottom, bool w_to_b) {

        while (b < e) {
            int k = top;
            int mid = b + (e - b) / 2;

            while (k < bottom && image[k][mid] == '0') {
                ++k;
            }

            if ((k < bottom) == w_to_b) {
                e = mid;

            } else {
                b = mid + 1;
            }
        }

        return b;
    }

    int by_binary_search_rows(vector<vector<char>>& image, int b, int e, int left, int right, bool w_to_b) {
        
        while (b < e) {
            int k = left;
            int mid = b + (e - b) / 2;

            while (k < right && image[mid][k] == '0') {
                ++k;
            }

            if ((k < right) == w_to_b) {
                e = mid;

            } else {
                b = mid + 1;
            }
        }

        return b;
    }
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        int rows = image.size();
        int cols = image[0].size();

        //based on the example, y means column, x means row
        int min_y = by_binary_search_cols(image, 0, y, 0, rows, true);
        int max_y = by_binary_search_cols(image, y + 1, cols, 0, rows, false);
        int min_x = by_binary_search_rows(image, 0, x, min_y, max_y, true);
        int max_x = by_binary_search_rows(image, x + 1, rows, min_y, max_y, false);

        return (max_x - min_x) * (max_y - min_y);
    }
};