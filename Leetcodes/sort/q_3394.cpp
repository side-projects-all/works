/*
You are given an integer n representing the dimensions of an n x n grid, with the origin at the bottom-left corner of the grid. You are also given a 2D array of coordinates rectangles, where rectangles[i] is in the form [startx, starty, endx, endy], representing a rectangle on the grid. Each rectangle is defined as follows:

    (startx, starty): The bottom-left corner of the rectangle.
    (endx, endy): The top-right corner of the rectangle.

Note that the rectangles do not overlap. Your task is to determine if it is possible to make either two horizontal or two vertical cuts on the grid such that:

    Each of the three resulting sections formed by the cuts contains at least one rectangle.
    Every rectangle belongs to exactly one section.

Return true if such cuts can be made; otherwise, return false.

 

Example 1:

Input: n = 5, rectangles = [[1,0,5,2],[0,2,2,4],[3,2,5,3],[0,4,4,5]]

Output: true

Explanation:

The grid is shown in the diagram. We can make horizontal cuts at y = 2 and y = 4. Hence, output is true.

Example 2:

Input: n = 4, rectangles = [[0,0,1,1],[2,0,3,4],[0,2,2,3],[3,0,4,3]]

Output: true

Explanation:

We can make vertical cuts at x = 2 and x = 3. Hence, output is true.

Example 3:

Input: n = 4, rectangles = [[0,2,2,4],[1,0,3,2],[2,2,3,4],[3,0,4,2],[3,2,4,4]]

Output: false

Explanation:

We cannot make two horizontal or two vertical cuts that satisfy the conditions. Hence, output is false.

 

Constraints:

    3 <= n <= 10^9
    3 <= rectangles.length <= 10^5
    0 <= rectangles[i][0] < rectangles[i][2] <= n
    0 <= rectangles[i][1] < rectangles[i][3] <= n
    No two rectangles overlap.


*/

class Solution {
public:
    bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
        //sorting by x
        std::sort(rectangles.begin(), rectangles.end(), [](std::vector<int>& v1, std::vector<int>& v2) {
            if (v1[0] == v2[0]) {
                return v1[2] < v2[2];
            }

            return v1[0] < v2[0];
        });

        int cnt = 0;
        int len = rectangles.size();
        int max_end = rectangles[0][2];
        for (int i = 1; i < len; ++i) {
            
            if (rectangles[i][0] >= max_end) {
                ++cnt;
            }
            max_end = std::max(max_end, rectangles[i][2]);
        }

        if (cnt >= 2) {
            return true;
        }

        //sorting by y
        std::sort(rectangles.begin(), rectangles.end(), [](std::vector<int>& v1, std::vector<int>& v2) {
            if (v1[1] == v2[1]) {
                return v1[3] < v2[3];
            }

            return v1[1] < v2[1];
        });

        cnt = 0;
        max_end = rectangles[0][3];
        for (int i = 1; i < len; ++i) {

            if (rectangles[i][1] >= max_end) {
                ++cnt;
            }
            max_end = std::max(max_end, rectangles[i][3]);
        }

        return cnt >= 2;
    }
};