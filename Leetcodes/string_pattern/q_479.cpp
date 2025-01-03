/*
Given an integer n, return the largest palindromic integer that can be represented as the product of two n-digits integers. Since the answer can be very large, return it modulo 1337.

 

Example 1:

Input: n = 2
Output: 987
Explanation: 99 x 91 = 9009, 9009 % 1337 = 987

Example 2:

Input: n = 1
Output: 9

 

Constraints:

    1 <= n <= 8


*/

class Solution {
public:
    int largestPalindrome(int n) {
        //base case
        if (n == 1) {
            return 9;
        }
        //upper and lower bounds for n-digit numbers
        int upper = pow(10, n) - 1;
        int lower = pow(10, n - 1);

        //loop through possible palindromes in decreasing order
        for (int left_part = upper; left_part >= lower; --left_part) {
            //create a palindrome by mirroring the left half
            long long palindrome = create_palindrome(left_part);

            //check if the palindrome can be a product of two n-digit numbers
            for (long long i = upper; i * i >= palindrome; --i) {

                if (palindrome % i == 0) {
                    
                    long long j = palindrome / i;
                    if (j >= lower && j <= upper) {
                        return palindrome % 1337;  //mod 1337 as per problem constraints
                    }
                }
            }
        }
        return -1;  //not valid
    }

private:
    //create a palindrome by mirroring the left half
    long long create_palindrome(int left_part) {
        std::string str = std::to_string(left_part);
        std::string rev = str;
        std::reverse(rev.begin(), rev.end());
        return std::stoll(str + rev);
    }
};