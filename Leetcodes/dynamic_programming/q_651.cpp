/*
Imagine you have a special keyboard with the following keys:

    A: Print one 'A' on the screen.
    Ctrl-A: Select the whole screen.
    Ctrl-C: Copy selection to buffer.
    Ctrl-V: Print buffer on screen appending it after what has already been printed.

Given an integer n, return the maximum number of 'A' you can print on the screen with at most n presses on the keys.

 

Example 1:

Input: n = 3
Output: 3
Explanation: We can at most get 3 A's on screen by pressing the following key sequence:
A, A, A

Example 2:

Input: n = 7
Output: 9
Explanation: We can at most get 9 A's on screen by pressing following key sequence:
A, A, A, Ctrl A, Ctrl C, Ctrl V, Ctrl V

 

Constraints:

    1 <= n <= 50


*/

class Solution {
private:
    int iterative(int n) {
        if (n <= 3) {
            return n;
        }

        std::vector<int> mem(n + 1, 0);
        mem[1] = 1;
        mem[2] = 2;
        

        for (int i = 3; i <= n; ++i) {
            mem[i] = i;

            for (int j = 1; j < i - 2; ++j) {
                mem[i] = std::max(mem[i], mem[j] * (i - j - 1));
            }
        }

        return mem[n];
    }
    int recursive(int n) {
        if (n <= 3) {
            return n;
        }

        int cnt = n;
        //int i means number of A pressed
        //why i is smaller than n - 2? because we need at least 2 press for ctrl-A and ctrl-C !!
        for (int i = 3; i < n - 2; ++i) {
            //compare only pressing A( will get number n of A) with i of A times the number of ctrl-V!!!
            //recursive(i)                  <- already printed A
            //recursive(i) * (n - 2 - i)    <- A by our ctrl-V operation
            //plus them together!!
            //it will be recursive(i) * (n - 1 - i)
            cnt = std::max(cnt, recursive(i) * (n - 1 - i));
        }

        return cnt;
    }

    int iterative_from_recursive_why(int n) {
        /*
        std::vector<int> mem(n + 1);
        std::iota(mem.begin(), mem.end(), 0);

        for (int i = 7; i <= n; ++i) {
            for (int j = 1; j < i - 2; ++j) {
                int total = mem[j] + (i - j - 2) * mem[j];
                mem[i] = std::max(mem[i], total);
            }
        }

        return mem[n];
        */

        std::vector<int> mem(n + 1, 0);
        std::iota(mem.begin(), mem.end(), 0);

        for (int i = 7; i <= n; ++i) {            

            mem[i] = std::max(3 * mem[i - 4], 4 * mem[i - 5]);
        }

        return mem[n];
        
    }

    int recursive_why(int n) {
        if (n <= 6) {
            return n;
        }
        
        //still do not understand why 4 and 5
        return std::max(3 * recursive_why(n - 4), 4 * recursive_why(n - 5));
    }
public:
    int maxA(int n) {
        //corner case
        if (n <= 6) {
            return n;
        }
        //return iterative_from_recursive_why(n);

        //return recursive_why(n);
        //return recursive(n);
        return iterative(n);
    }
};