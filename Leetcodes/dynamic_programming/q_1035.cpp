/*
You are given two integer arrays nums1 and nums2. We write the integers of nums1 and nums2 (in the order they are given) on two separate horizontal lines.

We may draw connecting lines: a straight line connecting two numbers nums1[i] and nums2[j] such that:

    nums1[i] == nums2[j], and
    the line we draw does not intersect any other connecting (non-horizontal) line.

Note that a connecting line cannot intersect even at the endpoints (i.e., each number can only belong to one connecting line).

Return the maximum number of connecting lines we can draw in this way.

 

Example 1:

Input: nums1 = [1,4,2], nums2 = [1,2,4]
Output: 2
Explanation: We can draw 2 uncrossed lines as in the diagram.
We cannot draw 3 uncrossed lines, because the line from nums1[1] = 4 to nums2[2] = 4 will intersect the line from nums1[2]=2 to nums2[1]=2.

Example 2:

Input: nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
Output: 3

Example 3:

Input: nums1 = [1,3,7,1,7,5], nums2 = [1,9,2,5,1]
Output: 2

 

Constraints:

    1 <= nums1.length, nums2.length <= 500
    1 <= nums1[i], nums2[j] <= 2000


*/

class Solution {
private:
    int iterative(vector<int>& nums1, vector<int>& nums2) {
        int s1 = nums1.size();
        int s2 = nums2.size();
        std::vector<std::vector<int>> mem(s1 + 1, std::vector<int>(s2 + 1, 0));

        for (int n1 = s1 - 1; n1 > -1; --n1) {
            for (int n2 = s2 - 1; n2 > -1; --n2) {
                
                if (nums1[n1] == nums2[n2]) {
                    mem[n1][n2] = 1 + mem[n1 + 1][n2 + 1];
                } else {
                    mem[n1][n2] = std::max(mem[n1][n2 + 1], mem[n1 + 1][n2]);
                }
            }

        }

        return mem[0][0];
    }

    int recursive(vector<int>& nums1, vector<int>& nums2, int n1, int n2, 
                    std::vector<std::vector<int>>& mem) {

            if (n1 == nums1.size() || n2 == nums2.size()) {
                return 0;
            }

            if (mem[n1][n2] != -1) {
                return mem[n1][n2];
            }

            int len = 0;
            if (nums1[n1] == nums2[n2]) {
                len = 1 + recursive(nums1, nums2, n1 + 1, n2 + 1, mem);
            } else {
                len = std::max(recursive(nums1, nums2, n1 + 1, n2, mem), 
                                recursive(nums1, nums2, n1, n2 + 1, mem));
            }

            mem[n1][n2] = len;
            
            return mem[n1][n2];
        }
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        //std::vector<std::vector<int>> mem(nums1.size(), std::vector<int>(nums2.size(), -1));

        //return recursive(nums1, nums2, 0, 0, mem);
        return iterative(nums1, nums2);
    }
};