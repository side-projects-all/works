#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

class Solution {
private:
    int by_binary_search(std::vector<int>& nums) {
        int n = nums.size();
        int b = 0;
        int e = n - 1;

        //find negative end
        while (b <= e) {
            int mid = b + (e - b) / 2;

            if (nums[mid] >= 0) {
                e = mid - 1;
            } else {
                
                b = mid + 1;
            }
        }

        int neg = b;
        
        e = n - 1;
        while (b <= e) {
            int mid = b + (e - b) / 2;

            if (nums[mid] > 0) {
                e = mid - 1;
            } else {
                
                b = mid + 1;
            }
        }

        int pos = n - b;

        return pos > neg ? pos : neg;
    }
public:
    Solution() {}
    ~Solution() {}

    int maximumCount(std::vector<int>& nums) {
        return by_binary_search(nums);
    }
};