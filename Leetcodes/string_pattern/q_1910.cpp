/*
Given two strings s and part, perform the following operation on s until all occurrences of the substring part are removed:

    Find the leftmost occurrence of the substring part and remove it from s.

Return s after removing all occurrences of part.

A substring is a contiguous sequence of characters in a string.

 

Example 1:

Input: s = "daabcbaabcbc", part = "abc"
Output: "dab"
Explanation: The following operations are done:
- s = "daabcbaabcbc", remove "abc" starting at index 2, so s = "dabaabcbc".
- s = "dabaabcbc", remove "abc" starting at index 4, so s = "dababc".
- s = "dababc", remove "abc" starting at index 3, so s = "dab".
Now s has no occurrences of "abc".

Example 2:

Input: s = "axxxxyyyyb", part = "xy"
Output: "ab"
Explanation: The following operations are done:
- s = "axxxxyyyyb", remove "xy" starting at index 4 so s = "axxxyyyb".
- s = "axxxyyyb", remove "xy" starting at index 3 so s = "axxyyb".
- s = "axxyyb", remove "xy" starting at index 2 so s = "axyb".
- s = "axyb", remove "xy" starting at index 1 so s = "ab".
Now s has no occurrences of "xy".

 

Constraints:

    1 <= s.length <= 1000
    1 <= part.length <= 1000
    s​​​​​​ and part consists of lowercase English letters.


*/

class Solution {
private:
    int kmp_search(string& s, string& part) {
        int ns = s.size();
        int np = part.size();

        if (ns < np) {
            return -1;
        }

        if (ns == np) {
            return s == part ? 0 : -1;
        }

        std::vector<int> longest_proper_border(np);
        int i = 1;
        int prev = 0;

        while (i < np) {

            if (part[i] == part[prev]) {
                ++prev;
                longest_proper_border[i] = prev;
                ++i;
            } else {
                if (prev == 0) {
                    longest_proper_border[i] = 0;
                    ++i;

                } else {
                    prev = longest_proper_border[prev - 1];
                }
            }
        }
        int s_ptr = 0;
        int p_ptr = 0;

        while (s_ptr < ns) {
            if (s[s_ptr] == part[p_ptr]) {
                ++s_ptr;
                ++p_ptr;

                if (p_ptr == np) {
                    return s_ptr - np;
                }

            } else {
                if (p_ptr == 0) {
                    ++s_ptr;

                } else {
                    p_ptr = longest_proper_border[p_ptr - 1];
                }
            }
        }

        return -1;
    }
public:
    string removeOccurrences(string s, string part) {
        int ns = s.size();
        int np = part.size();

        if (np > ns) {
            return s;
        }

        int pos = 0; 
        while (true) {
            pos = kmp_search(s, part);
            if (pos == -1) {
                return s;
            }

            s.erase(pos, np);
        }

        return s;
    }
};