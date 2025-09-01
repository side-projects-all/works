/*
The set [1, 2, 3, ..., n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order, we get the following sequence for n = 3:

    "123"
    "132"
    "213"
    "231"
    "312"
    "321"

Given n and k, return the kth permutation sequence.

 

Example 1:

Input: n = 3, k = 3
Output: "213"

Example 2:

Input: n = 4, k = 9
Output: "2314"

Example 3:

Input: n = 3, k = 1
Output: "123"

 

Constraints:

    1 <= n <= 9
    1 <= k <= n!


*/

class Solution {
public:
    string getPermutation(int n, int k) {
        
        std::vector<int> factorials(n);
        std::vector<int> nums(n);
        nums[0] = 1;;
        factorials[0] = 1;

        for (int i = 1; i < n; ++i) {
            //factorials[i] means the i-factorial, ex: factorial[5] is 5!
            factorials[i] = factorials[i - 1] * i;  
            nums[i] = i + 1;
        }

        k -= 1; //k is 1 start, not 0 start, so we minus 1
        std::string ans;
        for (int i = n - 1; i >= 0; --i) {

            int index = k / factorials[i];  
            //k -= index * factorials[i];
            k %= factorials[i];

            ans.push_back(nums[index] + '0');
            nums.erase(nums.begin() + index);
        }

        return ans;
        
    }
};