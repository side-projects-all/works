/*
Given the coordinates of two rectilinear rectangles in a 2D plane, return the total area covered by the two rectangles.

The first rectangle is defined by its bottom-left corner (ax1, ay1) and its top-right corner (ax2, ay2).

The second rectangle is defined by its bottom-left corner (bx1, by1) and its top-right corner (bx2, by2).

 

Example 1:
Rectangle Area

Input: ax1 = -3, ay1 = 0, ax2 = 3, ay2 = 4, bx1 = 0, by1 = -1, bx2 = 9, by2 = 2
Output: 45

Example 2:

Input: ax1 = -2, ay1 = -2, ax2 = 2, ay2 = 2, bx1 = -2, by1 = -2, bx2 = 2, by2 = 2
Output: 16

 

Constraints:

    -10^4 <= ax1 <= ax2 <= 10^4
    -10^4 <= ay1 <= ay2 <= 10^4
    -10^4 <= bx1 <= bx2 <= 10^4
    -10^4 <= by1 <= by2 <= 10^4


*/

class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        int area_a = std::abs(ax1 - ax2) * std::abs(ay1 - ay2);
        int area_b = std::abs(bx1 - bx2) * std::abs(by1 - by2);
        
        int left = std::max(ax1, bx1);
        int right = std::min(ax2, bx2);
        //if they did not overlap, it would be negative
        int x_overlap = right - left;

        int bottom = std::max(ay1, by1);
        int top = std::min(ay2, by2);
        //if they did not overlap, it would be negative
        int y_overlap = top - bottom;

        int area_overlap = 0;
        if (x_overlap > 0 && y_overlap > 0) {
            area_overlap = x_overlap * y_overlap;
        }

        return area_a + area_b - area_overlap;
    }
};