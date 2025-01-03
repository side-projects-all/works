/*
Given two vectors of integers v1 and v2, implement an iterator to return their elements alternately.

Implement the ZigzagIterator class:

    ZigzagIterator(List<int> v1, List<int> v2) initializes the object with the two vectors v1 and v2.
    boolean hasNext() returns true if the iterator still has elements, and false otherwise.
    int next() returns the current element of the iterator and moves the iterator to the next element.

 

Example 1:

Input: v1 = [1,2], v2 = [3,4,5,6]
Output: [1,3,2,4,5,6]
Explanation: By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,3,2,4,5,6].

Example 2:

Input: v1 = [1], v2 = []
Output: [1]

Example 3:

Input: v1 = [], v2 = [1]
Output: [1]

 

Constraints:

    0 <= v1.length, v2.length <= 1000
    1 <= v1.length + v2.length <= 2000
    -2^31 <= v1[i], v2[i] <= 2^31 - 1

*/

class ZigzagIterator {
private:
    int i3;
    int i4;
    std::vector<int> v3;
    std::vector<int> v4;
    bool is_v3;
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        v3 = v1;
        v4 = v2;
        i3 = 0;
        i4 = 0;

        is_v3 = v3.empty() ? false : true;
    }

    int next() {
        
        if (is_v3) {
            int i = i3;
            ++i3;

            if (i4 < v4.size()) {
                is_v3 = false;
            }

            return v3[i];
        }

        int i = i4;
        ++i4;

        if (i3 < v3.size()) {
            is_v3 = true;
        }
        
        return v4[i];
    }

    bool hasNext() {
        return (i3 + i4) < (v3.size() + v4.size());
    }
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */