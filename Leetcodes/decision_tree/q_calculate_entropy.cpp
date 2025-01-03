/*
Given a group of values, the entropy of the group is defined as the formula as following:

where P(x) is the probability of appearance for the value x.

The exercise is to calculate the entropy of a group. Here is one example.

the input group:  [1, 1, 2, 2]

the probability of value 1 is  2/4 = 1/2
the probability of value 2 is  2/4 = 1/2

As a result, its entropy can be obtained by:  - (1/2) * log2(1/2) - (1/2) * log2(1/2) = 1/2 + 1/2 = 1

Note: the precision of result would remain within 1e^-6.

*/

class Solution {
public:
    double calculateEntropy(vector<int>& input) {
        int total = input.size();
        std::unordered_map<int, int> cnt;
        
        for (int key : input) {
            if (cnt.find(key) != cnt.end()) {
                cnt[key] += 1;
            } else {
                cnt[key] = 1;
            }
        }
        
        
        double result = 0.0;
        for (auto pair : cnt) {
            double p = ((double)pair.second) / total;
            double log = -std::log2(p);
            result += p * log;
        }
        
        return result;
    }
};