/*
Given an input string s, reverse the order of the words.

A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.

Return a string of the words in reverse order concatenated by a single space.

Note that s may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words. Do not include any extra spaces.

 

Example 1:

Input: s = "the sky is blue"
Output: "blue is sky the"

Example 2:

Input: s = "  hello world  "
Output: "world hello"
Explanation: Your reversed string should not contain leading or trailing spaces.

Example 3:

Input: s = "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.

 

Constraints:

    1 <= s.length <= 10^4
    s contains English letters (upper-case and lower-case), digits, and spaces ' '.
    There is at least one word in s.

*/

class Solution {
public:
    string reverseWords(string s) {
        
        s.erase(0, s.find_first_not_of(' '));   //remove leading space
        s.erase(s.find_last_not_of(' ') + 1);  //remove trailing space

        std::reverse(s.begin(), s.end());
        int i = 0;
        while (i < s.size()) {
            int pb = i; //ptr of begin of substring
            int pe = i; //ptr of end of substring

            //remove extra spaces between substrings first
            while (pe < s.size() && s[pe] == ' ') {
                ++pe;
            }

            if (pe - pb > 1) {
                s.erase(pb, pe - pb - 1);
                ++pb;
            } else {
                pb = pe;
            }

            pe = pb;    //reset ptr of end of substring to the begin of substring
            while (pe < s.size() && s[pe] != ' ') {
                ++pe;
            }

            std::reverse(s.begin() + pb, s.begin() + pe);

            if (pe < s.size() && i < pe) {
                i = pe;
            } else {
                i = s.size();
            }

        }

        return s;
        /*
        //in place solution
        int word_beign = 0;
        
        //remove beginning and trailing space first
        while (s[word_beign] == ' ') {
            word_beign += 1;
        }
        if (word_beign > 0) {
            s.erase(0, word_beign);
        }
        
        int word_end = s.size() - 1;
        while (s[word_end] == ' ') {
            word_end -= 1;
        }
        if (word_end < s.size() - 1) {
            s.erase(word_end + 1, s.size() - word_end);
        }
        
        std::reverse(s.begin(), s.end());
        int i = 0;
        while (i < s.size()) {
            word_beign = i;
            word_end = i;

            //handling fore-space
            while (word_end < s.size() && s[word_end] == ' ') {
                word_end += 1;
            }

            if (word_end - word_beign > 1) {
                s.erase(word_beign, word_end - word_beign - 1);
                word_beign += 1;
                
            } else {
                word_beign = word_end;
            }

            word_end = word_beign;
            while (word_end < s.size() && s[word_end] != ' ') {
                word_end += 1;
            }

            std::reverse(s.begin() + word_beign, s.begin() + word_end);

            if (word_end < s.size() && word_end > i) {
                i = word_end;
            } else {
                i = s.size();
            }
        }

        return s;
        */

        // my naive solution
        /*
        std::vector<std::string> words;

        int i = 0;
        int sp_pos = 0;
        int w_start = 0;
        int w_end = 0;
        while (i < s.size()) {

            if (s[i] != ' ') {
                w_start = i;
                w_end = w_start;
                while (w_end < s.size() && s[w_end] != ' ') {
                    ++w_end;
                }

                words.push_back(s.substr(w_start, w_end - w_start));
            }

            if (w_end > i) {
                i = w_end;
            } else {
                ++i;
            }
        }

        int begin = 0;
        int end = words.size() - 1;

        while (begin < end) {
            std::string tmp = words[begin];
            words[begin] = words[end];
            words[end] = tmp;
            ++begin;
            --end;
        }

        std::string result = "";
        for (i = 0; i < words.size() - 1; ++i) {
            result += words[i] + ' ';
        }
        result += words[i];

        return result;
        */
    }
};