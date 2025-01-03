/*
The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle values.

    For examples, if arr = [2,3,4], the median is 3.
    For examples, if arr = [1,2,3,4], the median is (2 + 3) / 2 = 2.5.

You are given an integer array nums and an integer k. There is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the median array for each window in the original array. Answers within 10-5 of the actual value will be accepted.

 

Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
Explanation: 
Window position                Median
---------------                -----
[1  3  -1] -3  5  3  6  7        1
 1 [3  -1  -3] 5  3  6  7       -1
 1  3 [-1  -3  5] 3  6  7       -1
 1  3  -1 [-3  5  3] 6  7        3
 1  3  -1  -3 [5  3  6] 7        5
 1  3  -1  -3  5 [3  6  7]       6

Example 2:

Input: nums = [1,2,3,4,2,3,1,4,2], k = 3
Output: [2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]

 

Constraints:

    1 <= k <= nums.length <= 10^5
    -2^31 <= nums[i] <= 2^31 - 1


*/

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        int len = nums.size();
        std::priority_queue<int> low_part;  //max pq
        std::priority_queue<int, std::vector<int>, std::greater<int>> high_part;    //min pq

        for (int i = 0; i < k; ++i) {
            low_part.push(nums[i]);
        }

        for (int i = 0; i < k / 2; ++i) {
            high_part.push(low_part.top());
            low_part.pop();
        }

        std::vector<double> medians;
        std::unordered_map<int, int> invalid;
        int i = k;
        while (true) {
            double median = (k & 1 ? low_part.top() : (((double)low_part.top() + (double)high_part.top()) * 0.5));
            medians.push_back(median);
            
            if (i >= len) {
                break;
            }
            
            int b = nums[i - k];
            int e = nums[i];
            ++i;
            //balance every time
            //handle b value
            int balance = 0;
            balance += (b <= low_part.top() ? -1 : 1);
            invalid[b]++;

            //handle e value
            if (!low_part.empty() && e <= low_part.top()) {
                ++balance;
                low_part.push(e);
            } else {
                --balance;
                high_part.push(e);
            }

            //rebalance
            if (balance > 0) {
                high_part.push(low_part.top());
                low_part.pop();
                --balance;
            }

            if (balance < 0) {
                low_part.push(high_part.top());
                high_part.pop();
                ++balance;
            }

            //remove invalid
            while (invalid[low_part.top()]) {
                --invalid[low_part.top()];
                low_part.pop();
            }

            while (!high_part.empty() && invalid[high_part.top()]) {
                --invalid[high_part.top()];
                high_part.pop();
            }
        }

        return medians;
    }
};