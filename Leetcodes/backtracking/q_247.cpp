/*
Given an integer n, return all the strobogrammatic numbers that are of length n. You may return the answer in any order.

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

 

Example 1:

Input: n = 2
Output: ["11","69","88","96"]

Example 2:

Input: n = 1
Output: ["0","1","8"]

 

Constraints:

    1 <= n <= 14


*/

class Solution {
private:
    vector<string> recursive(int n, std::vector<std::vector<char>>& revisible, int targetLen) {
        if (n == 0) {
            return { "" };
        }
        if (n == 1) {
            return { "0", "1", "8" };
        }

        std::vector<std::string> prevStrobo = recursive(n - 2, revisible, targetLen);
        std::vector<std::string> currStrobo;

        for (std::string& prev : prevStrobo) {
            for (std::vector<char>& v : revisible) {

                //n != targetLen means we would not append '0' at the beginning of a number when recursion 
                //reachs target length
                if (v[0] != '0' || n != targetLen) {
                    currStrobo.push_back(v[0] + prev + v[1]);
                }
            }
        }

        return currStrobo;
    }
public:
    vector<string> findStrobogrammatic(int n) {
        if (n == 2) {
            return { "11", "69", "88", "96" };
        }

        std::vector<std::vector<char>> revisible { {'0', '0'}, {'1', '1'}, {'6', '9'}, {'8', '8'}, {'9', '6'} };

        return recursive(n, revisible, n);
    }
};