/*
There are n workers. You are given two integer arrays quality and wage where quality[i] is the quality of the ith worker and wage[i] is the minimum wage expectation for the ith worker.

We want to hire exactly k workers to form a paid group. To hire a group of k workers, we must pay them according to the following rules:

    Every worker in the paid group must be paid at least their minimum wage expectation.
    In the group, each worker's pay must be directly proportional to their quality. This means if a worker’s quality is double that of another worker in the group, then they must be paid twice as much as the other worker.

Given the integer k, return the least amount of money needed to form a paid group satisfying the above conditions. Answers within 10-5 of the actual answer will be accepted.

 

Example 1:

Input: quality = [10,20,5], wage = [70,50,30], k = 2
Output: 105.00000
Explanation: We pay 70 to 0th worker and 35 to 2nd worker.

Example 2:

Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], k = 3
Output: 30.66667
Explanation: We pay 4 to 0th worker, 13.33333 to 2nd and 3rd workers separately.

 

Constraints:

    n == quality.length == wage.length
    1 <= k <= n <= 10^4
    1 <= quality[i], wage[i] <= 10^4


*/

class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int N = quality.size();
        double ans = INT_MAX;
        double curr_total_q = 0;
        std::vector<std::pair<double,int>> w_to_q;

        for (int i = 0; i < N; ++i) {
            w_to_q.push_back({ 1.0 * wage[i] / quality[i], quality[i]});
        }

        std::sort(w_to_q.begin(), w_to_q.end());
        std::priority_queue<int> pq;

        for (int i = 0; i < N; ++i) {
            pq.push(w_to_q[i].second);
            curr_total_q += w_to_q[i].second;

            if (pq.size() > k) {
                curr_total_q -= pq.top();
                pq.pop();
            }

            if (pq.size() == k) {
                ans = std::min(ans, curr_total_q * w_to_q[i].first);
            }
        }

        return ans;
    }
};
