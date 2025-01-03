/*
Given a string path, where path[i] = 'N', 'S', 'E' or 'W', each representing moving one unit north, south, east, or west, respectively. You start at the origin (0, 0) on a 2D plane and walk on the path specified by path.

Return true if the path crosses itself at any point, that is, if at any time you are on a location you have previously visited. Return false otherwise.

 

Example 1:

Input: path = "NES"
Output: false 
Explanation: Notice that the path doesn't cross any point more than once.

Example 2:

Input: path = "NESWW"
Output: true
Explanation: Notice that the path visits the origin twice.

 

Constraints:

    1 <= path.length <= 10^4
    path[i] is either 'N', 'S', 'E', or 'W'.


*/

class Solution {
private:
    struct my_hash {
        template<class T1, class T2>
        std::size_t operator() (const std::pair<T1, T2>& p) const {
            return std::hash<T1>{} (p.first) ^ (std::hash<T2>{} (p.second) << 1);
        }
    };
public:
    bool isPathCrossing(string path) {
        std::unordered_map<char, std::vector<int>> dir = { {'N', {0, 1}}, {'E', {1, 0}}, 
                                                            {'S', {0, -1}}, {'W', {-1, 0}} };
        std::unordered_set<std::pair<int, int>, my_hash> walked;

        int x = 0;
        int y = 0;
        walked.insert({x, y});
        for (char c : path) {
            x += dir[c][0];
            y += dir[c][1];

            if (walked.find({x, y}) == walked.end()) {
                walked.insert({x, y});
            } else {
                return true;
            }
        }

        return false;
    }
};