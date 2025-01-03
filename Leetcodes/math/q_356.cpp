/*
Given n points on a 2D plane, find if there is such a line parallel to the y-axis that reflects the given points symmetrically.

In other words, answer whether or not if there exists a line that after reflecting all points over the given line, the original points' set is the same as the reflected ones.

Note that there can be repeated points.

 

Example 1:

Input: points = [[1,1],[-1,1]]
Output: true
Explanation: We can choose the line x = 0.

Example 2:

Input: points = [[1,1],[-1,-1]]
Output: false
Explanation: We can't choose a line.

 

Constraints:

    n == points.length
    1 <= n <= 10^4
    -108 <= points[i][j] <= 10^8

 

Follow up: Could you do better than O(n^2)?

*/

class Solution {
private:
    struct MyHash {
        std::size_t operator()(const std::pair<int, int>& p) const noexcept {
            std::size_t h1 = std::hash<int>{}(p.first);
            std::size_t h2 = std::hash<int>{}(p.second);
            return h1 ^ (h2 << 1); // or use boost::hash_combine
        }
    };
public:
    bool isReflected(vector<vector<int>>& points) {
        int n = points.size();
        if (n == 1) {
            return true;
        }

        std::unordered_map<std::pair<float, float>, int, MyHash> m;
        int min_x = INT_MAX;
        int max_x = INT_MIN;
        for (int i = 0; i < n; ++i) {
            min_x = std::min(min_x, points[i][0]);
            max_x = std::max(max_x, points[i][0]);
            ++m[{points[i][0] * 1.0, points[i][1] * 1.0 }];
        }

        float mid_x = min_x + (max_x - min_x) / 2.0;

        for (int i = 0; i < n; ++i) {
            std::pair<float, float> p{ 2.0 * mid_x - points[i][0], points[i][1] };
            
            if (m.find(p) == m.end()) {
                return false;
            }
        }


        return true;
    }
};