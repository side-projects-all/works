/*
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

    For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.

Return true if you can finish all courses. Otherwise, return false.

 

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.

Example 2:

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.

 

Constraints:

    1 <= numCourses <= 2000
    0 <= prerequisites.length <= 5000
    prerequisites[i].length == 2
    0 <= ai, bi < numCourses
    All the pairs prerequisites[i] are unique.


*/

class Solution {
private:
    bool is_cycle(std::vector<std::vector<int>>& adj, std::vector<int>& visited, int node) {
        if (visited[node] == 2) {
            return false;
        }

        if (visited[node] == 1) {
            return true;
        }

        visited[node] = 1;
        for (int nei : adj[node]) {
            if (is_cycle(adj, visited, nei)) {
                return true;
            }
        }

        visited[node] = 2;
        return false;
    }
    bool by_dfs(int& numCourses, vector<vector<int>>& prerequisites) {
        if (numCourses == 1) {
            return true;
        }

        std::vector<std::vector<int>> adj(numCourses);
        std::vector<int> visited(numCourses);   //0: unvisit, 1: visiting, 2: visited

        for (int i = 0; i < prerequisites.size(); ++i) {
            adj[prerequisites[i][1]].push_back(prerequisites[i][0]);
        }

        for (int i = 0; i < numCourses; ++i) {
            if (is_cycle(adj, visited, i)) {
                return false;
            }
        }

        return true;
    }
    bool by_topological_sort(int& numCourses, vector<vector<int>>& prerequisites) {
        if (numCourses == 1) {
            return true;
        }

        std::vector<std::vector<int>> adj(numCourses);
        std::vector<int> indegree(numCourses);
        int n = prerequisites.size();

        for (int i = 0; i < n; ++i) {
            adj[prerequisites[i][1]].push_back(prerequisites[i][0]);
            ++indegree[prerequisites[i][0]];
        }

        std::queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        int visited = 0;
        while (!q.empty()) {
            int c = q.front();
            q.pop();

            ++visited;

            for (int nei : adj[c]) {
                --indegree[nei];

                if (indegree[nei] == 0) {
                    q.push(nei);
                }
            }
        }

        return visited == numCourses;
    }
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        //return by_topological_sort(numCourses, prerequisites);
        return by_dfs(numCourses, prerequisites);
    }
};