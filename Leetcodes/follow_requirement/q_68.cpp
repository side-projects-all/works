/*
Given an array of strings words and a width maxWidth, format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line does not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left-justified, and no extra space is inserted between words.

Note:

    A word is defined as a character sequence consisting of non-space characters only.
    Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
    The input array words contains at least one word.

 

Example 1:

Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
Output:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]

Example 2:

Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
Output:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
Explanation: Note that the last line is "shall be    " instead of "shall     be", because the last line must be left-justified instead of fully-justified.
Note that the second line is also left-justified because it contains only one word.

Example 3:

Input: words = ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"], maxWidth = 20
Output:
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]

 

Constraints:

    1 <= words.length <= 300
    1 <= words[i].length <= 20
    words[i] consists of only English letters and symbols.
    1 <= maxWidth <= 100
    words[i].length <= maxWidth


*/

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        std::vector<std::string> ans;

        std::function<void(int, int, std::vector<std::string>&)> getWords = [&](int i, int maxLen, std::vector<std::string>& strs) {

            while (maxLen >= 0 && i < words.size() && words[i].size() <= maxLen) {
                strs.push_back(words[i]);
                maxLen -= (words[i].size() + 1);
                ++i;
            }
        };

        std::function<void(int, std::vector<std::string>&, std::string&)> createLine = [&](int i, std::vector<std::string>& strs, std::string& line) {
            int base_len = -1;
            for (const auto& s : strs) {
                base_len += s.size() + 1;
            }

            int spaces = maxWidth - base_len;

            if (strs.size() == 1 || i == words.size()) {
                for (int p = 0; p < strs.size() - 1; ++p) {
                    strs[p].push_back(' ');
                    line.append(strs[p]);
                }
                
                line.append(strs[strs.size() - 1] + std::string(spaces, ' '));

                return;
            }

            int word_cnt = strs.size() - 1;
            int avg_space = spaces / word_cnt;
            int extr_space = spaces % word_cnt;

            for (int j = 0; j < extr_space; ++j) {
                strs[j].push_back(' ');
            }

            for (int j = 0; j < word_cnt; ++j) {
                strs[j].append(std::string(avg_space, ' '));
            }

            for (int j = 0; j < strs.size() - 1; ++j) {
                line.append(strs[j] + " ");
            }
            line.append(strs[strs.size() - 1]);
        };

        int k = 0;
        while (k < words.size()) {
            std::vector<std::string> curr_words;
            getWords(k, maxWidth, curr_words);

            k += curr_words.size();

            std::string str_line;
            createLine(k, curr_words, str_line);

            ans.push_back(str_line);
        }

        return ans;
    }
};