/*
You are given an m x n binary matrix matrix.

You can choose any number of columns in the matrix and flip every cell in that column (i.e., Change the value of the cell from 0 to 1 or vice versa).

Return the maximum number of rows that have all values equal after some number of flips.

 

Example 1:

Input: matrix = [[0,1],[1,1]]
Output: 1
Explanation: After flipping no values, 1 row has all values equal.

Example 2:

Input: matrix = [[0,1],[1,0]]
Output: 2
Explanation: After flipping values in the first column, both rows have equal values.

Example 3:

Input: matrix = [[0,0,0],[0,0,1],[1,1,0]]
Output: 2
Explanation: After flipping values in the first two columns, the last two rows have equal values.

 

Constraints:

    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 300
    matrix[i][j] is either 0 or 1.


*/

class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        //store pattern frequency
        std::unordered_map<std::string, int> ptn_freq;

        for (auto& curr_row : matrix) {
            std::string ptn{ "" };

            //convert row to pattern relative to its first element
            for (int c = 0; c < curr_row.size(); ++c) {
                //'t' if it were equal to first element, 'f' otherwise
                if (curr_row[0] == curr_row[c]) {
                    ptn += "t";
                } else {
                    ptn += "f";
                }
            }

            //convert pattern to string and update its frequency in map
            ++ptn_freq[ptn];
        }

        //find the pattern with maximum frequency
        int max_freq = 0;
        for (auto& entry : ptn_freq) {
            max_freq = std::max(entry.second, max_freq);
        }

        return max_freq;
    }
};