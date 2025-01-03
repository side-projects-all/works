/*
Given two integers a and b, return the sum of the two integers without using the operators + and -.

 

Example 1:

Input: a = 1, b = 2
Output: 3

Example 2:

Input: a = 2, b = 3
Output: 5

 

Constraints:

    -1000 <= a, b <= 1000


*/

class Solution {
public:
    int getSum(int a, int b) {
        //return method01(a, b);
        return method02(a, b);
    }
    
private:
    int method01(int a, int b) {
        int x = std::abs(a);
        int y = std::abs(b);
        
        //reverse them for handling
        if (x < y) {
            return getSum(b, a);
        }
        
        int sign = a > 0 ? 1 : -1;
        int answer = 0;
        int carry = 0;
        int borrow = 0;
        if (a * b >= 0) {
            //sum of two positive integers where x > y
            while(y != 0) {
                answer = x ^ y;
                carry = (x & y) << 1;
                x = answer;
                y = carry;
            }

        } else {
            //difference of two positive integers where x > y
            while(y != 0) {
                answer = x ^ y;
                borrow = ((~x) & y) << 1;
                x = answer;
                y = borrow;
            }
        }
        
        return x * sign;
    }
    //a better way
    int method02(int a, int b) {
        long mask = 0xFFFFFFFF;
        
        int answer = 0;
        int carry = 0;
        while(b != 0) {
            answer = (a ^ b) & mask;
            carry = ((a & b) & mask) << 1;
            a = answer;
            b = carry;
        }
        
        return a < INT_MAX ? a : ~(a ^ mask);
    }
};