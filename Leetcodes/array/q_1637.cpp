/*
Given n points on a 2D plane where points[i] = [xi, yi], Return the widest vertical area between two points such that no points are inside the area.

A vertical area is an area of fixed-width extending infinitely along the y-axis (i.e., infinite height). The widest vertical area is the one with the maximum width.

Note that points on the edge of a vertical area are not considered included in the area.

 

Example 1:
​

Input: points = [[8,7],[9,9],[7,4],[9,7]]
Output: 1
Explanation: Both the red and the blue area are optimal.

Example 2:

Input: points = [[3,1],[9,0],[1,0],[1,4],[5,3],[8,8]]
Output: 3

 

Constraints:

    n == points.length
    2 <= n <= 10^5
    points[i].length == 2
    0 <= xi, yi <= 10^9


*/

class Solution {
public:
    int maxWidthOfVerticalArea(vector<vector<int>>& points) {
        std::sort(points.begin(), points.end());

        std::vector<int> countY;
        for (int i = 0; i < points.size(); ++i) {

            int now = i;
            int next = i + 1;
            while (next < points.size() && points[now][0] == points[next][0]) {
                ++next;
            }

            next -= 1;
            if (next < points.size()) {
                countY.push_back(points[next][0]);
            }

            if (i == points.size() - 1) {
                countY.push_back(points[next][0]);
            }
            
            i = next;
        }

        int maxTwo = 0;
        for (int i = 1; i < countY.size(); ++i) {
            maxTwo = std::max(maxTwo, countY[i] - countY[i - 1]);
        }

        return maxTwo;
    }
};