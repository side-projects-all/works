/*
Given an integer n, find a sequence that satisfies all of the following:

    The integer 1 occurs once in the sequence.
    Each integer between 2 and n occurs twice in the sequence.
    For every integer i between 2 and n, the distance between the two occurrences of i is exactly i.

The distance between two numbers on the sequence, a[i] and a[j], is the absolute difference of their indices, |j - i|.

Return the lexicographically largest sequence. It is guaranteed that under the given constraints, there is always a solution.

A sequence a is lexicographically larger than a sequence b (of the same length) if in the first position where a and b differ, sequence a has a number greater than the corresponding number in b. For example, [0,1,9,0] is lexicographically larger than [0,1,5,6] because the first position they differ is at the third number, and 9 is greater than 5.

 

Example 1:

Input: n = 3
Output: [3,1,2,3,2]
Explanation: [2,3,2,1,3] is also a valid sequence, but [3,1,2,3,2] is the lexicographically largest valid sequence.

Example 2:

Input: n = 5
Output: [5,3,1,4,3,5,2,4,2]

 

Constraints:

    1 <= n <= 20


*/

class Solution {
private:
    bool recursive(int curr, std::vector<int>& ans, std::vector<bool>& is_used, int& n) {
        if (curr == ans.size()) {
            return true;
        }

        if (ans[curr] != 0) {
            return recursive(curr + 1, ans, is_used, n);
        }

        for (int num = n; num >= 1; --num) {
            if (is_used[num]) {
                continue;
            }

            is_used[num] = true;
            ans[curr] = num;

            if (num == 1) {
                if (recursive(curr + 1, ans, is_used, n)) {
                    return true;
                }

            } else if (curr + num < ans.size() && ans[curr + num] == 0) {
                ans[curr + num] = num;

                if (recursive(curr + 1, ans, is_used, n)) {
                    return true;
                }

                ans[curr + num] = 0;
            }

            is_used[num] = false;
            ans[curr] = 0;
        }

        return false;
    }

    std::vector<int> by_back_tracking(int& n) {
        std::vector<int> ans(2 * n - 1);
        std::vector<bool> is_used(n + 1);

        recursive(0, ans, is_used, n);

        return ans;
    }
public:
    vector<int> constructDistancedSequence(int n) {
        return by_back_tracking(n);
    }
};