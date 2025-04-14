/*
Given a positive integer n, you can apply one of the following operations:

    If n is even, replace n with n / 2.
    If n is odd, replace n with either n + 1 or n - 1.

Return the minimum number of operations needed for n to become 1.

 

Example 1:

Input: n = 8
Output: 3
Explanation: 8 -> 4 -> 2 -> 1

Example 2:

Input: n = 7
Output: 4
Explanation: 7 -> 8 -> 4 -> 2 -> 1
or 7 -> 6 -> 3 -> 2 -> 1

Example 3:

Input: n = 4
Output: 2

 

Constraints:

    1 <= n <= 2^31 - 1


*/

class Solution {
public:
    int integerReplacement(int n) {
        //std::unordered_map<int, int> mem;
        //return recursive(n, mem);
        return iterative(n);
    }
private:
    int iterative(int n) {
        unsigned num = n;   //avoid overflow issues 
        int cnt = 0;
        while (num > 1) {

            if (!(num & 1)) {   //it is even
                num >>= 1;
                
            } else {

                //when it is odd

                //for this condition, if n == 3 or 
                //after right shift, the last bit will be zero
                if (num == 3 || !(((num - 1) >> 1) & 1)) {
                    --num;
                } else {
                    ++num;
                }
            }

            ++cnt;
        }

        return cnt;
    }
    int recursive(long n, std::unordered_map<int, int>& mem) {
        if (n <= 1) {
            return 0;
        }

        if (mem.find(n) != mem.end()) {
            return mem[n];
        }

        int ans = 0;
        if (n % 2) {
            ans = 1 + std::min(recursive(n - 1, mem), recursive(n + 1, mem));
            
        } else {
            ans = 1 + recursive(n / 2, mem);
        }

        return mem[n] = ans;
    }
};