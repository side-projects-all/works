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

    std::string smallestPalindrome(std::string s, int k) {
        int n = s.size();
        if (n == 1) {
            return s;
        }
        
        std::vector<int> cnts(26);
        for (int i = 0; i < n / 2; ++i) {
            ++cnts[s[i] - 'a'];
        }
        
        std::string half;
        for (int i = 0; i < 26; ++i) {
                
            if (cnts[i] > 0) {
                for (int j = 0; j < cnts[i]; ++j) {
                    half += (i + 'a');
                }
            }
        }
                
        std::sort(half.begin(), half.end());
        int cnt = 0;
        
        do {
            ++cnt;
            if (cnt == k) {
                break;
            }
            
        } while (std::next_permutation(half.begin(), half.end()));
        
        if (cnt < k) {
            return "";
        }
        
        std::string rev = half;
        std::reverse(rev.begin(), rev.end());

        if (n % 2 == 0) {
            return half + rev;
        }
                
        return half + s[n / 2] + rev;
    }
};