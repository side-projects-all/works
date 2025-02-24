/*
Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.

You must write an algorithm that runs in O(n) time.

 

Example 1:

Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.

Example 2:

Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9

 

Constraints:

    0 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9


*/

class Solution {
private:
    class Union_find {
    private:
        std::vector<int> parent;
        std::vector<int> rank;
    public:
        Union_find(int n) {
            parent.resize(n);
            rank.resize(n, 1);

            for (int i = 0; i < n; ++i) {
                parent[i] = i;
            }
        }

        int find(int x) {
            if (parent[x] == x) {
                return x;
            }

            return parent[x] = find(parent[x]);
        }

        void union_set(int x, int y) {
            int px = find(x);
            int py = find(y);

            if (px == py) {
                return;
            }

            parent[py] = px;
            rank[px] += rank[py];
            /*
            if (rank[px] > rank[py]) {
                parent[py] = px;
                rank[px] += rank[py];

            } else {
                parent[px] = py;
                rank[py] += rank[px];
            }
            */
        }

        int LCS() {
            int max_lcs = 0;
            for (int i = 0; i < parent.size(); ++i) {
                if (parent[i] == i && rank[i] > max_lcs) {
                    max_lcs = rank[i];
                }
            }

            return max_lcs;
        }
    };
    
    int by_union_find(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return 1;
        }

        Union_find uf(n);
        std::unordered_map<int, int> val_to_i;

        for (int i = 0; i < n; ++i) {
            if (val_to_i.find(nums[i]) != val_to_i.end()) {
                continue;
            }

            if (val_to_i.find(nums[i] - 1) != val_to_i.end()) {
                uf.union_set(i, val_to_i[nums[i] - 1]);
            }

            if (val_to_i.find(nums[i] + 1) != val_to_i.end()) {
                uf.union_set(i, val_to_i[nums[i] + 1]);
            }

            val_to_i[nums[i]] = i;
        }

        return uf.LCS();
    }
    int by_hash_set(vector<int>& nums) {
        std::unordered_set<int> set(nums.begin(), nums.end());

        int longest = 0;
        for (const auto& n : set) {

            if (!set.count(n - 1)) {
                int curr = n;
                int cnt = 1;
                while (set.count(curr + 1)) {
                    ++curr;
                    ++cnt; 
                }

                longest = std::max(longest, cnt);
            }
        }

        return longest;
    }
public:
    int longestConsecutive(vector<int>& nums) {
        //return by_hash_set(nums);
        return by_union_find(nums);
    }
};