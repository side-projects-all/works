/*
Given an integer array nums of 2n integers, group these integers into n pairs (a1, b1), (a2, b2), ..., (an, bn) such that the sum of min(ai, bi) for all i is maximized. Return the maximized sum.

 

Example 1:

Input: nums = [1,4,3,2]
Output: 4
Explanation: All possible pairings (ignoring the ordering of elements) are:
1. (1, 4), (2, 3) -> min(1, 4) + min(2, 3) = 1 + 2 = 3
2. (1, 3), (2, 4) -> min(1, 3) + min(2, 4) = 1 + 2 = 3
3. (1, 2), (3, 4) -> min(1, 2) + min(3, 4) = 1 + 3 = 4
So the maximum possible sum is 4.

Example 2:

Input: nums = [6,2,6,5,1,2]
Output: 9
Explanation: The optimal pairing is (2, 1), (2, 5), (6, 6). min(2, 1) + min(2, 5) + min(6, 6) = 1 + 2 + 6 = 9.

 

Constraints:

    1 <= n <= 10^4
    nums.length == 2 * n
    -10^4 <= nums[i] <= 10^4


*/

class Solution {
private:
    const static int K = 10000; //by the question constraint
public:
    int arrayPairSum(vector<int>& nums) {
        //using counting sort
        int countArr[2 * K + 1] = { 0 };
        for (int num : nums) {
            countArr[num + K] += 1;
        }

        int sum = 0;
        bool isEven = true;
        for (int i = 0; i <= 2 * K; ++i) {
            while (countArr[i]) {
                sum += (isEven ? i - K : 0);    //we add the value when it is even-indexed
                isEven = !isEven;   //flip it!!
                countArr[i] -= 1;
            }
        }

        return sum;

        //using sort
        /*
        std::sort(nums.begin(), nums.end());

        int sum = 0;
        for (int i = 0; i < nums.size(); i+=2) {
            sum += nums[i];
        }

        return sum;
        */
    }
};