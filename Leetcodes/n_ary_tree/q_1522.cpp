/*
Given a root of an N-ary tree, you need to compute the length of the diameter of the tree.

The diameter of an N-ary tree is the length of the longest path between any two nodes in the tree. This path may or may not pass through the root.

(Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value.)

 

Example 1:

Input: root = [1,null,3,2,4,null,5,6]
Output: 3
Explanation: Diameter is shown in red color.

Example 2:

Input: root = [1,null,2,null,3,4,null,5,null,6]
Output: 4

Example 3:

Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: 7

 

Constraints:

    The depth of the n-ary tree is less than or equal to 1000.
    The total number of nodes is between [1, 10^4].


*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
private:
    int recursive(Node* root, int& diameter) {
        //base case: reach leaf
        if (root != nullptr && root->children.size() == 0) {
            return 0;
        }

        //constant space for tracking two max height
        //the longest path that is bridged by a non-leaf node will come from 
        //the combination of two longest sub-paths downward to the leaves nodes 
        //from this non-leaf node.
        int maxHeight1 = 0;
        int maxHeight2 = 0;
        for (Node* c : root->children) {
            int parentHeight = recursive(c, diameter) + 1;

            if (parentHeight > maxHeight1) {
                maxHeight2 = maxHeight1;
                maxHeight1 = parentHeight;
            } else if (parentHeight > maxHeight2) {
                maxHeight2 = parentHeight;
            }

            int dis = maxHeight2 + maxHeight1;
            diameter = std::max(diameter, dis);
        }

        return maxHeight1;
    }
public:
    int diameter(Node* root) {
        int diameter = 0;

        recursive(root, diameter);

        return diameter;
    }
};