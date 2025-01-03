/*
You are given an integer array nums consisting of n elements, and an integer k.

Find a contiguous subarray whose length is greater than or equal to k that has the maximum average value and return this value. Any answer with a calculation error less than 10-5 will be accepted.

 

Example 1:

Input: nums = [1,12,-5,-6,50,3], k = 4
Output: 12.75000
Explanation:
- When the length is 4, averages are [0.5, 12.75, 10.5] and the maximum average is 12.75
- When the length is 5, averages are [10.4, 10.8] and the maximum average is 10.8
- When the length is 6, averages are [9.16667] and the maximum average is 9.16667
The maximum average is when we choose a subarray of length 4 (i.e., the sub array [12, -5, -6, 50]) which has the max average 12.75, so we return 12.75
Note that we do not consider the subarrays of length < 4.

Example 2:

Input: nums = [5], k = 1
Output: 5.00000

 

Constraints:

    n == nums.length
    1 <= k <= n <= 10^4
    -104 <= nums[i] <= 10^4


*/

class Solution {

    //check whether there exists a subarray whose length >= k and average >= mid
    bool check(std::vector<int>& nums, double mid, int k) {
        double sum = 0;
        double prev = 0;
        double min_sum = 0;

        //this is the sum equal to k
        for (int i = 0; i < k; ++i) {
            sum += nums[i] - mid;
        }

        if (sum >= 0) {
            return true;
        }

        //the most important part!!!
        //find the min_sum in previous sub-array, 
        //and accumulate array value, then substract this min_sum, 
        //if the result were larger than zero, 
        for (int i = k; i < nums.size(); ++i) {
            sum += nums[i] - mid;
            prev += nums[i - k] - mid;

            min_sum = std::min(prev, min_sum);

            if (sum - min_sum >= 0) {
                return true;
            }
        }

        return false;
    }

    double byBS(vector<int>& nums, int k) {
        double max_val = *std::max_element(nums.begin(), nums.end());
        double min_val = *std::min_element(nums.begin(), nums.end());

        double prev_mid = max_val;
        double err = max_val;

        while (err > 0.00001) {

            //we have minimum and maximum for the range of mid, 

            double mid = (max_val + min_val) * 0.5;

            //use check function to know whether there exists a subarray whose length >= k and average >= mid
            if (check(nums, mid, k)) {
                min_val = mid;
            } else {
                max_val = mid;
            }

            err = std::abs(prev_mid - mid);
            prev_mid = mid;
        }

        return min_val;
    }
public:
    double findMaxAverage(vector<int>& nums, int k) {
        return byBS(nums, k);
    }
};