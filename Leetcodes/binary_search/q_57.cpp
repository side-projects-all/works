/*
You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi] represent the start and the end of the ith interval and intervals is sorted in ascending order by starti. You are also given an interval newInterval = [start, end] that represents the start and end of another interval.

Insert newInterval into intervals such that intervals is still sorted in ascending order by starti and intervals still does not have any overlapping intervals (merge overlapping intervals if necessary).

Return intervals after the insertion.

Note that you don't need to modify intervals in-place. You can make a new array and return it.

 

Example 1:

Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Example 2:

Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

 

Constraints:

    0 <= intervals.length <= 10^4
    intervals[i].length == 2
    0 <= starti <= endi <= 10^5
    intervals is sorted by starti in ascending order.
    newInterval.length == 2
    0 <= start <= end <= 10^5


*/

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int pos = std::lower_bound(intervals.begin(), intervals.end(), newInterval) - intervals.begin();
        intervals.insert(intervals.begin() + pos, newInterval);

        std::vector<std::vector<int>> ans;
        for (const auto& v : intervals) {
            if (ans.empty() || ans.back()[1] < v[0]) {
                ans.push_back(v);
            } else {
                ans.back()[1] = std::max(ans.back()[1], v[1]);
            }
        }

        return ans;
    }
};

/*
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int N = intervals.size();
        int target = newInterval[0];
        int left = 0;
        int right = N - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (intervals[mid][0] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        intervals.insert(intervals.begin() + left , newInterval);
        std::vector<std::vector<int>> ans;

        for (const auto& v : intervals) {
            if (ans.empty() || ans.back()[1] < v[0]) {
                ans.push_back(v);
            } else {
                ans.back()[1] = std::max(ans.back()[1], v[1]);
            }
        }

        return ans;
    }
};
*/