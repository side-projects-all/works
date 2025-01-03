/*
You are given an array of non-overlapping axis-aligned rectangles rects where rects[i] = [ai, bi, xi, yi] indicates that (ai, bi) is the bottom-left corner point of the ith rectangle and (xi, yi) is the top-right corner point of the ith rectangle. Design an algorithm to pick a random integer point inside the space covered by one of the given rectangles. A point on the perimeter of a rectangle is included in the space covered by the rectangle.

Any integer point inside the space covered by one of the given rectangles should be equally likely to be returned.

Note that an integer point is a point that has integer coordinates.

Implement the Solution class:

    Solution(int[][] rects) Initializes the object with the given rectangles rects.
    int[] pick() Returns a random integer point [u, v] inside the space covered by one of the given rectangles.

 

Example 1:

Input
["Solution", "pick", "pick", "pick", "pick", "pick"]
[[[[-2, -2, 1, 1], [2, 2, 4, 6]]], [], [], [], [], []]
Output
[null, [1, -2], [1, -1], [-1, -2], [-2, -2], [0, 0]]

Explanation
Solution solution = new Solution([[-2, -2, 1, 1], [2, 2, 4, 6]]);
solution.pick(); // return [1, -2]
solution.pick(); // return [1, -1]
solution.pick(); // return [-1, -2]
solution.pick(); // return [-2, -2]
solution.pick(); // return [0, 0]

 

Constraints:

    1 <= rects.length <= 100
    rects[i].length == 4
    -10^9 <= ai < xi <= 10^9
    -10^9 <= bi < yi <= 10^9
    xi - ai <= 2000
    yi - bi <= 2000
    All the rectangles do not overlap.
    At most 104 calls will be made to pick.


*/

class Solution {
private:
    std::uniform_int_distribution<int> uni;
    std::mt19937 gen;
    std::vector<std::vector<int>> rects;
    std::vector<int> prefixes;

public:
    Solution(vector<vector<int>>& rects) : rects{ rects }, gen{ std::random_device{}() } {
        
        prefixes.resize(rects.size());
        prefixes[0] = (rects[0][2] - rects[0][0] + 1) * (rects[0][3] - rects[0][1] + 1);
        for (int r = 1; r < rects.size(); ++r) {
            //included the points on the perimeter
            prefixes[r] = (rects[r][2] - rects[r][0] + 1) * (rects[r][3] - rects[r][1] + 1) + prefixes[r - 1];
        }

        uni.param(std::uniform_int_distribution<int>::param_type(1, prefixes[rects.size() - 1]));
    }
    
    vector<int> pick() {
        int ran_area = uni(gen);    //random area
        int i = std::lower_bound(prefixes.begin(), prefixes.end(), ran_area) - prefixes.begin();

        const auto rect = rects[i];
        int ran_x = std::uniform_int_distribution<int>(rect[0], rect[2])(gen);
        int ran_y = std::uniform_int_distribution<int>(rect[1], rect[3])(gen);

        return { ran_x, ran_y };
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(rects);
 * vector<int> param_1 = obj->pick();
 */