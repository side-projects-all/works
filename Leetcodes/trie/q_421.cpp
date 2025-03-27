/*
Given an integer array nums, return the maximum result of nums[i] XOR nums[j], where 0 <= i <= j < n.

 

Example 1:

Input: nums = [3,10,5,25,2,8]
Output: 28
Explanation: The maximum result is 5 XOR 25 = 28.

Example 2:

Input: nums = [14,70,53,83,49,91,36,80,92,51,66,70]
Output: 127

 

Constraints:

    1 <= nums.length <= 2 * 10^5
    0 <= nums[i] <= 2^31 - 1


*/

class Solution {
private:
    struct Trie_node {
        Trie_node* subs[2];
        Trie_node() {
            subs[0] = nullptr;
            subs[1] = nullptr;
        }

        void put(int i, Trie_node* node) {
            if (i >= 0 && i <= 1 && subs[i] == nullptr) {
                subs[i] = node;
            }
        }

        bool contains(int i) {
            return i >= 0 && i <= 1 && subs[i] != nullptr;
        }
    };

    struct Trie {
        Trie_node* root;
        Trie() {
            root = new Trie_node();
        }
    };

    int by_trie(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return 0;
        }

        Trie trie;
        Trie_node* now;
        Trie_node* rev;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            now = trie.root;
            rev = trie.root;
            int tmp = 0;

            for (int bits = 31; bits >= 0; --bits) {
                int digit = (nums[i] >> bits) & 1;  //get most significant bit!

                if (!now->contains(digit)) {
                    now->put(digit, new Trie_node());
                }

                if (rev->contains(1 - digit)) {
                    tmp += 1 << bits;
                    rev = rev->subs[1 - digit];

                } else {
                    rev = rev->subs[digit];
                }

                now = now->subs[digit];
            }

            ans = std::max(ans, tmp);
        }

        return ans;
    }
public:
    int findMaximumXOR(vector<int>& nums) {
        return by_trie(nums);
    }
};