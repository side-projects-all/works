/*
You are given an array of people, people, which are the attributes of some people in a queue (not necessarily in order). Each people[i] = [hi, ki] represents the ith person of height hi with exactly ki other people in front who have a height greater than or equal to hi.

Reconstruct and return the queue that is represented by the input array people. The returned queue should be formatted as an array queue, where queue[j] = [hj, kj] is the attributes of the jth person in the queue (queue[0] is the person at the front of the queue).

 

Example 1:

Input: people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
Explanation:
Person 0 has height 5 with no other people taller or the same height in front.
Person 1 has height 7 with no other people taller or the same height in front.
Person 2 has height 5 with two persons taller or the same height in front, which is person 0 and 1.
Person 3 has height 6 with one person taller or the same height in front, which is person 1.
Person 4 has height 4 with four people taller or the same height in front, which are people 0, 1, 2, and 3.
Person 5 has height 7 with one person taller or the same height in front, which is person 1.
Hence [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] is the reconstructed queue.

Example 2:

Input: people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]
Output: [[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]]

 

Constraints:

    1 <= people.length <= 2000
    0 <= hi <= 10^6
    0 <= ki < people.length
    It is guaranteed that the queue can be reconstructed.


*/

class Solution {
private:
    std::vector<int> tree;
    int tree_len;
    void build_tree(int n) {
        tree_len = n + 1;
        tree.resize(tree_len, 0);

        for (int i = 0; i < tree_len - 1; ++i) {
            update(i, 1);
        }
    }

    void update(int i, int val) {
        ++i;
        while (i < tree_len) {
            tree[i] += val;
            i += i & -i;
        }
    }

    int get_index(int cnt, int MSB) {
        
        int i = 0;
        while (MSB != 0) {
            
            int next = i + MSB;
            if (next < tree_len && cnt >= tree[next]) {
                i = next;
                cnt -= tree[next];
            }

            MSB >>= 1;
        }

        return i;
    }

public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    
        std::sort(people.begin(), people.end(), [](const auto& v1, const auto& v2) {
            return v1[0] == v2[0] ? v1[1] > v2[1] : v1[0] < v2[0];
        });

        int n = people.size();
        std::vector<std::vector<int>> ans(n, std::vector<int>());

        build_tree(n);
        int MSB = 1 << (31 - __builtin_clz(n));

        for (const auto& p : people) {
            int i = get_index(p[1], MSB);
            ans[i] = p;
            update(i, -1);
        }

        return ans;
    }
};

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        int n = people.size();
        sort(people.begin(), people.end(), [](auto& a, auto& b) {
            return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
        });
        vector<vector<int>> res(n, vector<int>());
        
        BIT bit(n);
        int MSB = 1 << (31 - __builtin_clz(n));
        for (const auto& p : people) {
            int idx = bit.getIdx(p[1], MSB);
            res[idx] = p;
            bit.update(idx, -1);
        }
        
        return res;
    }
};