/*

*/

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        std::priority_queue<std::pair<int, std::pair<int, int>>> pq;

        for (std::vector<int> point : points) {
            int dist = point[0] * point[0] + point[1] * point[1];
            pq.push({dist, { point[0], point[1] }});

            if (pq.size() > k) {
                pq.pop();
            }
        }

        std::vector<std::vector<int>> ans;

        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();

            ans.push_back({ top.second.first, top.second.second });
        }

        return ans;
    }
};