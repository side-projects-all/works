/*
You are given a 0-indexed array of strings nums, where each string is of equal length and consists of only digits.

You are also given a 0-indexed 2D integer array queries where queries[i] = [ki, trimi]. For each queries[i], you need to:

    Trim each number in nums to its rightmost trimi digits.
    Determine the index of the kith smallest trimmed number in nums. If two trimmed numbers are equal, the number with the lower index is considered to be smaller.
    Reset each number in nums to its original length.

Return an array answer of the same length as queries, where answer[i] is the answer to the ith query.

Note:

    To trim to the rightmost x digits means to keep removing the leftmost digit, until only x digits remain.
    Strings in nums may contain leading zeros.

 

Example 1:

Input: nums = ["102","473","251","814"], queries = [[1,1],[2,3],[4,2],[1,2]]
Output: [2,2,1,0]
Explanation:
1. After trimming to the last digit, nums = ["2","3","1","4"]. The smallest number is 1 at index 2.
2. Trimmed to the last 3 digits, nums is unchanged. The 2nd smallest number is 251 at index 2.
3. Trimmed to the last 2 digits, nums = ["02","73","51","14"]. The 4th smallest number is 73.
4. Trimmed to the last 2 digits, the smallest number is 2 at index 0.
   Note that the trimmed number "02" is evaluated as 2.

Example 2:

Input: nums = ["24","37","96","04"], queries = [[2,1],[2,2]]
Output: [3,0]
Explanation:
1. Trimmed to the last digit, nums = ["4","7","6","4"]. The 2nd smallest number is 4 at index 3.
   There are two occurrences of 4, but the one at index 0 is considered smaller than the one at index 3.
2. Trimmed to the last 2 digits, nums is unchanged. The 2nd smallest number is 24.

 

Constraints:

    1 <= nums.length <= 100
    1 <= nums[i].length <= 100
    nums[i] consists of only digits.
    All nums[i].length are equal.
    1 <= queries.length <= 100
    queries[i].length == 2
    1 <= ki <= nums.length
    1 <= trimi <= nums[i].length

*/

class Solution {
private:
    inline int toInt(const std::string& str, const int radix) {
        return str[str.size() - radix] - '0';
    }

public:
    vector<int> smallestTrimmedNumbers(vector<string>& nums, vector<vector<int>>& queries) {
        int m = nums.size();
        int n = nums[0].size();
        std::vector<std::vector<int>> sorted_by_radix(n + 1, std::vector<int>(m, 0));

        std::iota(sorted_by_radix[0].begin(), sorted_by_radix[0].end(), 0);

        // radix sort 
        //the hole for loop is representing the sorting by the radix
        //the 2-dimension array above is used to repsent the process of every radix sorting
        std::vector<int> counts(10);
        for (int radix = 1; radix < n + 1; ++radix) {

            // counting sort for specific radix
            // e.g 254, size = 3, radix = 1, then we retrieve str[3 - 1], the last digit
            std::fill(counts.begin(), counts.end(), 0);
            for (int i = 0; i < m; ++i) {
                ++counts[toInt(nums[i], radix)];
            }

            //for calculating the position of every num in new array
            int index = 0;
            for (auto& count : counts) {
                std::swap(count, index);
                index += count;
            }

            for (int i = 0; i < m; ++i) {
                auto prev_index = sorted_by_radix[radix - 1][i];
                auto num = toInt(nums[prev_index], radix);
                sorted_by_radix[radix][counts[num]] = prev_index;

                //for example, using ["102","473","251","814"])
                //for representing the sequence of every num from 1 to 4 
                //e.g. counts:{0, 0, 1, 2, 3, 4, 4, 4, 4, 4} became {0, 1, 2, 3, 4, 4, 4, 4, 4, 4}
                ++counts[num];  
            }
        }

        std::vector<int> res(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            auto k = queries[i][0];
            auto radix = queries[i][1];
            res[i] = sorted_by_radix[radix][k - 1];
        }

        return res;
    }
};