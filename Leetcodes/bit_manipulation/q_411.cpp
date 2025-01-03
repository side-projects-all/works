/*
A string can be abbreviated by replacing any number of non-adjacent substrings with their lengths. For example, a string such as "substitution" could be abbreviated as (but not limited to):

    "s10n" ("s ubstitutio n")
    "sub4u4" ("sub stit u tion")
    "12" ("substitution")
    "su3i1u2on" ("su bst i t u ti on")
    "substitution" (no substrings replaced)

Note that "s55n" ("s ubsti tutio n") is not a valid abbreviation of "substitution" because the replaced substrings are adjacent.

The length of an abbreviation is the number of letters that were not replaced plus the number of substrings that were replaced. For example, the abbreviation "s10n" has a length of 3 (2 letters + 1 substring) and "su3i1u2on" has a length of 9 (6 letters + 3 substrings).

Given a target string target and an array of strings dictionary, return an abbreviation of target with the shortest possible length such that it is not an abbreviation of any string in dictionary. If there are multiple shortest abbreviations, return any of them.

 

Example 1:

Input: target = "apple", dictionary = ["blade"]
Output: "a4"
Explanation: The shortest abbreviation of "apple" is "5", but this is also an abbreviation of "blade".
The next shortest abbreviations are "a4" and "4e". "4e" is an abbreviation of blade while "a4" is not.
Hence, return "a4".

Example 2:

Input: target = "apple", dictionary = ["blade","plain","amber"]
Output: "1p3"
Explanation: "5" is an abbreviation of both "apple" but also every word in the dictionary.
"a4" is an abbreviation of "apple" but also "amber".
"4e" is an abbreviation of "apple" but also "blade".
"1p3", "2p2", and "3l1" are the next shortest abbreviations of "apple".
Since none of them are abbreviations of words in the dictionary, returning any of them is correct.

 

Constraints:

    m == target.length
    n == dictionary.length
    1 <= m <= 21
    0 <= n <= 1000
    1 <= dictionary[i].length <= 100
    log2(n) + m <= 21 if n > 0
    target and dictionary[i] consist of lowercase English letters.
    dictionary does not contain target.


*/

class Solution {
public:
    string minAbbreviation(string target, vector<string>& dictionary) {
        // words represented as numbers for faster implementation
        std::vector<int> filteredWords;

        for(auto word : dictionary) {
            if(word.size() != target.size()) {
                continue;
            }

            int v = 0;
            int mul = 1;

            //using bit mask to record the same char
            for(int i = 0 ; i < target.size() ; i++) {
                if(target[i] == word[i]) {
                    // we can also use + operation, results will be same, but slower
                    v |= mul; 
                }

                // won't exactly need LL, but if we increase target.size(), we might need it. 
                //mul *= 2LL; 
                mul *= 2; 
            }

            if(v > 0) {
                filteredWords.push_back(v);
            }
        }

        //no similar words in dictionary
        if(filteredWords.size() == 0) {
            bool hasSomeBodySameLength = false;

            //check if there existed a word with the same length as target
            for(auto word: dictionary) {
                if(word.size() == target.size()) {
                    hasSomeBodySameLength = true;
                    break;
                }
            }

            if(!hasSomeBodySameLength) {
                return std::to_string(target.size());
                
            } else {
                std::string ret = (string)"" + target[0];

                if(target.size() - 1 > 0) {
                    ret += std::to_string(target.size() - 1);
                }
                return ret;
            }
        }

        int limit = (1 << (int)target.size()) - 1;

        std::string ans = target;
        for(int i = 1; i <= limit; ++i) {

            //find no partial matched word to create answer
            int x;
            bool foundMatch = false;
            for(auto word : filteredWords) {
                x = i;
                x &= word;
                if(x == i) {
                    foundMatch = true;
                    break;
                }
            }

            if(!foundMatch) {
                vector<int> activeBits;

                //store the position where the i matched the target
                for(int j = 0; j < target.size(); ++j) {
                    if(i & (1 << j)) {
                        activeBits.push_back(j);
                    }
                }

                string tempAns = "";
                //check if first activeBits index value is not 0, 
                //if not 0, we could turn them into digit
                if(activeBits[0] != 0) {
                    tempAns += std::to_string(activeBits[0]);
                }

                for(int j = 0; j + 1 < activeBits.size() ; ++j) {

                    //add activeBits value that is index of character in target
                    tempAns += target[activeBits[j]];

                    //check if next value were equal to next index in target, 
                    //if not, turn the distance between two indices into digits
                    if(activeBits[j] + 1 != activeBits[j + 1]) {
                        tempAns += std::to_string(activeBits[j+1] - activeBits[j] - 1);
                    }
                }

                //add the character at target, which is last value of activeBits 
                tempAns += target[activeBits.back()];

                //check if it were the last character of target, 
                //if not, turn the rest characters into digits
                if(activeBits.back() != (int)target.size() - 1) {
                    tempAns += std::to_string(target.size() - activeBits.back() - 1);
                }

                //compare to get minimum size!!
                if(ans.size() > tempAns.size()) {
                    ans = tempAns;
                }
            }
        }

        return ans;
    }
};