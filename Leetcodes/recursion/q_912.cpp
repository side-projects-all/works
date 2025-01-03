/*
Given an array of integers nums, sort the array in ascending order and return it.

You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and with the smallest space complexity possible.

 

Example 1:

Input: nums = [5,2,3,1]
Output: [1,2,3,5]
Explanation: After sorting the array, the positions of some numbers are not changed (for example, 2 and 3), while the positions of other numbers are changed (for example, 1 and 5).

Example 2:

Input: nums = [5,1,1,2,0,0]
Output: [0,0,1,1,2,5]
Explanation: Note that the values of nums are not necessairly unique.

 

Constraints:

    1 <= nums.length <= 5 * 10^4
    -5 * 10^4 <= nums[i] <= 5 * 10^4


*/

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        //std::vector<int> tmpArr(nums.size());
        //mergeSort_recursive(nums, 0, nums.size() - 1, tmpArr);
        //heapSort_recursive(nums);
        //countSort(nums);
        radixSort(nums);
        return nums;
    }

private:
    void bucketSort(vector<int>& nums, int placeVal) {
        std::vector<std::vector<int>> buckets(10, std::vector<int>());
        //store val into every bucket based on placeVal

        int digit = 0;
        for (const int &val : nums) {
            digit = std::abs(val) / placeVal;
            digit = digit % 10;     //get the index value, for example, from the tens digit

            buckets[digit].push_back(val);
        }

        int index = 0;
        for (int i = 0; i < 10; ++i) {
            for (const int &val : buckets[i]) {
                nums[index] = val;
                ++index;
            }
        }
    }

    void radixSort(vector<int>& nums) {
        //find the absolute maximum element!!
        //then using it to find max number of digits.
        int maxElement = nums[0];
        for (const int &val : nums) {
            maxElement = std::max(std::abs(val), maxElement);
        }

        int maxDigits = 0;
        while (maxElement > 0) {
            maxDigits += 1;
            maxElement /= 10;
        }

        //this is what radix sort using bucketSort to do on every digit
        int placeVal = 1;
        for (int digit = 0; digit < maxDigits; ++digit) {
            bucketSort(nums, placeVal);
            placeVal *= 10;
        }

        //this part handle the negatives and reverse them
        std::vector<int> negatives;
        std::vector<int> positives;
        for (const int &val : nums) {
            if (val < 0) {
                negatives.push_back(val);
            } else {
                positives.push_back(val);
            }
        }

        std::reverse(negatives.begin(), negatives.end());
        std::merge(negatives.begin(), negatives.end(), positives.begin(), positives.end(), nums.begin());
    }



    void countSort(vector<int>& nums) {
        std::unordered_map<int, int> counts;

        //using algorithm library min_element and max_element
        int minVal = *std::min_element(nums.begin(), nums.end());
        int maxVal = *std::max_element(nums.begin(), nums.end());

        for (const auto &val : nums) {
            counts[val]++;
        }

        int index = 0;
        for (int val = minVal; val <= maxVal; ++val) {
            if (counts.find(val) != counts.end()) {
                while (counts[val] > 0) {
                    nums[index] = val;
                    ++index;
                    counts[val] -= 1;
                }
            }
        }
    }

    void heapSort_recursive(vector<int>& nums) {
        int n = nums.size();

        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify(nums, n, i);
        }

        for (int i = n - 1; i >= 0; --i) {
            std::swap(nums[0], nums[i]);
            heapify(nums, i, 0);
        }
    }

    void heapify(std::vector<int> &arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    void mergeSort_recursive(std::vector<int> &arr, int begin, int end, std::vector<int> &tmpArr) {

        if (begin >= end) {
            return;
        }

        int pivot = (begin + end) / 2;
        mergeSort_recursive(arr, begin, pivot, tmpArr);
        mergeSort_recursive(arr, pivot + 1, end, tmpArr);

        merge(arr, begin, pivot, end, tmpArr);
    }

    void merge(std::vector<int> &arr, int begin, int mid, int end, std::vector<int> &tmpArr) {
        int s1 = begin;
        int s2 = mid + 1;
        int len1 = mid - begin + 1;
        int len2 = end - mid;


        for (int i = 0; i < len1; ++i) {
            tmpArr[s1 + i] = arr[s1 + i];
        }
        for (int i = 0; i < len2; ++i) {
            tmpArr[s2 + i] = arr[s2 + i];
        }

        int i = 0;
        int j = 0;
        int k = begin;

        while (i < len1 && j < len2) {

            if (tmpArr[s1 + i] < tmpArr[s2 + j]) {
                arr[k] = tmpArr[s1 + i];
                ++i;
            } else {
                arr[k] = tmpArr[s2 + j];
                ++j;
            }

            ++k;
        }

        while (i < len1) {
            arr[k] = tmpArr[s1 + i];
            ++i;
            ++k;
        }

        while (j < len2) {
            arr[k] = tmpArr[s2 + j];
            ++j;
            ++k;
        }

    }
};