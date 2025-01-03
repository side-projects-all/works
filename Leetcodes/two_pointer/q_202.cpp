/*
Write an algorithm to determine if a number n is happy.

A happy number is a number defined by the following process:

    Starting with any positive integer, replace the number by the sum of the squares of its digits.
    Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
    Those numbers for which this process ends in 1 are happy.

Return true if n is a happy number, and false if not.

 

Example 1:

Input: n = 19
Output: true
Explanation:
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1

Example 2:

Input: n = 2
Output: false

 

Constraints:

    1 <= n <= 2^31 - 1



*/

class Solution {
public:
    bool isHappy(int n) {
        //return byHashSet(n);

        return byTwoPointers(n);
    }

private:
    bool byHashSet(int n) {
        std::unordered_set<int> store;
        int digit = 0;
        int square = 0;
        int num = n;
        
        while (true) {
            
            //calculate every digit and sum the square
            while (num >= 10) {
                digit = num % 10;
                square += digit * digit;
                
                num = num / 10;
            }
            
            square += num * num;
            
            //decide if square were a happy number
            if (square == 1) {
                return true;
                
            } else if (store.find(square) != store.end()) {
                return false;
                
            } else {
                store.insert(square);
                digit = 0;
                num = square;
                square = 0;
            }

        }
    }

    bool byTwoPointers(int n) {
        int slower = n;
        int faster = getNext(n);

        while (faster != 1 && slower != faster) {
            slower = getNext(slower);
            faster = getNext(getNext(faster));
        }

        return faster == 1;
    }

    int getNext(int n) {
        int sum = 0;
        int d = 0;
        while (n > 0) {
            d = n % 10;
            n = n / 10;
            sum += d * d;
        }

        return sum;
    }
};