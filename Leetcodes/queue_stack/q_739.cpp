/*
Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.

 

Example 1:

Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]

Example 2:

Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]

Example 3:

Input: temperatures = [30,60,90]
Output: [1,1,0]

 

Constraints:

    1 <= temperatures.length <= 10^5
    30 <= temperatures[i] <= 100


*/


class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int len = temperatures.size();
        std::vector<int> output(len, 0);
        std::vector<int> stack;
        
        int current = 0;
        int prevDay = 0;
        for (int i = 0; i < len; ++i) {
            current = temperatures[i];
            
            while(!stack.empty() && temperatures[stack.back()] < current) {
                prevDay = stack.back();
                stack.pop_back();
                output[prevDay] = i - prevDay;
            }
            
            stack.push_back(i);
        }
        
        return output;
    }
};