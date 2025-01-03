/*

*/

class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        
        std::sort(arr.begin(), arr.end());
        std::vector<std::vector<int>> result;
        int min_diff = std::numeric_limits<int>::max();

        /*
        //traverse twice
        //find minimum first, then find equal to min and put them into result
        for (int i = 1; i < arr.size(); i += 2) {
            
            int right = std::numeric_limits<int>::max();
            int left = arr[i] - arr[i - 1];

            if (i + 1 < arr.size()) {
                right = arr[i + 1] - arr[i];
            }

            min_diff = std::min(min_diff, std::min(left, right));
        }

        for (int i = 1; i < arr.size(); ++i) {
            if (arr[i] - arr[i - 1] == min_diff) {
                result.push_back({arr[i - 1], arr[i]});
            }
        }
        */

        //traverse once
        for (int i = 1; i < arr.size(); ++i) {
            
            int left = arr[i] - arr[i - 1];

            if (left < min_diff) {
                result.clear();

                result.push_back({arr[i - 1], arr[i]});
                min_diff = left;
                
            } else if (left == min_diff) {
                result.push_back({arr[i - 1], arr[i]});
            }
        }

        //if the array size is significant larger than the range min and max in the array, 
        //then using counting sort is really a good choice!!!
        /*
        // Initialize the auxiliary array `line`.
        // Keep a record of the minimum element and the maximum element.
        int minElement = *min_element(arr.begin(), arr.end());
        int maxElement = *max_element(arr.begin(), arr.end());
        int shift = -minElement;
        vector<uint8_t> line(maxElement - minElement + 1);
        vector<vector<int>> answer;
        
        // For each integer `num` in `arr`, we increment line[num + shift] by 1.
        for (const int& num : arr) {
            line[num + shift] = 1;
        }
        
        // Start from the index representing the minimum integer, initialize the 
        // absolute difference `min_pair_diff` as a huge value such as
        // `max_element - min_element` in order not to miss the absolute 
        // difference of the first pair.
        int minPairDiff = maxElement - minElement;
        int prev = 0;
        
        // Iterate over the array `line` and check if line[curr] 
        // holds the occurrence of an input integer.
        for (int curr = 1; curr <= maxElement + shift; ++curr) {
            // If line[curr] == 0, meaning there is no occurrence of the integer (curr - shift) 
            // held by this index, we will move on to the next index.
            if (line[curr] == 0) {
                continue;
            }
            
            // If the difference (curr - prev) equals `minPairDiff`, we add this pair 
            // {prev - shift, curr - shift} to the answer list. Otherwise, if the difference 
            // (curr - prev) is smaller than `minPairDiff`, we empty the answer list and add 
            // the pair {curr - shift, prev - shift} to the answre list and update the `minPairDiff`
            if (curr - prev == minPairDiff) {
                answer.push_back({prev - shift, curr - shift});
            } else if (curr - prev < minPairDiff) {
                minPairDiff = curr - prev;
                answer = {{prev - shift, curr - shift}};
            }        

            // Update prev as curr.
            prev = curr;
        }
        
        return answer;
        */

        return result;
    }
};