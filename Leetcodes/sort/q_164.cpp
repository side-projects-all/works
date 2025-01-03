/*
Given an integer array nums, return the maximum difference between two successive elements in its sorted form. If the array contains less than two elements, return 0.

You must write an algorithm that runs in linear time and uses linear extra space.

 

Example 1:

Input: nums = [3,6,9,1]
Output: 3
Explanation: The sorted form of the array is [1,3,6,9], either (3,6) or (6,9) has the maximum difference 3.

Example 2:

Input: nums = [10]
Output: 0
Explanation: The array contains less than 2 elements, therefore return 0.

 

Constraints:

    1 <= nums.length <= 10^5
    0 <= nums[i] <= 10^9


*/

class Bucket {
public:
    bool used = false;
    int minVal = std::numeric_limits<int>::max();
    int maxVal = std::numeric_limits<int>::min();
};

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        //edge case
        if (nums.size() < 2) {
            return 0;
        }

        
        //using comparison sort
        /*
        int max_diff = 0;
        std::sort(nums.begin(), nums.end());

        for (int i = 1; i < nums.size(); ++i) {
            max_diff = std::max(max_diff, nums[i] - nums[i - 1]);
        }

        return max_diff;
        */

        //the requirement is O(n)

        /*
        //using radix sort
        int max_val = *std::max_element(nums.begin(), nums.end());
        int exp = 1;
        int radix = 10;

        std::vector<int> aux(nums.size());

        while (max_val / exp > 0) {
            std::vector<int> count(radix, 0);

            //counting sort here
            for (int i = 0; i < nums.size(); ++i) {
                //get the digit after dividing by exp e.g 1, 10, 100
                int digit = (nums[i] / exp) % 10;   
                ++count[digit];
            }

            //finding every position from counting result
            for (int i = 1; i < count.size(); ++i) {
                count[i] += count[i - 1];
            }

            //put nums[i] into their position
            for (int i = nums.size() - 1; i > -1; --i) {
                int digit = (nums[i] / exp) % 10;
                int pos = --count[digit];

                aux[pos] = nums[i];
            }

            //put aux[i] into original array nums[i]
            for (int i = 0; i < nums.size(); ++i) {
                nums[i] = aux[i];
            }

            exp *= 10;
        }

        int max_diff = 0;

        for (int i = 1; i < nums.size(); ++i) {
            max_diff = std::max(max_diff, nums[i] - nums[i - 1]);
        }

        return max_diff;
        */

        //using bucket sort
        int min = *std::min_element(nums.begin(), nums.end());
        int max = *std::max_element(nums.begin(), nums.end());

        int bucketSize = std::max(1, (max - min) / ((int)nums.size() - 1));
        int bucketNum = (max - min) / bucketSize + 1;

        std::vector<Bucket> buckets(bucketNum);

        for (auto num : nums) {
            int bucketIndex = (num - min) / bucketSize;

            buckets[bucketIndex].used = true;
            buckets[bucketIndex].minVal = std::min(num, buckets[bucketIndex].minVal);
            buckets[bucketIndex].maxVal = std::max(num, buckets[bucketIndex].maxVal);
        }

        int max_diff = 0;
        int prevBucketMax = min;
        for (auto bucket : buckets) {
            if (!bucket.used) {
                continue;
            }

            max_diff = std::max(max_diff, bucket.minVal - prevBucketMax);
            prevBucketMax = bucket.maxVal;
        }

        return max_diff;
    }
};