/*
Given a string num that contains only digits and an integer target, return all possibilities to insert the binary operators '+', '-', and/or '*' between the digits of num so that the resultant expression evaluates to the target value.

Note that operands in the returned expressions should not contain leading zeros.

 

Example 1:

Input: num = "123", target = 6
Output: ["1*2*3","1+2+3"]
Explanation: Both "1*2*3" and "1+2+3" evaluate to 6.

Example 2:

Input: num = "232", target = 8
Output: ["2*3+2","2+3*2"]
Explanation: Both "2*3+2" and "2+3*2" evaluate to 8.

Example 3:

Input: num = "3456237490", target = 9191
Output: []
Explanation: There are no expressions that can be created from "3456237490" to evaluate to 9191.

 

Constraints:

    1 <= num.length <= 10
    num consists of only digits.
    -2^31 <= target <= 2^31 - 1


*/

class Solution {
private:
    std::string num;
    std::vector<std::string> ans;
    long long target;
    int n;

    void backtracking(int i, std::string& str, long long evaluation, long long pre_val) {

        if (i == n) {
            if (evaluation == target) {
                ans.push_back(str);
            }

            return;
        }

        int len_now = str.size();
        if (i > 0) {
            str.push_back(0);   //the last position will be len_now
        }

        long long curr_val = 0;
        for (int j = i; j < n && (j == i || num[i] != '0'); ++j) {
            curr_val = curr_val * 10 + num[j] - '0';
            str.push_back(num[j]);

            if (i == 0) {
                backtracking(j + 1, str, curr_val, curr_val);
            } else {
                str[len_now] = '+';
                backtracking(j + 1, str, evaluation + curr_val, curr_val);
                str[len_now] = '-';
                backtracking(j + 1, str, evaluation - curr_val, -curr_val);
                str[len_now] = '*';
                backtracking(j + 1, str, evaluation - pre_val + pre_val * curr_val, pre_val * curr_val);
            }
        }

        //use resize to discard extra substring from recursion
        str.resize(len_now);
    }
public:
    vector<string> addOperators(string num, int target) {
        if (num.size() == 1) {
            return std::stoi(num) == target ? std::vector<std::string>{ num } : std::vector<std::string>{};
        }

        this->num = num;
        this->n = num.size();
        this->target = target;
        std::string str;
        backtracking(0, str, 0, 0);

        return ans;
    }
};

