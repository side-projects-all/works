/*
Given a sorted integer array nums and three integers a, b and c, apply a quadratic function of the form f(x) = ax2 + bx + c to each element nums[i] in the array, and return the array in a sorted order.

 

Example 1:

Input: nums = [-4,-2,2,4], a = 1, b = 3, c = 5
Output: [3,9,15,33]

Example 2:

Input: nums = [-4,-2,2,4], a = -1, b = 3, c = 5
Output: [-23,-5,1,7]

 

Constraints:

    1 <= nums.length <= 200
    -100 <= nums[i], a, b, c <= 100
    nums is sorted in ascending order.

*/

class Solution {
private:
    int transform(int& val, int& a, int& b, int& c) {
        if (a == 0) {
            return b * val + c;
        }

        return a * val * val + b * val + c;
    }
public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        int n = nums.size();
        if (n == 1) {
            nums[0] = transform(nums[0], a, b, c);
            return nums;
        }

        std::vector<int> ans(n);
        int s = 0;
        int e = n - 1;

        if (a < 0) {
            
            int i = 0;

            while (s <= e) {
                int left = transform(nums[s], a, b, c);
                int right = transform(nums[e], a, b, c);

                if (left < right) {
                    ans[i] = left;
                    ++s;
                    
                } else {
                    ans[i] = right;
                    --e;
                }

                ++i;
            }

        } else {

            int i = n - 1;

            while (s <= e) {
                int left = transform(nums[s], a, b, c);
                int right = transform(nums[e], a, b, c);

                if (left > right) {
                    ans[i] = left;
                    ++s;
                    
                } else {
                    ans[i] = right;
                    --e;
                }

                --i;
            }
        }

        return ans;
    }
};