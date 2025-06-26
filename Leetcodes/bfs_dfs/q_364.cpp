/*
You are given a nested list of integers nestedList. Each element is either an integer or a list whose elements may also be integers or other lists.

The depth of an integer is the number of lists that it is inside of. For example, the nested list [1,[2,2],[[3],2],1] has each integer's value set to its depth. Let maxDepth be the maximum depth of any integer.

The weight of an integer is maxDepth - (the depth of the integer) + 1.

Return the sum of each integer in nestedList multiplied by its weight.

 

Example 1:

Input: nestedList = [[1,1],2,[1,1]]
Output: 8
Explanation: Four 1's with a weight of 1, one 2 with a weight of 2.
1*1 + 1*1 + 2*2 + 1*1 + 1*1 = 8

Example 2:

Input: nestedList = [1,[4,[6]]]
Output: 17
Explanation: One 1 at depth 3, one 4 at depth 2, and one 6 at depth 1.
1*3 + 4*2 + 6*1 = 17

 

Constraints:

    1 <= nestedList.length <= 50
    The values of the integers in the nested list is in the range [-100, 100].
    The maximum depth of any integer is less than or equal to 50.


*/

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
private:
    void dfs(vector<NestedInteger>& nestedList, int& max_depth, std::vector<int>& vals, std::vector<int>& depth, int curr_depth) {
        for (int i = 0; i < nestedList.size(); ++i) {
            if (nestedList[i].isInteger()) {
                vals.push_back(nestedList[i].getInteger());
                depth.push_back(curr_depth);

            } else {
                dfs(nestedList[i].getList(), max_depth, vals, depth, curr_depth + 1);
            }
        }

        max_depth = std::max(max_depth, curr_depth);
    }
    int by_dfs(vector<NestedInteger>& nestedList) {
        std::vector<int> vals;
        std::vector<int> depth;
        int max_depth = 1;
        
        dfs(nestedList, max_depth, vals, depth, 1);

        int sum = 0;
        for (int i = 0; i < vals.size(); ++i) {
            sum += vals[i] * (max_depth - depth[i] + 1);
        }

        return sum;
    }
public:
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        return by_dfs(nestedList);
    }
};

/*
class Solution {
private:
    void find_max_depth(vector<NestedInteger> nestedList, int& max_depth, int depth_now) {

        for (int i = 0; i < nestedList.size(); ++i) {

            //list that includes empty list means it has one element
            if (!nestedList[i].isInteger() && !nestedList[i].getList().empty()) {
 
                find_max_depth(nestedList[i].getList(), max_depth, depth_now + 1);
            }
        }

        max_depth = std::max(max_depth, depth_now);
    }
    void sum_all(vector<NestedInteger> nestedList, int& max_depth, int& sum, int depth_now) {

        for (int i = 0; i < nestedList.size(); ++i) {
            if (!nestedList[i].isInteger()) {
                sum_all(nestedList[i].getList(), max_depth, sum, depth_now + 1);

            } else {
                sum += (max_depth - depth_now + 1) * nestedList[i].getInteger();
            }
        }
    }
public:
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        int max_depth = 0;
        find_max_depth(nestedList, max_depth, 1);

        int sum = 0;
        sum_all(nestedList, max_depth, sum, 1);

        return sum;
    }
};
*/