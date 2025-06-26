/*
You are given three integers n, m, k. A good array arr of size n is defined as follows:

    Each element in arr is in the inclusive range [1, m].
    Exactly k indices i (where 1 <= i < n) satisfy the condition arr[i - 1] == arr[i].

Return the number of good arrays that can be formed.

Since the answer may be very large, return it modulo 109 + 7.

 

Example 1:

Input: n = 3, m = 2, k = 1

Output: 4

Explanation:

    There are 4 good arrays. They are [1, 1, 2], [1, 2, 2], [2, 1, 1] and [2, 2, 1].
    Hence, the answer is 4.

Example 2:

Input: n = 4, m = 2, k = 2

Output: 6

Explanation:

    The good arrays are [1, 1, 1, 2], [1, 1, 2, 2], [1, 2, 2, 2], [2, 1, 1, 1], [2, 2, 1, 1] and [2, 2, 2, 1].
    Hence, the answer is 6.

Example 3:

Input: n = 5, m = 2, k = 0

Output: 2

Explanation:

    The good arrays are [1, 2, 1, 2, 1] and [2, 1, 2, 1, 2]. Hence, the answer is 2.

 

Constraints:

    1 <= n <= 10^5
    1 <= m <= 10^5
    0 <= k <= n - 1


*/

const int mod = 1e9 + 7;
const int mx = 1e5;
long long factorial[mx];    //declare out of class affects performance a lot
long long inv_fact[mx];     //declare out of class affects performance a lot

class Solution {
private:
    void init() {
        //this if affects performance a lot
        if (factorial[0]) {
            return;
        }

        factorial[0] = 1;
        for (int i = 1; i < mx; ++i) {
            factorial[i] = i * factorial[i - 1] % mod;
        }

        inv_fact[mx - 1] = binary_exponential(factorial[mx - 1], mod - 2);
        for (int i = mx - 1; i >= 1; --i) {
            inv_fact[i - 1] = inv_fact[i] * i % mod;
        }
    }

    long long binary_exponential(long long val, int exp) {
        long long mul = 1;

        while (exp > 0) {

            if ((exp & 1) == 1) {
                //--exp;  //unnecessary operation 
                mul = mul * val % mod;
            }
            val = val * val % mod;
            exp >>= 1;
        }

        return mul;
    }

    long long combination(int n, int k) {
        return factorial[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;
    }

    int by_combinatoric(int& n, int& m, int& k) {
        init();

        return m * binary_exponential(m - 1, n - k - 1) % mod * combination(n - 1, k) % mod;
    }
public:
    int countGoodArrays(int n, int m, int k) {
        return by_combinatoric(n, m, k);
    }
};