/*
Given a string s containing an out-of-order English representation of digits 0-9, return the digits in ascending order.

 

Example 1:

Input: s = "owoztneoer"
Output: "012"

Example 2:

Input: s = "fviefuro"
Output: "45"

 

Constraints:

    1 <= s.length <= 10^5
    s[i] is one of the characters ["e","g","f","i","h","o","n","s","r","u","t","w","v","x","z"].
    s is guaranteed to be valid.


*/

class Solution {
public:
    string originalDigits(string s) {
        std::vector<int> cnts(26);
        for (char& c : s) {
            ++cnts[c - 'a'];
        }

        std::vector<int> digits(10);
        digits[0] = cnts[25];    //z
        digits[2] = cnts[22];    //w
        digits[4] = cnts[20];    //u
        digits[6] = cnts[23];    //x
        digits[8] = cnts[6];    //g
        digits[3] = cnts[7] - digits[8];    //h
        digits[5] = cnts[5] - digits[4];    //f
        digits[7] = cnts[18] - digits[6];    //s
        digits[9] = cnts[8] - digits[5] - digits[6] - digits[8];    //i
        digits[1] = cnts[13] - digits[7] - 2 * digits[9];    //n, nine use two n

        std::string ans;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < digits[i]; ++j) {
                ans += std::to_string(i);
            }
        }

        return ans;
    }
};