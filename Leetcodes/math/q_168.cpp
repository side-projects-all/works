/*
Given an integer columnNumber, return its corresponding column title as it appears in an Excel sheet.

For example:

A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28 
...

 

Example 1:

Input: columnNumber = 1
Output: "A"

Example 2:

Input: columnNumber = 28
Output: "AB"

Example 3:

Input: columnNumber = 701
Output: "ZY"

 

Constraints:

    1 <= columnNumber <= 2^31 - 1


*/

class Solution {
public:
    string convertToTitle(int columnNumber) {
        std::string ans;

        if (columnNumber <= 26) {
            ans += std::string(1, 'A' + columnNumber - 1);
            return ans;
        }

        while (columnNumber > 0) {
            --columnNumber;
            ans += static_cast<char>(columnNumber % 26 + 'A');
            columnNumber /= 26;
        }

        std::reverse(ans.begin(), ans.end());
        
        return ans;
    }
};