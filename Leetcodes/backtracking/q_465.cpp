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
    void pre_process(vector<vector<int>>& transactions, std::vector<int>& accounts) {
        int n = transactions.size();

        for (int i = 0; i < n; ++i) {
            accounts[transactions[i][0]] -= transactions[i][2];
            accounts[transactions[i][1]] += transactions[i][2];
        }

        std::sort(accounts.begin(), accounts.end());
        int b = 0;
        int e = 11;
        while (accounts[b] < 0 || accounts[e] > 0) {
            if (accounts[b] < 0) {
                ++b;
            }

            if (accounts[e] > 0) {
                --e;
            }
        }

        //remove zero
        accounts.erase(accounts.begin() + b, accounts.begin() + e + 1);
    }

    /*
    int recursive(std::vector<int>& mem, std::vector<int>&& accounts, int total_mask) {
        if (mem[total_mask] != -1) {
            return mem[total_mask];
        }   
        
        int balance_sum = 0;
        int ans = 0;

        for (int i = 0; i < accounts.size(); ++i) {
            int curr_bit = 1 << i;

            if ((total_mask & curr_bit) != 0) {
                balance_sum += accounts[i];
                ans = std::max(ans, recursive(mem, std::move(accounts), total_mask ^ curr_bit));
            }
        }

        mem[total_mask] = ans + (balance_sum == 0 ? 1 : 0);
        return mem[total_mask];
    }
    */
    
    int recursive(std::vector<int>&& accounts, std::vector<int>& mem, int& total, int used) {
        if (used == total) {
            return 0;
        }
        if (mem[used] != -1) {
            return mem[used];
        }

        int ans = 0;
        int balance = 0;
        for (int i = 0; i < accounts.size(); ++i) {

            if ((used & (1 << i)) == 0) {
                balance += accounts[i];
                ans = std::max(ans, recursive(std::move(accounts), mem, total, used ^ (1 << i)));
            }
        }

        mem[used] = ans + (balance == 0 ? 1 : 0);
        return mem[used];
    }
    int by_recursive_dp(vector<vector<int>>& transactions) {
        int n = transactions.size();
        if (n == 1) {
            return 1;
        }
        
        std::vector<int> accounts(12);
        pre_process(transactions, accounts);

        n = accounts.size();
        std::vector<int> mem(1 << n, -1);
        //mem[0] = 0;       //a little difference for handling base case

        //return n - recursive(mem, std::move(accounts), (1 << n) - 1); 
        int total_used = (1 << n) - 1;
        return n - recursive(std::move(accounts), mem, total_used, 0);
    }
    int back_tracking(std::vector<int>&& accounts, int& n, int pos) {
        while (pos < n && accounts[pos] == 0) {
            ++pos;
        }

        if (pos == n) {
            return 0;
        }

        int min_trans = INT_MAX;
        for (int next = pos + 1; next < n; ++next) {

            if (accounts[pos] * accounts[next] < 0) {
                int tmp = accounts[next];
                accounts[next] += accounts[pos];

                min_trans = std::min(min_trans, 1 + back_tracking(std::move(accounts), n, pos + 1));

                accounts[next] = tmp;
            }
        }

        return min_trans;
    }
    int by_back_tracking(vector<vector<int>>& transactions) {
        int n = transactions.size();
        if (n == 1) {
            return 1;
        }
        
        std::vector<int> accounts(12);
        pre_process(transactions, accounts);

        n = accounts.size();
        return back_tracking(std::move(accounts), n, 0);
    }
public:
    int minTransfers(vector<vector<int>>& transactions) {
        //return by_back_tracking(transactions);
        return by_recursive_dp(transactions);
    }
};