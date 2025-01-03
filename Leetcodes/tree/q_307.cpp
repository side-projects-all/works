/*
Given an integer array nums, handle multiple queries of the following types:

    Update the value of an element in nums.
    Calculate the sum of the elements of nums between indices left and right inclusive where left <= right.

Implement the NumArray class:

    NumArray(int[] nums) Initializes the object with the integer array nums.
    void update(int index, int val) Updates the value of nums[index] to be val.
    int sumRange(int left, int right) Returns the sum of the elements of nums between indices left and right inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).

 

Example 1:

Input
["NumArray", "sumRange", "update", "sumRange"]
[[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
Output
[null, 9, null, 8]

Explanation
NumArray numArray = new NumArray([1, 3, 5]);
numArray.sumRange(0, 2); // return 1 + 3 + 5 = 9
numArray.update(1, 2);   // nums = [1, 2, 5]
numArray.sumRange(0, 2); // return 1 + 2 + 5 = 8

 

Constraints:

    1 <= nums.length <= 3 * 10^4
    -100 <= nums[i] <= 100
    0 <= index < nums.length
    -100 <= val <= 100
    0 <= left <= right < nums.length
    At most 3 * 104 calls will be made to update and sumRange.


*/

class NumArray {
private:
    std::vector<int> tree;
    int n;

    void build_tree(std::vector<int>& nums) {

        //using fenwick tree
        n = nums.size() + 1;
        tree.resize(n);
        for (int i = 1; i <= n - 1; ++i) {
            tree[i] = nums[i - 1];
        }

        for (int i = 1; i <= n; ++i) {

            int j = i + (i & -i);
            if (j < n) {
                tree[j] += tree[i];
            }
        }

        //naive segment tree
        /*
        for (int i = n, j = 0; i < 2 * n; ++i, ++j) {
            tree[i] = nums[j];
        }

        for (int i = n - 1; i > 0; --i) {
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
        }
        */
    }

    //using fenwick tree
    void tree_update(int i, int val) {
        int old = tree_query(i) - tree_query(i - 1);
        tree[i] = tree[i] - old + val;
        i = i + (i & -i);
        while (i < n) {
            tree[i] = tree[i] - old + val;
            i = i + (i & -i);
        }
    }

    //using fenwick tree
    int tree_query(int i) {

        int sum = 0;
        while (i >= 1) {
            sum += tree[i];
            i -= (i & -i);
        }

        return sum;
    }

public:
    NumArray(vector<int>& nums) {
        
        build_tree(nums);

        //naive segment tree
        /*
        if (nums.size() > 0) {
            n = nums.size();
            tree = std::vector<int>(n * 2);
            build_tree(nums);
        }
        */
    }
    
    void update(int index, int val) {
        if (index >= n) {
            return;
        }

        tree_update(index + 1, val);

        //naive segment tree
        /*
        index += n;
        tree[index] = val;

        while (index > 0) {
            int left = index;
            int right = index;

            if (index % 2 == 0) {
                right = index + 1;
            } else {
                left = index - 1;
            }

            tree[index / 2] = tree[left] + tree[right];
            index /= 2;

        }
        */
    }
    
    int sumRange(int left, int right) {

        int sum_left = tree_query(left);    //because left is also inclusive
        int sum_right = tree_query(right + 1);

        return sum_right - sum_left;

        //naive segment tree
        /*
        left += n;
        right += n;
        int sum = 0;

        while (left <= right) {
            if ((left % 2) == 1) {
                sum += tree[left];
                ++left;
            }

            if ((right % 2) == 0) {
                sum += tree[right];
                --right;
            }

            left /= 2;
            right /= 2;
        }

        return sum;
        */
    }
};

/*  recursive way
class NumArray {
private:
    std::vector<int> segtree;
    int n;
    void build_tree(vector<int>& nums, int tree_i, int lo, int hi) {
        if (lo == hi) {
            segtree[tree_i] = nums[lo];
            return;
        }

        int mid = lo + (hi - lo) / 2;
        build_tree(nums, 2 * tree_i + 1, lo, mid);
        build_tree(nums, 2 * tree_i + 2, mid + 1, hi);

        segtree[tree_i] = segtree[2 * tree_i + 1] + segtree[2 * tree_i + 2];
    }

    void update(int arr_i, int lo, int hi, int tree_i, int val) {
        if (lo == hi) {
            segtree[tree_i] = val;
            return;
        }

        int mid = lo + (hi - lo) / 2;
        if (arr_i > mid) {
            update(arr_i, mid + 1, hi, 2 * tree_i + 2, val);
        } else {
            update(arr_i, lo, mid, 2 * tree_i + 1, val);
        }

       segtree[tree_i] = segtree[2 * tree_i + 1] + segtree[2 * tree_i + 2];
    }

    int query(int tree_i, int lo, int hi, int left, int right) {
        if (left > hi || right < lo) {
            return 0;
        }

        if (left <= lo && right >= hi) {
            return segtree[tree_i];
        }

        int mid = lo + (hi - lo) / 2;
        if (left > mid) {
            return query(2 * tree_i + 2, mid + 1, hi, left, right);

        } else if (right <= mid) {
            return query(2 * tree_i + 1, lo, mid, left, right);
        }

        int left_part = query(2 * tree_i + 1, lo, mid, left, mid);
        int right_part = query(2 * tree_i + 2, mid + 1, hi, mid + 1, right);

        return left_part + right_part;
    }
public:
    NumArray(vector<int>& nums) {
        n = nums.size();
        std::size_t len = 2 * std::pow(2, std::ceil(std::log2(n))) - 1;
        segtree.resize(len);
        build_tree(nums, 0, 0, n - 1);
        
    }
    
    void update(int index, int val) {
        update(index, 0, n - 1, 0, val);
    }
    
    int sumRange(int left, int right) {
        return query(0,  0, n - 1, left, right);
    }
};

*/
/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */