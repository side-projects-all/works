/*
On an 2 x 3 board, there are five tiles labeled from 1 to 5, and an empty square represented by 0. A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.

The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].

Given the puzzle board board, return the least number of moves required so that the state of the board is solved. If it is impossible for the state of the board to be solved, return -1.

 

Example 1:

Input: board = [[1,2,3],[4,0,5]]
Output: 1
Explanation: Swap the 0 and the 5 in one move.

Example 2:

Input: board = [[1,2,3],[5,4,0]]
Output: -1
Explanation: No number of moves will make the board solved.

Example 3:

Input: board = [[4,1,2],[5,0,3]]
Output: 5
Explanation: 5 is the smallest number of moves that solves the board.
An example path:
After move 0: [[4,1,2],[5,0,3]]
After move 1: [[4,1,2],[0,5,3]]
After move 2: [[0,1,2],[4,5,3]]
After move 3: [[1,0,2],[4,5,3]]
After move 4: [[1,2,0],[4,5,3]]
After move 5: [[1,2,3],[4,5,0]]

 

Constraints:

    board.length == 2
    board[i].length == 3
    0 <= board[i][j] <= 5
    Each value board[i][j] is unique.


*/

class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        // Direction map for zero's possible moves in a 1D representation of the
        // 2x3 board
        std::vector<std::vector<int>> directions = {{1, 3}, {0, 2, 4}, {1, 5},
                                          {0, 4}, {1, 3, 5}, {2, 4}};

        std::string target = "123450";
        std::string startState;

        // Convert the 2D board into a string representation
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                startState += std::to_string(board[i][j]);
            }
        }

        std::unordered_set<std::string> visited;  // To store visited states
        std::queue<std::string> queue;
        queue.push(startState);
        visited.insert(startState);

        int moves = 0;

        // BFS to find the minimum number of moves
        while (!queue.empty()) {

            int size = queue.size();
            while (size-- > 0) {
                string currentState = queue.front();
                queue.pop();

                // Check if we reached the target solved state
                if (currentState == target) {
                    return moves;
                }

                int zeroPos = currentState.find('0');
                for (int newPos : directions[zeroPos]) {
                    string nextState = currentState;
                    swap(nextState[zeroPos], nextState[newPos]);

                    // Skip if this state has been visited
                    if (visited.count(nextState)) continue;

                    // Mark the new state as visited and add it to the queue
                    visited.insert(nextState);
                    queue.push(nextState);
                }
            }
            
            ++moves;
        }

        return -1;
    }
};