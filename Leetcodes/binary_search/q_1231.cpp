/*
You have one chocolate bar that consists of some chunks. Each chunk has its own sweetness given by the array sweetness.

You want to share the chocolate with your k friends so you start cutting the chocolate bar into k + 1 pieces using k cuts, each piece consists of some consecutive chunks.

Being generous, you will eat the piece with the minimum total sweetness and give the other pieces to your friends.

Find the maximum total sweetness of the piece you can get by cutting the chocolate bar optimally.

 

Example 1:

Input: sweetness = [1,2,3,4,5,6,7,8,9], k = 5
Output: 6
Explanation: You can divide the chocolate to [1,2,3], [4,5], [6], [7], [8], [9]

Example 2:

Input: sweetness = [5,6,7,8,9,1,2,3,4], k = 8
Output: 1
Explanation: There is only one way to cut the bar into 9 pieces.

Example 3:

Input: sweetness = [1,2,2,1,2,2,1,2,2], k = 2
Output: 5
Explanation: You can divide the chocolate to [1,2,2], [1,2,2], [1,2,2]

 

Constraints:

    0 <= k < sweetness.length <= 10^4
    1 <= sweetness[i] <= 10^5


*/

class Solution {
private:
    int by_binary_search(vector<int>& sweetness, int& k) {
        int n = sweetness.size();
        if (n == 1) {
            return sweetness[0];
        }

        int b = sweetness[0];
        int e = sweetness[0];
        for (int i = 1; i < n; ++i) {
            b = std::min(sweetness[i], b);
            e += sweetness[i];
        }
        e /= (k + 1);

        while (b < e) {
            int mid = b + (e - b) / 2 + 1;
            //int mid = (e + b + 1) / 2;
            int sum = 0;
            int divide = 0;

            for (int i = 0; i < n; ++i) {
                sum += sweetness[i];

                if (sum >= mid) {
                    sum = 0;
                    ++divide;
                }
            }

            if (divide >= k + 1) {
                b = mid;

            } else {
                e = mid - 1;
            }
            
        }

        return b;
    }
public:
    int maximizeSweetness(vector<int>& sweetness, int k) {
        return by_binary_search(sweetness, k);
    }
};