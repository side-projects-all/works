/*
You are given a string s of even length. Split this string into two halves of equal lengths, and let a be the first half and b be the second half.

Two strings are alike if they have the same number of vowels ('a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'). Notice that s contains uppercase and lowercase letters.

Return true if a and b are alike. Otherwise, return false.

 

Example 1:

Input: s = "book"
Output: true
Explanation: a = "bo" and b = "ok". a has 1 vowel and b has 1 vowel. Therefore, they are alike.

Example 2:

Input: s = "textbook"
Output: false
Explanation: a = "text" and b = "book". a has 1 vowel whereas b has 2. Therefore, they are not alike.
Notice that the vowel o is counted twice.

 

Constraints:

    2 <= s.length <= 1000
    s.length is even.
    s consists of uppercase and lowercase letters.


*/

class Solution {
private:
    void counting(string& s, int& cntsFirst, int& cntsSecond, int i) {

        if ((s[i] == 'a' || s[i] == 'A') || (s[i] == 'e' || s[i] == 'E') || 
            (s[i] == 'i' || s[i] == 'I') || (s[i] == 'o' || s[i] == 'O') || 
            (s[i] == 'u' || s[i] == 'U')) {
            
            if (i >= s.size() / 2) {
                ++cntsSecond;
            } else {
                ++cntsFirst;
            }
        }
    }
public:
    bool halvesAreAlike(string s) {
        int N = s.size();
        //0: a, 1: e, 2: i, 3: o, 4: u
        int cntsFirst = 0;
        int cntsSecond = 0;
        for (int i = 0; i < N / 2; ++i) {
            int second = i + N / 2;

            counting(s, cntsFirst, cntsSecond, i);
            counting(s, cntsFirst, cntsSecond, second);
        }

        if (cntsFirst != cntsSecond) {
            return false;
        }

        return true;
    }
};