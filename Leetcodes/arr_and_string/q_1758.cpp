/*
You are given a string s consisting only of the characters '0' and '1'. In one operation, you can change any '0' to '1' or vice versa.

The string is called alternating if no two adjacent characters are equal. For example, the string "010" is alternating, while the string "0100" is not.

Return the minimum number of operations needed to make s alternating.

 

Example 1:

Input: s = "0100"
Output: 1
Explanation: If you change the last character to '1', s will be "0101", which is alternating.

Example 2:

Input: s = "10"
Output: 0
Explanation: s is already alternating.

Example 3:

Input: s = "1111"
Output: 2
Explanation: You need two operations to reach "0101" or "1010".

 

Constraints:

    1 <= s.length <= 10^4
    s[i] is either '0' or '1'.


*/

class Solution {
private:
    int iterative(std::string& s) {
        int N = s.size();

        //check only one 
        int start0 = 0;
        for (int i = 0; i < N; ++i) {
            if (s[i] - '0' == i % 2) {
                ++start0;
            }

            //above if check equal to below
            /*
            if (i % 2 == 0) {
                if (s[i] == '1') {
                    start0++;
                }
            } else {
                if (s[i] == '0') {
                    start0++;
                }
            }
            */
        }
        int start1 = N - start0;
        return std::min(start0, start1);

        /*
        int start0 = 0;
        int start1= 0;

        for (int i = 0; i < N; ++i) {
            
            
            if (i % 2 == 0) {
                //at even digit 
                if (s[i] == '0') {

                    //if it is 0 and you want to start with 1, then you need to change it
                    ++start1;
                } else {

                    //if it is 1 and you want to start with 0, then you need to change it
                    ++start0;
                }
            } else {

                //at odd digit
                if (s[i] == '1') {

                    //if it is 1 and you want to start with 1, then you need to change it to 0
                    ++start1;
                } else {

                    //if it is 0 and you want to start with 0, then you need to change it to 1
                    ++start0;
                }
            }
        }
        
        return std::min(start0, start1);
        */
    }
public:
    int minOperations(string s) {
        //corner case
        if (s.size() == 1) {
            return 0;
        }

        return iterative(s);
    }
};