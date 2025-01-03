/*
Given a m * n matrix seats  that represent seats distributions in a classroom. If a seat is broken, it is denoted by '#' character otherwise it is denoted by a '.' character.

Students can see the answers of those sitting next to the left, right, upper left and upper right, but he cannot see the answers of the student sitting directly in front or behind him. Return the maximum number of students that can take the exam together without any cheating being possible..

Students must be placed in seats in good condition.

 

Example 1:

Input: seats = [["#",".","#","#",".","#"],
                [".","#","#","#","#","."],
                ["#",".","#","#",".","#"]]
Output: 4
Explanation: Teacher can place 4 students in available seats so they don't cheat on the exam. 

Example 2:

Input: seats = [[".","#"],
                ["#","#"],
                ["#","."],
                ["#","#"],
                [".","#"]]
Output: 3
Explanation: Place all students in available seats. 

Example 3:

Input: seats = [["#",".",".",".","#"],
                [".","#",".","#","."],
                [".",".","#",".","."],
                [".","#",".","#","."],
                ["#",".",".",".","#"]]
Output: 10
Explanation: Place students in available seats in column 1, 3 and 5.

 

Constraints:

    seats contains only characters '.' and'#'.
    m == seats.length
    n == seats[i].length
    1 <= m <= 8
    1 <= n <= 8


*/

class Solution {
public:
    int maxStudents(vector<vector<char>>& seats) {
        int r = seats.size();
        int c = seats[0].size();

        //store all positions of good seats first
        std::vector<int> all_good_seats;

        int curr = 0;
        for (int i = 0; i < r; ++i) {
            curr = 0;
            for (int j = 0; j < c; ++j) {
                //this is for representing non-broken seats in a row
                curr = (curr << 1) + (seats[i][j] == '.');
            }

            all_good_seats.push_back(curr);
        }

        //storing all states
        std::vector<std::vector<int>> f(r + 1, std::vector<int>(1 << c, -1));

        //according to requirements, becuase we will visit f[0][0] first, 
        //it is always valid one because no students in it
        f[0][0] = 0;

        //good_seats_in_a_row
        int g = 0;
        for (int i = 1; i <= r; ++i) {
            g = all_good_seats[i - 1];

            //(1 << c) represent how many possible combinations in a row of students
            //in a binary representation, 0 means no student in that row
            //which is always a valid state
            for (int j = 0; j < (1 << c); ++j) {
                
                //so we check row i with row i - 1, and check if there is adjacency
                //(j & g) == j : check if j is a subset of good_seats_in_a_row
                //!(j & (j >> 1)) : check if there is no adjacent students in the row
                if (( (j & g) == j ) && ( !(j & (j >> 1)) )) {
                    
                    //state transition
                    for (int k = 0; k < (1 << c); ++k) {
                        // !(j & (k >> 1)): no students in the upper left positions
						// !((j >> 1) & k): no students in the upper right positions
						// f[i - 1][k] != -1: the previous state is valid
                        if (!(j & (k >> 1)) && !((j >> 1) & k) && f[i - 1][k] != -1) {
                            f[i][j] = std::max(f[i][j], f[i - 1][k] + __builtin_popcount(j));
                        }
                    }
                }
            }
        }

        return *std::max_element(f[r].begin(), f[r].end());;
    }
};