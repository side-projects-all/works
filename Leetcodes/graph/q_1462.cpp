/*
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course ai first if you want to take course bi.

    For example, the pair [0, 1] indicates that you have to take course 0 before you can take course 1.

Prerequisites can also be indirect. If course a is a prerequisite of course b, and course b is a prerequisite of course c, then course a is a prerequisite of course c.

You are also given an array queries where queries[j] = [uj, vj]. For the jth query, you should answer whether course uj is a prerequisite of course vj or not.

Return a boolean array answer, where answer[j] is the answer to the jth query.

 

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
Output: [false,true]
Explanation: The pair [1, 0] indicates that you have to take course 1 before you can take course 0.
Course 0 is not a prerequisite of course 1, but the opposite is true.

Example 2:

Input: numCourses = 2, prerequisites = [], queries = [[1,0],[0,1]]
Output: [false,false]
Explanation: There are no prerequisites, and each course is independent.

Example 3:

Input: numCourses = 3, prerequisites = [[1,2],[1,0],[2,0]], queries = [[1,0],[1,2]]
Output: [true,true]

 

Constraints:

    2 <= numCourses <= 100
    0 <= prerequisites.length <= (numCourses * (numCourses - 1) / 2)
    prerequisites[i].length == 2
    0 <= ai, bi <= numCourses - 1
    ai != bi
    All the pairs [ai, bi] are unique.
    The prerequisites graph has no cycles.
    1 <= queries.length <= 10^4
    0 <= ui, vi <= numCourses - 1
    ui != vi


*/

class Solution {
private:
    vector<bool> by_topological_sort(int& numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        
        std::vector<std::vector<int>> adj(numCourses, std::vector<int>());
        std::vector<int> indegree(numCourses);
        for (int i = 0; i < prerequisites.size(); ++i) {
            adj[prerequisites[i][0]].push_back(prerequisites[i][1]);
            ++indegree[prerequisites[i][1]];
        }

        std::queue<int> q;
        for (int i = 0; i < indegree.size(); ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        std::unordered_map<int, std::unordered_set<int>> pre_courses;
        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (auto& next_course : adj[node]) {

                pre_courses[next_course].insert(node);
                for (auto& pre_c : pre_courses[node]) {
                    pre_courses[next_course].insert(pre_c);
                }

                --indegree[next_course];
                if (indegree[next_course] == 0) {
                    q.push(next_course);
                }
            }
        }

        std::vector<bool> ans(queries.size());
        for (int q = 0; q < queries.size(); ++q) {
            ans[q] = pre_courses[queries[q][1]].contains(queries[q][0]);
        }
        return ans;
    }
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        return by_topological_sort(numCourses, prerequisites, queries);
    }
};