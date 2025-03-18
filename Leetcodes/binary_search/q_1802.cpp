/*
You are given three positive integers: n, index, and maxSum. You want to construct an array nums (0-indexed) that satisfies the following conditions:

    nums.length == n
    nums[i] is a positive integer where 0 <= i < n.
    abs(nums[i] - nums[i+1]) <= 1 where 0 <= i < n-1.
    The sum of all the elements of nums does not exceed maxSum.
    nums[index] is maximized.

Return nums[index] of the constructed array.

Note that abs(x) equals x if x >= 0, and -x otherwise.

 

Example 1:

Input: n = 4, index = 2,  maxSum = 6
Output: 2
Explanation: nums = [1,2,2,1] is one array that satisfies all the conditions.
There are no arrays that satisfy all the conditions and have nums[2] == 3, so 2 is the maximum nums[2].

Example 2:

Input: n = 6, index = 1,  maxSum = 10
Output: 3

 

Constraints:

    1 <= n <= maxSum <= 10^9
    0 <= index < n


*/

class Solution {
private:
    long getSum(int index, int val, int n) {
        long sum = 0;

        //left side
        if (val > index) {
            //no extra ones
            sum += (long)(val + (val - index)) * (index + 1) / 2;

        } else {
            //some extra ones, they will be (index - val + 1)
            sum += (long)(val + 1) * val / 2 + (index - val + 1);
        }

        //right side
        if (val >= n - index) {
            //no extra ones
            sum += (long)(val + (val + index - n + 1)) * (n - index) / 2;

        } else {
            //some extra ones, they will be (n - index - val)
            sum += (long)(val + 1) * val /2 + (n - index - val);
        }

        return sum - val;
    }
    int byBS(int n, int index, int maxSum) {
        int left = 1;
        int right = maxSum;

        while (left < right) {
            int mid = left + std::ceil(1.0 * (right - left) / 2);

            if (getSum(index, mid, n) <= maxSum) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }

        return left;
    }
public:
    int maxValue(int n, int index, int maxSum) {
        return byBS(n, index, maxSum);
    }
};