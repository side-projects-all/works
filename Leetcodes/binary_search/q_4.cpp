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
    //b1: begin of nums1, b2: begin of nums2, e1: end of nums1, e2: end of nums2
    /*
    int solve(vector<int>& nums1, vector<int>& nums2, int k, int b1, int e1, int b2, int e2) {
        if (e1 < b1) {
            return nums2[k - b1];
        }

        if (e2 < b2) {
            return nums1[k - b2];
        }

        int n1_mid = (b1 + e1) / 2;
        int n2_mid = (b2 + e2) / 2;
        int n1_mid_val = nums1[n1_mid];
        int n2_mid_val = nums2[n2_mid];

        if (n1_mid + n2_mid < k) {
            if (n1_mid_val > n2_mid_val) {
                return solve(nums1, nums2, k, b1, e1, n2_mid + 1, e2);
            } else {
                return solve(nums1, nums2, k, n1_mid + 1, e1, b2, e2);
            }
        } else {
            if (n1_mid_val > n2_mid_val) {
                return solve(nums1, nums2, k, b1, n1_mid - 1, b2, e2);
            } else {
                return solve(nums1, nums2, k, b1, e1, b2, n2_mid - 1);
            }
        }

        return -1;
    }
    */

public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        
        //recursive binary search
        /*
        int Na = nums1.size();
        int Nb = nums2.size();
        int N = Na + Nb;

        if (N % 2) {
            return solve(nums1, nums2, N / 2, 0, Na - 1, 0, Nb - 1);
        } else {
            return 1.0 * (solve(nums1, nums2, N / 2 - 1, 0, Na - 1, 0, Nb - 1) + 
                        solve(nums1, nums2, N / 2, 0, Na - 1, 0, Nb - 1)) / 2;
        }
        */

        //better binary search
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int N1 = nums1.size();
        int N2 = nums2.size();
        int left = 0;
        int right = N1;

        while (left <= right) {
            int partA = left + (right - left) / 2;
            int partB = (N1 + N2 + 1) / 2 - partA;

            int maxLeftA = (partA == 0) ? INT_MIN : nums1[partA - 1];
            int minRightA = (partA == N1) ? INT_MAX : nums1[partA];
            int maxLeftB = (partB == 0) ? INT_MIN : nums2[partB - 1];
            int minRightB = (partB == N2) ? INT_MAX : nums2[partB];

            if (maxLeftA <= minRightB && maxLeftB <= minRightA) {
                if ((N1 + N2) % 2 == 0) {
                    return (std::max(maxLeftA, maxLeftB) + std::min(minRightA, minRightB)) / 2.0;
                } else {
                    return std::max(maxLeftA, maxLeftB);
                }
            } else if (maxLeftA > minRightB) {
                right = partA - 1;
            } else {
                left = partA + 1;
            }

        }

        return 0.0;
    }
};