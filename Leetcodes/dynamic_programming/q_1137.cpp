/*
The Tribonacci sequence Tn is defined as follows: 

T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

Given n, return the value of Tn.

 

Example 1:

Input: n = 4
Output: 4
Explanation:
T_3 = 0 + 1 + 1 = 2
T_4 = 1 + 1 + 2 = 4

Example 2:

Input: n = 25
Output: 1389537

 

Constraints:

    0 <= n <= 37
    The answer is guaranteed to fit within a 32-bit integer, ie. answer <= 2^31 - 1.

*/

class Solution {
private:
    int iterative(int n) {
        if (n <= 0) {
            return 0;
        }

        if (n == 1 || n == 2) {
            return 1;
        }

        int Tn_1 = 1;   //T(n-1);
        int Tn_2 = 1;   //T(n-2);
        int Tn_3 = 0;   //T(n-3);
        int Tn = 0; //T(n) = T(n-3) + T(n-2) + T(n-1)

        for (int t = 3; t <= n; ++t) {
           
            Tn = Tn_3 +Tn_2 + Tn_1;

            Tn_3 = Tn_2;
            Tn_2 = Tn_1;
            Tn_1 = Tn;
        }

        return Tn;
    }

    int recursive(int n, std::unordered_map<int, int>& map) {
        if (n <= 0) {
            return 0;
        }

        if (n == 1 || n == 2) {
            return 1;
        }

        if (map.find(n) != map.end()) {
            return map[n];
        }

        int val = recursive(n - 1, map) + recursive(n - 2, map) + recursive(n - 3, map);
        map[n] = val;

        return val;
    }


public:
    int tribonacci(int n) {
        //std::unordered_map<int, int> m;

        //return recursive(n, m);
        return iterative(n);
    }
};