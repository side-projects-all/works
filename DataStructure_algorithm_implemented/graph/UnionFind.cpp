#include "UnionFind.h"

UnionFind::UnionFind(int len) {
    root.resize(len);
    rank.resize(len);
    for (int i = 0; i < len; ++i) {
        root[i] = i;
        rank[i] = 1;    //initialize all rank 1 !!!!
    }
}

int UnionFind::find_root(int x) {
    
    if (x == root[x]) {
        return x;
    }
    
    //path compression is here!!!
    return root[x] = find_root(root[x]);
    
    //using loop to path compression!!!
    /*
    int root_index = x;
    //find root first!!
    while (root[root_index] != root_index) {
        root_index = root[root_index];
    }
    
    //traverse from x, and set value as root_index every node on the path 
    int oldRoot = -1;
    while (x != root_index) {
        oldRoot = root[x];
        root[x] = root_index;
        x = oldRoot;
    }
    
    return root_index;
    */
}

void UnionFind::union_set(int x, int y) {
    //still big O(N)
    int rootX = find_root(x);
    int rootY = find_root(y);
    
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            root[rootY] = rootX;
            
        } else if (rank[rootX] < rank[rootY]) {
            root[rootX] = rootY;
            
        } else {
            root[rootY] = rootX;
            rank[rootX] += 1;
        }
    }
}

bool UnionFind::is_connected(int x, int y) {
    return UnionFind::find_root(x) == UnionFind::find_root(y);
}

/*
//basic quick find of Disjoint Set
class UnionFind {
public:
    UnionFind(int size) : root(size) {
        for (int i = 0; i < size; ++i) {
            root[i] = i;
        }
    }
    
    int find(int x) {
        return root[x];
    }
    
    void unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            for (int i = 0; i < root.size(); ++i) {
                //union two points, using root of X as root of Y
                if (root[i] == rootY) {
                    root[i] = rootX;
                }
            }
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
private:
    //this array stored root of every point
    //index is every point
    std::vector<int> root;
};

//basic quick union of Disjoint Set
class UnionFind {
public:
    UnionFind(int size) : root(size) {
        for (int i = 0; i < size; ++i) {
            root[i] = i;
        }
    }
    
    //this is find root
    int find(int x) {
        while (x != root[x]) {
            x = root[x];
        }
        
        return x;
    }
    
    void unionSet(int x, int y) {
        //still big O(N)
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            root[rootY] = rootX;
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
private:
    //this array stored root of every point
    //index is every point
    std::vector<int> root;
};

//basic quick union of Disjoint Set, but improving by rank
//it means we choose the root of taller tree as root for union
class UnionFind {
public:
    UnionFind(int size) : root(size), rank(size) {
        for (int i = 0; i < size; ++i) {
            root[i] = i;
            rank[i] = 1;    //initialize all rank 1 !!!!
        }
    }
    
    //this is find root
    int find(int x) {
        while (x != root[x]) {
            x = root[x];
        }
        
        return x;
    }
    
    void unionSet(int x, int y) {
        //still big O(N)
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                root[rootY] = rootX;
                
            } else if (rank[rootX] < rank[rootY]) {
                root[rootX] = rootY;
                
            } else {
                root[rootY] = rootX;
                rank[rootX] += 1;
            }

        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
private:
    //this array stored root of every point
    //index is every point
    std::vector<int> root;
    //for comparing criteria
    std::vector<int> rank;
};
*/