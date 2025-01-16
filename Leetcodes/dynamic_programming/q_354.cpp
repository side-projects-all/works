/*
You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] represents the width and the height of an envelope.

One envelope can fit into another if and only if both the width and height of one envelope are greater than the other envelope's width and height.

Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).

Note: You cannot rotate an envelope.

 

Example 1:

Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
Output: 3
Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).

Example 2:

Input: envelopes = [[1,1],[1,1],[1,1]]
Output: 1

 

Constraints:

    1 <= envelopes.length <= 10^5
    envelopes[i].length == 2
    1 <= wi, hi <= 10^5


*/

class Solution {
private:
    int iterative(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if (n == 1) {
            return 1;
        }

        std::sort(envelopes.begin(), envelopes.end(), [](auto& v1, auto& v2) {
            if (v1[0] == v2[0]) {
                return v1[1] > v2[1];
            }

            return v1[0] < v2[0];
        });

        std::vector<int> heights(n);
        for (int i = 0; i < n; ++i) {
            heights[i] = envelopes[i][1];
        }

        std::vector<int> dolls_heights;
        dolls_heights.push_back(heights[0]);
        for (int i = 1; i < n; ++i) {
            int j = std::lower_bound(dolls_heights.begin(), dolls_heights.end(), heights[i]) - dolls_heights.begin();

            if (j == dolls_heights.size()) {
                dolls_heights.push_back(heights[i]);

            } else {
                dolls_heights[j] = heights[i];
            }
        }

        return dolls_heights.size();
        /*
        int N = envelopes.size();

        std::sort(envelopes.begin(), envelopes.end(), [](const auto& v1, const auto& v2) {
            if (v1[0] == v2[0]) {
                return v1[1] > v2[1];
            }

            return v1[0] < v2[0];
        });

        std::vector<int> heights(N, 0);
        for (int i = 0; i < N; ++i) {
            heights[i] = envelopes[i][1];
        }

        std::vector<int> dp(N, 0);

        int last = 0;
        //apply the idea of longest increasing subsequence
        for (int i = 0; i < N; ++i) {
            int target = heights[i];
            int left = 0;
            int right = last;

            while (left < right) {
                int mid = left + (right - left) / 2;

                if (dp[mid] < target) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }

            dp[left] = target;

            if (left == last) {
                ++last;
            }
        }

        return last;
        */
    }
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        return iterative(envelopes);
    }
};