/*
Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane, return the maximum number of points that lie on the same straight line.

 

Example 1:

Input: points = [[1,1],[2,2],[3,3]]
Output: 3

Example 2:

Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4

 

Constraints:

    1 <= points.length <= 300
    points[i].length == 2
    -10^4 <= xi, yi <= 10^4
    All the points are unique.


*/

class Solution {
private:
    int by_slope(vector<vector<int>>& points, int n) {
        int ans = 2;
        for (int i = 0; i < n; ++i) {
            std::unordered_map<double, int> cnt;
            int parallel = 1;
            int coincide = 1;

            for (int j = i + 1; j < n; ++j) {
                if (points[i][0] == points[j][0] && points[i][1] == points[j][1]) {
                    ++coincide;

                } else if (points[i][0] == points[j][0]) {
                    ++parallel;

                } else {
                    double slope = ((double)(points[j][1] - points[i][1]) / 
                                        (double)(points[j][0] - points[i][0]));
                    ++cnt[slope];
                }
            }

            int points = 0;
            for (auto [slope, count] : cnt) {
                points = std::max(points, count);
            }

            ans = std::max(parallel, std::max(points + coincide, ans));
        }

        return ans;
    }
    int by_arctan(vector<vector<int>>& points, int n) {
        int ans = 2;
        for (int i = 0; i < n; ++i) {
            std::unordered_map<double, int> cnt;

            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    ++cnt[std::atan2(points[j][1] - points[i][1], points[j][0] - points[i][0])];
                }
            }

            for (auto [arctan, count] : cnt) {
                ans = std::max(ans, count + 1);
            }
        }

        return ans;
    }
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if (n == 1) {
            return 1;
        }

        //return by_arctan(points, n);
        
        return by_slope(points, n);
    }
};