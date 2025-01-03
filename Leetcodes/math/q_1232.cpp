/*
You are given an array coordinates, coordinates[i] = [x, y], where [x, y] represents the coordinate of a point. Check if these points make a straight line in the XY plane.

 

 

Example 1:

Input: coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
Output: true

Example 2:

Input: coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]]
Output: false

 

Constraints:

    2 <= coordinates.length <= 1000
    coordinates[i].length == 2
    -10^4 <= coordinates[i][0], coordinates[i][1] <= 10^4
    coordinates contains no duplicate point.

*/

class Solution {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        int y = 0;
        float diff_x = coordinates[0][0] - coordinates[1][0];
        float slope = 0;
        float constant = 0;
        bool vertical = false;
        if (diff_x != 0.0) {
            slope = (coordinates[0][1] - coordinates[1][1]) / (diff_x);
            constant = (coordinates[0][1]) - slope * (coordinates[0][0]);
        } else {
            vertical = true;
        }
        

        for (int i = 2; i < coordinates.size(); ++i) {
            
            if (vertical) {
                if ((coordinates[i][0] - coordinates[i - 1][0]) != 0) {
                    return false;
                }

            } else {
                y = slope * coordinates[i][0] + constant;

                if (y != coordinates[i][1]) {
                    return false;
                }
            }

            
        }

        return true;
    }
};