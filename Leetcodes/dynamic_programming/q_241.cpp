/*
Given a string expression of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. You may return the answer in any order.

The test cases are generated such that the output values fit in a 32-bit integer and the number of different results does not exceed 104.

 

Example 1:

Input: expression = "2-1-1"
Output: [0,2]
Explanation:
((2-1)-1) = 0 
(2-(1-1)) = 2

Example 2:

Input: expression = "2*3-4*5"
Output: [-34,-14,-10,-10,10]
Explanation:
(2*(3-(4*5))) = -34 
((2*3)-(4*5)) = -14 
((2*(3-4))*5) = -10 
(2*((3-4)*5)) = -10 
(((2*3)-4)*5) = 10

 

Constraints:

    1 <= expression.length <= 20
    expression consists of digits and the operator '+', '-', and '*'.
    All the integer values in the input expression are in the range [0, 99].


*/

class Solution {
private:
    int cal(char op, int v1, int v2) {

        if (op == '+') {
            return v1 + v2;
        }

        if (op == '-') {
            return v1 - v2;
        } 

        return v1 * v2;
    }
    vector<int> recursive(std::string&& s, std::unordered_map<std::string, std::vector<int>>& mem) {

        if (mem.find(s) != mem.end()) {
            return mem[s];
        }

        std::vector<int> ans;
        bool is_num = true; //is the string s now a number? ex: 45, 119

        for (int i = 0; i < s.size(); ++i) {

            if (!std::isdigit(s[i])) {
                is_num = false;
                std::vector<int> left = recursive(std::move(s.substr(0, i)), mem);
                std::vector<int> right = recursive(std::move(s.substr(i + 1)), mem);

                for (int& v1 : left) {
                    for (int& v2 : right) {
                        ans.push_back(cal(s[i], v1, v2));
                    }
                }
            }
        }

        if (is_num) {
            ans.push_back(std::stoi(s));
        }

        return mem[s] = ans;
    }
    vector<int> by_recursive_dp(string& expression) {
        std::unordered_map<std::string, std::vector<int>> mem;

        return recursive(std::move(expression), mem);
    }
public:
    vector<int> diffWaysToCompute(string expression) {
        return by_recursive_dp(expression);
    }
};