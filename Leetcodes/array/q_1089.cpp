/*
Given a fixed-length integer array arr, duplicate each occurrence of zero, shifting the remaining elements to the right.

Note that elements beyond the length of the original array are not written. Do the above modifications to the input array in place and do not return anything.

 

Example 1:

Input: arr = [1,0,2,3,0,4,5,0]
Output: [1,0,0,2,3,0,0,4]
Explanation: After calling your function, the input array is modified to: [1,0,0,2,3,0,0,4]

Example 2:

Input: arr = [1,2,3]
Output: [1,2,3]
Explanation: After calling your function, the input array is modified to: [1,2,3]

 

Constraints:

    1 <= arr.length <= 10^4
    0 <= arr[i] <= 9


*/

class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        //even in this way, it did not save more memory or run faster
        
        int zeros = 0;
        int end = arr.size() - 1;

        for (int i = 0; i <= end - zeros; ++i) {
            
            if (arr[i] == 0) {

                if (i == end - zeros) {
                    arr[end] = 0;
                    --end;
                    break;
                }
                ++zeros;
            }
        }

        int index = end - zeros;
        for (int i = index; i >= 0; --i) {
            
            if (arr[i] == 0) {
                arr[i + zeros] = 0;
                --zeros;
                arr[i + zeros] = 0;
            } else {
                arr[i + zeros] = arr[i];
            }

        }
        

        /*
        std::vector<int> nArr;

        for (int i = 0; i < arr.size(); ++i) {
            nArr.push_back(arr[i]);

            if (arr[i] == 0 && nArr.size() != arr.size()) {
                nArr.push_back(0);
            }

            if (nArr.size() == arr.size()) {
                break;
            }

        }

        arr = nArr;
        */
    }
};