/*
Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the result must be unique and you may return the result in any order.

 

Example 1:

Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]

Example 2:

Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [9,4]
Explanation: [4,9] is also accepted.

 

Constraints:

    1 <= nums1.length, nums2.length <= 1000
    0 <= nums1[i], nums2[i] <= 1000


*/

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        std::sort(nums1.begin(), nums1.end());
        std::sort(nums2.begin(), nums2.end());

        int p1 = 0;
        int p2 = 0;
        std::vector<int> ans;
        while (p1 < nums1.size() && p2 < nums2.size()) {

            if (nums1[p1] == nums2[p2]) {
                ans.push_back(nums1[p1]);
                ++p1;
                ++p2;

                //skip duplicate val
                while (p1 < nums1.size() && nums1[p1] == nums1[p1 -1]) {
                    ++p1;
                }

                while (p2 < nums2.size() && nums2[p2] == nums2[p2 -1]) {
                    ++p2;
                }

            } else if (nums1[p1] < nums2[p2]) {
                ++p1;

            } else {
                ++p2;
            }
        }

        return ans;
    }
};