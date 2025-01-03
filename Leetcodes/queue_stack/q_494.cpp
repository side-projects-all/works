/*
*/

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        p_sum = std::accumulate(nums.begin(), nums.end(), 0);
        memo = std::vector<std::vector<int>>(nums.size(), std::vector<int>(2 * p_sum + 1, -1));
        p_nums = nums;
        p_target = target;
        
        return topDown(0, 0);
    }
    
private:
    //for memo
    std::vector<std::vector<int>> memo;
    std::vector<int> p_nums;
    int p_target;
    int p_sum;
    
    //top down approach like dfs
    int topDown(int index, int sum) {
        if (index == p_nums.size()) {
            if (sum == p_target) {
                return 1;
            } else {
                return 0;
            }
            
        } else {
            if (memo[index][sum + p_sum] != -1) {
                return memo[index][sum + p_sum];
            }
            
            int add = topDown(index + 1, sum + p_nums[index]);
            int substract = topDown(index + 1, sum - p_nums[index]);
            memo[index][sum + p_sum] = add + substract;
            
            return memo[index][sum + p_sum];
        }
    }
    
};