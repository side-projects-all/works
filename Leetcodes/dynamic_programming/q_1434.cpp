/*
There are n people and 40 types of hats labeled from 1 to 40.

Given a 2D integer array hats, where hats[i] is a list of all hats preferred by the ith person.

Return the number of ways that the n people wear different hats to each other.

Since the answer may be too large, return it modulo 109 + 7.

 

Example 1:

Input: hats = [[3,4],[4,5],[5]]
Output: 1
Explanation: There is only one way to choose hats given the conditions. 
First person choose hat 3, Second person choose hat 4 and last one hat 5.

Example 2:

Input: hats = [[3,5,1],[3,5]]
Output: 4
Explanation: There are 4 ways to choose hats:
(3,5), (5,3), (1,3) and (1,5)

Example 3:

Input: hats = [[1,2,3,4],[1,2,3,4],[1,2,3,4],[1,2,3,4]]
Output: 24
Explanation: Each person can choose hats labeled from 1 to 4.
Number of Permutations of (1,2,3,4) = 24.

 

Constraints:

    n == hats.length
    1 <= n <= 10
    1 <= hats[i].length <= 40
    1 <= hats[i][j] <= 40
    hats[i] contains a list of unique integers.


*/

class Solution {
private:
    int recursive(vector<vector<int>>& hats) {
        int mod = 1000000007;
        int N = hats.size();
        int people = std::pow(2, N) - 1;
        std::vector<std::vector<int>> mem(41, std::vector<int>(people, -1));

        //reverse the relationship hat to people
        std::unordered_map<int, std::vector<int>> m;
        for (int i = 0; i < N; ++i) {
            for (int v : hats[i]) {
                m[v].push_back(i);
            }
        }

        std::function<int(int, int)> recurr = [&](int hat, int mask) -> int {
            if (mask == people) {
                return 1;
            }

            if (hat > 40) {
                return 0;
            }

            if (mem[hat][mask] != -1) {
                return mem[hat][mask];
            }

            //not use this hat for this person
            int ans = recurr(hat + 1, mask);

            //use this hat
            if (m.find(hat) != m.end()) {
                for (int p : m[hat]) {

                    //check this person not have this hat
                    if ((mask & (1 << p)) == 0) {
                        ans = (ans + recurr(hat + 1, mask | (1 << p))) % mod;
                    }
                }
            }

            return mem[hat][mask] = ans;
        };

        return recurr(1, 0);
    }
public:
    int numberWays(vector<vector<int>>& hats) {
        return recursive(hats);
    }
};