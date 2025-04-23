/*
A frog is crossing a river. The river is divided into some number of units, and at each unit, there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the water.

Given a list of stones positions (in units) in sorted ascending order, determine if the frog can cross the river by landing on the last stone. Initially, the frog is on the first stone and assumes the first jump must be 1 unit.

If the frog's last jump was k units, its next jump must be either k - 1, k, or k + 1 units. The frog can only jump in the forward direction.

 

Example 1:

Input: stones = [0,1,3,5,6,8,12,17]
Output: true
Explanation: The frog can jump to the last stone by jumping 1 unit to the 2nd stone, then 2 units to the 3rd stone, then 2 units to the 4th stone, then 3 units to the 6th stone, 4 units to the 7th stone, and 5 units to the 8th stone.

Example 2:

Input: stones = [0,1,2,3,4,8,9,11]
Output: false
Explanation: There is no way to jump to the last stone as the gap between the 5th and 6th stone is too large.

 

Constraints:

    2 <= stones.length <= 2000
    0 <= stones[i] <= 2^31 - 1
    stones[0] == 0
    stones is sorted in a strictly increasing order.


*/

class Solution {
private:
    bool by_iterative_dp(vector<int>& stones) {

        int n = stones.size();
        if (stones[0] + 1 != stones[1]) {
            return false;
        }

        std::vector<std::vector<int>> dp(n, std::vector<int>(n));
        dp[0][1] = 1;

        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {

                int distance = stones[j] - stones[i];
                if (distance > i + 1) {
                    break;
                }

                if (dp[i][distance]) {

                    if (j == n - 1) {
                        return true;
                    }

                    dp[j][distance - 1] = 1;
                    dp[j][distance] = 1;
                    dp[j][distance + 1] = 1;
                }
            }
        }

        return false;
        

        /*
        std::unordered_map<int, int> stones_pos;
        for (int i = 0; i < n; ++i) {
            stones_pos[stones[i]] = i;
        }

        //index and prev_jump
        std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(n + 1));
        dp[0][0] = true;

        for (int i = 0; i < n; ++i) {
            for (int prev_jump = 0; prev_jump <= n; ++prev_jump) {

                if (dp[i][prev_jump]) {

                    //find next stone
                    if (stones_pos[stones[i] + prev_jump]) {
                        dp[stones_pos[stones[i] + prev_jump]][prev_jump] = true;
                    }

                    if (stones_pos[stones[i] + prev_jump + 1]) {
                        dp[stones_pos[stones[i] + prev_jump + 1]][prev_jump + 1] = true;
                    }

                    if (stones_pos[stones[i] + prev_jump - 1]) {
                        dp[stones_pos[stones[i] + prev_jump - 1]][prev_jump - 1] = true;
                    }
                }
            }
        }

        for (int prev_jump = 0; prev_jump <= n; ++prev_jump) {
            if (dp[n - 1][prev_jump]) {
                return true;
            }
        }

        return false;
        */
    }
    bool recursive(vector<int>& stones, std::vector<std::vector<int>>& mem, int pos, int prev_jump) {
        int n = stones.size();

        if (mem[pos][prev_jump] != -1) {
            return mem[pos][prev_jump];
        }

        bool ans = false;
        for (int jump = prev_jump - 1; jump <= prev_jump + 1; ++jump) {
            if (jump <= 0) {
                continue;
            }

            int next = std::lower_bound(stones.begin(), stones.end(), jump + stones[pos]) - stones.begin();

            if (next != n && stones[next] == jump + stones[pos]) {

                if (next == n - 1 && stones[next] == jump + stones[pos]) {
                    ans = true;
                    break;
                    
                } else if (stones[next] == jump + stones[pos]) {
                    ans = ans || recursive(stones, mem, next, jump);
                }
            }
        }

        return mem[pos][prev_jump] = ans;
    }
    bool by_recursive_dp(vector<int>& stones) {
        int n = stones.size();
        if (n == 2) {
            return stones[1] == 1;
        }

        std::vector<std::vector<int>> mem(n, std::vector<int>(n, -1));

        return recursive(stones, mem, 0, 0);
    }
public:
    bool canCross(vector<int>& stones) {
        //return by_recursive_dp(stones);
        return by_iterative_dp(stones);
    }
};