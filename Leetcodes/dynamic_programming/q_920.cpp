/*
Your music player contains n different songs. You want to listen to goal songs (not necessarily different) during your trip. To avoid boredom, you will create a playlist so that:

    Every song is played at least once.
    A song can only be played again only if k other songs have been played.

Given n, goal, and k, return the number of possible playlists that you can create. Since the answer can be very large, return it modulo 109 + 7.

 

Example 1:

Input: n = 3, goal = 3, k = 1
Output: 6
Explanation: There are 6 possible playlists: [1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], and [3, 2, 1].

Example 2:

Input: n = 2, goal = 3, k = 0
Output: 6
Explanation: There are 6 possible playlists: [1, 1, 2], [1, 2, 1], [2, 1, 1], [2, 2, 1], [2, 1, 2], and [1, 2, 2].

Example 3:

Input: n = 2, goal = 3, k = 1
Output: 2
Explanation: There are 2 possible playlists: [1, 2, 1] and [2, 1, 2].

 

Constraints:

    0 <= k < n <= goal <= 100



*/

class Solution {
public:
    int numMusicPlaylists(int n, int goal, int k) {
        std::vector<std::vector<long>> mem(goal + 1, std::vector<long>(n + 1, -1));

        //the recursive function parameters: 
        //the "i" means target songs played and 
        //the "j" mean different songs played
        std::function<long(int, int)> recursive = [&](int i, int j) -> long {
            if (i == 0 && j == 0) {
                return 1L;
            }

            if (i == 0 || j == 0) {
                return 0L;
            }

            if (mem[i][j] != -1) {
                return mem[i][j];
            }

            mem[i][j] = (recursive(i - 1, j - 1) * (n - j + 1)) % 1000000007;

            //replay old songs
            if (j > k) {
                mem[i][j] = (mem[i][j] + recursive(i - 1, j) * (j - k)) % 1000000007;
            }

            return mem[i][j];
        };

        return recursive(goal, n);
    }
};