/*
A linked list of length n is given such that each node contains an additional random pointer, which could point to any node in the list, or null.

Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes, where each new node has its value set to the value of its corresponding original node. Both the next and random pointer of the new nodes should point to new nodes in the copied list such that the pointers in the original list and copied list represent the same list state. None of the pointers in the new list should point to nodes in the original list.

For example, if there are two nodes X and Y in the original list, where X.random --> Y, then for the corresponding two nodes x and y in the copied list, x.random --> y.

Return the head of the copied linked list.

The linked list is represented in the input/output as a list of n nodes. Each node is represented as a pair of [val, random_index] where:

    val: an integer representing Node.val
    random_index: the index of the node (range from 0 to n-1) that the random pointer points to, or null if it does not point to any node.

Your code will only be given the head of the original linked list.

 

Example 1:

Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]

Example 2:

Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]

Example 3:

Input: head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]

 

Constraints:

    0 <= n <= 1000
    -10^4 <= Node.val <= 10^4
    Node.random is null or is pointing to some node in the linked list.


*/


/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
private:
    Node* by_iterative(Node* head) {
        if (head == nullptr) {
            return head;
        }

        std::unordered_map<Node*, Node*> visited;

        std::function<Node*(Node*)> get_clone = [&visited](Node* node) -> Node* {

            if (node != nullptr) {
                if (visited.find(node) == visited.end()) {
                    visited[node] = new Node(node->val);
                }

                return visited[node];
            }

            return node;
        };

        Node* now = head;
        Node* copy = new Node(now->val);
        visited[now] = copy;

        while (now != nullptr) {
            copy->next = get_clone(now->next);
            copy->random = get_clone(now->random);

            now = now->next;
            copy = copy->next;
        }

        return visited[head];
    }

    Node* recursive(Node* head, std::unordered_map<Node*, Node*>& mem) {
        if (head == nullptr) {
            return head;
        }

        if (mem.find(head) != mem.end()) {
            return mem[head];
        }

        Node* now = new Node(head->val);
        mem[head] = now;

        now->next = recursive(head->next, mem);
        now->random = recursive(head->random, mem);

        return now;
    }
    Node* by_recursive(Node* head) {
        if (head == nullptr) {
            return head;
        }
        std::unordered_map<Node*, Node*> mem;

        return recursive(head, mem);
    }
public:
    Node* copyRandomList(Node* head) {
        //return by_recursive(head);
        return by_iterative(head);
    }
};