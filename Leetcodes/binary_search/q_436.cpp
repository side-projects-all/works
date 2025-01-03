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

struct myHash {

  template<class T1, class T2>
  std::size_t operator() (const std::pair<T1, T2>& p1) const {

    return std::hash<T1>{}(p1.first) ^ std::hash<T2>{}(p1.second);
  }
};
class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        int N = intervals.size();

        //corner case
        if (N == 1) {
          int left = intervals[0][0];
          int right = intervals[0][1];

          if (left >= right) {
            return { 0 };
          } else {
            return { -1 };
          }
        }

        //create index mapping
        std::unordered_map<std::pair<int, int>, int, myHash> m;
        for (int i = 0; i < N; ++i) {
          std::pair<int, int> p = std::make_pair(intervals[i][0], intervals[i][1]);
          m[p] = i;
        }

        std::sort(intervals.begin(), intervals.end());

        std::vector<int> result(N);

        for (int i = 0; i < N; ++i) {
          int target = intervals[i][1];

          //find from the indices that are larger than poisiton now
          int left = i;
          int right = N - 1;

          while (left <= right) {
            int mid = left + (right - left) / 2;

            if (target == intervals[mid][0]) {
              left = mid;
              break;
            }

            if (target > intervals[mid][0]) {
              left = mid + 1;
            } else {
              right = mid - 1;
            }
          }

          std::pair<int, int> p = { intervals[i][0], intervals[i][1] };
          int index = m[p];

          if (left < N) {
            p = { intervals[left][0], intervals[left][1] };
            int original_index_of_left = m[p];

            result[index] = original_index_of_left;

          } else {
            result[index] = -1;
          }
        }

        return result;
    }
};