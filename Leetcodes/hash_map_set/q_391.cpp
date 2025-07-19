/*
Given an array rectangles where rectangles[i] = [xi, yi, ai, bi] represents an axis-aligned rectangle. The bottom-left point of the rectangle is (xi, yi) and the top-right point of it is (ai, bi).

Return true if all the rectangles together form an exact cover of a rectangular region.

 

Example 1:

Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
Output: true
Explanation: All 5 rectangles together form an exact cover of a rectangular region.

Example 2:

Input: rectangles = [[1,1,2,3],[1,3,2,4],[3,1,4,2],[3,2,4,4]]
Output: false
Explanation: Because there is a gap between the two rectangular regions.

Example 3:

Input: rectangles = [[1,1,3,3],[3,1,4,2],[1,3,2,4],[2,2,4,4]]
Output: false
Explanation: Because two of the rectangles overlap with each other.

 

Constraints:

    1 <= rectangles.length <= 2 * 10^4
    rectangles[i].length == 4
    -10^5 <= xi < ai <= 10^5
    -10^5 <= yi < bi <= 10^5


*/

class Solution {
private:
    bool by_map(vector<vector<int>>& rectangles) {
        std::unordered_map<long long, int> pos;

        const long long begin = 100000;
        for (std::vector<int>& x : rectangles) {
            int bottom_left_col = x[0];
            int bottom_left_row = x[1];
            int top_right_col = x[2];
            int top_right_row = x[3];

            ++pos[bottom_left_col * begin + bottom_left_row];   //for same bottom left col, different row
            --pos[bottom_left_col * begin + top_right_row];     //for same bottom left col, inner point
            --pos[top_right_col * begin + bottom_left_row];     //for same top right col, inner point
            ++pos[top_right_col * begin + top_right_row];       //for same top right col, different row
        }

        int corners = 0;
        for (auto it : pos) {
            if (it.second != 0) {
                if (std::abs(it.second) != 1) return false;

                ++corners;
            }
        }

        return corners == 4;
    }
    bool by_set(vector<vector<int>>& rectangles) {
        std::set<std::pair<int, int>> corners;
        long area = 0;

        for (const auto& rect : rectangles) {            
            pair<int, int> p1{rect[0], rect[1]};    //bottom-left
            pair<int, int> p2{rect[2], rect[1]};    //top-left
            pair<int, int> p3{rect[2], rect[3]};    //top-right
            pair<int, int> p4{rect[0], rect[3]};    //bottom-right

            for (const auto& p : {p1, p2, p3, p4}) {        
                const auto& ret = corners.insert(p);

                if (!ret.second) {
                    corners.erase(ret.first);
                }
            }
            area += (long)(p3.first - p1.first) * (long)(p3.second - p1.second);
        }

        if (corners.size() != 4) return false;

        const auto& p1 = *begin(corners);
        const auto& p3 = *rbegin(corners);  

        return area == (long)(p3.first - p1.first) * (long)(p3.second - p1.second);
    }
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        return by_map(rectangles);
        //return by_set(rectangles);
    }
};