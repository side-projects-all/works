/*
In a row of dominoes, tops[i] and bottoms[i] represent the top and bottom halves of the ith domino. (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)

We may rotate the ith domino, so that tops[i] and bottoms[i] swap values.

Return the minimum number of rotations so that all the values in tops are the same, or all the values in bottoms are the same.

If it cannot be done, return -1.

 

Example 1:

Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
Output: 2
Explanation: 
The first figure represents the dominoes as given by tops and bottoms: before we do any rotations.
If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, as indicated by the second figure.

Example 2:

Input: tops = [3,5,1,2,3], bottoms = [3,6,3,3,4]
Output: -1
Explanation: 
In this case, it is not possible to rotate the dominoes to make one row of values equal.

 

Constraints:

    2 <= tops.length <= 2 * 10^4
    bottoms.length == tops.length
    1 <= tops[i], bottoms[i] <= 6


*/

class Solution {
private:
    int min_rotations(vector<int>& tops, vector<int>& bottoms, int& n, int num) {

        int top_rotations = 0;
        int bottoms_rotations = 0;
        for (int i = 0; i < n; ++i) {

            if (tops[i] != num && bottoms[i] != num) {
                return -1;
            }

            if (tops[i] != num) {
                ++top_rotations;
            }

            if (bottoms[i] != num) {
                ++bottoms_rotations;
            }
        }

        return std::min(top_rotations, bottoms_rotations);
    }
    int by_greedy(vector<int>& tops, vector<int>& bottoms) {
        int n = tops.size();

        int r1 = min_rotations(tops, bottoms, n, tops[0]);
        if (r1 != -1 || tops[0] == bottoms[0]) {
            return r1;
        }

        int r2 = min_rotations(tops, bottoms, n, bottoms[0]);
        return r2;
    }
public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        return by_greedy(tops, bottoms);
    }
};