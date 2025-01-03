/*
Given two integer arrays nums1 and nums2 of length n, count the pairs of indices (i, j) such that i < j and nums1[i] + nums1[j] > nums2[i] + nums2[j].

Return the number of pairs satisfying the condition.

 

Example 1:

Input: nums1 = [2,1,2,1], nums2 = [1,2,1,2]
Output: 1
Explanation: The pairs satisfying the condition are:
- (0, 2) where 2 + 2 > 1 + 1.

Example 2:

Input: nums1 = [1,10,6,2], nums2 = [1,4,1,5]
Output: 5
Explanation: The pairs satisfying the condition are:
- (0, 1) where 1 + 10 > 1 + 4.
- (0, 2) where 1 + 6 > 1 + 1.
- (1, 2) where 10 + 6 > 4 + 1.
- (1, 3) where 10 + 2 > 4 + 5.
- (2, 3) where 6 + 2 > 1 + 5.

 

Constraints:

    n == nums1.length == nums2.length
    1 <= n <= 10^5
    1 <= nums1[i], nums2[i] <= 10^5


*/

class Solution {
private:
    long long byBinarysearch(vector<int>& nums1, vector<int>& nums2) {
        int N = nums1.size();
        std::vector<long long> diff(N);

        for (int i = 0; i < N; ++i) {
            diff[i] = static_cast<long long>(nums1[i] - nums2[i]);
        }

        //the most important nuance is: (nums1[i] - nums2[i]) + (nums1[j] - nums2[j]) > 0
        //that is why we could use bs
        std::sort(diff.begin(), diff.end());
        long long cnt = 0;

        for (int i = 0; i < N; ++i) {

            if (diff[i] > 0) {
                cnt += N - i - 1;

            } else {
                int left = i + 1;
                int right = N - 1;
                
                while (left <= right) {
                    int mid = left + (right - left) / 2;

                    if (diff[i] + diff[mid] > 0) {
                        right = mid - 1;
                    } else {
                        left = mid + 1;
                    }
                }

                cnt += N - left;
            }
        }

        return cnt;
    }
public:
    long long countPairs(vector<int>& nums1, vector<int>& nums2) {
        return byBinarysearch(nums1, nums2);
    }
};