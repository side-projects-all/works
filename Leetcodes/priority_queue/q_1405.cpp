/*
A string s is called happy if it satisfies the following conditions:

    s only contains the letters 'a', 'b', and 'c'.
    s does not contain any of "aaa", "bbb", or "ccc" as a substring.
    s contains at most a occurrences of the letter 'a'.
    s contains at most b occurrences of the letter 'b'.
    s contains at most c occurrences of the letter 'c'.

Given three integers a, b, and c, return the longest possible happy string. If there are multiple longest happy strings, return any of them. If there is no such string, return the empty string "".

A substring is a contiguous sequence of characters within a string.

 

Example 1:

Input: a = 1, b = 1, c = 7
Output: "ccaccbcc"
Explanation: "ccbccacc" would also be a correct answer.

Example 2:

Input: a = 7, b = 1, c = 0
Output: "aabaa"
Explanation: It is the only correct answer in this case.

 

Constraints:

    0 <= a, b, c <= 100
    a + b + c > 0


*/

class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        //return by_greedy(a, b, c);
        return by_pq(a, b, c);
    }

private:
    std::string by_pq(int a, int b, int c) {
        std::priority_queue<std::pair<int, char>> pq;
        if (a > 0) {
            pq.push({a, 'a'});
        }
        if (b > 0) {
            pq.push({b, 'b'});
        }
        if (c > 0) {
            pq.push({c, 'c'});
        }

        std::string ans;
        while (!pq.empty()) {
            auto [cnt, ch] = pq.top();
            pq.pop();

            int len = ans.size();
            if (ans.size() >= 2 && ans[len - 1] == ch && ans[len - 2] == ch) {
                if (pq.empty()) {
                    break;
                }

                std::pair<int, char> top = pq.top();
                pq.pop();

                ans += top.second;
                if (top.first - 1 > 0) {
                    pq.push({top.first - 1, top.second});
                }

            } else {
                --cnt;
                ans += ch;
            }

            if (cnt > 0) {
                pq.push({cnt, ch});
            }
        }

        return ans;
    }
    std::string by_greedy(int a, int b, int c) {
        int curr_a = 0;
        int curr_b = 0;
        int curr_c = 0;
        int total_cnt = a + b + c;
        std::string ans;

        for (int i = 0; i < total_cnt; ++i) {
            if ((a >= b && a >= c && curr_a != 2) || (a > 0 && (curr_b ==2 || curr_c == 2))) {
                ans += 'a';
                --a;
                ++curr_a;
                curr_b = 0;
                curr_c = 0;

            } else if ((b >= a && b >= c && curr_b != 2) || (b > 0 && (curr_c == 2 || curr_a == 2))) {
                ans += 'b';
                --b;
                ++curr_b;
                curr_a = 0;
                curr_c = 0;


            } else if ((c >= a && c >= b && curr_c != 2) || (c > 0 && (curr_a == 2 || curr_b == 2))) {
                ans += 'c';
                --c;
                ++curr_c;
                curr_b = 0;
                curr_a = 0;
            }
        }

        return ans;
    }
};