/*
Given an integer num, return a string of its base 7 representation.

 

Example 1:

Input: num = 100
Output: "202"

Example 2:

Input: num = -7
Output: "-10"

 

Constraints:

    -10^7 <= num <= 10^7


*/

class Solution {
public:
    string convertToBase7(int num) {
        int mod = 0;
        int div = 0;
        std::string str = "";
        bool isNegative = false;
        
        if (num == 0) {
            return "0";
        }
        
        if (num < 0) {
            num = -num;   
            isNegative = true;
        }
        
        do {
            mod = num % 7;
            num = num / 7;
            str.append(std::to_string(mod));
            
        } while (num > 0);
        
        if (isNegative) {
            str.append("-");
        }
        std::reverse(str.begin(), str.end());
        
        return str;
    }
};