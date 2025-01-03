/*

*/

class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

        for (int i = 0; i < heights.size() - 1; ++i) {
            int climb = heights[i + 1] - heights[i];

            if (climb <= 0) {
                continue;
            }

            pq.push(climb);

            if (pq.size() <= ladders) {
                continue;
            }

            bricks -= pq.top();
            pq.pop();

            if (bricks < 0) {
                return i;
            }
        }

        return heights.size() - 1;
    }
};