/*
You are given k identical eggs and you have access to a building with n floors labeled from 1 to n.

You know that there exists a floor f where 0 <= f <= n such that any egg dropped at a floor higher than f will break, and any egg dropped at or below floor f will not break.

Each move, you may take an unbroken egg and drop it from any floor x (where 1 <= x <= n). If the egg breaks, you can no longer use it. However, if the egg does not break, you may reuse it in future moves.

Return the minimum number of moves that you need to determine with certainty what the value of f is.

 

Example 1:

Input: k = 1, n = 2
Output: 2
Explanation: 
Drop the egg from floor 1. If it breaks, we know that f = 0.
Otherwise, drop the egg from floor 2. If it breaks, we know that f = 1.
If it does not break, then we know f = 2.
Hence, we need at minimum 2 moves to determine with certainty what the value of f is.

Example 2:

Input: k = 2, n = 6
Output: 3

Example 3:

Input: k = 3, n = 14
Output: 4

 

Constraints:

    1 <= k <= 100
    1 <= n <= 10^4


*/

class Solution {
private:
    int recursive_byBS(int k, int n, std::vector<std::vector<int>>& mem) {
        if (mem[n][k] != -1) {
            return mem[n][k];
        }
        
        //base case
        if (n == 0) {
            mem[n][k] = 0;

            return 0;
        } else if (k == 1) {
            mem[n][k] = n;

            return n;
        }

        int left = 1;
        int right = n;
        while (left + 1 < right) {
            int x = left + (right - left) / 2;
            int t1 = recursive_byBS(k - 1, x - 1, mem);
            int t2 = recursive_byBS(k, n - x, mem);

            if (t1 < t2) {
                left = x;
            } else if (t1 > t2) {
                right = x;
            } else {
                left = right = x;
            }
        }

        int ans = 1 + std::min(std::max(recursive_byBS(k - 1, left - 1, mem), 
                                            recursive_byBS(k, n - left, mem)), 
                                std::max(recursive_byBS(k - 1, right - 1, mem), 
                                            recursive_byBS(k, n - right, mem)));

        return mem[n][k] = ans;
    }
public:
    int superEggDrop(int k, int n) {
        std::vector<std::vector<int>> mem(n + 1, std::vector<int>(k + 1, -1));
        return recursive_byBS(k, n, mem);
    }
};