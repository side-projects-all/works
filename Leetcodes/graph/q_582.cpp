/*
You have n processes forming a rooted tree structure. You are given two integer arrays pid and ppid, where pid[i] is the ID of the ith process and ppid[i] is the ID of the ith process's parent process.

Each process has only one parent process but may have multiple children processes. Only one process has ppid[i] = 0, which means this process has no parent process (the root of the tree).

When a process is killed, all of its children processes will also be killed.

Given an integer kill representing the ID of a process you want to kill, return a list of the IDs of the processes that will be killed. You may return the answer in any order.

 

Example 1:

Input: pid = [1,3,10,5], ppid = [3,0,5,3], kill = 5
Output: [5,10]
Explanation: The processes colored in red are the processes that should be killed.

Example 2:

Input: pid = [1], ppid = [0], kill = 1
Output: [1]

 

Constraints:

    n == pid.length
    n == ppid.length
    1 <= n <= 5 * 10^4
    1 <= pid[i] <= 5 * 10^4
    0 <= ppid[i] <= 5 * 10^4
    Only one process has no parent.
    All the values of pid are unique.
    kill is guaranteed to be in pid.


*/

static auto _ = [](){
  std::ios::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  return nullptr;
}();

class Solution {
private:
    vector<int> byBFS(vector<int>& pid, vector<int>& ppid, int kill) {
        std::vector<int> result;
        std::unordered_map<int, std::vector<int>> m;

        int n = pid.size();
        for (int i = 0; i < n; ++i) {
            m[ppid[i]].push_back(pid[i]);
        }

        std::queue<int> q;
        q.push(kill);

        while (!q.empty()) {
            int n = q.front();
            q.pop();

            result.push_back(n);

            if (m.find(n) != m.end()) {
                for (int i : m[n]) {
                    q.push(i);
                }
            }
        }

        return result;
    }

    int find_root(int x, std::vector<int>& root) {
        if (x != root[x]) {
            return root[x] = find_root(root[x], root);
        }

        return x;
    }

    vector<int> by_DSA_Find(vector<int>& pid, vector<int>& ppid, int kill) {

        int maxVal = *std::max_element(pid.begin(), pid.end());
        std::vector<int> root(maxVal + 1);
        std::iota(root.begin(), root.end(), 0);
        
        std::vector<int> rank(maxVal + 1, 1);

        int n = pid.size();
        for (int i = 0; i < n; ++i) {
            if (pid[i] == kill) {
                continue;
            }

            int r1 = find_root(pid[i], root);
            int r2 = find_root(ppid[i], root);

            if (r1 != r2) {
                root[r1] = r2;
            }
        }

        std::vector<int> result;
        for (int i : pid) {
            if (i == kill || find_root(i, root) == kill) {
                result.push_back(i);
            }
        }

        return result;
    }
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        if (ppid.size() < pid.size()) {
            return {};
        }

        //return by_DSA_Find(pid, ppid, kill);
        return byBFS(pid, ppid, kill);
    }
};