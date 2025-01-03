/*
A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).

Given two strings source and target, return the minimum number of subsequences of source such that their concatenation equals target. If the task is impossible, return -1.

 

Example 1:

Input: source = "abc", target = "abcbc"
Output: 2
Explanation: The target "abcbc" can be formed by "abc" and "bc", which are subsequences of source "abc".

Example 2:

Input: source = "abc", target = "acdbc"
Output: -1
Explanation: The target string cannot be constructed from the subsequences of source string due to the character "d" in target string.

Example 3:

Input: source = "xyz", target = "xzyxz"
Output: 3
Explanation: The target string can be constructed as follows "xz" + "y" + "xz".

 

Constraints:

    1 <= source.length, target.length <= 1000
    source and target consist of lowercase English letters.


*/

class Solution {
private:

    //i do not really understand this method
    //need to review it again
    int advance2d(std::string& source, std::string& target) {
        
        //using fixed array will be faster than vector
        //i guess pure array is much simpler than vector to construct
        int nextOccur[source.size()][26];

        for (int c = 0; c < 26; ++c) {
            nextOccur[source.size() - 1][c] = -1;
        }
        
        /*
        std::vector<std::vector<int>> nextOccur(source.size(), std::vector<int>(26, 0));
        for (int c = 0; c < 26; ++c) {
            nextOccur[source.size() - 1][c] = -1;
        }
        */
        
        //set base case, the last one
        int last = source.size() - 1;
        char last_char = source[last];
        nextOccur[last][last_char - 'a'] = source.size() - 1;

        for (int i = source.size() - 2; i > -1; --i) {
            for (int c = 0; c < 26; ++c) {

                //copy from last row
                nextOccur[i][c] = nextOccur[i + 1][c];
            }

            //the row index is character in source , 
            //the column index is the number( starts from 0) in 26 characters, 
            //set the value by its row index
            nextOccur[i][source[i] - 'a'] = i;
        }

        int s = 0;
        //start from 1 because at least using source 1 time by the constraint
        //1 <= source.length, target.length <= 1000
        int cnt = 1;    

        for (char c : target) {

            //this means all characters exist after the first character in source
            if (nextOccur[0][c - 'a'] == -1) {
                return -1;
            }

            if (s == source.size() || nextOccur[s][c - 'a'] == -1) {
                ++cnt;
                s = 0;
            }

            s = nextOccur[s][c - 'a'] + 1;
        }
        return cnt;
    }

    int byBinarySearch(std::string& source, std::string& target) {

        //std::vector<std::vector<int>> charToIndices(26, std::vector<int>());

        //another way for declaration!!
        std::vector<int> charToIndices[26];
        for (int i = 0; i < source.size(); ++i) {
            charToIndices[source[i] - 'a'].push_back(i);
        }

        int s = 0;
        int cnt = 1;

        for (int i = 0; i < target.size(); ++i) {

            if (charToIndices[target[i] - 'a'].size() ==0) {
                return -1;
            }

            std::vector<int> indices = charToIndices[target[i] - 'a'];
            int index = std::lower_bound(indices.begin(), indices.end(), s) - indices.begin();

            if (index == indices.size()) {
                ++cnt;
                s = indices[0] + 1;
            } else {
                s = indices[index] + 1;
            }
        }

        return cnt;
    }

    int twoPointer2(std::string& source, std::string& target) {
        // Boolean array to mark all characters of source
        bool sourceChars[26] = {false};
        for (char c : source) {
            sourceChars[c - 'a'] = true;
        }

        // Check if all characters of target are present in source
        // If any character is not present, return -1
        for (char c : target) {
            if (!sourceChars[c - 'a']) {
                return -1;
            }
        }

        // Length of source to loop back to start of source using mod
        int m = source.length();

        // Pointer for source
        int sourceIterator = 0;

        // Number of times source is traversed. It will be incremented when
        // while finding occurrence of a character in target, sourceIterator
        // reaches the start of source again.
        int count = 0;

        // Find all characters of target in source
        for (char c : target) {

            // If while finding, iterator reaches start of source again,
            // increment count
            if (sourceIterator == 0) {
                count++;
            }

            // Find the first occurrence of c in source
            while (source[sourceIterator] != c) {

                // Formula for incrementing while looping back to start.
                sourceIterator = (sourceIterator + 1) % m;

                // If while finding, iterator reaches start of source again,
                // increment count
                if (sourceIterator == 0) {
                    count++;
                }
            }

            // Loop will break when c is found in source. Thus, increment.
            // Don't increment count until it is not clear that target has
            // remaining characters.
            sourceIterator = (sourceIterator + 1) % m;
        }

        // Return count
        return count;
    }

    int twoPointer(std::string& source, std::string& target) {
        int s = 0;
        int t = 0;
        int result = 0;
        int equal_cnt = 0;
        while (t < target.size()) {

            while (s < source.size()) {

                if (source[s] == target[t]) {                    
                    ++t;
                    ++equal_cnt;
                }

                ++s;
            }

            if (equal_cnt > 0) {
                ++result;
            } else {
                return -1;
            }

            equal_cnt = 0;
            s = 0;
        }

        return result;
    }

public:
    int shortestWay(string source, string target) {

        //return twoPointer(source, target);

        //return twoPointer2(source, target);

        //return byBinarySearch(source, target);
        return advance2d(source, target);
    }
};