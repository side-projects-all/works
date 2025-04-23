#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

class Solution {
private:
    
public:
    Solution() {}
    ~Solution() {}

    long long calculateScore(std::vector<std::string>& instructions, std::vector<int>& values) {
        int n = instructions.size();
        std::vector<bool> visited(n);
        int score = 0;
        
        for (int i = 0; i < n; ++i) {
            
            if (visited[i]) {
                break;
            }
            
            if (instructions[i] == "add") {
                score += values[i];
                
            } else {
                int next_i = i + values[i];
                if (next_i >= n || next_i < 0 || visited[next_i]) {
                    break;
                }
                
                i = next_i - 1;
            }
        }
        
        return score;
    }
};