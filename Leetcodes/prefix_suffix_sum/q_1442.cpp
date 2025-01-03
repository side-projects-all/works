/*
Given an array of integers arr.

We want to select three indices i, j and k where (0 <= i < j <= k < arr.length).

Let's define a and b as follows:

    a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
    b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]

Note that ^ denotes the bitwise-xor operation.

Return the number of triplets (i, j and k) Where a == b.

 

Example 1:

Input: arr = [2,3,1,6,7]
Output: 4
Explanation: The triplets are (0,1,2), (0,2,2), (2,3,4) and (2,4,4)

Example 2:

Input: arr = [1,1,1,1,1]
Output: 10

 

Constraints:

    1 <= arr.length <= 300
    1 <= arr[i] <= 10^8


*/

class Solution {
public:
    int countTriplets(vector<int>& arr) {
        if (arr.size() == 1) {
            return 0;
        }

        arr.insert(arr.begin(), 0);
        int N = arr.size();

        for (int i = 1; i < N; ++i) {
            arr[i] ^= arr[i - 1];
        }
        int cnt = 0;

        for (int i = 0; i < N; ++i) {
            for (int k = i + 1; k < N; ++k) {

                //if we find a1 == a1 ^ a2 ^ a3 ^ a4, 
                //it means a1 ^ a1  == a1 ^ a1 ^ a2 ^ a3 ^ a4, 
                //then a2 ^ a3 ^ a4 == 0, 
                //indirectly, we have a1 == a1 ^ 0 == a1, 
                //that is why we have this if, 
                //and because of the prefix sum, 
                //in this example, we have two possibilities to make a2 ^ a3 ^ a4 == 0, 
                // (a2 ^ a3) == a4 or a2 == (a3 ^ a4), 
                //so we could use k - i - 1 to get the possibility counting
                if (arr[i] == arr[k]) {
                    cnt += k - i - 1;
                }
            }
        }

        return cnt;
    }
};