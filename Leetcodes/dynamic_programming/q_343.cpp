/*
Given an integer n, break it into the sum of k positive integers, where k >= 2, and maximize the product of those integers.

Return the maximum product you can get.

 

Example 1:

Input: n = 2
Output: 1
Explanation: 2 = 1 + 1, 1 × 1 = 1.

Example 2:

Input: n = 10
Output: 36
Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.

 

Constraints:

    2 <= n <= 58


*/

class Solution {
private:
    int iterative(int n) {
        std::vector<int> mem(n + 1, 0);
        std::iota(mem.begin(), mem.begin() + 4, 0);

        for (int num = 4; num <= n; ++num) {
            int maxProd = 0;

            for (int j = 2; j < num; ++j) {
                maxProd = std::max(maxProd, j * mem[num - j]);
            }
            
            mem[num] = maxProd;
        }

        return mem[n];
    }
    int recursive(int n, std::vector<int>& mem) {
        //base case
        if (n <= 1) {
            return 1;
        }

        if (mem[n] != -1) {
            return mem[n];
        }

        int maxProd = n;
        for (int k = 2; k < n; ++k) {
            
            maxProd = std::max(maxProd, k * recursive(n - k, mem));
        }

        mem[n] = maxProd;

        return maxProd;
    }

    int iterative_naive(int n) {
        if (n <= 2) {
            return 1;
        }

        int maxProd = 0;
        for (int i = 2; i < n; ++i) {
            int t = n / i;

            int r = 0 ;
            for (int j = 1; j <= t; ++j) {

                int rest = (n - j * i);
                rest = (rest > 0) ? rest : 1;
                r = std::max(r, (int)std::pow(i, j) * rest);
            }
            
            maxProd = std::max(maxProd, r);
        }

        return maxProd;
    }
public:
    int integerBreak(int n) {
        
        if (n <= 3) {
            return n - 1;
        }

        
        //std::vector<int> mem(n + 1, -1);
        //return recursive(n, mem);
        

        //return iterative_naive(n);
        return iterative(n);
    }
};