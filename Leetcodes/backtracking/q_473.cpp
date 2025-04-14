/*
You are given an integer array matchsticks where matchsticks[i] is the length of the ith matchstick. You want to use all the matchsticks to make one square. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.

Return true if you can make this square and false otherwise.

 

Example 1:

Input: matchsticks = [1,1,2,2,2]
Output: true
Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.

Example 2:

Input: matchsticks = [3,3,3,3,4]
Output: false
Explanation: You cannot find a way to form a square with all the matchsticks.

 

Constraints:

    1 <= matchsticks.length <= 15
    1 <= matchsticks[i] <= 10^8


*/

class Solution {
private:
    bool recursive(vector<int>& matchsticks, int& n, std::vector<int>& mem, int& side_len, int curr_len, int rest_sides, int pos, int used) {
        if (rest_sides == 1) {
            return true;
        }

        //this case is necessary for efficiency
        if (pos == n) {
            return false;
        }

        if (mem[used] != -1) {
            return mem[used];
        }

        if (curr_len == side_len) {
            return mem[used] = recursive(matchsticks, n, mem, side_len, 0, rest_sides - 1, 0, used);
        }

        for (int i = pos; i < n; ++i) {

            if (!(used & (1 << i)) && curr_len + matchsticks[i] <= side_len && 
                    recursive(matchsticks, n, mem, side_len, curr_len + matchsticks[i], rest_sides, i, used ^ (1 << i))) {

                return mem[used] = true;
            }
        }

        return false;
    }
    bool by_back_tracking(vector<int>& matchsticks) {
        int n = matchsticks.size();
        if (n < 4) {
            return false;
        }

        int sum = std::accumulate(matchsticks.begin(), matchsticks.end(), 0);
        if (sum % 4 != 0) {
            return false;
        }

        int side_len = sum / 4;
        std::vector<int> mem(1 << n, -1);
        return recursive(matchsticks, n, mem, side_len, 0, 4, 0, 0);
    }
public:
    bool makesquare(vector<int>& matchsticks) {
        return by_back_tracking(matchsticks);
    }
};