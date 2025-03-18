/*
Given two positive integers left and right, find the two integers num1 and num2 such that:

    left <= num1 < num2 <= right .
    Both num1 and num2 are 

    .
    num2 - num1 is the minimum amongst all other pairs satisfying the above conditions.

Return the positive integer array ans = [num1, num2]. If there are multiple pairs satisfying these conditions, return the one with the smallest num1 value. If no such numbers exist, return [-1, -1].

 

Example 1:

Input: left = 10, right = 19
Output: [11,13]
Explanation: The prime numbers between 10 and 19 are 11, 13, 17, and 19.
The closest gap between any pair is 2, which can be achieved by [11,13] or [17,19].
Since 11 is smaller than 17, we return the first pair.

Example 2:

Input: left = 4, right = 6
Output: [-1,-1]
Explanation: There exists only one prime number in the given range, so the conditions cannot be satisfied.

 

Constraints:

    1 <= left <= right <= 10^6

*/

class Solution {
private:
    vector<int> by_sieve_of_eratosthenes(int& left, int& right) {
        std::vector<bool> is_prime(right + 1, true);
        is_prime[0] = false;
        is_prime[1] = false;
        for (int i = 2; i * i <= right; ++i) {
            if (is_prime[i]) {
                for (int j = i * i; j <= right; j += i) {
                    is_prime[j] = false;
                }
            }
        }

        std::vector<int> primes;
        for (int i = left; i <= right; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
            }
        }

        if (primes.size() < 2) {
            return {-1, -1};
        }
        std::vector<int> ans(2, -1);
        int closest = INT_MAX;
        for (int e = 1; e < primes.size(); ++e) {
            if (primes[e] - primes[e - 1] < closest) {
                ans[0] = primes[e - 1];
                ans[1] = primes[e];
                closest = primes[e] - primes[e - 1];
            }
        }

        return ans;
    }
public:
    vector<int> closestPrimes(int left, int right) {
        return by_sieve_of_eratosthenes(left, right);
    }
};