/*
Given the integers zero, one, low, and high, we can construct a string by starting with an empty string, and then at each step perform either of the following:

    Append the character '0' zero times.
    Append the character '1' one times.

This can be performed any number of times.

A good string is a string constructed by the above process having a length between low and high (inclusive).

Return the number of different good strings that can be constructed satisfying these properties. Since the answer can be large, return it modulo 109 + 7.

 

Example 1:

Input: low = 3, high = 3, zero = 1, one = 1
Output: 8
Explanation: 
One possible valid good string is "011". 
It can be constructed as follows: "" -> "0" -> "01" -> "011". 
All binary strings from "000" to "111" are good strings in this example.

Example 2:

Input: low = 2, high = 3, zero = 1, one = 2
Output: 5
Explanation: The good strings are "00", "11", "000", "110", and "011".

 

Constraints:

    1 <= low <= high <= 10^5
    1 <= zero, one <= low


*/

class Solution {
private:
    int iterative(int low, int high, int zero, int one) {
        int MOD = 1'000'000'007;
        std::vector<int> dp(high + 1);  //ways for buildings good string at every length
        dp[0] = 1;  //length 0 only one way

        //build from 1 to high first
        for (int i = 1; i <= high; ++i) {
            if (i >= zero) {
                dp[i] += dp[i - zero];
            }

            if (i >= one) {
                dp[i] += dp[i - one];
            }

            dp[i] %= MOD;
        }

        int sum = 0;
        //collect from low to high
        for (int i = low; i <= high; ++i) {
            sum += dp[i];
            sum %= MOD;
        }

        return sum;
    }
    int recursive(int zero, int one, int end, int mod, std::vector<int>& mem) {
        //base case
        if (end < 0) {
            return 0;
        }

        if (mem[end] != -1) {
            return mem[end];
        }

        int cnt = 0;
        if (end >= one) {
            cnt += recursive(zero, one, end - one, mod, mem);
        }

        if (end >= zero) {
            cnt += recursive(zero, one, end - zero, mod, mem);
        }

        mem[end] = cnt % mod;

        return mem[end];

    }
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        std::vector<int> mem(high + 1, -1);
        mem[0] = 1;
        int mod = 1000000007;

        int ans = 0;
        for (int end = low; end <= high; ++end) {
            ans += recursive(zero, one, end, mod, mem);
            ans %= mod;
        }
        
        return ans;
        //return iterative(low, high, zero, one);
    }
};