/*
Given a list of 24-hour clock time points in "HH:MM" format, return the minimum minutes difference between any two time-points in the list.

 

Example 1:

Input: timePoints = ["23:59","00:00"]
Output: 1

Example 2:

Input: timePoints = ["00:00","23:59","00:00"]
Output: 0

 

Constraints:

    2 <= timePoints.length <= 2 * 10^4
    timePoints[i] is in the format "HH:MM".

*/

class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        int n = timePoints.size();
        std::vector<int> mins(n);
        for (int i = 0; i < n; ++i) {
            int h = (timePoints[i][0] - '0') * 10 + timePoints[i][1] - '0';
            int m = (timePoints[i][3] - '0') * 10 + timePoints[i][4] - '0';
            mins[i] = h * 60 + m;
        }

        std::sort(mins.begin(), mins.end());
        int ans = INT_MAX;
        for (int i = 1; i < n; ++i) {
            ans = std::min(ans, mins[i] - mins[i - 1]);
        }

        return std::min(ans, 24 * 60 - mins[n - 1] + mins[0]);
    }
};