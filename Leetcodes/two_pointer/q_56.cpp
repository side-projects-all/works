/*
Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.

 

Example 1:

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

Example 2:

Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.

 

Constraints:

    1 <= intervals.length <= 10^4
    intervals[i].length == 2
    0 <= starti <= endi <= 10^4


*/

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        
        int N = intervals.size();
        if (N <= 1) {
            return intervals;
        }

        std::sort(intervals.begin(), intervals.end());
        std::vector<std::vector<int>> ans;
        int s = intervals[0][0];
        int e = intervals[0][1];

        for (int i = 1; i < N; ++i) {
            
            if (e >= intervals[i][0]) {
                e = std::max(e, intervals[i][1]);

            } else {
                ans.push_back({s, e});
                s = intervals[i][0];
                e = intervals[i][1];
            }
        }

        ans.push_back({s, e});

        return ans;
    }
};