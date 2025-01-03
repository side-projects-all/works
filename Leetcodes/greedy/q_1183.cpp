/*
Consider a matrix M with dimensions width * height, such that every cell has value 0 or 1, and any square sub-matrix of M of size sideLength * sideLength has at most maxOnes ones.

Return the maximum possible number of ones that the matrix M can have.

 

Example 1:

Input: width = 3, height = 3, sideLength = 2, maxOnes = 1
Output: 4
Explanation:
In a 3*3 matrix, no 2*2 sub-matrix can have more than 1 one.
The best solution that has 4 ones is:
[1,0,1]
[0,0,0]
[1,0,1]

Example 2:

Input: width = 3, height = 3, sideLength = 2, maxOnes = 2
Output: 6
Explanation:
[1,0,1]
[1,0,1]
[1,0,1]

 

Constraints:

    1 <= width, height <= 100
    1 <= sideLength <= width, height
    0 <= maxOnes <= sideLength * sideLength


*/

class Solution {
public:
    int maximumNumberOfOnes(int width, int height, int sideLength, int maxOnes) {
        /*
        vector<int> count;

        for (int r = 0; r < sideLength; r++) {
            for (int c = 0; c < sideLength; c++) {
                int cntInCol = 1 + (height - 1 - r) / sideLength;
                int colRepeat = 1 + (width - 1 - c) / sideLength;
                int total = cntInCol * colRepeat;
                count.push_back(total);
            }
        }

        sort(count.begin(), count.end(), greater<int>());

        int ans = 0;
        for (int i = 0; i < maxOnes; i++) {
            ans += count[i];
        }

        return ans;
        */

        std::vector<int> count(sideLength * sideLength, 0);

        for (int r = 0; r < height; ++r) {
            for (int c = 0; c < width; ++c) {
                count[(r % sideLength) * sideLength + (c % sideLength)]++;
            }
        }

        std::sort(count.begin(), count.end(), std::greater<int>());

        int sum = 0;
        for (int i = 0; i < maxOnes; ++i) {
            sum += count[i];
        }

        return sum;  

    }
};