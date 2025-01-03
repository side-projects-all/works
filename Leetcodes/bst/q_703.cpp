/*
Design a class to find the kth largest element in a stream. Note that it is the kth largest element in the sorted order, not the kth distinct element.

Implement KthLargest class:

    KthLargest(int k, int[] nums) Initializes the object with the integer k and the stream of integers nums.
    int add(int val) Appends the integer val to the stream and returns the element representing the kth largest element in the stream.

 

Example 1:

Input
["KthLargest", "add", "add", "add", "add", "add"]
[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
Output
[null, 4, 5, 5, 8, 8]

Explanation
KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
kthLargest.add(3);   // return 4
kthLargest.add(5);   // return 5
kthLargest.add(10);  // return 5
kthLargest.add(9);   // return 8
kthLargest.add(4);   // return 8

 

Constraints:

    1 <= k <= 10^4
    0 <= nums.length <= 10^4
    -1064 <= nums[i] <= 10^4
    -10^4 <= val <= 10^4
    At most 10^4 calls will be made to add.
    It is guaranteed that there will be at least k elements in the array when you search for the kth element.


*/

struct Node {
    Node* left;
    Node* right;
    int val;
    int cnt;

    Node(int v, int c) : left(nullptr), right(nullptr), val(v), cnt(c) {
    }
};

class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) {
        /*
        pq_size = k;

        for (int num : nums) {
            heapify(num);
        }*/

        //using binary search tree!!
        root = nullptr;

        for (int num : nums) {
            root = insertNode(root, num);
        }

        m_k = k;
    }
    
    int add(int val) {
        //heapify(val);

        //return -pq.top();
        //return pq.top();

        //using binary search tree!!
        root = insertNode(root, val);

        return searchKth(root, m_k);
    }

private:
    Node* root;
    int m_k;
    Node* insertNode(Node* root, int num) {
        
        if (root == nullptr) {
            return new Node(num, 1);
        }

        if (root->val < num) {
            root->right = insertNode(root->right, num);
        } else {
            root->left = insertNode(root->left, num);
        }

        ++(root->cnt);

        return root;
    }

    int searchKth(Node* root, int k) {
        //m is the size of right subtree
        int m = (root->right == nullptr) ? 0 : (root->right)->cnt;

        //root is the m + 1 largest node in the binary search tree
        if (k == m + 1) {
            return root->val;
        }

        if (k <= m) {
            return searchKth(root->right, k);
        } else {
            return searchKth(root->left, k - m - 1);
        }
    }
    /*
    //std::priority_queue<int> pq;
    //using greater could make priority queue become min heap
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    int pq_size;

    void heapify(int num) {
        //pq.push(-num);
        pq.push(num);

        if (pq.size() > pq_size) {
            pq.pop();
        }
    }
    */

};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */