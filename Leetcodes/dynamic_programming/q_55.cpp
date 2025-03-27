/*

*/

class Solution {
private:
    bool greedy(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return true;
        }

        int end_pos = n - 1;
        for (int i = n - 2; i >= 0; --i) {

            if (i + nums[i] >= end_pos) {
                end_pos = i;
            }
        }

        return end_pos == 0;
    }

    bool iterative(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return true;
        }

        std::vector<bool> dp(n);
        dp[0] = true;

        //dp relationship: dp[i] = (j + nums[j]) >= i && dp[j]
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (j + nums[j] >= i && dp[j]) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n - 1];
    }

    bool recursive02(vector<int>& nums, int i, std::vector<int>& mem) {
        if (mem[i] != -1) {
            return ((mem[i] == 1) ? true : false);
        }

        int maxJump = std::min(i + nums[i], (int)(nums.size() - 1));
        for (int next = i + 1; next <= maxJump; ++next) {

            if (recursive02(nums, next, mem)) {
                mem[next] = 1;
                return true;
            }
        }

        mem[i] = 2;
        return false;
    }

    int recursive(vector<int>& nums, int i, std::vector<int>& mem) {
        if (i >= nums.size() - 1) {
            return nums.size() - 1;
        }

        if (nums[i] == 0) {
            return i;
        }

        if (mem[i] != -1) {
            return mem[i];
        }

        int steps = -1;
        for (int s = nums[i]; s >= 1; --s) {
            steps = std::max(steps, recursive(nums, i + s, mem));

            if (steps >= nums.size() - 1) {
                break;
            }
        }

        mem[i] = steps;

        return mem[i];
    }
public:
    bool canJump(vector<int>& nums) {

        if (nums.size() == 1) {
            return true;
        }

        /*
        std::vector<int> mem(nums.size(), -1);
        int result = recursive(nums, 0, mem);

        return (result >= nums.size() - 1) ? true : false;
        */

        //1: good index, 2: bad index, -1: unknow
        //std::vector<int> mem(nums.size(), -1);
        //mem[mem.size() - 1] = 1;
        //return recursive02(nums, 0, mem);

        //return iterative(nums);
        return greedy(nums);
    }
};