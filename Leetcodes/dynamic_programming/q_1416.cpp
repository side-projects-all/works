/*
A program was supposed to print an array of integers. The program forgot to print whitespaces and the array is printed as a string of digits s and all we know is that all integers in the array were in the range [1, k] and there are no leading zeros in the array.

Given the string s and the integer k, return the number of the possible arrays that can be printed as s using the mentioned program. Since the answer may be very large, return it modulo 109 + 7.

 

Example 1:

Input: s = "1000", k = 10000
Output: 1
Explanation: The only possible array is [1000]

Example 2:

Input: s = "1000", k = 10
Output: 0
Explanation: There cannot be an array that was printed this way and has all integer >= 1 and <= 10.

Example 3:

Input: s = "1317", k = 2000
Output: 8
Explanation: Possible arrays are [1317],[131,7],[13,17],[1,317],[13,1,7],[1,31,7],[1,3,17],[1,3,1,7]

 

Constraints:

    1 <= s.length <= 10^5
    s consists of only digits and does not contain leading zeros.
    1 <= k <= 10^9


*/

class Solution {
private:
    int MOD = 1'000'000'007;
    int recursive(string& s, int k, int start, std::vector<int>& mem) {
        //base case
        if (start == s.size()) {
            return 1;
        }

        if (s[start] == '0') {
            return 0;
        }

        if (mem[start] != -1) {
            return mem[start];
        }
        
        int cnt = 0;
        for (int end = start; end < s.size(); ++end) {
            //the substr function is different from Java's susbstring
            std::string currNum = s.substr(start, end - start + 1);
            
            if (std::stoll(currNum) > (long long)k) {
                break;
            }

            cnt = (cnt + recursive(s, k, end + 1, mem)) % MOD;
        }
        
        mem[start] = cnt;
        return cnt;
    }
public:
    int numberOfArrays(string s, int k) {
        
        std::vector<int> mem(s.size() + 1, -1);
        return recursive(s, k, 0, mem);
    }
};