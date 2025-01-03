/*
Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

If multiple answers are possible, return any of them.

It is guaranteed that the length of the answer string is less than 104 for all the given inputs.

 

Example 1:

Input: numerator = 1, denominator = 2
Output: "0.5"

Example 2:

Input: numerator = 2, denominator = 1
Output: "2"

Example 3:

Input: numerator = 4, denominator = 333
Output: "0.(012)"

 

Constraints:

    -2^31 <= numerator, denominator <= 2^31 - 1
    denominator != 0


*/

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) {
            return "0";
        }

        std::string fraction;
        //if one of them were negative
        if (numerator < 0 ^ denominator < 0) {
            fraction.append("-");
        }

        long long dividend = std::labs((long long)numerator);
        long long divisor = std::labs((long long)denominator);
        fraction.append(std::to_string(dividend / divisor));
        long long remainder = dividend % divisor;

        if (remainder == 0) {
            return fraction;
        }

        fraction.append(".");
        std::unordered_map<long long, int> m;
        while (remainder != 0) {
            if (m.find(remainder) != m.end()) {
                fraction.insert(m[remainder], "(");
                fraction.append(")");
                break;
            }

            m[remainder] = fraction.size();
            remainder *= 10;
            fraction.append(std::to_string(remainder / divisor));
            remainder %= divisor;
        }

        return fraction;
    }
};