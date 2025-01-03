/*
Given an array of non-negative integers arr, you are initially positioned at start index of the array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach any index with value 0.

Notice that you can not jump outside of the array at any time.

 

Example 1:

Input: arr = [4,2,3,0,3,1,2], start = 5
Output: true
Explanation: 
All possible ways to reach at index 3 with value 0 are: 
index 5 -> index 4 -> index 1 -> index 3 
index 5 -> index 6 -> index 4 -> index 1 -> index 3 

Example 2:

Input: arr = [4,2,3,0,3,1,2], start = 0
Output: true 
Explanation: 
One possible way to reach at index 3 with value 0 is: 
index 0 -> index 4 -> index 1 -> index 3

Example 3:

Input: arr = [3,0,2,1,2], start = 2
Output: false
Explanation: There is no way to reach at index 1 with value 0.

 

Constraints:

    1 <= arr.length <= 5 * 10^4
    0 <= arr[i] < arr.length
    0 <= start < arr.length


*/

class Solution {
private:
    bool bfs(vector<int>& arr, int start) {
        std::queue<int> q;
        q.push(start);

        while (!q.empty()) {
            int index = q.front();
            q.pop();

            if (arr[index] == 0) {
                return true;
            }

            if (arr[index] < 0) {
                continue;
            }

            if (index - arr[index] >= 0) {
                q.push(index - arr[index]);
            }

            if (index + arr[index] < arr.size()) {
                q.push(index + arr[index]);
            }

            arr[index] = -arr[index];
        }

        return false;
    }

    bool dfs(vector<int>& arr, int start) {
        if (start < 0 || start >= arr.size() || arr[start] < 0) {
            return false;
        }

        if (arr[start] == 0) {
            return true;
        }

        arr[start] = -arr[start];

        return dfs(arr, start - arr[start]) || dfs(arr, start + arr[start]);
    }
public:
    bool canReach(vector<int>& arr, int start) {
        //return dfs(arr, start);
        return bfs(arr, start);
    }
};