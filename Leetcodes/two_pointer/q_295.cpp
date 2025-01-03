/*
The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.

    For example, for arr = [2,3,4], the median is 3.
    For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.

Implement the MedianFinder class:

    MedianFinder() initializes the MedianFinder object.
    void addNum(int num) adds the integer num from the data stream to the data structure.
    double findMedian() returns the median of all elements so far. Answers within 10-5 of the actual answer will be accepted.

 

Example 1:

Input
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
Output
[null, null, null, 1.5, null, 2.0]

Explanation
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0

 

Constraints:

    -10^5 <= num <= 10^5
    There will be at least one element in the data structure before calling findMedian.
    At most 5 * 10^4 calls will be made to addNum and findMedian.

*/

class MedianFinder {
private:
    //if total 2n + 1, small holds n+ 1 and large holds n
    //else if total 2n, then they both will be n
    //max queue for small 
    std::priority_queue<int> small;
    //min queue for large
    std::priority_queue<int, std::vector<int>, std::greater<int>> large;
    /*
    std::multiset<int> data;
    std::multiset<int>::iterator lo_med;
    std::multiset<int>::iterator hi_med;
    */
public:
    MedianFinder() {}
    /*
    MedianFinder() : lo_med{ data.end() }, hi_med{ data.end() } {
        
    }
    */
    void addNum(int num) {
        
        if (small.empty() || num < small.top()) {
            small.push(num);

        } else {
            large.push(num);
        }
        
        //balancing here
        //if only use small.size() - large.size() > 1, we meet type problem, 
        //so transform the result into integer
        if ((int)(small.size() - large.size()) > 1) {
            large.push(small.top());
            small.pop();

        } else if (small.size() < large.size()) {
            small.push(large.top());
            large.pop();
        }
        
        /*
        const size_t n = data.size();   //previous size
        data.insert(num);

        if (!n) {
            //no elements before, one element now
            lo_med = data.begin();
            hi_med = data.begin();

        } else if (n & 1) {
            //odd case
            if (num < *lo_med) {
                --lo_med;
            } else {
                ++hi_med;
            }

        } else {
            //even case
            if (num > *lo_med && num < *hi_med) {
                //between lo and hi median
                ++lo_med;
                --hi_med;

            } else if (num >= *hi_med) {
                ++lo_med;
            } else {
                --hi_med;
                lo_med = hi_med;
            }
        }
        */
    }
    
    double findMedian() {
        if (small.size() == large.size()) {
            return (small.top() + large.top()) / 2.0;
        } else {
            return small.top();
        }
        
        //return ((double) *lo_med + * hi_med) * .5;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */