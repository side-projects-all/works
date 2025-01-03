/*
You are given an integer n indicating there are n people numbered from 0 to n - 1. You are also given a 0-indexed 2D integer array meetings where meetings[i] = [xi, yi, timei] indicates that person xi and person yi have a meeting at timei. A person may attend multiple meetings at the same time. Finally, you are given an integer firstPerson.

Person 0 has a secret and initially shares the secret with a person firstPerson at time 0. This secret is then shared every time a meeting takes place with a person that has the secret. More formally, for every meeting, if a person xi has the secret at timei, then they will share the secret with person yi, and vice versa.

The secrets are shared instantaneously. That is, a person may receive the secret and share it with people in other meetings within the same time frame.

Return a list of all the people that have the secret after all the meetings have taken place. You may return the answer in any order.

 

Example 1:

Input: n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
Output: [0,1,2,3,5]
Explanation:
At time 0, person 0 shares the secret with person 1.
At time 5, person 1 shares the secret with person 2.
At time 8, person 2 shares the secret with person 3.
At time 10, person 1 shares the secret with person 5.​​​​
Thus, people 0, 1, 2, 3, and 5 know the secret after all the meetings.

Example 2:

Input: n = 4, meetings = [[3,1,3],[1,2,2],[0,3,3]], firstPerson = 3
Output: [0,1,3]
Explanation:
At time 0, person 0 shares the secret with person 3.
At time 2, neither person 1 nor person 2 know the secret.
At time 3, person 3 shares the secret with person 0 and person 1.
Thus, people 0, 1, and 3 know the secret after all the meetings.

Example 3:

Input: n = 5, meetings = [[3,4,2],[1,2,1],[2,3,1]], firstPerson = 1
Output: [0,1,2,3,4]
Explanation:
At time 0, person 0 shares the secret with person 1.
At time 1, person 1 shares the secret with person 2, and person 2 shares the secret with person 3.
Note that person 2 can share the secret at the same time as receiving it.
At time 2, person 3 shares the secret with person 4.
Thus, people 0, 1, 2, 3, and 4 know the secret after all the meetings.

 

Constraints:

    2 <= n <= 10^5
    1 <= meetings.length <= 10^5
    meetings[i].length == 3
    0 <= xi, yi <= n - 1
    xi != yi
    1 <= timei <= 10^5
    1 <= firstPerson <= n - 1


*/

class Solution {
private:
    vector<int> byDSU(int n, vector<vector<int>>& meetings, int firstPerson) {
        std::vector<int> parent(n);
        std::vector<int> rank(n, 1);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }

        std::function<int(int)> find = [&](int x) -> int {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }

