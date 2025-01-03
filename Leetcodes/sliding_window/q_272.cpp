/*
Given the root of a binary search tree, a target value, and an integer k, return the k values in the BST that are closest to the target. You may return the answer in any order.

You are guaranteed to have only one unique set of k values in the BST that are closest to the target.

 

Example 1:

Input: root = [4,2,5,1,3], target = 3.714286, k = 2
Output: [4,3]

Example 2:

Input: root = [1], target = 0.000000, k = 1
Output: [1]

 

Constraints:

    The number of nodes in the tree is n.
    1 <= k <= n <= 10^4.
    0 <= Node.val <= 10^9
    -10^9 <= target <= 10^9

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        //return by_inorder_two_ptr(root, target, k);
        
        return by_inorder_deq(root, target, k);
    }

private:
    std::vector<int> by_inorder_deq(TreeNode* root, double target, int k) {
        std::deque<int> dq;
        inorder_deq(root, dq, target, k);

        return {dq.begin(), dq.end()};
    }

    void inorder_deq(TreeNode* root, std::deque<int>& dq, double& target, int& k) {
        if (root == nullptr) {
            return;
        }

        inorder_deq(root->left, dq, target, k);
        dq.push_back(root->val);
        if (dq.size() > k) {
            if (std::abs(dq.front() - target) <= std::abs(dq.back() - target)) {
                dq.pop_back();
                return;
            } else {
                dq.pop_front();
            }
        }

        inorder_deq(root->right, dq, target, k);
    }

    std::vector<int> by_inorder_two_ptr(TreeNode* root, double target, int k) {
        std::vector<int> arr;
        inorder_vec(root, arr, target);

        if (k == arr.size()) {
            return arr;
        }

        double min_diff = DBL_MAX;
        int min_pos = 0;  //min_pos
        for (int i = 0; i < arr.size(); ++i) {
            if (std::abs(arr[i] - target) < min_diff) {
                min_diff = std::abs(arr[i] - target);
                min_pos = i;
            }
        }

        std::vector<int> ans(k);
        
        if (min_pos == 0) {

            //min position at 0
            for (int i = 0; i < k; ++i) {
                ans[i] = arr[i];
            }
        } else if (min_pos == arr.size() - 1) {

            //min position at arr.size() - 1
            for (int i = arr.size() - k; i < arr.size(); ++i) {
                ans[i - arr.size() + k] = arr[i];
            }

        } else {
            int b = min_pos;    //begin
            int e = min_pos + 1;    //end

            while (e - b - 1 < k) {

                if (b < 0) {
                    ++e;
                    continue;
                }  
                
                if (e == arr.size() || std::abs(arr[b] - target) <= std::abs(arr[e] - target)){
                    --b;
                } else {
                    ++e;
                }

            }

            for (int i = b + 1; i < e; ++i) {
                ans[i - b - 1] = arr[i];
            }
        }

        return ans;
    }
    void inorder_vec(TreeNode* root, std::vector<int>& arr, double target) {
        if (root == nullptr) {
            return;
        }

        inorder_vec(root->left, arr, target);
        arr.push_back(root->val);
        inorder_vec(root->right, arr, target);
    }
};