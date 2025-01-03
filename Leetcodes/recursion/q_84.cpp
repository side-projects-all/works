/*

*/

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        //return recursive(heights, 0, heights.size() - 1);
        return iterative(heights);
    }

private:

    int iterative(std::vector<int>& heights) {
        std::stack<int> stk;
        stk.push(-1);

        int max_area = 0;
        for (size_t i = 0; i < heights.size(); ++i) {
            while (stk.top() != -1 && heights[stk.top()] >= heights[i]) {
                int curr_height = heights[stk.top()];
                stk.pop();
                int curr_width = i - stk.top() - 1;
                max_area = std::max(max_area, curr_height * curr_width);
            }

            stk.push(i);
        }

        while (stk.top() != -1) {
            int curr_height = heights[stk.top()];
            stk.pop();
            int curr_width = heights.size() - stk.top() - 1;
            max_area = std::max(max_area, curr_height * curr_width);
        }

        return max_area;
    }

    //recursive-way still exceeds time limit
    int recursive(std::vector<int>& heights, int start, int end) {
        if (start > end) {
            return 0;
        }

        int min = start;
        for (int i = start; i <= end; ++i) {
            if (heights[min] > heights[i]) {
                min = i;
            }
        }

        int max_area = heights[min] * (end - start + 1);
        int left_area = recursive(heights, start, min - 1);
        int right_area = recursive(heights, min + 1, end);

        return std::max({max_area, left_area, right_area});
    }
};