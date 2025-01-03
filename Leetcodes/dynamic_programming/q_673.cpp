/*
Given an integer array nums, return the number of longest increasing subsequences.

Notice that the sequence has to be strictly increasing.

 

Example 1:

Input: nums = [1,3,5,4,7]
Output: 2
Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and [1, 3, 5, 7].

Example 2:

Input: nums = [2,2,2,2,2]
Output: 5
Explanation: The length of the longest increasing subsequence is 1, and there are 5 increasing subsequences of length 1, so output 5.

 

Constraints:

    1 <= nums.length <= 2000
    -10^6 <= nums[i] <= 10^6


*/

class Solution {
private:
    int iterative(std::vector<int>& nums) {
        //edge case
        if (nums.size() == 1) {
            return 1;
        }

        std::vector<int> len(nums.size(), 1);
        std::vector<int> cnt(nums.size(), 1);
        //std::vector<int> max_indices;

        int max = -1;
        for (int i = 0; i < nums.size() ; ++i) {

            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {

                    if (len[i] < len[j] + 1) {
                        len[i] = len[j] + 1;
                        cnt[i] = 0; //reset originally longest count

                    }
                    
                    if (len[i] == len[j] + 1) {
                        cnt[i] += cnt[j];
                        
                    }
                }
            }

            max = std::max(max, len[i]);

            //tring to use vector space manipulation, but the truth is 
            //any delete operation causes inefficiency
            /*
            if (max < len[i]) {
                max_indices.clear();
                max_indices.push_back(i);
                max = len[i];
            } else if (max == len[i]) {
                max_indices.push_back(i);
            }*/
        }

        int result = 0;
        /*
        for (int i = 0; i < max_indices.size(); ++i) {
            result += cnt[max_indices[i]];
        }*/
        
        for (int i = 0; i < nums.size(); ++i) {
            if (len[i] == max) {
                result += cnt[i];
            }
        }

        return result;
    }
public:
    int findNumberOfLIS(vector<int>& nums) {
        
        return iterative(nums);
    }
};