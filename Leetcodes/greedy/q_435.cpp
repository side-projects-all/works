/*
Given an array of intervals intervals where intervals[i] = [starti, endi], return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

Note that intervals which only touch at a point are non-overlapping. For example, [1, 2] and [2, 3] are non-overlapping.

 

Example 1:

Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.

Example 2:

Input: intervals = [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of the intervals non-overlapping.

Example 3:

Input: intervals = [[1,2],[2,3]]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.

 

Constraints:

    1 <= intervals.length <= 10^5
    intervals[i].length == 2
    -5 * 10^4 <= starti < endi <= 5 * 10^4


*/

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        std::sort(intervals.begin(), intervals.end(), [](const auto& v1, const auto& v2) { return v1[1] < v2[1]; });
        
        int cnt = 0;  
        int end = INT_MIN;
        for (int i = 0; i < intervals.size(); ++i) {
            if (end > intervals[i][0]) {
                ++cnt;
            } else {
                end = intervals[i][1];
            }
        }

        return cnt;
    }
};