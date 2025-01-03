/*
Given an array of meeting time intervals intervals where intervals[i] = [starti, endi], return the minimum number of conference rooms required.

 

Example 1:

Input: intervals = [[0,30],[5,10],[15,20]]
Output: 2

Example 2:

Input: intervals = [[7,10],[2,4]]
Output: 1

 

Constraints:

    1 <= intervals.length <= 10^4
    0 <= start[i] < end[i] <= 10^6


*/

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        
        //return byPriorityQueue(intervals);
        return byGreedy(intervals);
    }

private:
    int byGreedy(std::vector<std::vector<int>>& intervals) {
        int n = intervals.size();
        if (n == 1) {
            return 1;
        }

        std::vector<int> begins(n);
        std::vector<int> ends(n);
        for (int i = 0; i < n; ++i) {
            begins[i] = intervals[i][0];
            ends[i] = intervals[i][1];
        }
        std::sort(begins.begin(), begins.end());
        std::sort(ends.begin(), ends.end());

        int b = 0;
        int e = 0;
        int used = 0;
        while (b < n && e < n) {

            if (begins[b] >= ends[e]) {
                --used;
                ++e;
            }

            ++b;
            ++used;
        }

        return used;
    }
    int byPriorityQueue(std::vector<std::vector<int>>& intervals) {

        if (intervals.empty()) {
            return 0;
        }

        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

        auto compareVector = [](std::vector<int>& v1, std::vector<int>& v2) {
            return v1[0] < v2[0];
        };

        std::sort(intervals.begin(), intervals.end(), compareVector);

        pq.push(intervals[0][1]);

        for (int i = 1; i < intervals.size(); ++i) {

            if (intervals[i][0] >= pq.top()) {
                pq.pop();
            }

            pq.push(intervals[i][1]);
        }

        return pq.size();
    }
};