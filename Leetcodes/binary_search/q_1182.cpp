/*
You are given an array colors, in which there are three colors: 1, 2 and 3.

You are also given some queries. Each query consists of two integers i and c, return the shortest distance between the given index i and the target color c. If there is no solution return -1.

 

Example 1:

Input: colors = [1,1,2,1,3,2,2,3,3], queries = [[1,3],[2,2],[6,1]]
Output: [3,0,3]
Explanation: 
The nearest 3 from index 1 is at index 4 (3 steps away).
The nearest 2 from index 2 is at index 2 itself (0 steps away).
The nearest 1 from index 6 is at index 3 (3 steps away).

Example 2:

Input: colors = [1,2], queries = [[0,3]]
Output: [-1]
Explanation: There is no 3 in the array.

 

Constraints:

    1 <= colors.length <= 5*10^4
    1 <= colors[i] <= 3
    1 <= queries.length <= 5*10^4
    queries[i].length == 2
    0 <= queries[i][0] < colors.length
    1 <= queries[i][1] <= 3


*/

class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        int n = colors.size();
        std::vector<std::vector<int>> m(4);    //val to index array
        for (int i = 0; i < n; ++i) {
            m[colors[i]].push_back(i);
        }

        n = queries.size();
        std::vector<int> ans(n);
        int i = 0;
        for (const auto& q : queries) {

            if (m[q[1]].empty()) {
                ans[i] = -1;

            } else if (colors[q[0]] == q[1]) {   //the same color
                ans[i] = 0;
            } else {
                int index = std::lower_bound(m[q[1]].begin(), m[q[1]].end(), q[0]) - m[q[1]].begin();

                if (index == m[q[1]].size()) {
                    ans[i] = q[0] - m[q[1]][index - 1];   //right most
                } else if (index == 0) {
                    ans[i] = m[q[1]][index] - q[0];       //left most
                } else {
                    ans[i] = std::min(q[0] - m[q[1]][index - 1], m[q[1]][index] - q[0]);
                }
            }
            
            ++i;
        }

        return ans;
    }
};