/*
Given a string s, reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

 

Example 1:

Input: s = "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"

Example 2:

Input: s = "God Ding"
Output: "doG gniD"

 

Constraints:

    1 <= s.length <= 5 * 10^4
    s contains printable ASCII characters.
    s does not contain any leading or trailing spaces.
    There is at least one word in s.
    All the words in s are separated by a single space.


*/

class Solution {
public:
    string reverseWords(string s) {

        //inner two pointer
        int len = s.size();
        int i = 0;

        while (i < len) {
            int start = i;
            int end = i;

            while (end <s.size() && s[end] != ' ') {
                ++end;
            }

            //do reverse
            int r_start = start;
            int r_end = end - 1;
            while (r_start < r_end) {
                char tmp = s[r_start];
                s[r_start] = s[r_end];
                s[r_end] = tmp;
                --r_end;
                ++r_start;
            }

            if (end < s.size()) {
                i = end + 1;
            } else {
                i = s.size();
            }

        }

        return s;


        //original naive solution
        /*
        std::reverse(s.begin(), s.end());

        std::vector<std::string> words;
        int w_begin = 0;
        int w_end = s.size();
        for (int i = s.size() - 1; i > -1; --i) {
            w_end = i;
            w_begin = i;

            while (w_begin > -1 && s[w_begin] != ' ') {
                --w_begin;
            }

            words.push_back(s.substr(w_begin + 1, w_end - w_begin));
            if (w_begin > -1 && w_begin < i) {
                i = w_begin;
            } else {
                i = 0;
            }
        }

        std::string result = "";
        int i = 0;
        for (i = 0; i < words.size() - 1; ++i) {
            result += words[i] + ' ';
        }
        result += words[i];

        return result;
        */
    }
};