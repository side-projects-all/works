/*
Given two integer arrays arr1 and arr2, return the minimum number of operations (possibly zero) needed to make arr1 strictly increasing.

In one operation, you can choose two indices 0 <= i < arr1.length and 0 <= j < arr2.length and do the assignment arr1[i] = arr2[j].

If there is no way to make arr1 strictly increasing, return -1.

 

Example 1:

Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
Output: 1
Explanation: Replace 5 with 2, then arr1 = [1, 2, 3, 6, 7].

Example 2:

Input: arr1 = [1,5,3,6,7], arr2 = [4,3,1]
Output: 2
Explanation: Replace 5 with 3 and then replace 3 with 4. arr1 = [1, 3, 4, 6, 7].

Example 3:

Input: arr1 = [1,5,3,6,7], arr2 = [1,6,3,3]
Output: -1
Explanation: You can't make arr1 strictly increasing.

 

Constraints:

    1 <= arr1.length, arr2.length <= 2000
    0 <= arr1[i], arr2[i] <= 10^9

*/

class Solution {
private:
    struct my_hash {
        std::size_t operator()(const std::pair<int, int>& p) const noexcept {
            std::size_t h1 = std::hash<int>{}(p.first);
            std::size_t h2 = std::hash<int>{}(p.second);
            return h1 ^ (h2 << 1); // or use boost::hash_combine
        }
    };
    int recursive(vector<int>& arr1, vector<int>& arr2) {
        std::sort(arr2.begin(), arr2.end());
        int N1 = arr1.size();
        int N2 = arr2.size();
        std::unordered_map<std::pair<int, int>, int, my_hash> mem;

        std::function<int(int, int)> recurr = [&](int i, int pre) -> int {
            if (i == N1) {
                return 0;
            }

            if (mem.find({i, pre}) != mem.end()) {
                return mem[{i, pre}];
            }

            int nums = 2001;
            if (arr1[i] > pre) {
                nums = recurr(i + 1, arr1[i]);
            }

            int target = pre;
            int left = 0;
            int right = N2;
            while (left < right) {
                int mid = left + (right - left) / 2;

                if (arr2[mid] <= target) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }

            int next_i = left;
            if (next_i < N2) {
                nums = std::min(nums, 1 + recurr(i + 1, arr2[next_i]));
            }

            return mem[{i, pre}] = nums;
        };

        int ans = recurr(0, -1);

        return ans < 2001 ? ans : -1;
    }
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        return recursive(arr1, arr2);
    }
};