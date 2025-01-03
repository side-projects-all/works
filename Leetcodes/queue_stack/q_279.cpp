/*
Given an integer n, return the least number of perfect square numbers that sum to n.

A perfect square is an integer that is the square of an integer; in other words, it is the product of some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.

 

Example 1:

Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.

Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.

 

Constraints:

    1 <= n <= 10^4


*/

class Solution {
public:
    int numSquares(int n) {
        std::vector<int> sqr_nums;
        for (int i = 1; i * i <= n; ++i) {
            sqr_nums.push_back(i * i);
        }
        
        std::set<int> q;
        q.insert(n);
        
        int level = 0;
        while(q.size() > 0) {
            level += 1;
            std::set<int> q02;  //this means nodes in next level, using set to avoid repititive number

            for (int remainder : q) {
                for (int square : sqr_nums) {
                    if (remainder == square) {
                        return level;
                    } else if (remainder < square) {
                        break;
                    } else {
                        q02.insert(remainder - square);
                    }
                }
            }
            
            q = q02;
        }
        
        return level;
    }
};