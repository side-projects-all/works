/*
You are given an array of strings arr. A string s is formed by the concatenation of a subsequence of arr that has unique characters.

Return the maximum possible length of s.

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.

 

Example 1:

Input: arr = ["un","iq","ue"]
Output: 4
Explanation: All the valid concatenations are:
- ""
- "un"
- "iq"
- "ue"
- "uniq" ("un" + "iq")
- "ique" ("iq" + "ue")
Maximum length is 4.

Example 2:

Input: arr = ["cha","r","act","ers"]
Output: 6
Explanation: Possible longest valid concatenations are "chaers" ("cha" + "ers") and "acters" ("act" + "ers").

Example 3:

Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
Output: 26
Explanation: The only string in arr has all 26 characters.

 

Constraints:

    1 <= arr.length <= 16
    1 <= arr[i].length <= 26
    arr[i] contains only lowercase English letters.


*/

class Solution {
private:
    int recursive(vector<string>& arr) {
        //int max_len = 0;
        std::vector<int> letters(26, 0);

        std::function<int(int)> recurr = [&](int pos) -> int {
            //base case
            int max_len = 0;
            for (int i = 0; i < 26; ++i) {
                if (letters[i] > 1) {
                    return 0;
                } else if (letters[i] == 1) {
                    ++max_len;
                }
            }

            for (int i = pos; i < arr.size(); ++i) {

                for (int j = 0; j < arr[i].size(); ++j) {
                    ++letters[arr[i][j] - 'a'];
                }

                max_len = std::max(max_len, recurr(i + 1));

                for (int j = 0; j < arr[i].size(); ++j) {
                    if (letters[arr[i][j] - 'a'] == 1) {
                        letters[arr[i][j] - 'a'] = 0;
                    } else  {
                        --letters[arr[i][j] - 'a'];
                    }
                }
            }

            return max_len;
        };

        return recurr(0);
    }
public:
    int maxLength(vector<string>& arr) {
        return recursive(arr);
    }
};