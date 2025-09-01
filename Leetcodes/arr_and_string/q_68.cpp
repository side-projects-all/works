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
private:
    void select_words(const std::vector<std::string>& words, const int& len, int max_w, int& i, 
            std::vector<std::string>& selected) {

        while (max_w >= 0 && i < len && words[i].size() <= max_w) {
            selected.push_back(words[i]);
            max_w -= (words[i].size() + 1); //an extra space needs to count in
            ++i;
        }
    }

    void get_line(std::vector<std::string>& selected, const int& max_w, const int& index, const int& n, std::string& line) {
        //sum every word size with one space
        int base_len = -1;  //the last word does not need extra space
        for (int i = 0; i < selected.size(); ++i) {
            base_len += (selected[i].size() + 1);
        }

        int sz = selected.size();
        int extra = max_w - base_len;   //those extra spaces

        //for corner case: only 1 word in selected or i equal to words.size()
        if (sz == 1 || index == n) {
            for (int i = 0; i < sz - 1; ++i) {
                line += selected[i];
                line.push_back(' ');
            }

            line += selected[sz - 1] + std::string(extra, ' ');
            return;
        }

        --sz;   //only gaps between every word need to add spaces
        
        int avg = extra / sz;           //average spaces need to add
        int rest = extra % sz;          //rest spaces evenly distribute from left to right

        for (int i = 0; i < rest; ++i) {    //add rest spaces
            selected[i].push_back(' ');
        }
        
        for (int i = 0; i < sz; ++i) {      //add average spaces and the original one space after every word
            line += (selected[i] + std::string(avg, ' '));
            line.push_back(' ');
        }
       
        line += selected[sz];   //add last word
    }

public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        std::vector<std::string> ans;
        int n = words.size();
        int i = 0;

        while (i < n) {
            std::vector<std::string> selected;
            select_words(words, n, maxWidth, i, selected);

            std::string line;
            get_line(selected, maxWidth, i, n, line);

            ans.push_back(line);
        }
        return ans;
    }
};