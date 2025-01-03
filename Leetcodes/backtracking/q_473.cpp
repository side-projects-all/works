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
public:
    bool makesquare(vector<int>& matchsticks) {
        int n = matchsticks.size();
        if (n < 4) {
            return false;
        }

        int sum = std::accumulate(matchsticks.begin(), matchsticks.end(), 0);
        if (sum % 4 != 0) {
            return false;
        }

        int per_side = sum / 4;
        int len = matchsticks.size();
        //std::vector<bool> used(len);
        std::vector<int> mem((1 << matchsticks.size()) + 1, -1);

        return recursive(matchsticks, mem, per_side, 4, 0, 0, 0);

        //return backtracking(matchsticks, used, per_side, 0, 4, 0);
    }

private:
    bool backtracking(std::vector<int>& matchsticks, std::vector<bool>& used, 
                                int& per_side, int pos, int sides, int curr_sum) {
        if (sides == 1) {
            return true;
        }

        if (curr_sum > per_side) {
            return false;
        }

        if (curr_sum == per_side) {
            return backtracking(matchsticks, used, per_side, 0, sides - 1, 0);
        }

        int prev = -1;
        for (int i = pos; i < matchsticks.size(); ++i) {
            if (used[i]) {
                continue;
            }

            if (matchsticks[i] == prev) {
                continue;
            }

            used[i] = true;
            prev = matchsticks[i];

            if (backtracking(matchsticks, used, per_side, i + 1, sides, curr_sum + matchsticks[i])) {
                return true;
            }

            used[i] = false;
        }

        return false;
    }
    
    bool recursive(std::vector<int>& matchsticks, std::vector<int>& mem, 
                                    int& per_side, int rest_sides, int curr_sum, int mask, int i) {
        
        if (rest_sides == 1) {
            return true;
        }

        if (i == matchsticks.size()) {
            return false;
        }

        if (mem[mask] != -1) {
            return mem[mask];
        }

        //find one side
        if (curr_sum == per_side) {
            return mem[mask] = recursive(matchsticks, mem, per_side, rest_sides - 1, 0, mask, 0);
        }

        for (int j = i; j < matchsticks.size(); ++j) {
            if (!(mask & (1 << j)) && matchsticks[j] + curr_sum <= per_side && 
                    recursive(matchsticks, mem, per_side, rest_sides, 
                                matchsticks[j] + curr_sum, mask | (1 << j), j + 1)) {

                return mem[mask] = true;
            }
        }

        return mem[mask] = false;
    }
    
};