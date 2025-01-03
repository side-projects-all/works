/*
You are given an array of points on the X-Y plane points where points[i] = [xi, yi]. The points form a polygon when joined sequentially.

Return true if this polygon is convex and false otherwise.

You may assume the polygon formed by given points is always a simple polygon. In other words, we ensure that exactly two edges intersect at each vertex and that edges otherwise don't intersect each other.

 

Example 1:

Input: points = [[0,0],[0,5],[5,5],[5,0]]
Output: true

Example 2:

Input: points = [[0,0],[0,10],[10,10],[10,0],[5,5]]
Output: false

 

Constraints:

    3 <= points.length <= 10^4
    points[i].length == 2
    -10^4 <= xi, yi <= 10^4
    All the given points are unique.


*/

class Solution {
public:
    bool isConvex(vector<vector<int>>& points) {
        int n = points.size();
        long long prevCrossProduct = 0;

        for (int i = 0; i < n; ++i) {
            // Get three consecutive points: A, B, and C
            std::vector<int>& A = points[i];
            std::vector<int>& B = points[(i + 1) % n];  // Next point
            std::vector<int>& C = points[(i + 2) % n];  // Next to next point

            // Calculate the cross product of vectors AB and BC
            long long crossProduct = (long long)(B[0] - A[0]) * (C[1] - B[1]) -
                                     (long long)(B[1] - A[1]) * (C[0] - B[0]);

            // If crossProduct is 0, the points are collinear, we skip it
            if (crossProduct != 0) {
                // Check if the crossProduct signs differ
                if (prevCrossProduct != 0 && crossProduct * prevCrossProduct < 0) {
                    return false;
                }
                // Update previous cross product value
                prevCrossProduct = crossProduct;
            }
        }

        return true;  // All cross products had the same sign
    }
};
