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

class Solution {
public:
    Node* copyRandomList(Node* head) {

        
        //return recursive(head);
        //return iterative(head);
        return iterative02(head);
    }
    
private:
    std::unordered_map<Node*, Node*> visited;
    
    Node* recursive(Node* now) {
        if (now == NULL) {
            return NULL;
        }
        
        if (visited.find(now) != visited.end()) {
            return visited[now];
        }
        
        Node* node = new Node(now->val);
        visited[now] = node;
        
        node->next = recursive(now->next);
        node->random = recursive(now->random);
        
        return node;
    }
    
    Node* iterative(Node* now) {
        if (now == NULL) {
            return NULL;
        }
        
        Node* old = now;
        
        //copying head node
        Node* cloneNode = new Node(old->val);
        visited[now] = cloneNode;
        
        while(old != NULL) {
            cloneNode->random = getCloneNode(old->random);
            cloneNode->next = getCloneNode(old->next);
            
            old = old->next;
            cloneNode = cloneNode->next;
        }
        
        
        return visited[now];
    }
    
    Node* getCloneNode(Node* now) {
        if (now == NULL) {
            return NULL;
        }
        
        if (visited.find(now) != visited.end()) {
            return visited[now];
        }
        
        Node* node = new Node(now->val);
        visited[now] = node;
        
        return visited[now];
    }
    
    //this one only had O(1) space complexity
    Node* iterative02(Node* now) {
        if (now == NULL) {
            return NULL;
        }
        
        Node* ptr = now;
        
        //interleaving the cloning node
        while(ptr != NULL) {
            Node* newNode = new Node(ptr->val);
            
            newNode->next = ptr->next;
            ptr->next = newNode;
            
            //move on to next original node
            ptr = newNode->next;
        }
        
        //rewind to original head
        ptr = now;
        
        while(ptr != NULL) {
            ptr->next->random = (ptr->random != NULL) ? ptr->random->next : NULL;
            ptr = ptr->next->next;
        }
        
        
        //separate into original list and clone list
        Node* oldPtr = now;
        Node* clonePtr = now->next;
        Node* headNew = now->next;
        while(oldPtr != NULL) {
            oldPtr->next = oldPtr->next->next;
            clonePtr->next = (clonePtr->next != NULL) ? clonePtr->next->next : NULL;
            
            
            //MOVE ON
            oldPtr = oldPtr->next;
            clonePtr = clonePtr->next;
        }
        
        return headNew;
    }
};