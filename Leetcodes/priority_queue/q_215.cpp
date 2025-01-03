/*
Given an integer array nums and an integer k, return the kth largest element in the array.

Note that it is the kth largest element in the sorted order, not the kth distinct element.

Can you solve it without sorting?

 

Example 1:

Input: nums = [3,2,1,5,6,4], k = 2
Output: 5

Example 2:

Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4

 

Constraints:

    1 <= k <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4


*/

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {

        //using c++ priority_queue to do kth target
        //c++ priority_queue default is max priority queue, 
        //so we need to multiply each value with -1
        /*
        std::priority_queue<int> heap;

        for (int num : nums) {
            
            if (heap.size() < k) {
                heap.push(-num);
            } else {
                
                //we do not push in those value that are larger in negative
                if (-num > heap.top()) {
                    continue;
                } 
                
                heap.pop();
                heap.push(-num);
            }
        }
        
        return -heap.top();
        */

        //or we could use comparator std::greater to create min heap
        std::priority_queue<int, std::vector<int>, std::greater<int>> heap;
        for (int num : nums) {
            if (heap.size() < k) {
                heap.push(num);
            } else {
                if (num > heap.top()) {
                    heap.pop();
                    heap.push(num);
                }
            }
        }

        return heap.top();
        /*
        for (int num : nums) {
            heap.push(-num);

            if (heap.size() > k) {
                heap.pop();
            }
        }
        */

    }
};