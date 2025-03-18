/*

*/

class Solution {
public:
    bool divideArray(vector<int>& nums) {
        int n = nums.size();
        std::vector<int> cnts(501);

        for (int i = 0; i < n; ++i) {
            ++cnts[nums[i]];
        }

        for (int i = 0; i < cnts.size(); ++i) {
            if (cnts[i] != 0 && cnts[i] % 2) {
                return false;
            }
        }

        return true;
    }
};