/*
Given two integer arrays nums1 and nums2, return the maximum length of a subarray that appears in both arrays.

 

Example 1:

Input: nums1 = [1,2,3,2,1], nums2 = [3,2,1,4,7]
Output: 3
Explanation: The repeated subarray with maximum length is [3,2,1].

Example 2:

Input: nums1 = [0,0,0,0,0], nums2 = [0,0,0,0,0]
Output: 5

 

Constraints:

    1 <= nums1.length, nums2.length <= 1000
    0 <= nums1[i], nums2[i] <= 100


*/

class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        p_nums1 = nums1;
        p_nums2 = nums2;
        len01 = nums1.size();
        len02 = nums2.size();
        memo = std::vector<std::vector<int>>(len01, std::vector<int>(len02, -1));
        
        /*
        int max  = std::numeric_limits<int>::min();
        for (int i = 0; i < len01; ++i) {
            for (int k = 0; k < len02; ++k) {
                max = std::max(max, topDown(i, k));
            }
        }
        
        return max;
        */
        
        return buttomUp();
    }
private:
    std::vector<int> p_nums1;
    std::vector<int> p_nums2;
    int len01;
    int len02;
    std::vector<std::vector<int>> memo;
    
    int topDown(int n1Index, int n2Index) {
        if (n1Index == len01 || n2Index == len02) {
            return 0;
        }
        
        if (memo[n1Index][n2Index] != -1) {
            return memo[n1Index][n2Index];
        }
        
        if (p_nums1[n1Index] == p_nums2[n2Index]) {
            memo[n1Index][n2Index] = 1 + topDown(n1Index + 1, n2Index + 1);
        }  else {
            memo[n1Index][n2Index] = 0;
        }
        
        return memo[n1Index][n2Index];
    }
    
    int buttomUp() {
        int t[len01 + 1][len02 + 1];
        int maxL = 0;
        for(int i = 0; i <= len01; ++i) {
            for(int j = 0; j <= len02; ++j) {
                if(i == 0 || j == 0) {
                    t[i][j] = 0;
                } else {
                    if(p_nums1[i - 1] == p_nums2[j - 1]) {
                        t[i][j] = 1 + t[i - 1][j - 1];
                        maxL = std::max(maxL, t[i][j]);
                    } else {
                        t[i][j] = 0;
                    }
                }
            }
        }
        return maxL;
    }
};