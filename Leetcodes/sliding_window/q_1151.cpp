/*
Given a binary array data, return the minimum number of swaps required to group all 1’s present in the array together in any place in the array.

 

Example 1:

Input: data = [1,0,1,0,1]
Output: 1
Explanation: There are 3 ways to group all 1's together:
[1,1,1,0,0] using 1 swap.
[0,1,1,1,0] using 2 swaps.
[0,0,1,1,1] using 1 swap.
The minimum is 1.

Example 2:

Input: data = [0,0,0,1,0]
Output: 0
Explanation: Since there is only one 1 in the array, no swaps are needed.

Example 3:

Input: data = [1,0,1,0,1,0,0,1,1,0,1]
Output: 3
Explanation: One possible solution that uses 3 swaps is [0,0,0,0,0,1,1,1,1,1,1].

 

Constraints:

    1 <= data.length <= 10^5
    data[i] is either 0 or 1.


*/

class Solution {
private:
    int by_sliding_window(vector<int>& data) {
        int n = data.size();
        int ones = 0;
        for (int i = 0; i < n; ++i) {
            ones += data[i];
        }

        int min_zeros = 0;
        for (int i = 0; i < ones; ++i) {
            if (data[i] == 0) {
                ++min_zeros;
            }
        }

        int curr_zeros = min_zeros;
        for (int b = 1, e = ones + b - 1; e < n; ++e, ++b) {

            if (data[b - 1] == 0) {
                curr_zeros -= 1;
            }

            if (data[e] == 0) {
                curr_zeros += 1;
            }
            
            min_zeros = std::min(min_zeros, curr_zeros);
        }

        return min_zeros;
    }
public:
    int minSwaps(vector<int>& data) {
        return by_sliding_window(data);
    }
};