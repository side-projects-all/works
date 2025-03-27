/*
You are given a positive integer days representing the total number of days an employee is available for work (starting from day 1). You are also given a 2D array meetings of size n where, meetings[i] = [start_i, end_i] represents the starting and ending days of meeting i (inclusive).

Return the count of days when the employee is available for work but no meetings are scheduled.

Note: The meetings may overlap.

 

Example 1:

Input: days = 10, meetings = [[5,7],[1,3],[9,10]]

Output: 2

Explanation:

There is no meeting scheduled on the 4th and 8th days.

Example 2:

Input: days = 5, meetings = [[2,4],[1,3]]

Output: 1

Explanation:

There is no meeting scheduled on the 5th day.

Example 3:

Input: days = 6, meetings = [[1,6]]

Output: 0

Explanation:

Meetings are scheduled for all working days.

 

Constraints:

    1 <= days <= 10^9
    1 <= meetings.length <= 10^5
    meetings[i].length == 2
    1 <= meetings[i][0] <= meetings[i][1] <= days


*/

class Solution {
public:
    int countDays(int days, vector<vector<int>>& meetings) {
        if (days == 1) {
            return 0;
        }

        std::sort(meetings.begin(), meetings.end(), [](std::vector<int>& v1, std::vector<int>& v2) {
            if (v1[0] == v2[0]) {
                return v1[1] < v2[1];
            }

            return v1[0] < v2[0];
        });

        int cnt = 0;
        int n = meetings.size();
        int max_end = meetings[0][1];
        int min_begin = meetings[0][0];

        for (int i = 1; i < n; ++i) {
            
            if (meetings[i][0] > max_end) {
                cnt += meetings[i][0] - max_end - 1;
            }

            min_begin = std::min(min_begin, meetings[i][0]);
            max_end = std::max(max_end, meetings[i][1]);
        }

        //corner case: gap between day1 and min_begin and gap between end day and max_end
        //the starting and ending days of meeting i (inclusive)
        cnt += min_begin - 1;         
        cnt += days - max_end;  

        return cnt;
    }
};