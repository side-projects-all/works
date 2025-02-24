/*
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).

 

Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.

 

Constraints:

    nums1.length == m
    nums2.length == n
    0 <= m <= 1000
    0 <= n <= 1000
    1 <= m + n <= 2000
    -10^6 <= nums1[i], nums2[i] <= 10^6


*/

class Solution {
private:
    double by_binary_search(vector<int>& nums1, int& n1, vector<int>& nums2, int& n2) {
        //focus on building smaller part of two arrays
        int left = 0;
        int right = n1;

        while (left <= right) {
            int part_a = left + (right - left) / 2;     //this is smaller part
            int part_b = (n1 + n2 + 1) / 2 - part_a;

            int max_left_a = (part_a == 0) ? INT_MIN : nums1[part_a - 1];
            int min_right_a = (part_a == n1) ? INT_MAX : nums1[part_a];
            int max_left_b = (part_b == 0) ? INT_MIN : nums2[part_b - 1];
            int min_right_b = (part_b == n2) ? INT_MAX : nums2[part_b];

            if (max_left_a <= min_right_b && max_left_b <= min_right_a) {

                if ((n1 + n2) % 2 == 0) {
                    return (std::max(max_left_a, max_left_b) + std::min(min_right_a, min_right_b)) * 0.5;
                } else {
                    return std::max(max_left_a, max_left_b);
                }

            } else if (max_left_a > min_right_b) {
                right = part_a - 1;

            } else {
                // not use  if (max_left_b > min_right_a) for better performance
                left = part_a + 1;
            }
        }

        return 0.0;
    }
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        if (n1 > n2) {
            return by_binary_search(nums2, n2, nums1, n1);
        }

        return by_binary_search(nums1, n1, nums2, n2);
    }
};