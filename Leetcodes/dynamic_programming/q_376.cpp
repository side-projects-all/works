/*
A wiggle sequence is a sequence where the differences between successive numbers strictly alternate between positive and negative. The first difference (if one exists) may be either positive or negative. A sequence with one element and a sequence with two non-equal elements are trivially wiggle sequences.

    For example, [1, 7, 4, 9, 2, 5] is a wiggle sequence because the differences (6, -3, 5, -7, 3) alternate between positive and negative.
    In contrast, [1, 4, 7, 2, 5] and [1, 7, 4, 5, 5] are not wiggle sequences. The first is not because its first two differences are positive, and the second is not because its last difference is zero.

A subsequence is obtained by deleting some elements (possibly zero) from the original sequence, leaving the remaining elements in their original order.

Given an integer array nums, return the length of the longest wiggle subsequence of nums.

 

Example 1:

Input: nums = [1,7,4,9,2,5]
Output: 6
Explanation: The entire sequence is a wiggle sequence with differences (6, -3, 5, -7, 3).

Example 2:

Input: nums = [1,17,5,10,13,15,10,5,16,8]
Output: 7
Explanation: There are several subsequences that achieve this length.
One is [1, 17, 10, 13, 10, 16, 8] with differences (16, -7, 3, -3, 6, -8).

Example 3:

Input: nums = [1,2,3,4,5,6,7,8,9]
Output: 2

 

Constraints:

    1 <= nums.length <= 1000
    0 <= nums[i] <= 1000

*/

class Solution {
private:
    int iterative_greedy(vector<int>& nums) {
        int prevDiff = nums[1] - nums[0];
        int cnt = (prevDiff != 0) ? 2 : 1;

        for (int i = 2; i < nums.size(); ++i) {
            int diff = nums[i] - nums[i - 1];

            if ((diff > 0 && prevDiff <= 0) || (diff < 0 && prevDiff >= 0)) {
                ++cnt;
                prevDiff = diff;
            }
        }

        return cnt;
    }
    int iterative_space_optimize(vector<int>& nums) {

        int upNow = 0;
        int upPrev = 1;
        int downNow = 0;
        int downPrev = 1;

        for (int i = nums.size() - 2; i > -1; --i) {
            if (nums[i] > nums[i + 1]) {
                upNow = downPrev + 1;
                downNow = downPrev;
            } else if (nums[i] < nums[i + 1]) {
                downNow = upPrev + 1;
                upNow = upPrev;
            } else {
                downNow = downPrev;
                upNow = upPrev;
            }

            upPrev = upNow;
            downPrev = downNow;
        }

        return std::max(upNow, downNow);
    }
    int iterative_better(vector<int>& nums) {

        std::vector<int> up(nums.size());
        std::vector<int> down(nums.size());
        up[nums.size() - 1] = 1;
        down[nums.size() - 1] = 1;

        // from the iterative function, we could conclude
        // if we update memPos[i], then we do not update memNeg[i], 
        // it implies that memNeg[i] did not change from memNeg[i - 1] and vice versa.
        // so, we could reduce the time complexity from O(n^2) to O(n) by updating two array at the same time.
        for (int i = nums.size() - 2; i > -1; --i) {
            if (nums[i] > nums[i + 1]) {
                up[i] = down[i + 1] + 1;
                down[i] = down[i + 1];
            } else if (nums[i] < nums[i + 1]) {
                down[i] = up[i + 1] + 1;
                up[i] = up[i + 1];
            } else {
                down[i] = down[i + 1];
                up[i] = up[i + 1];
            }
        }

        return std::max(down[0], up[0]);
        /*
        up[0] = 1;
        down[0] = 1;

        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] > nums[i - 1]) {
                up[i] = down[i - 1] + 1;
                down[i] = down[i - 1];
            } else if (nums[i] < nums[i - 1]) {
                down[i] = up[i - 1] + 1;
                up[i] = up[i - 1];
            } else {
                down[i] = down[i - 1];
                up[i] = up[i - 1];
            }
        }

        return std::max(down[nums.size() - 1], up[nums.size() - 1]);
        */
    }

    int iterative(vector<int>& nums) {
        std::vector<int> memPos(nums.size(), 0);
        std::vector<int> memNeg(nums.size(), 0);

        for (int i = nums.size() - 2; i > -1; --i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                if (nums[i] > nums[j]) {
                    memNeg[i] = std::max(memNeg[i], 1 + memPos[j]);
                    
                } else if (nums[i] < nums[j]) {
                    memPos[i] = std::max(memPos[i], 1 + memNeg[j]);
                } 
            }
        }

        return 1 + std::max(memPos[0], memNeg[0]);
    }

    int recursive(vector<int>& nums, int now, bool isUp, std::vector<int>& memPos, std::vector<int>& memNeg) {
        if (now == nums.size() - 1) {
            return 0;
        }

        if (isUp && memPos[now] != -1) {
            return memPos[now];
        }

        if (!isUp && memNeg[now] != -1) {
            return memNeg[now];
        }

        int negMaxLen = 0;
        int posMaxLen = 0;

        for (int i = now + 1; i < nums.size(); ++i) {
            if (isUp && nums[now] < nums[i]) {
                posMaxLen = std::max(posMaxLen, 1 + recursive(nums, i, !isUp, memPos, memNeg));

            } else if (!isUp && nums[now] > nums[i]) {
                negMaxLen = std::max(negMaxLen, 1 + recursive(nums, i, !isUp, memPos, memNeg));                
            } 
        }

        if (isUp) {
            memPos[now] = posMaxLen;
            return posMaxLen;
        } else {
            memNeg[now] = negMaxLen;
            return negMaxLen;
        }
    }

public:
    int wiggleMaxLength(vector<int>& nums) {

        //corner case
        if (nums.size() < 2) {
            return nums.size();
        }

        /*
        std::vector<int> memPos(nums.size(), -1);
        std::vector<int> memNeg(nums.size(), -1);
        
        return 1 + std::max(recursive(nums, 0, true, memPos, memNeg), 
                                recursive(nums, 0, false, memPos, memNeg));
        */
        
        //return iterative(nums);
        //return iterative_better(nums);
        //return iterative_space_optimize(nums);
        return iterative_greedy(nums);
    }
};