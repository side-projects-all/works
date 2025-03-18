/*
You are given an integer array ranks representing the ranks of some mechanics. ranksi is the rank of the ith mechanic. A mechanic with a rank r can repair n cars in r * n2 minutes.

You are also given an integer cars representing the total number of cars waiting in the garage to be repaired.

Return the minimum time taken to repair all the cars.

Note: All the mechanics can repair the cars simultaneously.

 

Example 1:

Input: ranks = [4,2,3,1], cars = 10
Output: 16
Explanation: 
- The first mechanic will repair two cars. The time required is 4 * 2 * 2 = 16 minutes.
- The second mechanic will repair two cars. The time required is 2 * 2 * 2 = 8 minutes.
- The third mechanic will repair two cars. The time required is 3 * 2 * 2 = 12 minutes.
- The fourth mechanic will repair four cars. The time required is 1 * 4 * 4 = 16 minutes.
It can be proved that the cars cannot be repaired in less than 16 minutes.​​​​​

Example 2:

Input: ranks = [5,1,8], cars = 6
Output: 16
Explanation: 
- The first mechanic will repair one car. The time required is 5 * 1 * 1 = 5 minutes.
- The second mechanic will repair four cars. The time required is 1 * 4 * 4 = 16 minutes.
- The third mechanic will repair one car. The time required is 8 * 1 * 1 = 8 minutes.
It can be proved that the cars cannot be repaired in less than 16 minutes.​​​​​

 

Constraints:

    1 <= ranks.length <= 10^5
    1 <= ranks[i] <= 100
    1 <= cars <= 10^6


*/

class Solution {
private:
    long long by_binary_search(vector<int>& ranks, int& cars) {
        int n = ranks.size();
        if (n == 1) {
            return (long long)ranks[0] * cars * cars;
        }

        int min_rank = ranks[0];
        int max_rank = ranks[0];
        for (int i = 1; i < n; ++i) {
            min_rank = std::min(min_rank, ranks[i]);
            max_rank = std::max(max_rank, ranks[i]);
        }

        std::vector<int> freq(max_rank + 1);
        for (int i = 0; i < n; ++i) {
            ++freq[ranks[i]];
        }

        long long b = 1;
        long long e = (long long)min_rank * cars * cars;

        while (b < e) {
            long long mid = b + (e - b) / 2;
            long long cars_repaired = 0;

            for (int r = min_rank; r <= max_rank; ++r) {
                cars_repaired += (long long)std::sqrt(mid / (long long)r) * freq[r];
            }

            if (cars_repaired >= cars) {
                e = mid;

            } else {
                b = mid + 1;
            }
        }

        return b;
    }
public:
    long long repairCars(vector<int>& ranks, int cars) {
        return by_binary_search(ranks, cars);
    }
};