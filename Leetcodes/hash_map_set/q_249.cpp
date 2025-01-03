/*
We can shift a string by shifting each of its letters to its successive letter.

    For example, "abc" can be shifted to be "bcd".

We can keep shifting the string to form a sequence.

    For example, we can keep shifting "abc" to form the sequence: "abc" -> "bcd" -> ... -> "xyz".

Given an array of strings strings, group all strings[i] that belong to the same shifting sequence. You may return the answer in any order.

 

Example 1:

Input: strings = ["abc","bcd","acef","xyz","az","ba","a","z"]
Output: [["acef"],["a","z"],["abc","bcd","xyz"],["az","ba"]]

Example 2:

Input: strings = ["a"]
Output: [["a"]]

 

Constraints:

    1 <= strings.length <= 200
    1 <= strings[i].length <= 50
    strings[i] consists of lowercase English letters.


*/

class Solution {
private:
    char shift(char c, int shift) {
        //in case of 'c - shift' become negative, so we plus 26
        return (c - shift + 26) % 26 + 'a';
    }

    std::string afterHash(std::string& s) {

        //for example, bcd used 'b' as base for shifting, then it will become abc
        int base = s[0];
        std::string result;
        
        for (char c : s) {
            result += shift(c, base);
        }

        //using the hashed result, we could get the same key and put those strings with the same key 
        //into the same vector
        return result;
    }
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        std::unordered_map<std::string, std::vector<std::string>> m;

        for (std::string& s : strings) {
            std::string key = afterHash(s);

            m[key].push_back(s);
        }

        std::vector<std::vector<std::string>> result;
        for (std::pair<std::string, std::vector<std::string>> p : m) {
            result.push_back(p.second);
        }

        return result;
    }
};