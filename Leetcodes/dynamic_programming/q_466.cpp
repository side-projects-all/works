/*
We define str = [s, n] as the string str which consists of the string s concatenated n times.

    For example, str == ["abc", 3] =="abcabcabc".

We define that string s1 can be obtained from string s2 if we can remove some characters from s2 such that it becomes s1.

    For example, s1 = "abc" can be obtained from s2 = "abdbec" based on our definition by removing the bolded underlined characters.

You are given two strings s1 and s2 and two integers n1 and n2. You have the two strings str1 = [s1, n1] and str2 = [s2, n2].

Return the maximum integer m such that str = [str2, m] can be obtained from str1.

 

Example 1:

Input: s1 = "acb", n1 = 4, s2 = "ab", n2 = 2
Output: 2

Example 2:

Input: s1 = "acb", n1 = 1, s2 = "acb", n2 = 1
Output: 1

 

Constraints:

    1 <= s1.length, s2.length <= 100
    s1 and s2 consist of lowercase English letters.
    1 <= n1, n2 <= 10^6


*/

class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {

        int len1 = s1.size();
        int len2 = s2.size();
        std::unordered_map<int, std::pair<int, int>> indexMap; // s2_index -> (s1_count, s2_count)

        int s1_count = 0;
        int s2_count = 0; 
        int index = 0;

        while (s1_count < n1) {

            for (int i = 0; i < len1; ++i) {
                if (s1[i] == s2[index]) {

                    ++index;    //s2 position
                    if (index == len2) {
                        index = 0;
                        ++s2_count;
                    }
                }
            }

            ++s1_count;

            // Cycle detected
            if (indexMap.count(index)) {
                int prev_s1_count = indexMap[index].first;
                int prev_s2_count = indexMap[index].second;

                int cycle_len = s1_count - prev_s1_count;
                int cycle_s2 = s2_count - prev_s2_count;

                int remaining = n1 - s1_count;
                int cycles = remaining / cycle_len;

                s1_count += cycles * cycle_len;
                s2_count += cycles * cycle_s2;
                
            } else {
                indexMap[index] = {s1_count, s2_count};
            }
        }

        return s2_count / n2;
    }
};




