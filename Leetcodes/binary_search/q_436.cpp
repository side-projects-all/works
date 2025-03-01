/*
You are given an array of intervals, where intervals[i] = [starti, endi] and each starti is unique.

The right interval for an interval i is an interval j such that startj >= endi and startj is minimized. Note that i may equal j.

Return an array of right interval indices for each interval i. If no right interval exists for interval i, then put -1 at index i.

 

Example 1:

Input: intervals = [[1,2]]
Output: [-1]
Explanation: There is only one interval in the collection, so it outputs -1.

Example 2:

Input: intervals = [[3,4],[2,3],[1,2]]
Output: [-1,0,1]
Explanation: There is no right interval for [3,4].
The right interval for [2,3] is [3,4] since start0 = 3 is the smallest start that is >= end1 = 3.
The right interval for [1,2] is [2,3] since start1 = 2 is the smallest start that is >= end2 = 2.

Example 3:

Input: intervals = [[1,4],[2,3],[3,4]]
Output: [-1,2,-1]
Explanation: There is no right interval for [1,4] and [3,4].
The right interval for [2,3] is [3,4] since start2 = 3 is the smallest start that is >= end1 = 3.

 

Constraints:

    1 <= intervals.length <= 2 * 10^4
    intervals[i].length == 2
    -10^6 <= starti <= endi <= 10^6
    The start point of each interval is unique.


*/

class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        int n = intervals.size();
        //not necessary if error test case [[4, 4]] still exist 
        /*
        if (n == 1) {
            return {-1};
        }
        */
        std::vector<std::pair<int, int>> copy(n);
        for (int i = 0; i < n; ++i) {
            copy[i] = {intervals[i][0], i};
        }

        const auto compr = [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
            return p1.first < p2.first;
        };
        std::sort(copy.begin(), copy.end(), compr);

        std::vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            auto it = std::lower_bound(copy.begin(), copy.end(), std::make_pair(intervals[i][1], i), compr);

            if (it != copy.end()) {
                ans[i] = it->second;

            } else {
                ans[i] = -1;
            }
        }

        return ans;
    }
};