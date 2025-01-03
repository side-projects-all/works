/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

 

Example 1:

Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.

Example 2:

Input: height = [4,2,0,3,2,5]
Output: 9

 

Constraints:

    n == height.length
    1 <= n <= 2 * 10^4
    0 <= height[i] <= 10^5


*/


class Solution {
public:
    int trap(vector<int>& height) {
        //return by_two_ptr(height);
        return by_dp(height);
    }

private:
    int by_two_ptr(std::vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int left_max = 0;
        int right_max = 0;
        int trap = 0;

        while (left < right) {

            if (height[left] < height[right]) {
                left_max < height[left] ? left_max = height[left] : trap += left_max - height[left];
                ++left;

            } else {
                right_max < height[right] ? right_max = height[right] : trap += right_max - height[right];
                --right;
            }
        }

        return trap;
    }

    int by_dp(std::vector<int>& height) {
        int n = height.size();
        std::vector<int> left_max(n);
        std::vector<int> right_max(n);

        left_max[0] = height[0];
        for (int i = 1; i < n; ++i) {
            left_max[i] = std::max(left_max[i - 1], height[i]);
        }

        right_max[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            right_max[i] = std::max(right_max[i + 1], height[i]);
        }

        int trap = 0;
        for (int i = 0; i < n; ++i) {
            trap += std::min(left_max[i], right_max[i]) - height[i];
        }
        return trap;
    }
};