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
    std::unordered_map<std::string, std::vector<int>> m;
    int ops(int x, int y, char op) {
        if (op == '+') {
            return x + y;
        }
        
        if (op == '-') {
            return x - y;
        }

        return x * y;
    }

public:
    vector<int> diffWaysToCompute(string expression) {

        if (m.find(expression) != m.end()) {
            return m[expression];
        }

        std::vector<int> ans;
        bool is_num = true;

        for (int i = 0; i < expression.size(); ++i) {

            if (!std::isdigit(expression[i])) {
                is_num = false;

                std::vector<int> left = diffWaysToCompute(expression.substr(0, i));
                std::vector<int> right = diffWaysToCompute(expression.substr(i + 1));

                for (int x : left) {
                    for (int y : right) {
                        int n = ops(x, y, expression[i]);
                        ans.push_back(n);
                    }
                }
            }
        }

        if (is_num) {
            ans.push_back(std::stoi(expression));
        }

        m[expression] = ans;

        return ans;
    }
};