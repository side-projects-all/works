/*
Given a list of non-negative integers nums, arrange them such that they form the largest number and return it.

Since the result may be very large, so you need to return a string instead of an integer.

 

Example 1:

Input: nums = [10,2]
Output: "210"

Example 2:

Input: nums = [3,30,34,5,9]
Output: "9534330"

 

Constraints:

    1 <= nums.length <= 100
    0 <= nums[i] <= 10^9


*/

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        if (nums.size() == 1) {
            return std::to_string(nums[0]);
        }

        std::vector<std::string> str_nums(nums.size());
        for (int i = 0; i < nums.size(); ++i) {
            str_nums[i] = std::to_string(nums[i]);
        }

        std::sort(str_nums.begin(), str_nums.end(), [](std::string& s1, std::string& s2) {
            return s1 + s2 > s2 + s1;
        });

        if (str_nums[0] == "0") {
            return "0";
        }
        
        std::string ans;
        for (int i = 0; i < str_nums.size(); ++i) {
            ans += str_nums[i];
        }

        return ans;
    }
};