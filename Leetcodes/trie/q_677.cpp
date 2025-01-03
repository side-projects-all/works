/*
Design a map that allows you to do the following:

    Maps a string key to a given value.
    Returns the sum of the values that have a key with a prefix equal to a given string.

Implement the MapSum class:

    MapSum() Initializes the MapSum object.
    void insert(String key, int val) Inserts the key-val pair into the map. If the key already existed, the original key-value pair will be overridden to the new one.
    int sum(string prefix) Returns the sum of all the pairs' value whose key starts with the prefix.

 

Example 1:

Input
["MapSum", "insert", "sum", "insert", "sum"]
[[], ["apple", 3], ["ap"], ["app", 2], ["ap"]]
Output
[null, null, 3, null, 5]

Explanation
MapSum mapSum = new MapSum();
mapSum.insert("apple", 3);  
mapSum.sum("ap");           // return 3 (apple = 3)
mapSum.insert("app", 2);    
mapSum.sum("ap");           // return 5 (apple + app = 3 + 2 = 5)

 

Constraints:

    1 <= key.length, prefix.length <= 50
    key and prefix consist of only lowercase English letters.
    1 <= val <= 1000
    At most 50 calls will be made to insert and sum.


*/

class MapSum {
private:
    struct Node {
        //bool isEnd;
        Node* links[26];
        int score;

        Node() {
            //isEnd = false;
            score = 0;

            for (auto& link : links) {
                link = nullptr;
            }
        }
    };

    Node* root;
    std::unordered_map<std::string, int> scores;
public:
    MapSum() {
        root = new Node();
    }
    
    void insert(string key, int val) {
        
        int delta = 0;
        if (scores.count(key) == 0) {
            scores[key] = val;  //if it not existed, we set this key with its val
            delta = val;        //the difference, delta, is the val
        } else {
            //if it existed, we calculate the difference for the usage of rest links
            delta = val - scores[key];
            //replace with the newest val
            scores[key] = val;
        }
        
        Node* n = root;
        n->score += delta;

        for (char c : key) {
            int i = c - 'a';

            if (n->links[i] == nullptr) {
                n->links[i] = new Node();
            }
            
            n = n->links[i];
            n->score += delta;
        }
    }
    
    int sum(string prefix) {
        Node* n = root;

        for (char c : prefix) {
            int i = c - 'a';

            if (n->links[i] == nullptr) {
                return 0;
            }

            n = n->links[i];
        }

        return n->score;
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
