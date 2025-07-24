/*
You are given a 2D integer array points, where points[i] = [xi, yi] represents the coordinates of the ith point on the Cartesian plane.

A horizontal trapezoid is a convex quadrilateral with at least one pair of horizontal sides (i.e. parallel to the x-axis). Two lines are parallel if and only if they have the same slope.

Return the number of unique horizontal trapezoids that can be formed by choosing any four distinct points from points.

Since the answer may be very large, return it modulo 109 + 7.

 

Example 1:

Input: points = [[1,0],[2,0],[3,0],[2,2],[3,2]]

Output: 3

Explanation:

There are three distinct ways to pick four points that form a horizontal trapezoid:

    Using points [1,0], [2,0], [3,2], and [2,2].
    Using points [2,0], [3,0], [3,2], and [2,2].
    Using points [1,0], [3,0], [3,2], and [2,2].

Example 2:

Input: points = [[0,0],[1,0],[0,1],[2,1]]

Output: 1

Explanation:

There is only one horizontal trapezoid that can be formed.

 

Constraints:

    4 <= points.length <= 10^5
    –10^8 <= xi, yi <= 10^8
    All points are pairwise distinct.


*/

class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        const int mod = 1e9 + 7;
        std::unordered_map<int, int> y_cnt;
        for (auto& p : points) {
            ++y_cnt[p[1]];
        }

        std::vector<long long> pairs;   //those same rows, calculate the total combination
        for (auto& [y, cnt] : y_cnt) {
            if (cnt >= 2) {
                long long v = (long long)cnt * (cnt - 1) / 2;
                pairs.push_back(v);
            }
        }

        long long total_pairs = 0;
        long long pairs_square_sum = 0;
        for (long long p : pairs) {
            total_pairs = (total_pairs + p) % mod;
            pairs_square_sum = (pairs_square_sum + p * p % mod) % mod;
        }
        long long ans = (total_pairs * total_pairs % mod - pairs_square_sum + mod) % mod;   //add mod to avoid negative
        ans = ans * ((mod + 1) / 2) % mod;
        return ans;
        /*
        std::vector<std::pair<int, int>> ys_cnts;
        for (auto& [y, cnt] : y_cnt) {
            if (cnt >= 2) {
                ys_cnts.push_back({y, cnt});
            }
        }

        int n = ys_cnts.size();
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            int combination_i = ys_cnts[i].second;
            long long pairs_i = combination_i * (combination_i - 1) / 2;

            for (int j = i + 1; j < n; ++j) {
                int combination_j = ys_cnts[j].second;
                long long pairs_j = combination_j * (combination_j - 1) / 2;
                ans = (ans + (pairs_i * pairs_j) % mod) % mod;
            }
        }

        return ans;
        */
    }
};