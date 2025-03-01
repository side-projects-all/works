/*
Given an n x n matrix where each of the rows and columns is sorted in ascending order, return the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

You must find a solution with a memory complexity better than O(n2).

 

Example 1:

Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
Output: 13
Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15], and the 8th smallest number is 13

Example 2:

Input: matrix = [[-5]], k = 1
Output: -5

 

Constraints:

    n == matrix.length == matrix[i].length
    1 <= n <= 300
    -109 <= matrix[i][j] <= 109
    All the rows and columns of matrix are guaranteed to be sorted in non-decreasing order.
    1 <= k <= n2

 

Follow up:

    Could you solve the problem with a constant memory (i.e., O(1) memory complexity)?
    Could you solve the problem in O(n) time complexity? The solution may be too advanced for an interview but you may find reading this paper fun.


*/

/*
class Node {
public:
    int row;
    int col;
    int val;

    Node() {
        row = 0;
        col = 0;
        val = 0;
    }

    Node(int p_val, int p_row, int p_col) {
        val = p_val;
        row = p_row;
        col = p_col;
    }
};
*/
struct Node {
        int row;
        int col;
        int val;

        Node() {
            row = 0;
            col = 0;
            val = 0;
        }

        Node(int p_val, int p_row, int p_col) {
            val = p_val;
            row = p_row;
            col = p_col;
        }
    };

//declaring struct for priority_queue comparator!!
struct Greater {
    //template<class Node>
    bool operator() (Node n1, Node n2) {
        return n1.val > n2.val;
    }
};

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        
        //return byPriorityQueue(matrix, k);
        return byBinarySearch(matrix, k);
    }

private:
    
    int byBinarySearch(std::vector<std::vector<int>>& matrix, int k) {
        int len = matrix.size();
        int start = matrix[0][0];
        int end = matrix[len - 1][len - 1];

        while (start < end) {

            int mid = start + (end - start) / 2;
            std::pair<int, int> smallLargePair = { matrix[0][0], matrix[len - 1][len - 1] };

            int count = countLessEqual(matrix, mid, smallLargePair);

            if (count == k) {
                return smallLargePair.first;
            }

            if (count < k) {
                start = smallLargePair.second;
            } else {
                end = smallLargePair.first;
            }

        }

        return start;
    }

    int countLessEqual(std::vector<std::vector<int>>& matrix, int mid, std::pair<int, int>& smallLargePair) {
        int count = 0;
        int len = matrix.size();
        int row = len - 1;
        int col = 0;

        while (row >= 0 && col < len) {

            if (matrix[row][col] > mid) {
              
              //using min here
              smallLargePair.second = std::min(smallLargePair.second, matrix[row][col]);
              --row;

            } else {

              //using max here
              smallLargePair.first = std::max(smallLargePair.first, matrix[row][col]);
              count += row + 1;
              ++col;

            }
        }

        return count;
    }

    int byPriorityQueue(std::vector<std::vector<int>>& matrix, int k) {
        
        if (matrix[0].size() == 1 && matrix.size() == 1) {
            return matrix[0][0];
        }

        int rows = matrix.size();
        //using lambda for creating comparator!!
        //not using lambda is faster in this question
        //auto greater = [](Node n1, Node n2) { return n1.val > n2.val; };

        std::priority_queue<Node, std::vector<Node>, Greater> pq;
        //std::priority_queue<Node, std::vector<Node>, decltype(greater)> pq(greater);

        //create priority_queue with type Node first
        int len = std::min(rows, k);
        for (int r = 0; r < len; ++r) {
            pq.push(Node(matrix[r][0], r, 0));
        }

        //loop through by column, then row again
        Node now;
        while (k > 0) {

            now = pq.top();
            pq.pop();
            int row = now.row;
            int col = now.col;

            if (col < rows - 1) {
                pq.push(Node(matrix[row][col + 1], row, col + 1));
            }

            --k;
        }

        return now.val;
    }
};