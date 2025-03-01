/*
You are given an array original of length n and a 2D array bounds of length n x 2, where bounds[i] = [ui, vi].

You need to find the number of possible arrays copy of length n such that:

    (copy[i] - copy[i - 1]) == (original[i] - original[i - 1]) for 1 <= i <= n - 1.
    ui <= copy[i] <= vi for 0 <= i <= n - 1.

Return the number of such arrays.

 

Example 1:

Input: original = [1,2,3,4], bounds = [[1,2],[2,3],[3,4],[4,5]]

Output: 2

Explanation:

The possible arrays are:

    [1, 2, 3, 4]
    [2, 3, 4, 5]

Example 2:

Input: original = [1,2,3,4], bounds = [[1,10],[2,9],[3,8],[4,7]]

Output: 4

Explanation:

The possible arrays are:

    [1, 2, 3, 4]
    [2, 3, 4, 5]
    [3, 4, 5, 6]
    [4, 5, 6, 7]

Example 3:

Input: original = [1,2,1,2], bounds = [[1,1],[2,3],[3,3],[2,3]]

Output: 0

Explanation:

No array is possible.

 

Constraints:

    2 <= n == original.length <= 10^5
    1 <= original[i] <= 10^9
    bounds.length == n
    bounds[i].length == 2
    1 <= bounds[i][0] <= bounds[i][1] <= 10^9


*/

class Solution {
private:
public:
    int countArrays(vector<int>& original, vector<vector<int>>& bounds) {

        int n = original.size();
    
        int lower = bounds[0][0];
        int upper = bounds[0][1];

        for (int i = 1; i < n; i++) {
            int diff = original[i] - original[i - 1];

            // Update the valid range for copy[i]
            lower = std::max(bounds[i][0], lower + diff);
            upper = std::min(bounds[i][1], upper + diff);

            // If no valid range exists, return 0
            if (lower > upper) return 0;
        }

        // The number of valid sequences
        return upper - lower + 1;
    }
};