/*
A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Given the locations and heights of all the buildings, return the skyline formed by these buildings collectively.

The geometric information of each building is given in the array buildings where buildings[i] = [lefti, righti, heighti]:

    lefti is the x coordinate of the left edge of the ith building.
    righti is the x coordinate of the right edge of the ith building.
    heighti is the height of the ith building.

You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

The skyline should be represented as a list of "key points" sorted by their x-coordinate in the form [[x1,y1],[x2,y2],...]. Each key point is the left endpoint of some horizontal segment in the skyline except the last point in the list, which always has a y-coordinate 0 and is used to mark the skyline's termination where the rightmost building ends. Any ground between the leftmost and rightmost buildings should be part of the skyline's contour.

Note: There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...,[2 3],[4 5],[7 5],[11 5],[12 7],...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...,[2 3],[4 5],[12 7],...]

 

Example 1:

Input: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
Explanation:
Figure A shows the buildings of the input.
Figure B shows the skyline formed by those buildings. The red points in figure B represent the key points in the output list.

Example 2:

Input: buildings = [[0,2,3],[2,5,3]]
Output: [[0,3],[5,0]]

 

Constraints:

    1 <= buildings.length <= 10^4
    0 <= lefti < righti <= 2^31 - 1
    1 <= heighti <= 2^31 - 1
    buildings is sorted by lefti in non-decreasing order.


*/

class Solution {
private:
    vector<vector<int>> by_sweep_line_two_pq(vector<vector<int>>& buildings) {
        std::vector<std::pair<int, int>> edges;
        for (int i = 0; i < buildings.size(); ++i) {
            edges.push_back({buildings[i][0], buildings[i][2]});
            edges.push_back({buildings[i][1], -buildings[i][2]});
        }

        std::sort(edges.begin(), edges.end());
        std::priority_queue<int> live;
        std::priority_queue<int> past;
        std::vector<std::vector<int>> ans;
        int i = 0;
        while (i < edges.size()) {
            int curr_x = edges[i].first;

            //check the same x edges
            while (i < edges.size() && edges[i].first == curr_x) {
                int height = edges[i].second;

                if (height > 0) {
                    live.push(height);

                } else {
                    past.push(-height);
                }

                ++i;
            }

            while (!past.empty() && live.top() == past.top()) {
                live.pop();
                past.pop();
            }

            int curr_h = live.empty() ? 0 : live.top();

            if (ans.empty() || ans.back()[1] != curr_h) {
                ans.push_back({curr_x, curr_h});
            }
        }

        return ans;
    }
    vector<vector<int>> by_sweep_line_pq(vector<vector<int>>& buildings) {
        std::vector<std::pair<int, int>> edges;
        for (int i = 0; i < buildings.size(); ++i) {
            edges.push_back({buildings[i][0], i});
            edges.push_back({buildings[i][1], i});
        }

        std::sort(edges.begin(), edges.end());
        std::priority_queue<std::pair<int, int>> pq;
        std::vector<std::vector<int>> ans;
        int i = 0;
        while (i < edges.size()) {
            int curr_x = edges[i].first;

            //check the same x edges
            while (i < edges.size() && edges[i].first == curr_x) {
                int b_index = edges[i].second;

                if (buildings[b_index][0] == curr_x) {
                    int right = buildings[b_index][1];
                    int height = buildings[b_index][2];
                    pq.push({height, right});
                }

                ++i;
            }

            //pop out passed x
            while (!pq.empty() && pq.top().second <= curr_x) {
                pq.pop();
            }

            int curr_h = pq.empty() ? 0 : pq.top().first;

            if (ans.empty() || ans.back()[1] != curr_h) {
                ans.push_back({curr_x, curr_h});
            }
        }

        return ans;
    }

    std::vector<std::vector<int>> divideAndConquer(std::vector<std::vector<int>>& buildings, 
                                                    int left, int right) {

        //if there was only one building, return its left point with height and right point with 0 as end
        if (left == right) {
            return {{buildings[left][0], buildings[left][2]}, {buildings[left][1], 0}};
        }

        int mid = left + (right - left) / 2;
        std::vector<std::vector<int>> leftPart = divideAndConquer(buildings, left, mid);
        std::vector<std::vector<int>> rightPart = divideAndConquer(buildings, mid + 1, right);

        return merge(leftPart, rightPart);
    }

    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& left, 
                                        std::vector<std::vector<int>>& right) {
        
        int leftPos = 0;
        int rightPos = 0;
        int leftPrevHeight = 0;
        int rightPrevHeight = 0;
        int curr_x = 0;
        int curr_y = 0;

        std::vector<std::vector<int>> result;

        while (leftPos < left.size() && rightPos < right.size()) {
            int nextLeft_x = left[leftPos][0];
            int nextRight_x = right[rightPos][0];

            if (nextLeft_x < nextRight_x) {
                curr_x = nextLeft_x;
                curr_y = std::max(left[leftPos][1], rightPrevHeight);

                leftPrevHeight = left[leftPos][1];
                ++leftPos;

            } else if (nextLeft_x > nextRight_x) {
                curr_x = nextRight_x;
                curr_y = std::max(right[rightPos][1], leftPrevHeight);

                rightPrevHeight = right[rightPos][1];
                ++rightPos;

            } else {
                curr_x = nextLeft_x;
                curr_y = std::max(left[leftPos][1], right[rightPos][1]);

                leftPrevHeight = left[leftPos][1];
                rightPrevHeight = right[rightPos][1];
                ++leftPos;
                ++rightPos;
            }

            if (result.empty() || curr_y != result.back()[1]) {
                result.push_back({curr_x, curr_y});
            }
        }

        while (leftPos < left.size()) {
            result.push_back(left[leftPos]);
            ++leftPos;
        }

        while (rightPos < right.size()) {
            result.push_back(right[rightPos]);
            ++rightPos;
        }

        return result;
    }
    
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        return by_sweep_line_two_pq(buildings);
        //return by_sweep_line_pq(buildings);
        //return divideAndConquer(buildings, 0, buildings.size() - 1);
    }
};