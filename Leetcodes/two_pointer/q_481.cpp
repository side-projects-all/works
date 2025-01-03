/*
A magical string s consists of only '1' and '2' and obeys the following rules:

    The string s is magical because concatenating the number of contiguous occurrences of characters '1' and '2' generates the string s itself.

The first few elements of s is s = "1221121221221121122……". If we group the consecutive 1's and 2's in s, it will be "1 22 11 2 1 22 1 22 11 2 11 22 ......" and the occurrences of 1's or 2's in each group are "1 2 2 1 1 2 1 2 2 1 2 2 ......". You can see that the occurrence sequence is s itself.

Given an integer n, return the number of 1's in the first n number in the magical string s.

 

Example 1:

Input: n = 6
Output: 3
Explanation: The first 6 elements of magical string s is "122112" and it contains three 1's, so return 3.

Example 2:

Input: n = 1
Output: 1

 

Constraints:

    1 <= n <= 10^5


*/

class Solution {
public:
    int magicalString(int n) {

        // "122" has only one '1' in the first three characters
        if (n <= 3) {
            return 1;  
        }

        // Start with "122"
        std::vector<int> magic = { 1, 2, 2 };  
        int cnt_ones = 1;  // Initialize with one '1' already counted
        int i = 2;          // Index that determines the number of times to add the next number
        int next_num = 1;    // The number to add next in the sequence

        while (magic.size() < n) {

            int repeat = magic[i];
            for (int j = 0; j < repeat; ++j) {

                magic.push_back(next_num);
                if (next_num == 1 && magic.size() <= n) {
                    cnt_ones++;
                }
            }
            next_num = 3 - next_num;  // Toggle between 1 and 2
            i++;
        }

        return cnt_ones;
    }
};