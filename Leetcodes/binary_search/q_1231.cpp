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
public:
    int maximizeSweetness(vector<int>& sweetness, int k) {
        int numPeople = k + 1;
        int left = *std::min_element(sweetness.begin(), sweetness.end());
        int right = std::accumulate(sweetness.begin(), sweetness.end(), 0) / numPeople;

        /*
        refer to editorial

        If we use mid = (left + right) / 2, then mid will be equal to left for which a workable plan exists. 
        According to the rule for how we reduce the search space, we will set left = mid for the next search. 
        Thus, the new search space is [mid, right] = [left, right], which is exactly the same as our previous 
        search space. Thus, the search will loop forever!

        However, using mid = (left + right + 1) / 2 means we will now set mid equal to right instead. Since 
        the new mid is not workable, we will create the new search space according to the rule, 
        that is [left, mid - 1] = [left, left]. Since the left boundary equals the right boundary, 
        we can successfully stop the binary search and return either boundary as the correct answer!
        */

        while (left < right) {
            int mid = (left + right + 1) / 2;
            int currSweet = 0;
            int peopleWithChoc = 0;

            for (int s : sweetness) {
                currSweet += s;

                if (currSweet >= mid) {
                    peopleWithChoc += 1;
                    currSweet = 0;
                }
            }

            if (peopleWithChoc >= numPeople) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }

        return right;
    }
};