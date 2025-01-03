/*
You are given a 0-indexed integer array nums, and you are allowed to traverse between its indices. You can traverse between index i and index j, i != j, if and only if gcd(nums[i], nums[j]) > 1, where gcd is the greatest common divisor.

Your task is to determine if for every pair of indices i and j in nums, where i < j, there exists a sequence of traversals that can take us from i to j.

Return true if it is possible to traverse between all such pairs of indices, or false otherwise.

 

Example 1:

Input: nums = [2,3,6]
Output: true
Explanation: In this example, there are 3 possible pairs of indices: (0, 1), (0, 2), and (1, 2).
To go from index 0 to index 1, we can use the sequence of traversals 0 -> 2 -> 1, where we move from index 0 to index 2 because gcd(nums[0], nums[2]) = gcd(2, 6) = 2 > 1, and then move from index 2 to index 1 because gcd(nums[2], nums[1]) = gcd(6, 3) = 3 > 1.
To go from index 0 to index 2, we can just go directly because gcd(nums[0], nums[2]) = gcd(2, 6) = 2 > 1. Likewise, to go from index 1 to index 2, we can just go directly because gcd(nums[1], nums[2]) = gcd(3, 6) = 3 > 1.

Example 2:

Input: nums = [3,9,5]
Output: false
Explanation: No sequence of traversals can take us from index 0 to index 2 in this example. So, we return false.

Example 3:

Input: nums = [4,3,12,8]
Output: true
Explanation: There are 6 possible pairs of indices to traverse between: (0, 1), (0, 2), (0, 3), (1, 2), (1, 3), and (2, 3). A valid sequence of traversals exists for each pair, so we return true.

 

Constraints:

    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5


*/

class Solution {
private:
    bool byDSU(vector<int>& nums) {
        
        int N = nums.size();
        if (N == 1) {
            return true;
        }

        int maxVal = 0;
        for (int v : nums) {
            if (v == 1) {
                return false;
            }

            maxVal = std::max(maxVal, v);
        }
        
        //sieve of Eratosthenes
        //tag with their common prime
        std::vector<int> sieve(maxVal + 1);
        for (int d = 2; d <= maxVal; ++d) {

            if (sieve[d] == 0) {
                for (int v = d; v <= maxVal; v += d) {
                    sieve[v] = d;
                }
            }
        }

        //DSU container and function
        std::vector<int> root(maxVal + 1);
        std::vector<int> rank(maxVal + 1, 1);
        for (int i = 0; i <= maxVal; ++i) {
            root[i] = i;
        }

        std::function<int(int)> find = [&](int x) -> int {
            if (root[x] == x) {
                return x;
            }

            return root[x] = find(root[x]);
        };

        std::function<void(int, int)> unionByRank = [&](int x, int y) {
            int rx = find(x);   //rx : rootX
            int ry = find(y);   //ry : rootY

            if (rx == ry) {
                return;
            }

            if (rank[rx] > rank[ry]) {
                int tmp = rx;
                rx = ry;
                ry = tmp;
            }

            root[rx] = ry;
            rank[ry] += rank[rx];
        };

        for (int x : nums) {

            int val = x;
            while (val > 1) {

                int prime = sieve[val];
 
                unionByRank(prime, x);

                while (val % prime == 0 && val > 1) {
                    val /= prime;
                }
            }
        }

        int f = find(nums[0]);
        for (int i : nums) {
            if (find(i) != f) {
                return false;
            }
        }

        return true;
    }

public:
    bool canTraverseAllPairs(vector<int>& nums) {
        return byDSU(nums);
    }
};