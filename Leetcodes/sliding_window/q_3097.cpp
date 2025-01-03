/*
You are given an array nums of non-negative integers and an integer k.

An array is called special if the bitwise OR of all of its elements is at least k.

Return the length of the shortest special non-empty
subarray
of nums, or return -1 if no special subarray exists.

 

Example 1:

Input: nums = [1,2,3], k = 2

Output: 1

Explanation:

The subarray [3] has OR value of 3. Hence, we return 1.

Example 2:

Input: nums = [2,1,8], k = 10

Output: 3

Explanation:

The subarray [2,1,8] has OR value of 11. Hence, we return 3.

Example 3:

Input: nums = [1,2], k = 0

Output: 1

Explanation:

The subarray [1] has OR value of 1. Hence, we return 1.

 

Constraints:

    1 <= nums.length <= 2 * 10^5
    0 <= nums[i] <= 10^9
    0 <= k <= 10^9


*/

class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int min_len = INT_MAX;
        //window begin and end
        int b = 0;
        int e = 0;
        //tracks count of set bits at each position
        std::vector<int> bit_cnts(32, 0);  

        //loop window to end of array
        while (e < nums.size()) {
            //add current num to window
            update_bit_cnts(bit_cnts, nums[e], 1);

            //narrow window while OR value is valid
            while (b <= e && bit_cnts_to_num(bit_cnts) >= k) {
                // Update minimum length found so far
                min_len = min(min_len, e - b + 1);

                // Remove leftmost number and shrink window
                update_bit_cnts(bit_cnts, nums[b], -1);
                ++b;
            }

            ++e;
        }

        return min_len == INT_MAX ? -1 : min_len;
    }

private:
    //update bit count array when adding/removing a number from window
    void update_bit_cnts(vector<int>& bit_cnts, int num, int delta) {

        for (int bit_pos = 0; bit_pos < 32; ++bit_pos) {

            //check if bit is set at current position
            if ((num >> bit_pos) & 1) {
                bit_cnts[bit_pos] += delta;
            }
        }
    }

    //change bit count array back to number using OR operation
    int bit_cnts_to_num(const vector<int>& bit_cnts) {

        int ans = 0;
        for (int bit_pos = 0; bit_pos < 32; ++bit_pos) {

            if (bit_cnts[bit_pos] != 0) {
                ans |= 1 << bit_pos;
            }
        }
        return ans;
    }
};