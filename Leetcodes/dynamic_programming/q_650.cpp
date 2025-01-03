/*
There is only one character 'A' on the screen of a notepad. You can perform one of two operations on this notepad for each step:

    Copy All: You can copy all the characters present on the screen (a partial copy is not allowed).
    Paste: You can paste the characters which are copied last time.

Given an integer n, return the minimum number of operations to get the character 'A' exactly n times on the screen.

 

Example 1:

Input: n = 3
Output: 3
Explanation: Initially, we have one character 'A'.
In step 1, we use Copy All operation.
In step 2, we use Paste operation to get 'AA'.
In step 3, we use Paste operation to get 'AAA'.

Example 2:

Input: n = 1
Output: 0

 

Constraints:

    1 <= n <= 1000


*/


class Solution {
private:
    int iterative(int n) {
        if (n <= 1) {
            return 0;
        }
        //this dp array means minimal moves for acheiving n
        /*
        std::vector<int> mem(n + 1, 0);

        for (int i = 2; i <= n; ++i) {
            mem[i] = i;

            for (int j = i - 1; j > 1; --j) {
                if (i % j == 0) {
                    mem[i] = std::min(mem[i], mem[j] + i / j);
                }
            }
        }

        return mem[n];
        */

        int ans = 0;
        int d = 2;

        while (n > 1) {

            while (n % d == 0) {
                ans += d;
                n /= d;
            }
            
            ++d;
        }

        return ans;
    }

    int recursive(int n) {
        if (n <= 1) {
            return 0;
        }

        int moves = n;
        for (int i = n - 1; i > 1; --i) {
            if (n % i == 0) {
                moves = std::min(moves, recursive(n / i) + i);
            }
        }

        return moves;
    }
public:
    int minSteps(int n) {
        //return recursive(n);
        return iterative(n);
    }
};