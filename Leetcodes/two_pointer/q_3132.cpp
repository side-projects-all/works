/*
You are given two integer arrays nums1 and nums2.

From nums1 two elements have been removed, and all other elements have been increased (or decreased in the case of negative) by an integer, represented by the variable x.

As a result, nums1 becomes equal to nums2. Two arrays are considered equal when they contain the same integers with the same frequencies.

Return the minimum possible integer x that achieves this equivalence.

 

Example 1:

Input: nums1 = [4,20,16,12,8], nums2 = [14,18,10]

Output: -2

Explanation:

After removing elements at indices [0,4] and adding -2, nums1 becomes [18,14,10].

Example 2:

Input: nums1 = [3,5,5,3], nums2 = [7,7]

Output: 2

Explanation:

After removing elements at indices [0,3] and adding 2, nums1 becomes [7,7].

 

Constraints:

    3 <= nums1.length <= 200
    nums2.length == nums1.length - 2
    0 <= nums1[i], nums2[i] <= 1000
    The test cases are generated in a way that there is an integer x such that nums1 can become equal to nums2 by removing two elements and adding x to each element of nums1.


*/

class Solution {
public:
    int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2) {
        std::sort(nums1.begin(), nums1.end());
        std::sort(nums2.begin(), nums2.end());
        int min = INT_MAX;
        
        int N1 = nums1.size();
        int N2 = nums2.size();
        
        for (int i = 0; i < N1; ++i) {

            int cnt = 0;
            int diff = nums2[0] - nums1[i];
            int i2 = 0;

            //two pointer here?
            for (int k = 0; k < N1 && i2 < N2; ++k) {
                if (nums1[k] + diff != nums2[i2]) {
                    ++cnt;
                } else {
                    ++i2;
                }
            }

            if (cnt <= 2) {
                min = std::min(min, diff);
            }
        }
        
        return min;
    }
};