/*
We build a table of n rows (1-indexed). We start by writing 0 in the 1st row. Now in every subsequent row, we look at the previous row and replace each occurrence of 0 with 01, and each occurrence of 1 with 10.

    For example, for n = 3, the 1st row is 0, the 2nd row is 01, and the 3rd row is 0110.

Given two integer n and k, return the kth (1-indexed) symbol in the nth row of a table of n rows.

 

Example 1:

Input: n = 1, k = 1
Output: 0
Explanation: row 1: 0

Example 2:

Input: n = 2, k = 1
Output: 0
Explanation: 
row 1: 0
row 2: 01

Example 3:

Input: n = 2, k = 2
Output: 1
Explanation: 
row 1: 0
row 2: 01

 

Constraints:

    1 <= n <= 30
    1 <= k <= 2n - 1


*/

class Solution {
public:
    int kthGrammar(int n, int k) {
        //std::vector<int> result = recursive(n);

        //return result[k - 1];
        //return recursive2(n, k);
        //return recursive3(n, k);
        return final_fun(n, k);
    }

private:
    int final_fun(int n, int k) {
        return __builtin_popcount(k - 1) % 2;
    }

    int recursive3(int n, int k) {
        if (n == 1) {
            return 0;
        }

        if (k <= (1 << (n - 2))) {
            return recursive3(n - 1, k);
        }
        return recursive3(n - 1, k - (1 << (n - 2))) ^ 1;
    }

    int recursive2(int n, int k) {
        if (n == 1) {
            return 0;
        }

        return (~k & 1) ^ recursive2(n - 1, (k + 1) / 2);
    }

    std::vector<int> recursive(int n) {
        if (n == 1) {
            return std::vector<int>(1, 0);
        }

        std::vector<int> now = recursive(n - 1);
        
        int len = now.size();
        for (int i = 0; i < len; ++i) {
            if (now[i] == 0) {
                now.push_back(1);
            } else {
                now.push_back(0);
            }
            
        }

        return now;
    }
};