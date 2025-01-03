/*
An attendance record for a student can be represented as a string where each character signifies whether the student was absent, late, or present on that day. The record only contains the following three characters:

    'A': Absent.
    'L': Late.
    'P': Present.

Any student is eligible for an attendance award if they meet both of the following criteria:

    The student was absent ('A') for strictly fewer than 2 days total.
    The student was never late ('L') for 3 or more consecutive days.

Given an integer n, return the number of possible attendance records of length n that make a student eligible for an attendance award. The answer may be very large, so return it modulo 109 + 7.

 

Example 1:

Input: n = 2
Output: 8
Explanation: There are 8 records with length 2 that are eligible for an award:
"PP", "AP", "PA", "LP", "PL", "AL", "LA", "LL"
Only "AA" is not eligible because there are 2 absences (there need to be fewer than 2).

Example 2:

Input: n = 1
Output: 3

Example 3:

Input: n = 10101
Output: 183236316

 

Constraints:

    1 <= n <= 10^5


*/

class Solution {
private:
    int iterative(int n) {
        int MOD = 1'000'000'007;
        std::vector<std::vector<std::vector<int>>> mem(n + 1, std::vector<std::vector<int>>(2, std::vector<int>(3, 0)));

        mem[0][0][0] = 1;

        for (int day = 0; day < n; ++day) {
            for (int ab_now = 0; ab_now <= 1; ++ab_now) {
                for (int late_now = 0; late_now <= 2; ++late_now) {
                    mem[day + 1][ab_now][0] = (mem[day + 1][ab_now][0] + mem[day][ab_now][late_now]) % MOD;

                    if (ab_now < 1) {
                        mem[day + 1][ab_now + 1][0] = (mem[day + 1][ab_now + 1][0] + mem[day][ab_now][late_now]) % MOD;
                    }

                    if (late_now < 2) {
                        mem[day+ 1][ab_now][late_now + 1] = (mem[day + 1][ab_now][late_now + 1] + mem[day][ab_now][late_now]) % MOD;
                    }
                }
            }
        }

        int cnt = 0;
        for (int ab_now = 0; ab_now <= 1; ++ab_now) {
            for (int late_now = 0; late_now <= 2; ++late_now) {
                cnt  = (cnt + mem[n][ab_now][late_now]) % MOD;
            }
        }

        return cnt;
    }
    int recursive(int n) {
        int MOD = 1'000'000'007;
        std::vector<std::vector<std::vector<int>>> mem(n + 1, std::vector<std::vector<int>>(2, std::vector<int>(3, -1)));

        std::function<int(int, int, int)> re = [&](int day, int ab_now, int late_now) -> int {
            if (ab_now >= 2 || late_now >= 3) {
                return 0;
            }

            if (day == 0) {
                return 1;
            }

            if (mem[day][ab_now][late_now] != -1) {
                return mem[day][ab_now][late_now];
            }

            int cnt = 0;
            cnt = (cnt + re(day - 1, ab_now, 0)) % MOD;
            cnt = (cnt + re(day - 1, ab_now + 1, 0)) % MOD;
            cnt = (cnt + re(day - 1, ab_now, late_now + 1)) % MOD;

            mem[day][ab_now][late_now] = cnt;
            return mem[day][ab_now][late_now];
        };

        return re(n, 0, 0);
    }
public:
    int checkRecord(int n) {
        //return recursive(n);
        return iterative(n);
    }
};