/*
There are n piles of coins on a table. Each pile consists of a positive number of coins of assorted denominations.

In one move, you can choose any coin on top of any pile, remove it, and add it to your wallet.

Given a list piles, where piles[i] is a list of integers denoting the composition of the ith pile from top to bottom, and a positive integer k, return the maximum total value of coins you can have in your wallet if you choose exactly k coins optimally.

 

Example 1:

Input: piles = [[1,100,3],[7,8,9]], k = 2
Output: 101
Explanation:
The above diagram shows the different ways we can choose k coins.
The maximum total we can obtain is 101.

Example 2:

Input: piles = [[100],[100],[100],[100],[100],[100],[1,1,1,1,1,1,700]], k = 7
Output: 706
Explanation:
The maximum total can be obtained if we choose all coins from the last pile.

 

Constraints:

    n == piles.length
    1 <= n <= 1000
    1 <= piles[i][j] <= 105
    1 <= k <= sum(piles[i].length) <= 2000



*/

class Solution {
private:
    int recursive(vector<vector<int>>& prefixSums, int k, int i, std::vector<std::vector<int>>& mem) {
        //base case: index less than 0 or k is 0
        if (i < 0 || k == 0) {
            return 0;
        }

        if (mem[i][k] != -1) {
            return mem[i][k];
        }

        int pileLen = prefixSums[i].size();
        //using minimal lenth
        int minLen = std::min(pileLen, k);

        //two recursive condition: not take from this pile, and take from this pile
        int notTake = recursive(prefixSums, k, i - 1, mem);

        //if we take from this pile, then we have to count in the coin of this pile, 
        int take = 0;

        //then we sum up value now and what we pick next during recursion and find out which one is maximum
        for (int p = 0; p < minLen; ++p) {
            take = std::max(take, prefixSums[i][p] + recursive(prefixSums, k - p - 1, i - 1, mem));
        }

        mem[i][k] = std::max(take, notTake);

        return mem[i][k];
    }
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        //sum in advance, then we do not need to sum during processing
        /*
        std::vector<std::vector<int>> prefixSums;
        for (auto& p : piles) {
            std::vector<int> pile = p;
            
            for (int i = 1; i < p.size(); ++i) {
                pile[i] = pile[i] + pile[i - 1];
            }

            prefixSums.push_back(pile);
        }

        //for memoization
        std::vector<std::vector<int>> mem(piles.size() + 1, std::vector<int>(k + 1, -1));

        return recursive(prefixSums, k, piles.size() - 1, mem);
        */
        
        int n = piles.size();
        //n piles, take k coins, maximize the money
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1));   

        for (int i = 1; i <= n; ++i) {
            for (int coins = 0; coins <= k; ++coins) {
                
                int curr_sum = 0;
                //piles[i - 1].size() will change!!!
                int coins_len = std::min((int)piles[i - 1].size(), coins);

                for (int curr_coins = 0; curr_coins <= coins_len; ++curr_coins) {
                    if (curr_coins > 0) {
                        //from previous number of piles, we get total money = (curr_coins - 1)
                        //accumulate amount from different number of coins
                        curr_sum += piles[i - 1][curr_coins - 1];
                    }

                    dp[i][coins] = std::max(dp[i][coins], dp[i - 1][coins - curr_coins] + curr_sum);
                }
            }
        }

        return dp[n][k];
    }
};