/*

*/

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size();
        int m = needle.size();
        if (n < m) {
            return -1;
        }

        //by KMP algorithm
        std::vector<int> longest_border(m);
        int prev = 0;
        int i = 1;

        //preprocessing for geting longest_border
        while (i < m) {
            if (needle[i] == needle[prev]) {
                ++prev;
                longest_border[i] = prev;
                ++i;
            } else {
                if (prev == 0) {
                    longest_border[i] = 0;
                    ++i;
                } else {
                    prev = longest_border[prev - 1];
                }
            }
        }

        //searching matching substring
        int haystackPtr = 0;
        int needlePtr = 0;

        while (haystackPtr < n) {
            if (haystack[haystackPtr] == needle[needlePtr]) {
                ++needlePtr;
                ++haystackPtr;

                if (needlePtr == m) {
                    return haystackPtr - m;
                }
            } else {
                if (needlePtr == 0) {
                    ++haystackPtr;
                } else {
                    needlePtr = longest_border[needlePtr - 1];
                }
            }
        }

        //naive sliding window
        /*
        int pos = 0;
        for (int i = 0; i <= haystack.size() - needle.size(); ++i) {
            
            pos = i;
            int start = 0;
            while (start < needle.size()) {
                if (needle[start] != haystack[pos]) {
                    break;
                }

                ++pos;
                ++start;
            }

            if (start == needle.size()) {
                return i;
            }
        }
        */

        //by hashing?


        return -1;
    }
};