/*
Design and implement a data structure for a Least Frequently Used (LFU) cache.

Implement the LFUCache class:

    LFUCache(int capacity) Initializes the object with the capacity of the data structure.
    int get(int key) Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
    void put(int key, int value) Update the value of the key if present, or inserts the key if not already present. When the cache reaches its capacity, it should invalidate and remove the least frequently used key before inserting a new item. For this problem, when there is a tie (i.e., two or more keys with the same frequency), the least recently used key would be invalidated.

To determine the least frequently used key, a use counter is maintained for each key in the cache. The key with the smallest use counter is the least frequently used key.

When a key is first inserted into the cache, its use counter is set to 1 (due to the put operation). The use counter for a key in the cache is incremented either a get or put operation is called on it.

The functions get and put must each run in O(1) average time complexity.

 

Example 1:

Input
["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, 3, null, -1, 3, 4]

Explanation
// cnt(x) = the use counter for key x
// cache=[] will show the last used order for tiebreakers (leftmost element is  most recent)
LFUCache lfu = new LFUCache(2);
lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
lfu.get(1);      // return 1
                 // cache=[1,2], cnt(2)=1, cnt(1)=2
lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
                 // cache=[3,1], cnt(3)=1, cnt(1)=2
lfu.get(2);      // return -1 (not found)
lfu.get(3);      // return 3
                 // cache=[3,1], cnt(3)=2, cnt(1)=2
lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
                 // cache=[4,3], cnt(4)=1, cnt(3)=2
lfu.get(1);      // return -1 (not found)
lfu.get(3);      // return 3
                 // cache=[3,4], cnt(4)=1, cnt(3)=3
lfu.get(4);      // return 4
                 // cache=[4,3], cnt(4)=2, cnt(3)=3

 

Constraints:

    1 <= capacity <= 10^4
    0 <= key <= 10^5
    0 <= value <= 10^9
    At most 2 * 10^5 calls will be made to get and put.

*/

class LFUCache {
private:
    struct Node {
        int key;
        int val;
        int freq;
        Node* prev;
        Node* next;

        Node(int k, int v) : key{ k }, val{ v }, freq{ 1 }, prev{ nullptr }, next{ nullptr } { 

        }
    };

    int curr_len;
    int cap;
    int min_freq;
    std::unordered_map<int, Node*> key_to_last;
    std::unordered_map<int, std::pair<Node*, Node*>> freq_to_headTail;

    void add_to_freq_map(int freq, Node* node) {
        Node* head = nullptr;
        Node* tail = nullptr;

        //if the freq did not exist in freq_to_headTail, we need to initialize the list
        if (freq_to_headTail.find(freq) == freq_to_headTail.end()) {
            head = new Node(-1, -1);
            tail = new Node(-1, -1);
            head->next = tail;
            tail->prev = head;
            freq_to_headTail[freq] = { head, tail };

        } else {
            head = freq_to_headTail[freq].first;
            tail = freq_to_headTail[freq].second;
        }

        //connect this node at beginning
        head->next->prev = node;
        node->next = head->next;
        head->next = node;
        node->prev = head;
    }

public:
    LFUCache(int capacity) {
        min_freq = 1;
        curr_len = 0;
        cap = capacity;
    }
    
    int get(int key) {
        if (key_to_last.find(key) == key_to_last.end() || key_to_last[key] == nullptr) {
            return -1;
        }

        Node* last = key_to_last[key];
        last->prev->next = last->next;
        last->next->prev = last->prev;

        int old_freq = last->freq;
        last->freq += 1;    //update this freq

        //for corner case: a new list, update min_freq
        if (min_freq == old_freq && freq_to_headTail[min_freq].first->next == freq_to_headTail[min_freq].second) {
            ++min_freq;
        }

        add_to_freq_map(last->freq, last);

        return last->val;
    }
    
    void put(int key, int value) {
        if (cap == 0) {
            return;
        }

        //not exist or empty list
        if (key_to_last.find(key) == key_to_last.end() || key_to_last[key] == nullptr) {

            if (curr_len < cap) {
                ++curr_len;

            } else {

                // under the condition curr_len >= cap, we need a space
                // remove the last node from the min_freq list
                // this part is the LFU cache that removing the least frequent one
                Node* tail = freq_to_headTail[min_freq].second;
                Node* last = tail->prev;
                last->prev->next = tail;
                tail->prev = last->prev;
                key_to_last[last->key] = nullptr;   //remove this node in key map
                delete last;
            }

            //this is the new node to add
            Node* new_node = new Node(key, value);
            key_to_last[key] = new_node;
            min_freq = 1;
            add_to_freq_map(1, new_node);

        } else {
            Node* last = key_to_last[key];
            //remove this node from the original list
            last->prev->next = last->next;
            last->next->prev = last->prev;

            last->val = value;  //update its value

            int old_freq = last->freq;
            last->freq += 1;

            //for corner case: a new list, update min_freq
            if (min_freq == old_freq && freq_to_headTail[min_freq].first->next == freq_to_headTail[min_freq].second) {
                ++min_freq;
            }

            add_to_freq_map(last->freq, last);
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */