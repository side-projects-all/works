/*
Given an integer n, return the least number of perfect square numbers that sum to n.

A perfect square is an integer that is the square of an integer; in other words, it is the product of some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.

 

Example 1:

Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.

Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.

 

Constraints:

    1 <= n <= 10^4


*/

class Solution {
private:
    int recursive(int n) {
        std::vector<int> mem(n + 1, 10001);

        std::function<int(int)> recurr = [&](int rest_n) -> int {
            if (rest_n <= 0) {
                return 0;
            }

            if (mem[rest_n] != 10001) {
                return mem[rest_n];
            }

            int min_cnt = 10001;
            int max_sqrt = std::sqrt(rest_n);
            for (int i = max_sqrt; i >= 1; --i) {

                int cnt = 0;
                if (i * i <= rest_n) {
                    cnt = 1 + recurr(rest_n - i * i);
                }

                min_cnt = std::min(min_cnt, cnt);
            }

            return mem[rest_n] = min_cnt;
        };

        return recurr(n);
    }

    int iterative_better(int n) {
        /*
        std::vector<int> mem(n + 1, 10001);
        mem[0] = 0;

        for (int i = 1; i * i <= n; ++i) {

            int sq = i * i;
            for (int j = sq; j < n + 1; ++j) {

                mem[j] = std::min(mem[j], 1 + mem[j - sq]);
            }
        }

        return mem[n];
        */
        
        std::vector<int> dp(n + 1, n + 1);  //it means the count of minimal number of perfect squares
        dp[0] = 0;

        for (int i = 1; i * i <= n; ++i) {
            int square = i * i;

            for (int sq = square; sq <= n; ++sq) {
                dp[sq] = std::min(dp[sq], 1 + dp[sq - square]);
            }
        }

        return dp[n];
    }
    int iterative(int n) {
        std::vector<int> mem(n + 1, 10001);
        mem[0] = 0;

        int max_square_index = (int)std::sqrt(n) + 1;
        std::vector<int> square_nums(max_square_index);
        for (int i = 1; i < max_square_index; ++i) {
            square_nums[i] = i * i;
        }

        for (int i = 1; i <= n; ++i) {
            for (int s = 1; s < max_square_index; ++s) {
                if (i < square_nums[s]) {
                    break;
                }

                mem[i] = std::min(mem[i], mem[i - square_nums[s]] + 1);
            }
        }

        return mem[n];
    }
public:
    int numSquares(int n) {
        //return iterative(n);

        //return recursive(n);

        return iterative_better(n);
    }
};