/*
You are given an array of transactions transactions where transactions[i] = [fromi, toi, amounti] indicates that the person with ID = fromi gave amounti $ to the person with ID = toi.

Return the minimum number of transactions required to settle the debt.

 

Example 1:

Input: transactions = [[0,1,10],[2,0,5]]
Output: 2
Explanation:
Person #0 gave person #1 $10.
Person #2 gave person #0 $5.
Two transactions are needed. One way to settle the debt is person #1 pays person #0 and #2 $5 each.

Example 2:

Input: transactions = [[0,1,10],[1,0,1],[1,2,5],[2,0,5]]
Output: 1
Explanation:
Person #0 gave person #1 $10.
Person #1 gave person #0 $1.
Person #1 gave person #2 $5.
Person #2 gave person #0 $5.
Therefore, person #1 only need to give person #0 $4, and all debt is settled.

 

Constraints:

    1 <= transactions.length <= 8
    transactions[i].length == 3
    0 <= fromi, toi < 12
    fromi != toi
    1 <= amounti <= 100


*/

class Solution {
private:
    int recursive(vector<vector<int>>& transactions) {
        std::unordered_map<int, int> map;
        for (auto& v : transactions) {
            map[v[0]] += v[2];
            map[v[1]] -= v[2];
        }

        std::vector<int> notZero;
        for (auto& p : map) {
            if (p.second != 0) {
                notZero.push_back(p.second);
            }
        }

        int N = notZero.size();
        std::vector<int> mem(1 << N, -1);
        mem[0] = 0;

        std::function<int(int)> recurr = [&](int totalMask) -> int {
            
            if (mem[totalMask] != -1) {
                return mem[totalMask];
            }

            int balanceSum = 0;
            int ans = 0;
            for (int i = 0; i < N; ++i) {
                
                int currBit = 1 << i;

                if ((totalMask & currBit) != 0) {
                    balanceSum += notZero[i];

                    //totalMask ^ currBit means remove that notZero[i]
                    ans = std::max(ans, recurr(totalMask ^ currBit));
                }
                
            }

            mem[totalMask] = ans + (balanceSum == 0 ? 1 : 0);

            return mem[totalMask];
        };

        //(1 << N) - 1 means let every element in notZero array included!!!
        //e.g. 2^3 = 8, 8 is 1000, 8 - 1 = 7, 7 is 0111, all 3 elements are included!
        return N - recurr((1 << N) - 1);

        //naive method
        /*
        std::function<int(int)> recurr = [&](int curr) -> int {
            while (curr < N && notZero[curr] == 0) {
                ++curr;
            }

            if (curr == N) {
                return 0;
            }

            int trans = 429981697;
            for (int next = curr + 1; next < N; ++next) {

                if (notZero[next] * notZero[curr] < 0) {
                    notZero[next] = notZero[next] + notZero[curr];

                    trans = std::min(trans, 1 + recurr(curr + 1));

                    notZero[next] = notZero[next] - notZero[curr];
                }
            }

            return trans;
        };

        return recurr(0);
        */
    }
public:
    int minTransfers(vector<vector<int>>& transactions) {
        return recursive(transactions);
    }
};