            return parent[x];
        };

        std::function<void(int, int)> unionByRank = [&](int x, int y) {
            int px = find(x);
            int py = find(y);

            if (px == py) {
                return;
            }

            if (rank[px] > rank[py]) {
                parent[py] = px;
            } else if (rank[px] < rank[py]) {
                parent[px] = py;
            } else {
                parent[py] = px;
                rank[px] += 1;
            }
        };

        std::function<bool(int, int)> isConn = [&](int x, int y) -> bool {
            return find(x) == find(y);
        };

        std::function<void(int)> reset = [&](int x) {
            parent[x] = x;
            rank[x] = 1;
        };
        std::sort(meetings.begin(), meetings.end(), [](auto& a, auto& b) {
            return a[2] < b[2];
        });

        std::map<int, std::vector<std::pair<int, int>>> sameTimeMeetings;
        for (auto& m : meetings) {
            sameTimeMeetings[m[2]].emplace_back(m[0], m[1]);
        }

        //init firstPerson and 0
        unionByRank(firstPerson, 0);
        for (auto& [t, meetings] : sameTimeMeetings) {
            for (auto& [x, y] : meetings) {
                unionByRank(x, y);
            }

            for (auto& [x, y] : meetings) {
                if (!isConn(x, 0)) {
                    reset(x);
                    reset(y);
                }
            }
        }

        std::vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (isConn(i, 0)) {
                ans.push_back(i);
            }
        }

        return ans;
    }

    vector<int> byTimelyBFS(int n, vector<vector<int>>& meetings, int firstPerson) {
        std::sort(meetings.begin(), meetings.end(), [](auto& a, auto& b) {
            return a[2] < b[2];
        });

        std::map<int, std::vector<std::pair<int, int>>> sameTimeMeetings;
        for (auto& m : meetings) {
            sameTimeMeetings[m[2]].emplace_back(m[0], m[1]);
        }

        std::vector<bool> knowsSecret(n);
        knowsSecret[0] = true;
        knowsSecret[firstPerson] = true;

        for (auto& [t, meetings] : sameTimeMeetings) {

            std::unordered_map<int, std::vector<int>> meet;
            for (auto& [x, y] : meetings) {
                meet[x].push_back(y);
                meet[y].push_back(x);
            }

            std::unordered_set<int> start;
            for (auto& [x, y] : meetings) {
                if (knowsSecret[x]) {
                    start.insert(x);
                }

                if (knowsSecret[y]) {
                    start.insert(y);
                }
            }

            std::queue<int> q;
            for (auto& person : start) {
                q.push(person);
            }

            while (!q.empty()) {
                int person = q.front();
                q.pop();

                for (auto& nextP : meet[person]) {
                    if (!knowsSecret[nextP]) {
                        knowsSecret[nextP] = true;
                        q.push(nextP);
                    }
                }
            }
        }

        std::vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (knowsSecret[i]) {
                ans.push_back(i);
            }
        }

        return ans;
    }
    vector<int> byPriorityQueue(int n, vector<vector<int>>& meetings, int firstPerson) {
        std::unordered_map<int, std::vector<std::pair<int, int>>> adj;

        for (auto& m : meetings) {
            adj[m[0]].emplace_back(m[2], m[1]);
            adj[m[1]].emplace_back(m[2], m[0]);
        }

        std::priority_queue<std::pair<int, int>, 
                            std::vector<std::pair<int, int>>, 
                            std::greater<std::pair<int, int>>> pq;

        pq.emplace(0, 0);
        pq.emplace(0, firstPerson);

        std::vector<bool> visited(n);

        while (!pq.empty()) {
            auto [time, person] = pq.top();
            pq.pop();

            if (visited[person]) {
                continue;
            }

            visited[person] = true;
            for (auto [t, nextP] : adj[person]) {
                if (!visited[nextP] && t >= time) {
                    pq.emplace(t, nextP);
                }
            }
        }

        std::vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (visited[i]) {
                ans.push_back(i);
            }
        }

        return ans;
    }
    vector<int> byDFS(int n, vector<vector<int>>& meetings, int firstPerson) {
        std::unordered_map<int, std::vector<std::pair<int, int>>> adj;

        for (auto& m : meetings) {
            adj[m[0]].emplace_back(m[2], m[1]);
            adj[m[1]].emplace_back(m[2], m[0]);
        }

        std::vector<int> earliest(n, INT_MAX);
        earliest[0] = 0;
        earliest[firstPerson] = 0;

        std::stack<std::pair<int, int>> s;
        s.emplace(0, 0);
        s.emplace(0, firstPerson);

        while (!s.empty()) {
            auto [time, person] = s.top();
            s.pop();

            for (auto [t, nextP] : adj[person]) {
                if (t >= time && earliest[nextP] > t) {
                    earliest[nextP] = t;
                    s.emplace(t, nextP);
                }
            }
        }

        std::vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (earliest[i] != INT_MAX) {
                ans.push_back(i);
            }
        }

        return ans;
    }

    vector<int> byBFS(int n, vector<vector<int>>& meetings, int firstPerson) {
        std::unordered_map<int, std::vector<std::pair<int, int>>> adj;

        for (auto& m : meetings) {
            adj[m[0]].emplace_back(m[2], m[1]);
            adj[m[1]].emplace_back(m[2], m[0]);
        }

        std::vector<int> earliest(n, INT_MAX);
        earliest[0] = 0;
        earliest[firstPerson] = 0;

        std::queue<std::pair<int, int>> q;
        q.emplace(0, 0);
        q.emplace(0, firstPerson);

        while (!q.empty()) {
            auto [time, person] = q.front();
            q.pop();

            for (auto [t, nextP] : adj[person]) {
                if (t >= time && earliest[nextP] > t) {
                    earliest[nextP] = t;
                    q.emplace(t, nextP);
                }
            }
        }

        std::vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (earliest[i] != INT_MAX) {
                ans.push_back(i);
            }
        }

        return ans;
    }

public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        //return byBFS(n, meetings, firstPerson);
        //return byDFS(n, meetings, firstPerson);
        
        //return byPriorityQueue(n, meetings, firstPerson);
        
        //return byTimelyBFS(n, meetings, firstPerson);
        
        return byDSU(n, meetings, firstPerson);
    }
};