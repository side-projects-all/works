/*
Given an integer array nums, return the length of the longest strictly increasing
subsequence
.

 

Example 1:

Input: nums = [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.

Example 2:

Input: nums = [0,1,0,3,2,3]
Output: 4

Example 3:

Input: nums = [7,7,7,7,7,7,7]
Output: 1

 

Constraints:

    1 <= nums.length <= 2500
    -10^4 <= nums[i] <= 10^4

*/

class Solution {
private:
    int iterative3(vector<int>& nums) {

        int n = nums.size();
        if (n == 1) {
            return 1;
        }

        std::vector<int> sub;
        sub.push_back(nums[0]);

        for (int i = 1; i < n; ++i) {

            int j = std::lower_bound(sub.begin(), sub.end(), nums[i]) - sub.begin();

            if (j == sub.size()) {
                sub.push_back(nums[i]);
            } else {
                sub[j] = nums[i];
            }
            /*
            if (nums[i] > sub.back()) {
                sub.push_back(nums[i]);

            } else {

                int j = std::lower_bound(sub.begin(), sub.end(), nums[i]) - sub.begin();
                sub[j] = nums[i]; 
            }
            */
        }

        return sub.size();

        //this is greedy and binary search
        /*
        int N = nums.size();

        std::vector<int> sub;
        sub.push_back(nums[0]);

        for (int i = 1; i < N; ++i) {
            if (nums[i] > sub[sub.size() - 1]) {
                sub.push_back(nums[i]);
            } else {
                int target = nums[i];
                int left = 0;
                int right = sub.size() - 1;

                while (left < right) {
                    int mid = left + (right - left) / 2;

                    if (sub[mid] < target) {
                        left = mid + 1;
                    } else {
                        right = mid;
                    }
                }

                sub[left] = nums[i];
            }
        }

        return sub.size();
        */
        
        /*
        std::vector<int> sub_seq;
        sub_seq.push_back(nums[0]);

        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] > sub_seq.back()) {
                sub_seq.push_back(nums[i]);

            } else {
                int j = std::lower_bound(sub_seq.begin(), sub_seq.end(), nums[i]) - sub_seq.begin();

                if (j < 0) {
                    sub_seq[0] = nums[i];

                } else {
                    sub_seq[j] = nums[i];
                }
                
            }
        }

        return sub_seq.size();
        */
    }
    int iterative2(vector<int>& nums) {

        //this is greedy 
        int N = nums.size();

        std::vector<int> sub;
        sub.push_back(nums[0]);

        for (int i = 1; i < N; ++i) {
            if (nums[i] > sub[sub.size() - 1]) {
                sub.push_back(nums[i]);
            } else {
                int pos = 0;

                while (nums[i] > sub[pos]) {
                    ++pos;
                }

                sub[pos] = nums[i];
            }
        }

        return sub.size();
    }
    int iterative(vector<int>& nums) {
        int N = nums.size();

        std::vector<int> mem(N, 1);
        int maxLen = 0;
        for (int i = 1; i < N; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    mem[i] = std::max(mem[i], mem[j] + 1);
                }
            }

            maxLen = std::max(maxLen, mem[i]);
        }

        return maxLen;
    }

    int recursive(vector<int>& nums) {
        int N = nums.size();

        std::vector<int> mem(N, -1);

        std::function<int(int)> recurr = [&](int i) -> int {

            if (mem[i] != -1) {
                return mem[i];
            }

            mem[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    mem[i] = std::max(mem[i], 1 + recurr(j));
                }
            }

            return mem[i];
        };

        int max = 1;
        for (int k = 0; k < N; ++k) {
            max = std::max(max, recurr(k));
        }

        return max;
        /*
        std::vector<std::vector<int>> mem(N, std::vector<int>(N, -1));

        std::function<int(int, int)> recurr = [&](int pre, int curr) -> int {
            //base case
            if (curr == N) {
                return 0;
            }

            if (mem[pre + 1][curr] != -1) {
                return mem[pre + 1][curr];
            }

            int notUse = 0;
            int use = 0;

            //not use current val (including case : pre == -1)
            notUse = recurr(pre, curr + 1);

            //use current val (including case : pre == -1)
            if (pre == -1 || nums[pre] < nums[curr]) {
                use = 1 + recurr(curr, curr + 1);
            }

            return mem[pre + 1][curr] = std::max(use, notUse);
        };

        return recurr(-1, 0);
        */
    }
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() == 1) {
            return 1;
        }

        //return recursive(nums);
        //return iterative(nums);
        //return iterative2(nums);
        return iterative3(nums);
    }
};