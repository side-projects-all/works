/*
You are given an integer num. You can swap two digits at most once to get the maximum valued number.

Return the maximum valued number you can get.

 

Example 1:

Input: num = 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.

Example 2:

Input: num = 9973
Output: 9973
Explanation: No swap.

 

Constraints:

    0 <= num <= 10^8


*/

class Solution {
public:
    int maximumSwap(int num) {
        std::string str_n = std::to_string(num);
        int n = str_n.size();
        int max_digit_i = -1;
        int smaller = -1;
        int larger = -1;

        //from lowest digit
        for (int i = n - 1; i >= 0; --i) {

            if (max_digit_i == -1 || str_n[i] > str_n[max_digit_i]) {
                max_digit_i = i;

            } else if (str_n[i] < str_n[max_digit_i]) {
                smaller = i;
                larger = max_digit_i;
            }
        }

        if (smaller != -1 && larger != -1) {
            std::swap(str_n[smaller], str_n[larger]);
        }

        return std::stoi(str_n);
    }
};