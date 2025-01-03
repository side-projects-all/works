/*
There are n items each belonging to zero or one of m groups where group[i] is the group that the i-th item belongs to and it's equal to -1 if the i-th item belongs to no group. The items and the groups are zero indexed. A group can have no item belonging to it.

Return a sorted list of the items such that:

    The items that belong to the same group are next to each other in the sorted list.
    There are some relations between these items where beforeItems[i] is a list containing all the items that should come before the i-th item in the sorted array (to the left of the i-th item).

Return any solution if there is more than one solution and return an empty list if there is no solution.

 

Example 1:

Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3,6],[],[],[]]
Output: [6,3,4,1,5,2,0,7]

Example 2:

Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3],[],[4],[]]
Output: []
Explanation: This is the same as example 1 except that 4 needs to be before 6 in the sorted list.

 

Constraints:

    1 <= m <= n <= 3 * 10^4
    group.length == beforeItems.length == n
    -1 <= group[i] <= m - 1
    0 <= beforeItems[i].length <= n - 1
    0 <= beforeItems[i][j] <= n - 1
    i != beforeItems[i][j]
    beforeItems[i] does not contain duplicates elements.


*/

class Solution {
private:
    void topologicalSort(std::unordered_map<int, std::vector<int>>& adj, 
                                std::vector<int>& indegree, std::vector<int>& visited) {

        std::queue<int> q;

        //find indices of indegree 0
        for (int i = 0; i < indegree.size(); ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int now = q.front();
            q.pop();

            visited.push_back(now);

            for (int neighbor : adj[now]) {
                --indegree[neighbor];

                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        //set empty if cycle existed
        if (visited.size() != adj.size()) {
            visited.clear();
        }
    }

public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        int groupId = m;
        for (int i = 0; i < n; ++i) {
            if (group[i] == -1) {
                
                //assign new group Id if group[i] is -1
                group[i] = groupId;
                ++groupId;
            }
        }

        std::unordered_map<int, std::vector<int>> itemAdj;
        std::vector<int> itemIndegree(n);

        std::unordered_map<int, std::vector<int>> groupAdj;
        std::vector<int> groupIndegree(groupId);
        
        for (int curr = 0; curr < n; ++curr) {
            for (int prev : beforeItems[curr]) {
                itemAdj[prev].push_back(curr);
                ++itemIndegree[curr];

                if (group[curr] != group[prev]) {
                    groupAdj[group[prev]].push_back(group[curr]);
                    ++groupIndegree[group[curr]];
                }
            }
        }

        std::vector<int> itemSorted;
        std::vector<int> groupSorted;
        topologicalSort(itemAdj, itemIndegree, itemSorted);
        topologicalSort(groupAdj, groupIndegree, groupSorted);

        //if cycle existed, return empty
        if (itemSorted.empty() || groupSorted.empty()) {
            return {};
        }

        //use groupAdj again, but we clear first
        groupAdj.clear();
        for (int item : itemSorted) {
            groupAdj[group[item]].push_back(item);
        }

        std::vector<int> result;
        for (int group : groupSorted) {
            result.insert(result.end(), groupAdj[group].begin(), groupAdj[group].end());
        }

        return result;
    }
};