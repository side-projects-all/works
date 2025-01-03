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
    0 <= nums[i] <= 231 - 1


*/

class Solution {
private:

    struct TrieNode {
        TrieNode* children[2];

        TrieNode() {

            for (auto& node : children) {
                node = nullptr;
            }
        }
    };

    TrieNode* root;

public:

    int findMaximumXOR(vector<int>& nums) {
        root = new TrieNode();
        int max = 0;
        
        //by the constraint of this question, we set the length of bitset as 32
        std::bitset<32> binaryForm;
        for (int num : nums) {
            TrieNode* now = root;
            TrieNode* xorNow = now;
            int currXor = 0;

            binaryForm = num;
            std::string binaryStr = binaryForm.to_string();
            for (int i = 0; i < binaryStr.size(); ++i) {
                int index = binaryStr[i] - '0';

                if (now->children[index] == nullptr) {
                    now->children[index] = new TrieNode();
                }

                now = now->children[index];

                //index could be 1 or 0, to maximize by XOR, 
                //if index was 0, we try to find 1, 
                //if index was 1, we try to find 0
                int reverse = (index == 1) ? 0 : 1;
                if (xorNow->children[reverse] != nullptr) {
                    //if we found it, current xor result will become 1,
                    //so we carry 1 and plus 1
                    currXor = ((currXor << 1) | 1);
                    xorNow = xorNow->children[reverse];     //if we found it, we go to the child of reverse
                    
                } else {
                    //if we did not find it, current xor result will become 0,
                    //so we just carry 1
                    currXor = (currXor << 1);
                    xorNow = xorNow->children[index];       //if we could notfound it, we go to the child of index
                }

                max = std::max(max, currXor);
            }
        }

        return max;
    }
};