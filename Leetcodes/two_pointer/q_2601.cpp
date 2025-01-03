/*
You are given a 0-indexed integer array nums of length n.

You can perform the following operation as many times as you want:

    Pick an index i that you haven’t picked before, and pick a prime p strictly less than nums[i], then subtract p from nums[i].

Return true if you can make nums a strictly increasing array using the above operation and false otherwise.

A strictly increasing array is an array whose each element is strictly greater than its preceding element.

 

Example 1:

Input: nums = [4,9,6,10]
Output: true
Explanation: In the first operation: Pick i = 0 and p = 3, and then subtract 3 from nums[0], so that nums becomes [1,9,6,10].
In the second operation: i = 1, p = 7, subtract 7 from nums[1], so nums becomes equal to [1,2,6,10].
After the second operation, nums is sorted in strictly increasing order, so the answer is true.

Example 2:

Input: nums = [6,8,11,12]
Output: true
Explanation: Initially nums is sorted in strictly increasing order, so we don't need to make any operations.

Example 3:

Input: nums = [5,8,3]
Output: false
Explanation: It can be proven that there is no way to perform operations to make nums sorted in strictly increasing order, so the answer is false.

 

Constraints:

    1 <= nums.length <= 1000
    1 <= nums[i] <= 1000
    nums.length == n


*/

class Solution {
public:
    bool primeSubOperation(vector<int>& nums) {
        int max_num = *std::max_element(nums.begin(), nums.end());

        //Sieve of Eratosthenes to calculate primes array.
        std::vector<bool> sieve(max_num + 1, true);
        sieve[0] = false;
        sieve[1] = false;
        for (int i = 2; i * i <= max_num ; ++i) {

            if (sieve[i]) {
                for (int j = i * i; j <= max_num; j += i) {
                    sieve[j] = false;
                }
            }
        }

        int curr = 1;   //using curr to infer the prime, the curr means nums[i] - a possible prime
        int i = 0;
        while (i < nums.size()) {
            //the diff needed to make nums[i] equal to curr.
            int diff = nums[i] - curr;

            //if diff were less than 0, it means nums[i] is already less than curr, 
            //then we could not have strictly increasing array
            if (diff < 0) {
                return 0;
            }

            //if the diff is prime or zero, then nums[i] can be made equal to curr.
            if (sieve[diff] == true || diff == 0) {
                ++i;

                //increaing curr gradually, and when curr increased, the possible prime is smaller, 
                //then we could have larger val after nums[i] - prime
                ++curr; 
            } else {

                ++curr; //try next curr
            }
        }
        return 1;
    }
};