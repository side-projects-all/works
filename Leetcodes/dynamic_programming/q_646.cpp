/*
You are given an array of n pairs pairs where pairs[i] = [lefti, righti] and lefti < righti.

A pair p2 = [c, d] follows a pair p1 = [a, b] if b < c. A chain of pairs can be formed in this fashion.

Return the length longest chain which can be formed.

You do not need to use up all the given intervals. You can select pairs in any order.

 

Example 1:

Input: pairs = [[1,2],[2,3],[3,4]]
Output: 2
Explanation: The longest chain is [1,2] -> [3,4].

Example 2:

Input: pairs = [[1,2],[7,8],[4,5]]
Output: 3
Explanation: The longest chain is [1,2] -> [4,5] -> [7,8].

 

Constraints:

    n == pairs.length
    1 <= n <= 1000
    -1000 <= lefti < righti <= 1000


*/



class Solution {
private:
    int byGreedy(vector<vector<int>>& pairs) {
        /*
        struct custom_compare {
            bool operator() (const std::vector<int>& v1, const std::vector<int>& v2) {
                return v1[1] < v2[1];
            }
        };

        std::sort(pairs.begin(), pairs.end(), custom_compare());
        int max = -1001;
        int result = 0;

        for (int i = 0; i < pairs.size(); ++i) {
            if (pairs[i][0] > max) {
                ++result;
                max = pairs[i][1];
            }
        }

        return result;
        */
        
        int n = pairs.size();
        if (n == 1) {
            return 1;
        }
        
        std::sort(pairs.begin(), pairs.end(), [](std::vector<int>& v1, std::vector<int>& v2) {
            return v1[1] < v2[1];
        });

        int max_len = 1;
        int max = pairs[0][1];
        for (int i = 1; i < n; ++i) {
            if (pairs[i][0] > max) {
                max = pairs[i][1];
                ++max_len;
            }
        }

        return max_len;
    }

    int iterative(vector<vector<int>>& pairs) {
        //edge case
        if (pairs.size() == 1) {
            return 1;
        }

        std::sort(pairs.begin(), pairs.end());
        std::vector<int> mem(pairs.size(), 1);
        int max = -1;

        //same result by starting from 1
        for (int i = 1; i < pairs.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (pairs[j][1] < pairs[i][0]) {
                    mem[i] = std::max(mem[i], 1 + mem[j]);
                }
            }

            max = std::max(max, mem[i]);
        }
        /*
        for (int i = pairs.size() - 2; i > -1; --i) {
            for (int j = i + 1; j < pairs.size(); ++j) {
                if (pairs[i][1] < pairs[j][0]) {
                    mem[i] = std::max(mem[i], 1 + mem[j]);
                }
            }

            max = std::max(max, mem[i]);
        }
        */

        return max;
    }

    int recursive(vector<vector<int>>& pairs, int i, std::vector<int>& mem) {
        if (mem[i] != -1) {
            return mem[i];
        }

        mem[i] = 1;
        for (int j = i + 1; j < pairs.size(); ++j) {
            if (pairs[i][1] < pairs[j][0]) {
                mem[i] = std::max(mem[i], 1 + recursive(pairs, j, mem));
            }
        }

        return mem[i];
    }

public:
    int findLongestChain(vector<vector<int>>& pairs) {
        /*
        std::sort(pairs.begin(), pairs.end());
        std::vector<int> mem(pairs.size(), -1);
        int max = -1;

        for (int i = 0; i < pairs.size(); ++i) {
            max = std::max(max , recursive(pairs, i, mem));
        }
        
        return max;
        */

        //return iterative(pairs);
        return byGreedy(pairs);
    }
};