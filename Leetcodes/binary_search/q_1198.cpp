/*
Given an m x n matrix mat where every row is sorted in strictly increasing order, return the smallest common element in all rows.

If there is no common element, return -1.

 

Example 1:

Input: mat = [[1,2,3,4,5],[2,4,5,8,10],[3,5,7,9,11],[1,3,5,7,9]]
Output: 5

Example 2:

Input: mat = [[1,2,3],[2,3,4],[2,3,5]]
Output: 2

 

Constraints:

    m == mat.length
    n == mat[i].length
    1 <= m, n <= 500
    1 <= mat[i][j] <= 10^4
    mat[i] is sorted in strictly increasing order.


*/

class Solution {
public:
    int smallestCommonElement(vector<vector<int>>& mat) {

        //by pointers
        int rows = mat.size();
        int cols = mat[0].size();
        
        //position of every row
        /*
        int curr_max = 0;
        int cnt = 0;
        std::vector<int> pos(rows, 0);

        while (true) {
            for (int i = 0; i < rows; ++i) {
                while (pos[i] < cols && mat[i][pos[i]] < curr_max) {
                    ++pos[i];
                }

                if (pos[i] >= cols) {
                    return -1;
                }

                if (mat[i][pos[i]] != curr_max) {
                    cnt = 1;
                    curr_max = mat[i][pos[i]];

                } else if ((++cnt) == rows) {
                    return curr_max;
                }
            }
        }
        */


        //by binary search
        int cnt = 1;
        //loop through every columns in row 0
        for (int i = 0; i < cols; ++i) {
            int target = mat[0][i];
            
            //start from row 1 to do binary search in every row
            for (int r = 1; r < rows; ++r) {
                int left = 0;
                int right = cols - 1;

                while (left <= right) {
                    int mid = left + (right - left) / 2;

                    if (mat[r][mid] > target) {
                        right = mid - 1;
                    } else if (mat[r][mid] < target) {
                        left = mid + 1;
                    } else {
                        cnt += 1;
                        break;
                    }
                }

                if (left > right) {
                    break;
                }

            }

            if (cnt == rows) {
                return target;
            }

            cnt = 1;
        }

        return -1;
    }
};