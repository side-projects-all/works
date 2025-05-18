/*
Design a data structure to store the strings' count with the ability to return the strings with minimum and maximum counts.

Implement the AllOne class:

    AllOne() Initializes the object of the data structure.
    inc(String key) Increments the count of the string key by 1. If key does not exist in the data structure, insert it with count 1.
    dec(String key) Decrements the count of the string key by 1. If the count of key is 0 after the decrement, remove it from the data structure. It is guaranteed that key exists in the data structure before the decrement.
    getMaxKey() Returns one of the keys with the maximal count. If no element exists, return an empty string "".
    getMinKey() Returns one of the keys with the minimum count. If no element exists, return an empty string "".

Note that each function must run in O(1) average time complexity.

 

Example 1:

Input
["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey", "getMinKey"]
[[], ["hello"], ["hello"], [], [], ["leet"], [], []]
Output
[null, null, null, "hello", "hello", null, "hello", "leet"]

Explanation
AllOne allOne = new AllOne();
allOne.inc("hello");
allOne.inc("hello");
allOne.getMaxKey(); // return "hello"
allOne.getMinKey(); // return "hello"
allOne.inc("leet");
allOne.getMaxKey(); // return "hello"
allOne.getMinKey(); // return "leet"

 

Constraints:

    1 <= key.length <= 10
    key consists of lowercase English letters.
    It is guaranteed that for each call to dec, key is existing in the data structure.
    At most 5 * 104 calls will be made to inc, dec, getMaxKey, and getMinKey.


*/

class AllOne {
private:
    struct Node {       //list node order by freq
        int freq{ 0 };
        Node* prev{ nullptr };
        Node* next{ nullptr };
        std::unordered_set<std::string> keys;

        Node(int val) : freq{ val } {

        }
    };

    Node* head;
    Node* tail;
    void remove(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;

        delete node;
    }

    std::unordered_map<std::string, Node*> m;   //for checking if existed, key to Node with its freq


public:
    AllOne() {
        head = new Node(-1);
        tail = new Node(-1);
        head->next = tail;
        tail->prev = head;
    }
    
    void inc(string key) {
        
        if (m.find(key) != m.end()) {

            Node* curr = m[key];
            int freq = curr->freq;
            curr->keys.erase(key);
            Node* next_node = curr->next;

            if (next_node == tail || freq + 1 != next_node->freq) {
                Node* new_node = new Node(freq + 1);
                new_node->keys.insert(key);

                new_node->prev = curr;
                new_node->next = next_node;

                curr->next = new_node;
                next_node->prev = new_node;

                m[key] = new_node;

            } else {
                next_node->keys.insert(key);
                m[key] = next_node;
            }

            if (curr->keys.empty()) {
                remove(curr);
            }

            return;
        }

        Node* old_first = head->next;
        if (old_first == tail || old_first->freq > 1) {
            Node* new_node = new Node(1);
            new_node->keys.insert(key);
        
            new_node->next = old_first;
            new_node->prev = head;

            head->next = new_node;
            old_first->prev = new_node;
            m[key] = new_node;

        } else {
            old_first->keys.insert(key);
            m[key] = old_first;
        }
    }
    
    void dec(string key) {
        if (m.find(key) == m.end()) {
            return;
        }

        Node* curr = m[key];
        curr->keys.erase(key);
        int freq = curr->freq;

        if (freq == 1) {
            m.erase(key);

        } else {

            Node* prev_node = curr->prev;

            if (prev_node == head || freq - 1 != prev_node->freq) {
                Node* new_node = new Node(freq - 1);
                new_node->keys.insert(key);

                new_node->prev = prev_node;
                new_node->next = curr;

                curr->prev = new_node;
                prev_node->next = new_node;

                m[key] = new_node;

            } else {
                prev_node->keys.insert(key);
                m[key] = prev_node;
            }
        }

        if (curr->keys.empty()) {
            remove(curr);
        }
    }
    
    string getMaxKey() {
        if (tail->prev == head) {
            return "";
        }

        std::string ans = *(tail->prev->keys.begin());
        return ans;
    }
    
    string getMinKey() {
        if (head->next == tail) {
            return "";
        }
        std::string ans = *(head->next->keys.begin());
        return ans; 
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */