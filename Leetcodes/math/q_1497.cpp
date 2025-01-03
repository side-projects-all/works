/*
Given an array of integers arr of even length n and an integer k.

We want to divide the array into exactly n / 2 pairs such that the sum of each pair is divisible by k.

Return true If you can find a way to do that or false otherwise.

 

Example 1:

Input: arr = [1,2,3,4,5,10,6,7,8,9], k = 5
Output: true
Explanation: Pairs are (1,9),(2,8),(3,7),(4,6) and (5,10).

Example 2:

Input: arr = [1,2,3,4,5,6], k = 7
Output: true
Explanation: Pairs are (1,6),(2,5) and(3,4).

Example 3:

Input: arr = [1,2,3,4,5,6], k = 10
Output: false
Explanation: You can try all possible pairs to see that there is no way to divide arr into 3 pairs each with sum divisible by 10.

 

Constraints:

    arr.length == n
    1 <= n <= 10^5
    n is even.
    -10^9 <= arr[i] <= 10^9
    1 <= k <= 10^5


*/

class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {

        //return by_map(arr, k);
        return by_vec(arr, k);
    }
private:
    bool by_vec(vector<int>& arr, int k) {
        std::vector<int> freq(k);

        for (int v : arr) {
            ++freq[(v % k + k) % k];
        }

        if (freq[0] % 2 != 0) {
            return false;
        }

        for (int i = 1; i <= k / 2; ++i) {
            if (freq[i] != freq[k - i]) {
                return false;
            }
        }

        return true;
    }
    bool by_map(vector<int>& arr, int k) {
        std::unordered_map<int, int> m;
        int n = arr.size();

        for (int i = 0; i < n; ++i) {
            ++m[(arr[i] % k + k) % k];
        }

        for (int i = 0; i < n; ++i) {
            int r = (arr[i] % k + k) % k;

            if (r == 0) {
                if (m[r] % 2 == 1) {
                    return false;
                }
            } else if (m[r] != m[k - r]) {
                return false;
            }
        }

        return true;
    }
};