/*
Alice has some number of cards and she wants to rearrange the cards into groups so that each group is of size groupSize, and consists of groupSize consecutive cards.

Given an integer array hand where hand[i] is the value written on the ith card and an integer groupSize, return true if she can rearrange the cards, or false otherwise.

 

Example 1:

Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
Output: true
Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8]

Example 2:

Input: hand = [1,2,3,4,5], groupSize = 4
Output: false
Explanation: Alice's hand can not be rearranged into groups of 4.

 

Constraints:

    1 <= hand.length <= 10^4
    0 <= hand[i] <= 10^9
    1 <= groupSize <= hand.length

*/

class Solution {
private:
    bool byPQ(vector<int>& hand, int groupSize) {
        if (hand.size() < groupSize || hand.size() % groupSize) {
            return false;
        }

        std::unordered_map<int, int> m;
        for (int v : hand) {
            ++m[v];
        }

        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
        for (const auto& p : m) {
            pq.push(p.first);
        }

        while (!pq.empty()) {
            int first = pq.top();

            if (m[first] == 0) {
                pq.pop();
                //m.erase(first);
                continue;
            }

            --m[first];
            int cnt = groupSize - 1;
            while (cnt > 0) {
                if (m[first + 1]) {
                    --m[first + 1];
                    --cnt;
                    ++first;
                } else {
                    return false;
                }
            }
        }

        return true;
    }
    bool byMap(vector<int>& hand, int groupSize) {
        if (hand.size() < groupSize || hand.size() % groupSize) {
            return false;
        }

        std::map<int, int> m;

        for (int i = 0; i < hand.size(); ++i) {
            ++m[hand[i]];
        }

        while (!m.empty()) {

            int start_key = m.begin()->first;
            for (int i = 0; i < groupSize; ++i) {
                if (m[start_key + i] == 0) {
                    return false;
                }
                
                --m[start_key + i];

                if (m[start_key + i] < 1) {
                    m.erase(start_key + i);
                }
            }
        }

        return true;
    }
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        
        //return byMap(hand, groupSize);
        return byPQ(hand, groupSize);
    }
};