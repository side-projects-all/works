/*
You are given an integer array nums. You want to maximize the number of points you get by performing the following operation any number of times:

Pick any nums[i] and delete it to earn nums[i] points. Afterwards, you must delete every element equal to nums[i] - 1 and every element equal to nums[i] + 1.

Return the maximum number of points you can earn by applying the above operation some number of times.

ex1:
Input: nums = [3,4,2]
Output: 6
Explanation: You can perform the following operations:
- Delete 4 to earn 4 points. Consequently, 3 is also deleted. nums = [2].
- Delete 2 to earn 2 points. nums = [].
You earn a total of 6 points.

ex2:
Input: nums = [2,2,3,3,3,4]
Output: 9
Explanation: You can perform the following operations:
- Delete a 3 to earn 3 points. All 2's and 4's are also deleted. nums = [3,3].
- Delete a 3 again to earn 3 points. nums = [3].
- Delete a 3 once more to earn 3 points. nums = [].
You earn a total of 9 points.
*/

class Solution {
private:
    int iterative4(vector<int>& nums) {
        std::unordered_map<int, int> points;
        for (int i = 0; i < nums.size(); ++i) {
            points[nums[i]] += nums[i];
        }

        int n = points.size();
        std::vector<int> keys(n);
        int k = 0;
        for (const auto& p : points) {
            keys[k] = p.first;
            ++k;
        }

        std::sort(keys.begin(), keys.end());

        //for better understanding, we use this dp array
        //it means how many nums we have
        /*
        std::vector<int> dp(n + 1); 
        dp[1] = points[keys[0]];
        */
        int max_earn = points[keys[0]];
        int prev_2 = 0;
        int prev_1 = points[keys[0]];

        for (int i = 2; i < n + 1; ++i) {

            /*
            if (keys[i - 1] == keys[i - 2] + 1) {
                dp[i] = std::max(dp[i - 1], dp[i - 2] + points[keys[i - 1]]);
            } else {
                dp[i] = dp[i - 1] + points[keys[i - 1]];
            }
            */
            if (keys[i - 1] == keys[i - 2] + 1) {
                max_earn = std::max(prev_1, prev_2 + points[keys[i - 1]]);

            } else {
                max_earn = prev_1 + points[keys[i - 1]];
            }

            prev_2 = prev_1;
            prev_1 = max_earn;
        }

        //return dp[n];
        return max_earn;
    }
    int iterative3_better(std::unordered_map<int, int>& points) {
        std::vector<int> keys;

        for (std::pair<int, int> p : points) {
            keys.push_back(p.first);
        }

        std::sort(keys.begin(), keys.end());

        int twoPrev = 0;
        int onePrev = points[keys[0]];
        
        for (int i = 1; i < keys.size(); ++i) {
            int tmp = onePrev;
            int curr = keys[i];

            if (curr == keys[i - 1] + 1) {
                onePrev = std::max(onePrev, twoPrev + points[curr]);
            } else {
                onePrev += points[curr];
            }
            
            twoPrev = tmp;
        }

        return onePrev;
    }

    int iterative2(std::vector<int>& nums, int maxVal, std::unordered_map<int, int>& points) {
        
        int twoPrev = 0;
        int onePrev = (points.find(1) == points.end()) ? 0 : points[1];
        
        for (int num = 2; num <= maxVal; ++num) {
            int tmp = onePrev;
            int gain = (points.find(num) == points.end()) ? 0 : points[num];

            onePrev = std::max(onePrev, twoPrev + gain);
            twoPrev = tmp;
        }

        return onePrev;
    }

    int iterative(std::vector<int>& nums, int maxVal, std::unordered_map<int, int>& points) {
        std::vector<int> maxPoints(maxVal + 1, 0);
        maxPoints[1] = (points.find(1) == points.end()) ? 0 : points[1];

        for (int num = 2; num < maxPoints.size(); ++num) {
            int gain = (points.find(num) == points.end()) ? 0 : points[num];
            maxPoints[num] = std::max(maxPoints[num - 1],  maxPoints[num - 2] + gain);
        }

        return maxPoints[maxVal];
    }

    int recursive(int num, std::unordered_map<int, int>& points, std::unordered_map<int, int>& mem) {
        if (num <= 0) {
            return 0;
        }
        if (num == 1) {
            return (points.find(num) == points.end()) ? 0 : points[num];
        }

        if (mem.find(num) != mem.end()) {
            return mem[num];
        }

        int gain = (points.find(num) == points.end()) ? 0 : points[num];
        int max = std::max(recursive(num - 1, points, mem), recursive(num - 2, points, mem) + gain);
        mem[num] = max;

        return max;
    }

public:
    int deleteAndEarn(vector<int>& nums) {
        
        std::unordered_map<int, int> points;
        std::unordered_map<int, int> mem;

        int max = 0;
        for (int num : nums) {

            if (points.find(num) == points.end()) {
                points[num] = num;
            } else {
                points[num] += num;
            }

            max = std::max(max, num);
        }

        //return recursive(max, points, mem);
        //return iterative(nums, max, points);
        //return iterative2(nums, max, points);
        return iterative3_better(points);

    }
};