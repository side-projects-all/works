/*
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

    For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.

Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

 

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].

Example 2:

Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].

Example 3:

Input: numCourses = 1, prerequisites = []
Output: [0]

 

Constraints:

    1 <= numCourses <= 2000
    0 <= prerequisites.length <= numCourses * (numCourses - 1)
    prerequisites[i].length == 2
    0 <= ai, bi < numCourses
    ai != bi
    All the pairs [ai, bi] are distinct.


*/

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        
        //std::unordered_map<int, std::vector<int>> adjNodes;
        std::vector<std::vector<int>> adjNodes(numCourses);
        std::vector<int> indegree(numCourses, 0);
        std::vector<int> result(numCourses, 0);

        //build adjacent list
        for (const auto &pre : prerequisites) {
            int dest = pre[0];
            int src = pre[1];

            adjNodes[src].push_back(dest);
            /*
            if (adjNodes.find(src) == adjNodes.end()) {
                adjNodes.insert(std::make_pair(src, std::vector<int>(1, dest)));
            } else {
                std::vector<int> list = adjNodes[src];
                list.push_back(dest);
                adjNodes[src] = list;
            }
            */
            
            indegree[dest] += 1;
        }

        //queue
        std::queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        //for checking if loop all nodes, if not, then return empty list
        int index = 0;
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            result[index] = node;
            ++index;

            for (auto neighbor : adjNodes[node]) {
                //reduce the degree
                indegree[neighbor] -= 1;

                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
            /*
            if (adjNodes.find(node) != adjNodes.end()) {
                for (auto neighbor : adjNodes[node]) {
                    //reduce the degree
                    indegree[neighbor] -= 1;

                    if (indegree[neighbor] == 0) {
                        q.push(neighbor);
                    }
                }
            }
            
            */
        }

        if (index == numCourses) {
            return result;
        }
        
        return {};
    }
};