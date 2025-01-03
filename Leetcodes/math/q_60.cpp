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
        //because the permutation require an ascending order, 
        //the number of permutation sequence is from 0 to (n! - 1), 
        //and those numbers could be mapped by Factorial Number System Representation
        //for example, n = 3, it means 3! = 3 * 2 * 1 = 6, 
        //then the permutation number sequence is from 0 to 5, 
        //and using actorial Number System Representation, 
        //we will have 000, 010, 100, 110, 200, 210 to represent 0 to 5

        //the question provides us n for n! but requires k-th permutation, 
        //so all we need to do is k - 1 Factorial Number System Representation, 
        //and then we reverse it back to decimal number!!

        //important idea!!
        //The coefficients in factorial representation are indexes of elements in the input array. 
        //These are not direct indexes, but the indexes after the removal of already used elements. 
        //That's a consequence of the fact that each element should be used in permutation only once.
        std::vector<int> factorials(n);
        std::vector<int> nums(n);
        nums[0] = 1;;
        factorials[0] = 1;

        for (int i = 1; i < n; ++i) {
            //factorials[i] means the i-factorial, ex: factorial[5] is 5!
            factorials[i] = factorials[i - 1] * i;  
            nums[i] = i + 1;
        }

        k -= 1;
        std::string ans;
        for (int i = n - 1; i > -1; --i) {
            //why we use division here?
            //because we eliminate larger part of factorial representation to 
            //get the index in after the removal of already used elements!!
            //in other words, we continues to delete the largest part of factorial representation
            int index = k / factorials[i];  
            k -= index * factorials[i];

            ans += std::to_string(nums[index]);
            nums.erase(nums.begin() + index);
        }

        return ans;
    }
};