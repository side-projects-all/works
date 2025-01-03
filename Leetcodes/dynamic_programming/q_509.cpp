/*
The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,

F(0) = 0, F(1) = 1
F(n) = F(n - 1) + F(n - 2), for n > 1.

Given n, calculate F(n).

 

Example 1:

Input: n = 2
Output: 1
Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.

Example 2:

Input: n = 3
Output: 2
Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.

Example 3:

Input: n = 4
Output: 3
Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.

 

Constraints:

    0 <= n <= 30


*/

class Solution {
public:
    int fib(int n) {
        
        //return iterative(n);
        return recursive(n);
    }
private:
    std::unordered_map<int, int> mem = std::unordered_map<int, int>();

    int recursive(int n) {
        if (n == 0) {
            return 0;
        }

        if (n == 1) {
            return 1;
        }

        if (mem.find(n) != mem.end()) {
            return mem[n];
        }

        int tmp = recursive(n - 1) + recursive(n - 2);
        mem[n] = tmp;

        return mem[n];
    }

    int iterative(int n) {
        if (n == 0) {
            return 0;
        }

        if (n == 1) {
            return 1;
        }
        
        int fn_1 = 0;
        int fn_2 = 1;
        int fn = 0;
        int t = 0;

        for (int i = 2; i <=n; ++i) {
            fn = fn_2 + fn_1;
            t = fn_2;
            fn_2 = fn;
            fn_1 = t;
        }

        return fn;
    }
};