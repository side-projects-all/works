/*
Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

 

Example 1:

Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.

Example 2:

Input: heights = [2,4]
Output: 4

 

Constraints:

    1 <= heights.length <= 10^5
    0 <= heights[i] <= 10^4




*/

class Solution {
private:
    int by_stack(vector<int>& heights) {
        int n = heights.size();
        if (n == 1) {
            return heights[0];
        }

        std::stack<int> stack;
        stack.push(-1);
        int max_area = 0;
        for (int i = 0; i < n; ++i) {

            while (stack.top() != -1 && heights[stack.top()] >= heights[i]) {
                int h = heights[stack.top()];
                stack.pop();

                int w = i - stack.top() - 1;
                max_area = std::max(max_area, w * h);
            }

            stack.push(i);
        }

         while (stack.top() != -1) {
            int h = heights[stack.top()];
            stack.pop();

            int w = n - stack.top() - 1;
            max_area = std::max(max_area, w * h);
        }
        return max_area;
    }
public:
    int largestRectangleArea(vector<int>& heights) {
        return by_stack(heights);
    }
};