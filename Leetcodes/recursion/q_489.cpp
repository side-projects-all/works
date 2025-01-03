/*

*/

/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *   public:
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     bool move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     void turnLeft();
 *     void turnRight();
 *
 *     // Clean the current cell.
 *     void clean();
 * };
 */

//unordered_set or unordered_map do not have default constructor for std::pair<T1, T2>.
//So, if you want to use type std::pair<T1, T2>, you need to construct your own hash function
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (std::pair<T1, T2> const &pair) const {
        std::size_t h1 = std::hash<T1>()(pair.first);
        std::size_t h2 = std::hash<T2>()(pair.second);
 
        return h1 ^ h2;
    }
};

class Solution {
public:
    void cleanRoom(Robot& robot) {
        //p_robot = &robot;
        backtrack(0, 0, 0, robot);
        //backtrack(0, 0, 0);
    }

    //move back 1 cell with the same direction
    void backward(Robot& robot) {
    //void backward() {
        
        robot.turnRight();
        robot.turnRight();
        robot.move();
        robot.turnRight();
        robot.turnRight();
        
        /*
        p_robot->turnRight();
        p_robot->turnRight();
        p_robot->move();
        p_robot->turnRight();
        p_robot->turnRight();
        */
    }
    
private:
    std::unordered_set<std::pair<int, int>, pair_hash> visited;
    //four directions in clock-wise 0: up, 1: right, 2: down, 3: left
    std::vector<std::vector<int>> dir = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
    //Robot *p_robot;

    void backtrack(int row, int col, int d, Robot& robot) {
    //void backtrack(int row, int col, int d) {
        visited.insert(std::make_pair(row, col));
        robot.clean();
        //p_robot->clean();

        for (int i = 0; i < 4; ++i) {
            int newD = (d + i) % 4;
            int newRow = row + dir[newD][0];
            int newCol = col + dir[newD][1];

            if (visited.find(std::make_pair(newRow, newCol)) == visited.end() && robot.move()) {
            //if (visited.find(std::make_pair(newRow, newCol)) == visited.end() && p_robot->move()) {
                backtrack(newRow, newCol, newD, robot);
                //backtrack(newRow, newCol, newD);
                backward(robot);
                //backward();
            }

            robot.turnRight();
            //p_robot->turnRight();
        }
    }
};