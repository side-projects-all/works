/*
Design your implementation of the linked list. You can choose to use a singly or doubly linked list.
A node in a singly linked list should have two attributes: val and next. val is the value of the current node, and next is a pointer/reference to the next node.
If you want to use the doubly linked list, you will need one more attribute prev to indicate the previous node in the linked list. Assume all nodes in the linked list are 0-indexed.

Implement the MyLinkedList class:

    MyLinkedList() Initializes the MyLinkedList object.
    int get(int index) Get the value of the indexth node in the linked list. If the index is invalid, return -1.
    void addAtHead(int val) Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
    void addAtTail(int val) Append a node of value val as the last element of the linked list.
    void addAtIndex(int index, int val) Add a node of value val before the indexth node in the linked list. If index equals the length of the linked list, the node will be appended to the end of the linked list. If index is greater than the length, the node will not be inserted.
    void deleteAtIndex(int index) Delete the indexth node in the linked list, if the index is valid.


Example 1:

Input
["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get", "deleteAtIndex", "get"]
[[], [1], [3], [1, 2], [1], [1], [1]]
Output
[null, null, null, null, 2, null, 3]

Explanation
MyLinkedList myLinkedList = new MyLinkedList();
myLinkedList.addAtHead(1);
myLinkedList.addAtTail(3);
myLinkedList.addAtIndex(1, 2);    // linked list becomes 1->2->3
myLinkedList.get(1);              // return 2
myLinkedList.deleteAtIndex(1);    // now the linked list is 1->3
myLinkedList.get(1);              // return 3


Constraints:

    0 <= index, val <= 1000
    Please do not use the built-in LinkedList library.
    At most 2000 calls will be made to get, addAtHead, addAtTail, addAtIndex and deleteAtIndex.


*/

class MyLinkedList {
private:
    
    struct Node {
        int val;
        Node* next;
        Node(int v) : val(v), next(NULL) {}
    };
    
    Node* header;    
    int len;    

    //the parameter index means the index-th node ex: index = 5, it's 5th node
    Node* getNode(int index) {
        
        Node* now = header;
        
        //index from 0
        int i = 0;
        while(now != NULL && i < index) {
            now = now->next;
            ++i;
        }
        return now;
        
    }
    
public:
    //this is 0-indexed linked list, starting from 0 !!!
    MyLinkedList() {    
        len = 0;
        header = NULL;   
    }
    //the parameter index means the index-th node ex: index = 5, it's 5th node
    int get(int index) {

        //index from 0
        if (index < 0 || header == NULL || index > len) {
            return -1;
        }
        
        int result = -1;
        Node* now = getNode(index);
        
        if (now != NULL) {
            result = now->val;
        }
        
        return result;
    }
    
    void addAtHead(int val) {

        Node* newHeader = new Node(val);
        newHeader->next = header;
        header = newHeader;
        ++len;
    }
    
    void addAtTail(int val) {
        
        Node* newTail = new Node(val);
        if (header == NULL) {
            addAtHead(val);
            return;
        }
        
        Node* oldTail = getNode(len - 1);   //use len - 1 to get last node
        oldTail->next = newTail;
        newTail->next = NULL;
        ++len;

    }
    //the parameter index means the index-th node ex: index = 5, it's 5th node
    void addAtIndex(int index, int val) {
        
        //we could not add at the position which is larger than length
        if (index < 0 || index > len) {
            return;
        }
        
        if (index == 0) {
            addAtHead(val);
            return;
        }
        
        if (index == len) {
            addAtTail(val);
            return;
        }
        
        Node* newNode = new Node(val);
        
        //index - 1, means node prev 
        Node* prev = getNode(index - 1);   
        Node* nextForNewNode = prev->next;
        prev->next = newNode;
        newNode->next = nextForNewNode;
        ++len;
        
        
    }
    //the parameter index means the index-th node ex: index = 5, it's 5th node
    void deleteAtIndex(int index) {
        if (index < 0 || index > len) {
            return;
        }
        
        Node* now = NULL;
        Node* prev = NULL;
        Node* nextNode = NULL;
        //delete at header
        if (index == 0) {
            now = header;
            nextNode = now->next;
            header = nextNode;
            
            now->next = NULL;
            delete now;
            --len;
            return;
        }
        
        //index - 1, means node prev 
        prev = getNode(index - 1);
        now = prev->next;
        if (now != NULL) {
            prev->next = now->next;
            now->next = NULL;
            delete now;
            --len;
        }
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */