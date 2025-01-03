/*
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize an N-ary tree. An N-ary tree is a rooted tree in which each node has no more than N children. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that an N-ary tree can be serialized to a string and this string can be deserialized to the original tree structure.

For example, you may serialize the following 3-ary tree

 

as [1 [3[5 6] 2 4]]. Note that this is just an example, you do not necessarily need to follow this format.

Or you can follow LeetCode's level order traversal serialization format, where each group of children is separated by the null value.

 

For example, the above tree may be serialized as [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14].

You do not necessarily need to follow the above-suggested formats, there are many more different formats that work so please be creative and come up with different approaches yourself.

 

Example 1:

Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]

Example 2:

Input: root = [1,null,3,2,4,null,5,6]
Output: [1,null,3,2,4,null,5,6]

Example 3:

Input: root = []
Output: []

 

Constraints:

    The number of nodes in the tree is in the range [0, 10^4].
    0 <= Node.val <= 10^4
    The height of the n-ary tree is less than or equal to 1000
    Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.


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

class Codec {
private:
    std::pair<int, int> getNum(const std::string& data, int pos) {
        std::pair<int, int> result;
        int num = 0;
        std::string sub = "";

        while (data[pos] != '.') {
            sub += data[pos];
            ++pos;
        }

        num = std::stoi(sub);
        result.first = num;
        result.second = pos;

        return result;
    }

public:
    // Encodes a tree to a single string.
    string serialize(Node* root) {
        if (root == nullptr) {
            return "";
        }

        std::string result = "";
        //two dummy Node as sentinel
        Node* end = new Node();
        Node* child = new Node();

        std::queue<Node*> q;
        q.push(root);
        q.push(end);

        while (!q.empty()) {

            Node* now = q.front();
            q.pop();

            if (now == end) {

                //when we reach endNode, we add # to string, 
                //and then we check if the queue was empty, 
                //if it was not empty, we push endNode into it again to 
                //signify end of a level
                result += '#';
                if (!q.empty()) {
                    q.push(end);
                }

            } else if (now == child) {

                //for marking another parent
                result += '$';

            } else {

                result += std::to_string(now->val) + ".";    
                for (Node* c : now->children) {
                    q.push(c);
                }

                //check if the end of this level, 
                //if not, we add childNode for separating different parent
                if (q.front() != end) {
                    q.push(child);
                }
            }

        }

        return result;
    }
	
    // Decodes your encoded data to tree.
    Node* deserialize(string data) {
        if (data.size() == 0) {
            return nullptr;
        }
        
        //using dot to separate number!!
        //need a function to do it, 
        //return a pair, first one is result number, 
        //second one is dot position which could be used to replace original i!!!!
        //this function need std::string&, int pos_to_start, two parameter!!!!
        std::pair<int, int> nums = getNum(data, 0);
        int val = nums.first;
        int pos = nums.second + 1;  //move 1 step forward to the '#'
        Node* root = new Node(val, std::vector<Node*>());
        std::vector<Node*> currentLevel;
        std::vector<Node*> prevLevel;

        currentLevel.push_back(root);
        Node* parent = root;

        for (int i = pos; i < data.size(); ++i) {
            char d = data[i];      

            if (d == '#') {
                prevLevel = currentLevel;
                currentLevel = std::vector<Node*>();

                parent = prevLevel.front();
                //be careful if the size is zero, we could not do erase
                if (prevLevel.size() > 0) {
                    prevLevel.erase(prevLevel.begin());
                }
                
            } else {
                if (d == '$') {
                    parent = prevLevel.front();
                    //be careful if the size is zero, we could not do erase
                    if (prevLevel.size() > 0) {
                        prevLevel.erase(prevLevel.begin());
                    }

                } else {
                    
                    std::pair<int, int> nums = getNum(data, i);
                    int val = nums.first;
                    int pos = nums.second;

                    Node* child = new Node(val, std::vector<Node*>());
                    currentLevel.push_back(child);
                    parent->children.push_back(child);

                    i = pos;    //chanage i to pos to move index!!!
                }
            }
        }

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));