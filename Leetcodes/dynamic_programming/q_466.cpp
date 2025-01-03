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
    int getMaxRepetitions(std::string s1, int n1, std::string s2, int n2) {
         //return optimized_from_example(s1, n1, s2, n2);
         //return by_scanning_s1_n1_times(s1, n1, s2, n2);

         return by_scanning_s1_n1_times_with_hashmap(s1, n1, s2, n2);
    }

private:
    int by_scanning_s1_n1_times_with_hashmap(std::string& s1, int n1, std::string& s2, int n2) {
        int s1_cnt = 0;     // Tracks how many times we've processed s1
        int s2_cnt = 0;     // Tracks how many times we've matched s2
        int s2_pos = 0;      // Tracks the current index in s2
        std::unordered_map<int, std::pair<int, int>> same_index_at;  // Stores index and (s1_count, s2_count)

        // Loop through s1 up to n1 times
        while (s1_cnt < n1) {
            ++s1_cnt;
            for (char c : s1) {
                if (c == s2[s2_pos]) {
                    ++s2_pos;
                    if (s2_pos == s2.size()) {
                        ++s2_cnt;
                        s2_pos = 0;
                    }
                }
            }

            // Detect if the same state (index, s2_count) has occurred before
            if (same_index_at.find(s2_pos) != same_index_at.end()) {
                auto [prev_s1_cnt, prev_s2_cnt] = same_index_at[s2_pos];
                int pre_loop_s1 = prev_s1_cnt;
                int pre_loop_s2 = prev_s2_cnt;
                int in_loop_s1 = s1_cnt - prev_s1_cnt;
                int in_loop_s2 = s2_cnt - prev_s2_cnt;

                // Calculate how many full loops can be made
                int loops = (n1 - pre_loop_s1) / in_loop_s1;

                // Jump forward by as many full loops as possible
                s1_cnt = pre_loop_s1 + loops * in_loop_s1;
                s2_cnt = pre_loop_s2 + loops * in_loop_s2;
            }

            // Store current state for cycle detection
            same_index_at[s2_pos] = {s1_cnt, s2_cnt};
        }

        return s2_cnt / n2;
    }
    int by_scanning_s1_n1_times(std::string& s1, int n1, std::string& s2, int n2) {
        std::vector<int> repeat_cnt(n1 + 1, 0);
        std::vector<int> next_i(n1 + 1, 0);

        int j = 0;  //for s2 index
        int cnt = 0;
        for (int k = 1; k <= n1; ++k) {     //repeat n1 times
            for (int i = 0; i < s1.size(); ++i) {
                if (s1[i] == s2[j]) {
                    ++j;

                    if (j == s2.size()) {       //complete s2(original) 1 time
                        j = 0;
                        ++cnt;
                    }
                }
            }

            repeat_cnt[k] = cnt;
            next_i[k] = j;

            for (int b = 0; b < k; ++b) {
                if (next_i[b] == j) {
                    int prefix_cnt = repeat_cnt[b];
                    int pattern_cnt = (n1 - b) / (k - b) * (repeat_cnt[k] - prefix_cnt);
                    int suffix_cnt = repeat_cnt[b + (n1 - b) % (k - b)] - prefix_cnt;

                    return (prefix_cnt + pattern_cnt + suffix_cnt) / n2;
                }
            }
        }

        return repeat_cnt[n1] / n2;
    }
    int optimized_from_example(std::string& s1, int n1, std::string& s2, int n2) {
        std::vector<int> rapport(101, -1);
        std::vector<int> rest(101, -1);
        int b = -1;
        int posRest = 0;
        int rap = 0;
        int last = -1;
        rapport[0] = 0;
        rest[0] = 0;

        for(int i = 1; i <= s2.size(); ++i) {

            int j;
            for(j = 0; j < s1.size(); ++j) {

                if(s2[posRest] == s1[j]) {

                    ++posRest;
                    if(posRest == s2.size()) {
                        ++rap;
                        posRest = 0;
                    }
                }
            }
            
            for(int k = 0; k < i; ++k) {
                
                if(posRest == rest[k]) {
                    b = k;
                    last = i;
                    break;
                }
            }
            
            rapport[i] = rap;
            rest[i] = posRest;
            if (b >= 0) break;
        }
        
        int interval = last - b;
        if (b >= n1) {
            return rapport[n1] / n2;
        }       
        
        return ((n1 - b) / interval * (rapport[last] - rapport[b]) + rapport[(n1 - b) % interval + b]) / n2; 
    }
};




