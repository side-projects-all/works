/*
Given an integer num, return a string representing its hexadecimal representation. For negative integers, two’s complement method is used.

All the letters in the answer string should be lowercase characters, and there should not be any leading zeros in the answer except for the zero itself.

Note: You are not allowed to use any built-in library method to directly solve this problem.

 

Example 1:

Input: num = 26
Output: "1a"

Example 2:

Input: num = -1
Output: "ffffffff"

 

Constraints:

    -2^31 <= num <= 2^31 - 1


*/

class Solution {
public:
    string toHex(int num) {
        std::string map = "0123456789abcdef";
        std::string result = "";
        
        if (num == 0) {
            return "0";
        }
        
        int move = 0;
        for (int i = 0; i < 8; ++i) {
            move = (num >> 4 * i) & 0xf;
            result += map[move];    
        }
        
        std::reverse(result.begin(), result.end());
        
        //after reverse, get substring from first none '0' index
        int j = 0;
        for (j = 0; j < result.size(); ++j) {
            if (result[j] != '0') {
                break;
            }
        }
        std::string residual = result.substr(j, result.size() - j);
        
        return residual;
    }
};