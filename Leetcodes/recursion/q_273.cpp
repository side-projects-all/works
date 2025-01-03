/*
Convert a non-negative integer num to its English words representation.

 

Example 1:

Input: num = 123
Output: "One Hundred Twenty Three"

Example 2:

Input: num = 12345
Output: "Twelve Thousand Three Hundred Forty Five"

Example 3:

Input: num = 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

 

Constraints:

    0 <= num <= 2^31 - 1


*/

class Solution {
private:
    std::vector<std::string> first_19{ "", " One", " Two", " Three", " Four", " Five", 
                                            " Six", " Seven", " Eight", " Nine", " Ten", " Eleven", 
                                            " Twelve", " Thirteen", " Fourteen", " Fifteen", " Sixteen", 
                                            " Seventeen",  " Eighteen", " Nineteen" };
    std::vector<std::string> two_digits{ "", " Ten", " Twenty", " Thirty", " Forty", " Fifty", 
                                                    " Sixty", " Seventy", " Eighty", " Ninety" };
    std::vector<std::string> three_digits{ "", " Thousand", " Million", " Billion" };

    std::string recursive(int n) {
        if (n < 20) {
            return first_19[n];
        }

        if (n < 100) {
            return two_digits[n / 10] + recursive(n % 10);
        }

        if (n < 1000) {
            return recursive(n / 100) + " Hundred" + recursive(n % 100);
        }

        for (int i = 3; i >= 0; --i) {
            if (n >= pow(1000, i)) {
                return recursive(n / pow(1000, i)) + three_digits[i] + recursive(n % (int)pow(1000, i));
            }
        }

        return "";
    }
public:
    string numberToWords(int num) {
        if (num == 0) {
            return "Zero";
        }
        
        return recursive(num).substr(1);
    }
};