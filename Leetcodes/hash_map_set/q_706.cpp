/*
Design a HashMap without using any built-in hash table libraries.

Implement the MyHashMap class:

    MyHashMap() initializes the object with an empty map.
    void put(int key, int value) inserts a (key, value) pair into the HashMap. If the key already exists in the map, update the corresponding value.
    int get(int key) returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key.
    void remove(key) removes the key and its corresponding value if the map contains the mapping for the key.

 

Example 1:

Input
["MyHashMap", "put", "put", "get", "get", "put", "get", "remove", "get"]
[[], [1, 1], [2, 2], [1], [3], [2, 1], [2], [2], [2]]
Output
[null, null, null, 1, -1, null, 1, null, -1]

Explanation
MyHashMap myHashMap = new MyHashMap();
myHashMap.put(1, 1); // The map is now [[1,1]]
myHashMap.put(2, 2); // The map is now [[1,1], [2,2]]
myHashMap.get(1);    // return 1, The map is now [[1,1], [2,2]]
myHashMap.get(3);    // return -1 (i.e., not found), The map is now [[1,1], [2,2]]
myHashMap.put(2, 1); // The map is now [[1,1], [2,1]] (i.e., update the existing value)
myHashMap.get(2);    // return 1, The map is now [[1,1], [2,1]]
myHashMap.remove(2); // remove the mapping for 2, The map is now [[1,1]]
myHashMap.get(2);    // return -1 (i.e., not found), The map is now [[1,1]]

 

Constraints:

    0 <= key, value <= 10^6
    At most 104 calls will be made to put, get, and remove.


*/

class MyHashMap {
public:
    MyHashMap() : size(769), index(0) {
        store = std::vector<std::vector<std::pair<int, int>>>(size, std::vector<std::pair<int, int>>());
    }
    
    void put(int key, int value) {
        index = myHash(key); 
        
        for (std::vector<std::pair<int, int>>::iterator it = store[index].begin(); it != store[index].end(); ++it) {
            if (it->first == key) {
                it->second = value;
                return;
            }
        }
        
        store[index].push_back(std::pair<int, int>(key, value));
    }
    
    int get(int key) {
        index = myHash(key); 
        
        for (std::vector<std::pair<int, int>>::iterator it = store[index].begin(); it != store[index].end(); ++it) {
            if (it->first == key) {
                return it->second;
            }
        }
        
        return -1;
    }
    
    void remove(int key) {
        index = myHash(key); 
        
        for (std::vector<std::pair<int, int>>::iterator it = store[index].begin(); it != store[index].end(); ++it) {
            if (it->first == key) {
                store[index].erase(it);
                break;
            }
        }
    }

private:
    std::vector<std::vector<std::pair<int, int>>> store;
    int size;
    int index;
        
    int myHash(int key) {
        return key % size;
    }
    
    bool contains(int key) {
        index = myHash(key); 
        
        for (std::vector<std::pair<int, int>>::iterator it = store[index].begin(); it != store[index].end(); ++it) {
            if (it->first == key) {
                return true;
            }
        }
        
        return false;
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */