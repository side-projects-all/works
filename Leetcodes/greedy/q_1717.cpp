/*
You are given a string s and two integers x and y. You can perform two types of operations any number of times.

    Remove substring "ab" and gain x points.
        For example, when removing "ab" from "cabxbae" it becomes "cxbae".
    Remove substring "ba" and gain y points.
        For example, when removing "ba" from "cabxbae" it becomes "cabxe".

Return the maximum points you can gain after applying the above operations on s.

 

Example 1:

Input: s = "cdbcbbaaabab", x = 4, y = 5
Output: 19
Explanation:
- Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5 points are added to the score.
- Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4 points are added to the score.
- Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points are added to the score.
- Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are added to the score.
Total score = 5 + 4 + 5 + 5 = 19.

Example 2:

Input: s = "aabbaaxybbaabb", x = 5, y = 4
Output: 20

 

Constraints:

    1 <= s.length <= 10^5
    1 <= x, y <= 10^4
    s consists of lowercase English letters.


*/

class Solution {
private:
    int greedy_by_counting(string& s, int x, int y) {
        if (x < y) {
            int tmp = x;
            x = y;
            y = tmp;

            std::reverse(s.begin(), s.end());
        }

        int a_cnt = 0;
        int b_cnt = 0;
        int cnt = 0;

        for (int i = 0; i < s.size(); ++i) {
            
            if (s[i] == 'a') {
                ++a_cnt;

            } else if (s[i] == 'b') {

                if (a_cnt > 0) {
                    --a_cnt;
                    cnt += x;
                } else {
                    ++b_cnt;
                }

            } else {
                cnt += std::min(b_cnt, a_cnt) * y;
                a_cnt = 0;
                b_cnt = 0;
            }
        }

        cnt += std::min(b_cnt, a_cnt) * y;

        return cnt;
    }
    int remove_without_stack(std::string& input, std::string target, int points) {
        int cnt = 0;
        int w = 0;

        for (int r = 0; r < input.size(); ++r) {
            input[w] = input[r];
            ++w;

            if (w > 1 && input[w - 2] == target[0] && input[w - 1] == target[1]) {
                w -= 2;
                cnt += points;
            }
        }

        input.erase(input.begin() + w, input.end());

        return cnt;
    }
    int greedy_without_stack(string& s, int x, int y) {
        int cnt = 0;
        if (x > y) {
            cnt += remove_without_stack(s, "ab", x);
            cnt += remove_without_stack(s, "ba", y);
        } else {
            cnt += remove_without_stack(s, "ba", y);
            cnt += remove_without_stack(s, "ab", x);
        }

        return cnt;
    }
    std::string remove_by_stack(const std::string& input, const std::string& target) {
        std::stack<char> stack;

        for (int i = 0; i < input.size(); ++i) {
            if (input[i] == target[1] && !stack.empty() && stack.top() == target[0]) {
                stack.pop();
            } else {
                stack.push(input[i]);
            }
        }

        std::string remain;
        while(!stack.empty()) {
            remain += stack.top();
            stack.pop();
        }

        std::reverse(remain.begin(), remain.end());

        return remain;
    }
    int greedy_by_stack(string& s, int x, int y) {
        int cnt = 0;
        std::string high;
        std::string low;
        int H = 0;
        int L = 0;

        if (x > y) {
            high = "ab";
            low = "ba";
            H = x;
            L = y;
        } else {
            high = "ba";
            low = "ab";
            H = y;
            L = x;
        }

        std::string first_pass = remove_by_stack(s, high);
        int removed01 = (s.size() - first_pass.size()) / 2;

        cnt += removed01 * H;

        std::string second_pass = remove_by_stack(first_pass, low);
        int removed02 = (first_pass.size() - second_pass.size()) / 2;

        cnt += removed02 * L;

        return cnt;
    }
public:
    int maximumGain(string s, int x, int y) {
        //return greedy_by_stack(s, x, y);
        //return greedy_without_stack(s, x, y);
        return greedy_by_counting(s, x, y);
    }
};