/*
An integer has sequential digits if and only if each digit in the number is one more than the previous digit.

Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.

 

Example 1:

Input: low = 100, high = 300
Output: [123,234]

Example 2:

Input: low = 1000, high = 13000
Output: [1234,2345,3456,4567,5678,6789,12345]

 

Constraints:

    10 <= low <= high <= 10^9


*/

class Solution {
private:

public:
    vector<int> sequentialDigits(int low, int high) {

        std::function<int(int)> digitLen = [](int num) -> int {
            int len = 0;
            while (num > 0) {
                ++len;
                num /= 10;
            }

            return len;
        };

        int len_low = digitLen(low);
        int len_high = digitLen(high);

        std::vector<int> result;
        for (int i = len_low; i <= len_high; ++i) {
            
            for (int n = 1; n <= 9; ++n) {
                int ans = n;
                int len_ans = 1;
                int next_digit = n - 1;
                while (len_ans < i && next_digit > 0) {
                    ans += next_digit * std::pow(10, len_ans);

                    len_ans = digitLen(ans);
                    --next_digit;
                }

                len_ans = digitLen(ans);
                if (ans >= low && ans <= high && len_ans == i) {
                    result.push_back(ans);
                } else if (ans > high) {
                    break;
                }
            }
        }

        return result;
    }
};