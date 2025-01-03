/*
Given two strings s1 and s2, return the lowest ASCII sum of deleted characters to make two strings equal.

 

Example 1:

Input: s1 = "sea", s2 = "eat"
Output: 231
Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.

Example 2:

Input: s1 = "delete", s2 = "leet"
Output: 403
Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d] + 101[e] + 101[e] to the sum.
Deleting "e" from "leet" adds 101[e] to the sum.
At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.

 

Constraints:

    1 <= s1.length, s2.length <= 1000
    s1 and s2 consist of lowercase English letters.


*/

struct pair_hash {
    template<class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        return h1 ^ h2;
    }
};

class Solution {
private:
    int recursive(std::string& s1, std::string& s2, int s1Index, int s2Index,
                     std::unordered_map<std::pair<int, int>, int, pair_hash>& mem) {
        
        if (s1Index < 0 && s2Index < 0) {
            return 0;
        }

        std:pair<int, int> key = std::make_pair(s1Index, s2Index);

        if (s1Index < 0) {
            mem[key] = s2[s2Index] + recursive(s1, s2, s1Index, s2Index - 1, mem);
            
            return mem[key];
        }

        if (s2Index < 0) {
            mem[key] = s1[s1Index] + recursive(s1, s2, s1Index - 1, s2Index, mem);
            
            return mem[key];
        }

        
        if (mem.find(key) != mem.end()) {
            return mem[key];
        }

        if (s1[s1Index] == s2[s2Index]) {
            mem[key] = recursive(s1, s2, s1Index - 1, s2Index - 1, mem);
            
        } else {
            mem[key] = std::min(s1[s1Index] + recursive(s1, s2, s1Index - 1, s2Index, mem), 
                                std::min(s2[s2Index] + recursive(s1, s2, s1Index, s2Index - 1, mem), 
                                    s1[s1Index] + s2[s2Index] + recursive(s1, s2, s1Index - 1, s2Index - 1, mem)));

        }

        return mem[key];
    }
public:
    int minimumDeleteSum(string s1, string s2) {
        std::unordered_map<std::pair<int, int>, int, pair_hash> mem;
        return recursive(s1, s2, s1.size() - 1, s2.size() - 1, mem);
    }
};