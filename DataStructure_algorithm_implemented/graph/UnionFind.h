#include <vector>

class UnionFind {
public:
    UnionFind(int);
    
    int find_root(int);
    void union_set(int, int);
    bool is_connected(int, int);
private:
    //this array stored root of every point
    //index is every point
    std::vector<int> root;
    //for comparing criteria
    std::vector<int> rank;
};