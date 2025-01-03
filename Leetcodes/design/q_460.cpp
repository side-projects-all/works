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
    //key: frequency, val: a list of original key-value pair
    std::unordered_map<int, std::list<std::pair<int, int>>> freqs;
    //key: original key, val: {freq, the freq's iterator}
    std::unordered_map<int, std::pair<int, std::list<std::pair<int, int>>::iterator>> cache;
    int capacity;
    int min_freq;

    void update_two_map(int key, int freq, int val) {
        freqs[freq].push_back({key, val});
        cache[key] = {freq, --freqs[freq].end()};
    }
public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        min_freq = 0;
    }
    
    int get(int key) {
        const auto it = cache.find(key);
        if (it == cache.end()) {
            return -1;
        }

        const int freq = it->second.first;
        const auto freq_it = it->second.second;
        const std::pair<int, int> key_val = *freq_it;

        freqs[freq].erase(freq_it); //erase this key_val pair in this freq list

        if (freqs[freq].empty()) {
            freqs.erase(freq);

            if (min_freq == freq) {
                ++min_freq;
            }
        }

        update_two_map(key, freq + 1, key_val.second);

        return key_val.second;
    }
    
    void put(int key, int value) {
        if (capacity <= 0) {
            return;
        }

        const auto it = cache.find(key);
        //exist in cache
        if (it != cache.end()) {
            it->second.second->second = value;
            get(key);

            return;
        }

        //not exist in cache
        //check capacity first
        if (capacity == cache.size()) {
            cache.erase(freqs[min_freq].front().first);
            freqs[min_freq].pop_front();

            if (freqs[min_freq].empty()) {
                freqs.erase(min_freq);
            }
        }

        min_freq = 1;
        update_two_map(key, 1, value);
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */