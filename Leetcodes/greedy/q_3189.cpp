/*
Given a 2D array rooks of length n, where rooks[i] = [xi, yi] indicates the position of a rook on an n x n chess board. Your task is to move the rooks 1 cell at a time vertically or horizontally (to an adjacent cell) such that the board becomes peaceful.

A board is peaceful if there is exactly one rook in each row and each column.

Return the minimum number of moves required to get a peaceful board.

Note that at no point can there be two rooks in the same cell.

 

Example 1:

Input: rooks = [[0,0],[1,0],[1,1]]

Output: 3

Explanation:

Example 2:

Input: rooks = [[0,0],[0,1],[0,2],[0,3]]

Output: 6

Explanation:

 

Constraints:

    1 <= n == rooks.length <= 500
    0 <= xi, yi <= n - 1
    The input is generated such that there are no 2 rooks in the same cell.


*/

class Solution {
public:
    int minMoves(vector<vector<int>>& rooks) {
        return by_counting(rooks);
        //return by_greedy(rooks);
    }
private:
    int by_counting(vector<vector<int>>& rooks) {
        int moves = 0;
        int n = rooks.size();
        std::vector<int> row(n);
        std::vector<int> col(n);

        for (int i = 0; i < n; ++i) {
            ++row[rooks[i][0]];
            ++col[rooks[i][1]];
        }

        int r_moves = 0;
        int c_moves = 0;
        for (int i = 0; i < n; ++i) {
            r_moves += row[i] - 1;
            c_moves += col[i] - 1;

            moves += std::abs(r_moves) + std::abs(c_moves);
        }

        return moves;
    }
    int by_greedy(vector<vector<int>>& rooks) {
        int moves = 0;

        std::sort(rooks.begin(), rooks.end());
        for (int i = 0; i < rooks.size(); ++i) {
            moves += std::abs(rooks[i][0] - i);
        }

        std::sort(rooks.begin(), rooks.end(), 
                    [](const auto& v1, const auto& v2) { return v1[1] < v2[1]; });
        for (int i = 0; i < rooks.size(); ++i) {
            moves += std::abs(rooks[i][1] - i);
        }

        return moves;
    }
};