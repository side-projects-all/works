/*
Given two positive integers a and b, return the count of numbers having unique digits in the range [a, b] (inclusive).

 

Example 1:

Input: a = 1, b = 20
Output: 19
Explanation: All the numbers in the range [1, 20] have unique digits except 11. Hence, the answer is 19.

Example 2:

Input: a = 9, b = 19
Output: 10
Explanation: All the numbers in the range [9, 19] have unique digits except 11. Hence, the answer is 10. 

Example 3:

Input: a = 80, b = 120
Output: 27
Explanation: There are 41 numbers in the range [80, 120], 27 of which have unique digits.

 

Constraints:

    1 <= a <= b <= 1000

*/

class Solution {
private:
    int naive(int& a, int& b) {
        int cnt = 0;
        for (int v = a; v <= b; ++v) {

            //std::unordered_set<int> digits;
            int val = v;
            bool is_unique = true;
            int curr = 0;
            while (val > 0) {
                int d = val % 10;

                if (curr & (1 << d)) {
                    is_unique = false;
                    break;

                } else {
                    curr |= 1 << d;
                }
                /*
                if (digits.count(d) == 0) {
                    digits.insert(d);
                } else {
                    is_unique = false;
                    break;
                }*/

                val /= 10;
            }

            if (is_unique) {
                ++cnt;
            }
        }

        return cnt;
    }
public:
    int numberCount(int a, int b) {
        
        if (b < 10) {
            return b - a + 1;
        }

        return naive(a, b);
    }
};