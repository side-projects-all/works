/*
You are given two strings order and s. All the characters of order are unique and were sorted in some custom order previously.

Permute the characters of s so that they match the order that order was sorted. More specifically, if a character x occurs before a character y in order, then x should occur before y in the permuted string.

Return any permutation of s that satisfies this property.

 

Example 1:

Input:  order = "cba", s = "abcd" 

Output:  "cbad" 

Explanation: "a", "b", "c" appear in order, so the order of "a", "b", "c" should be "c", "b", and "a".

Since "d" does not appear in order, it can be at any position in the returned string. "dcba", "cdba", "cbda" are also valid outputs.

Example 2:

Input:  order = "bcafg", s = "abcd" 

Output:  "bcad" 

Explanation: The characters "b", "c", and "a" from order dictate the order for the characters in s. The character "d" in s does not appear in order, so its position is flexible.

Following the order of appearance in order, "b", "c", and "a" from s should be arranged as "b", "c", "a". "d" can be placed at any position since it's not in order. The output "bcad" correctly follows this rule. Other arrangements like "bacd" or "bcda" would also be valid, as long as "b", "c", "a" maintain their order.

 

Constraints:

    1 <= order.length <= 26
    1 <= s.length <= 200
    order and s consist of lowercase English letters.
    All the characters of order are unique.


*/

class Solution {
public:
    string customSortString(string order, string s) {
        /*
        std::unordered_map<char, int> m;

        for (int i = 0; i < order.size(); ++i) {
            m[order[i]] = i;
        }

        auto comp = [](std::pair<int, char>& p1,  std::pair<int, char>& p2) {
                return p1.first > p2.first;
        };
        std::priority_queue<std::pair<int, char>, std::vector<std::pair<int, char>>, decltype(comp)> pq;

        for (int i = 0; i < s.size(); ++i) {
            int index = (m.find(s[i]) != m.end()) ? m[s[i]] : 201 + i;
            pq.push({index, s[i]});
        }

        std::string ans = "";
        while (!pq.empty()) {
            ans += pq.top().second;

            pq.pop();
        }

        return ans;
        */

        //sorting
        /*
        std::sort(s.begin(), s.end(), [order](char c1, char c2) {
            return order.find(c1) <order.find(c2);
        });
        */

        //frequency
        std::vector<int> freq(26, 0);
        for (char c : s) {
            ++freq[c - 'a'];
        }

        std::string ans = "";
        for (char c : order) {

            while (freq[c - 'a'] > 0) {
                ans += c;
                --freq[c - 'a'];
            }
        }

        for (int i = 0; i < freq.size(); ++i) {

            while (freq[i] > 0) {
                char c = i + 'a';
                ans += c;

                --freq[i];
            }
        }

        return ans;
    }
};