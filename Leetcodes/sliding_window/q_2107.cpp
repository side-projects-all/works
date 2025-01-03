/*
You are given a 0-indexed integer array candies, where candies[i] represents the flavor of the ith candy. Your mom wants you to share these candies with your little sister by giving her k consecutive candies, but you want to keep as many flavors of candies as possible.

Return the maximum number of unique flavors of candy you can keep after sharing with your sister.

 

Example 1:

Input: candies = [1,2,2,3,4,3], k = 3
Output: 3
Explanation: 
Give the candies in the range [1, 3] (inclusive) with flavors [2,2,3].
You can eat candies with flavors [1,4,3].
There are 3 unique flavors, so return 3.

Example 2:

Input: candies = [2,2,2,2,3,3], k = 2
Output: 2
Explanation: 
Give the candies in the range [3, 4] (inclusive) with flavors [2,3].
You can eat candies with flavors [2,2,2,3].
There are 2 unique flavors, so return 2.
Note that you can also share the candies with flavors [2,2] and eat the candies with flavors [2,2,3,3].

Example 3:

Input: candies = [2,4,5], k = 0
Output: 3
Explanation: 
You do not have to give any candies.
You can eat the candies with flavors [2,4,5].
There are 3 unique flavors, so return 3.

 

Constraints:

    1 <= candies.length <= 10^5
    1 <= candies[i] <= 10^5
    0 <= k <= candies.length


*/

class Solution {
public:
    int shareCandies(vector<int>& candies, int k) {
        int max_uniques = 0;

        std::unordered_map<int, int> freq;
        for (int i = k; i < candies.size(); ++i) {
            ++freq[candies[i]];
        }

        max_uniques = freq.size();
        if (k == 0) {
            return max_uniques;
        }

        int curr_uniques = max_uniques;
        for (int i = 0; i + k < candies.size(); ++i) {

            if (freq.find(candies[i]) == freq.end()) {
                ++curr_uniques;
            }

            ++freq[candies[i]];         //leaving the window, add it back
            --freq[candies[i + k]];     //adding to the window, deduct it
            if (freq.find(candies[i + k])->second == 0) {
                --curr_uniques;
                freq.erase(candies[i + k]);
            }

            max_uniques = std::max(max_uniques, curr_uniques);
        }

        return max_uniques;
    }
};