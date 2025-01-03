/*
A string can be abbreviated by replacing any number of non-adjacent, non-empty substrings with their lengths. The lengths should not have leading zeros.

For example, a string such as "substitution" could be abbreviated as (but not limited to):

    "s10n" ("s ubstitutio n")
    "sub4u4" ("sub stit u tion")
    "12" ("substitution")
    "su3i1u2on" ("su bst i t u ti on")
    "substitution" (no substrings replaced)

The following are not valid abbreviations:

    "s55n" ("s ubsti tutio n", the replaced substrings are adjacent)
    "s010n" (has leading zeros)
    "s0ubstitution" (replaces an empty substring)

Given a string word and an abbreviation abbr, return whether the string matches the given abbreviation.

A substring is a contiguous non-empty sequence of characters within a string.

 

Example 1:

Input: word = "internationalization", abbr = "i12iz4n"
Output: true
Explanation: The word "internationalization" can be abbreviated as "i12iz4n" ("i nternational iz atio n").

Example 2:

Input: word = "apple", abbr = "a2e"
Output: false
Explanation: The word "apple" cannot be abbreviated as "a2e".

 

Constraints:

    1 <= word.length <= 20
    word consists of only lowercase English letters.
    1 <= abbr.length <= 10
    abbr consists of lowercase English letters and digits.
    All the integers in abbr will fit in a 32-bit integer.


*/

class Solution {
public:
    bool validWordAbbreviation(string word, string abbr) {
        int w_len = word.size();
        int a_len = abbr.size();

        if (w_len < a_len) {
            return false;
        }

        int w_ptr = 0;
        int a_ptr = 0;

        while (w_ptr < w_len && a_ptr < a_len) {

            if (word[w_ptr] == abbr[a_ptr]) {
                ++w_ptr;
                ++a_ptr;

            } else {

                //no leading zero
                if (abbr[a_ptr] == '0') {
                    return false;
                }

                int val = 0;
                while (a_ptr < a_len && std::isdigit(abbr[a_ptr])) {
                    val = val * 10 + (abbr[a_ptr] - '0');
                    ++a_ptr;
                }

                w_ptr += val;
                if (w_ptr >= w_len) {
                    break;
                }

                if (word[w_ptr] != abbr[a_ptr]) {
                    return false;
                }
            }
        }

        return a_ptr == a_len && w_ptr == w_len;
    }
};