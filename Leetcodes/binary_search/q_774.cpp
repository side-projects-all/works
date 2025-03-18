/*
You are given an integer array stations that represents the positions of the gas stations on the x-axis. You are also given an integer k.

You should add k new gas stations. You can add the stations anywhere on the x-axis, and not necessarily on an integer position.

Let penalty() be the maximum distance between adjacent gas stations after adding the k new stations.

Return the smallest possible value of penalty(). Answers within 10-6 of the actual answer will be accepted.

 

Example 1:

Input: stations = [1,2,3,4,5,6,7,8,9,10], k = 9
Output: 0.50000

Example 2:

Input: stations = [23,24,36,39,46,56,57,65,84,98], k = 1
Output: 14.00000

 

Constraints:

    10 <= stations.length <= 2000
    0 <= stations[i] <= 10^8
    stations is sorted in a strictly increasing order.
    1 <= k <= 10^6


*/

class Solution {
private:
    int add_cnt(vector<int>& stations, int& n, double& dis, int& k) {
        int cnt = 0;
        
        for (int i = 1; i < n; ++i) {
            cnt += (int)((stations[i] - stations[i - 1]) / dis);
        }

        return cnt;
    }
    double by_binary_search(vector<int>& stations, int& k) {
        int n = stations.size();
        double b = 0;
        double e = 0;

        for (int i = 1; i < n; ++i) {
            e = std::max(e, (double)(stations[i] - stations[i - 1]));
        }

        while (e - b > 1e-6) {
            double mid = b + (e - b) / 2;
            int possible_add = add_cnt(stations, n, mid, k);

            if (possible_add > k) {
                b = mid;

            } else {
                e = mid;
            }
        }

        return b;
    }
public:
    double minmaxGasDist(vector<int>& stations, int k) {
        return by_binary_search(stations, k);
    }
};