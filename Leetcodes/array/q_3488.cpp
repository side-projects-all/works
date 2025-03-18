/*
You are given a circular array nums and an array queries.

For each query i, you have to find the following:

    The minimum distance between the element at index queries[i] and any other index j in the circular array, where nums[j] == nums[queries[i]]. If no such index exists, the answer for that query should be -1.

Return an array answer of the same size as queries, where answer[i] represents the result for query i.

 

Example 1:

Input: nums = [1,3,1,4,1,3,2], queries = [0,3,5]

Output: [2,-1,3]

Explanation:

    Query 0: The element at queries[0] = 0 is nums[0] = 1. The nearest index with the same value is 2, and the distance between them is 2.
    Query 1: The element at queries[1] = 3 is nums[3] = 4. No other index contains 4, so the result is -1.
    Query 2: The element at queries[2] = 5 is nums[5] = 3. The nearest index with the same value is 1, and the distance between them is 3 (following the circular path: 5 -> 6 -> 0 -> 1).

Example 2:

Input: nums = [1,2,3,4], queries = [0,1,2,3]

Output: [-1,-1,-1,-1]

Explanation:

Each value in nums is unique, so no index shares the same value as the queried element. This results in -1 for all queries.

 

Constraints:

    1 <= queries.length <= nums.length <= 10^5
    1 <= nums[i] <= 10^6
    0 <= queries[i] < nums.length


*/

class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int qn = queries.size();
        int n = nums.size();
        
        std::unordered_map<int, std::vector<int>> m;    //val, index array
        for (int i = 0; i < n; ++i) {
            m[nums[i]].push_back(i);
        }
        
        std::vector<int> ans(qn, -1);
        for (int i = 0; i < qn; ++i) {
            int index = queries[i];
            int val = nums[index];
            
            if (m[val].size() == 1) {
                continue;
            }
            
            //find position
            int pos = std::lower_bound(m[val].begin(), m[val].end(), index) - m[val].begin();
                        
            int len = m[val].size();
            int right = (pos + 1) % len;
            int left = (pos - 1 + len) % len;
            int d_right = std::abs(index - m[val][right]);
            int d_left = std::abs(index - m[val][left]);
            d_right = std::min(d_right, n - d_right);
            d_left = std::min(d_left, n - d_left);
            ans[i] = std::min(d_left, d_right);
        }
        
        return ans;
    }
};
