/*
Given an integer array nums and two integers lower and upper, return the number of range sums that lie in [lower, upper] inclusive.

Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j inclusive, where i <= j.

 

Example 1:

Input: nums = [-2,5,-1], lower = -2, upper = 2
Output: 3
Explanation: The three ranges are: [0,0], [2,2], and [0,2] and their respective sums are: -2, -1, 2.

Example 2:

Input: nums = [0], lower = 0, upper = 0
Output: 1

 

Constraints:

    1 <= nums.length <= 10^5
    -2^31 <= nums[i] <= 231 - 1
    -10^5 <= lower <= upper <= 10^5
    The answer is guaranteed to fit in a 32-bit integer.


*/

class Solution {
private:
    std::vector<int> tree;
    int tree_len;
    void build_tree() {

        tree.resize(tree_len);

        for (int i = 0; i < tree_len - 1; ++i) {
            update(i, 1);
        }
    }

    void update(int i, int val) {
        ++i;    //do not forget the one index diff

        while (i < tree_len) {
            tree[i] += val;
            i += i & -i;
        }
    }

    int query(int i) {
        ++i;
        
        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= i & -i;
        }

        return sum;
    }

public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {

        int n = nums.size() + 1;

        std::vector<long> prefix_sum(n);
        for (int i = 0; i < n - 1; ++i) {
            prefix_sum[i + 1] = nums[i] + prefix_sum[i];
        }

        std::vector<long> sorted_sum(prefix_sum);
        std::sort(sorted_sum.begin(), sorted_sum.end());

        tree_len = n + 1;
        build_tree();

        /*  
        important idea
        sum(i,j) = sum(0,j)-sum(0,i-1), where i <= j
        lower <= sum(i, j) <= upper

        then we have => lower + sum(0,i-1) <= sum(0,j) <= upper + sum(0, i-1)
        */

        int cnt = 0;
        for (const auto& s : prefix_sum) {
            int i = std::lower_bound(sorted_sum.begin(), sorted_sum.end(), s) - sorted_sum.begin();
            //lower bound
            int lb = std::lower_bound(sorted_sum.begin(), sorted_sum.end(), s + lower) - sorted_sum.begin();
            //upper bound
            int ub = std::upper_bound(sorted_sum.begin(), sorted_sum.end(), s + upper) - sorted_sum.begin() - 1;

            update(i, -1);  //this prefix_sum at i is already used, we need to remove this its counting
            cnt += query(ub) - query(lb - 1);
        }
        return cnt;
    }
};