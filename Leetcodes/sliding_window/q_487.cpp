/*
Given a binary array nums, return the maximum number of consecutive 1's in the array if you can flip at most one 0.

 

Example 1:

Input: nums = [1,0,1,1,0]
Output: 4
Explanation: 
- If we flip the first zero, nums becomes [1,1,1,1,0] and we have 4 consecutive ones.
- If we flip the second zero, nums becomes [1,0,1,1,1] and we have 3 consecutive ones.
The max number of consecutive ones is 4.

Example 2:

Input: nums = [1,0,1,1,0,1]
Output: 4
Explanation: 
- If we flip the first zero, nums becomes [1,1,1,1,0,1] and we have 4 consecutive ones.
- If we flip the second zero, nums becomes [1,0,1,1,1,1] and we have 4 consecutive ones.
The max number of consecutive ones is 4.

 

Constraints:

    1 <= nums.length <= 10^5
    1 <= nums.length <= 10^5
    nums[i] is either 0 or 1.

*/

class Solution {
private:
    int slidingWindow2(vector<int>& nums) {
        //count 1 before first 0
        int zerosN = 0;
        //count 1 before second 0
        int zerosNplusOne = 0;
        int maxLen = 0;

        int zeros = 0;
        //find first 0, and count 1 before it
        //break when we meet zero
        int i = 0;
        for (i = 0; i < nums.size(); ++i) {
            if (nums[i] == 1) {
                ++zerosN;
            } else {
                //for counting zeros
                zeros += 1;
                break;
            }
        }

        //start after first zero, 
        //then calculate and compare max consecutive ones after first zero
        for (i = i + 1; i < nums.size(); ++i) {
            if (nums[i] == 1) {
                ++zerosNplusOne;
            } else {
                maxLen = std::max(maxLen, zerosN + zerosNplusOne + 1);
                zerosN = zerosNplusOne;
                zerosNplusOne = 0;
                ++zeros;
            }
        }

        //make the last count if no zero till the end
        maxLen = std::max(maxLen, zerosN + zerosNplusOne + 1);

        //corner case, no zero
        if (zeros == 0) {
            maxLen = nums.size();
        }

        return maxLen;
    }

    int slidingWindow(vector<int>& nums) {
        int longest = 0;
        int left = 0;
        int right = 0;
        int zeros = 0;

        //the sliding window size controled by at most 1 zersos
        while (right < nums.size()) {
            if (nums[right] == 0) {
                ++zeros;
            }

            while (zeros == 2) {
                if (nums[left] == 0) {
                    --zeros;
                }

                ++left;
            }

            longest = std::max(longest, right - left + 1);
            ++right;
        }

        return longest;
    }

    int naiveThough(vector<int>& nums) {
        int pos = 0;
            int maxFlip = 0;
            int allOnes = true;

            for (int i = 0; i < nums.size(); ++i) {
                if (nums[i] == 0) {
                    int index = i;
                    int count = 1;

                    --index;
                    while (index > -1 && nums[index] != 0) {
                        ++count;
                        --index;
                    }

                    index = i;
                    ++index;
                    while (index < nums.size() && nums[index] != 0) {
                        ++count;
                        ++index;
                    }

                    maxFlip = std::max(maxFlip, count);
                    allOnes = false;
                } 
            }

            if (allOnes) {
                maxFlip = nums.size();
            }

            return maxFlip;
    }
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        //edge case
        if (nums.size() == 1) {
            return 1;
        }

        
        //return slidingWindow(nums);
        //return naiveThough(nums);
        return slidingWindow2(nums);
    }
};