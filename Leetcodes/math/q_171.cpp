/*
Given a string columnTitle that represents the column title as appears in an Excel sheet, return its corresponding column number.

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

Input: columnTitle = "A"
Output: 1

Example 2:

Input: columnTitle = "AB"
Output: 28

Example 3:

Input: columnTitle = "ZY"
Output: 701

 

Constraints:

    1 <= columnTitle.length <= 7
    columnTitle consists only of uppercase English letters.
    columnTitle is in the range ["A", "FXSHRXW"].


*/

class Solution {
public:
    int titleToNumber(string columnTitle) {
        int n = columnTitle.size();
        if (n == 1) {
            return columnTitle[0] - 'A' + 1;
        }

        int vals = 0;
        int pow = n - 1;
        for (int i = 0; i < n - 1; ++i) {
            vals += static_cast<int>(std::pow(26, pow)) * (columnTitle[i] - 'A' + 1);
            --pow;
        }

        vals += columnTitle[n - 1] - 'A' + 1;
        return vals;
    }
};