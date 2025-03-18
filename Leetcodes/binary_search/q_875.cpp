/*
Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.

 

Example 1:

Input: piles = [3,6,7,11], h = 8
Output: 4

Example 2:

Input: piles = [30,11,23,4,20], h = 5
Output: 30

Example 3:

Input: piles = [30,11,23,4,20], h = 6
Output: 23

 

Constraints:

    1 <= piles.length <= 10^4
    piles.length <= h <= 10^9
    1 <= piles[i] <= 10^9


*/

class Solution {
private:
    int by_binary_search(vector<int>& piles, int& h) {
        int n = piles.size();
        if (n == 1) {
            return piles[0] / h + (piles[0] % h != 0);
        }

        int b = 1;
        int e = piles[0];
        for (int i = 1; i < n; ++i) {
            e = std::max(e, piles[i]);
        }

        while (b < e) {
            int mid = b + (e - b) / 2;
            int hours = 0;
            for (int i = 0; i < n; ++i) {
                hours += piles[i] / mid + (piles[i] % mid != 0);
            }

            if (hours > h) {
                b = mid + 1;

            } else {
                e = mid;
            }
        }

        return b;
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        return by_binary_search(piles, h);
    }
};