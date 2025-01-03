/*

*/

class Solution {
private:
    int bySort(vector<int>& nums) {
        //corner case
        if (nums.size() == 1) {
            return nums[0];
        }

        std::sort(nums.begin(), nums.end());

        for (int i = nums.size() - 1; i > -1; --i) {
            if (i == 0 || nums[i] != nums[i - 1]) {
                return nums[i];
            }

            while (i > 0 && nums[i] == nums[i - 1]) {
                --i;
            }
        }

        return -1;
    }

    int naiveMap(vector<int>& nums) {
        int max = -1;

        std::unordered_map<int, int> m;

        for (int n : nums) {
            m[n] += 1;
        }

        for (auto& p : m) {
            if (p.second == 1 && p.first > max) {
                max = p.first;
            }
        }

        return max;
    }

public:
    int largestUniqueNumber(vector<int>& nums) {

        //Time complexity of both ways are close!
        return naiveMap(nums);

        //return bySort(nums);
    }
};