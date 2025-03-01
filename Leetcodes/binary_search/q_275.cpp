/*
Given an array of integers citations where citations[i] is the number of citations a researcher received for their ith paper and citations is sorted in ascending order, return the researcher's h-index.

According to the definition of h-index on Wikipedia: The h-index is defined as the maximum value of h such that the given researcher has published at least h papers that have each been cited at least h times.

You must write an algorithm that runs in logarithmic time.

 

Example 1:

Input: citations = [0,1,3,5,6]
Output: 3
Explanation: [0,1,3,5,6] means the researcher has 5 papers in total and each of them had received 0, 1, 3, 5, 6 citations respectively.
Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, their h-index is 3.

Example 2:

Input: citations = [1,2,100]
Output: 2

 

Constraints:

    n == citations.length
    1 <= n <= 10^5
    0 <= citations[i] <= 1000
    citations is sorted in ascending order.


*/

class Solution {
private:
    int by_sorting_and_ptr(vector<int>& citations) {
        int n = citations.size();
        if (n == 1) {
            return citations[0] >= 1;
        }
        std::sort(citations.begin(), citations.end());

        int i = 0;
        for (i = 0; i < n;/* ++i */) {
            
            if (citations[n - i - 1] > i) {
                ++i;
            } else {
                break;
            }
            
            /*
            if (citations[citations.size() - i - 1] <= i) {
                break;
            }*/
        }

        return i;
    }
    int by_binary_search(vector<int>& citations) {
        int n = citations.size();
        if (n == 1) {
            return citations[0] >= 1;
        }

        int left = 0;
        int right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (n - mid  == citations[mid]) {
                return n - mid;

            } else if (n - mid < citations[mid]) {
                right = mid - 1;
                
            } else {
                left = mid + 1;
            }
        }

        return n - left;
    }
public:
    int hIndex(vector<int>& citations) {
        //return by_binary_search(citations);
        return by_sorting_and_ptr(citations);
    }
};