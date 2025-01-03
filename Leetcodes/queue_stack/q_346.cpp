/*
Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.

Implement the MovingAverage class:

    MovingAverage(int size) Initializes the object with the size of the window size.
    double next(int val) Returns the moving average of the last size values of the stream.

 

Example 1:

Input
["MovingAverage", "next", "next", "next", "next"]
[[3], [1], [10], [3], [5]]
Output
[null, 1.0, 5.5, 4.66667, 6.0]

Explanation
MovingAverage movingAverage = new MovingAverage(3);
movingAverage.next(1); // return 1.0 = 1 / 1
movingAverage.next(10); // return 5.5 = (1 + 10) / 2
movingAverage.next(3); // return 4.66667 = (1 + 10 + 3) / 3
movingAverage.next(5); // return 6.0 = (10 + 3 + 5) / 3

 

Constraints:

    1 <= size <= 1000
    -10^5 <= val <= 10^5
    At most 10^4 calls will be made to next.


*/


class MovingAverage {
private:
    std::queue<int> q;
    int q_size;
    int sum_now;


public:
    MovingAverage(int size) {
        q_size = size;
        sum_now = 0;
    }
    
    double next(int val) {
        q.push(val);

        int len = q.size();
        if (len > q_size) {
            int front = q.front();
            q.pop();
            len = q_size;   //pop, so update the queue size

            sum_now = sum_now - front + val;
        
        } else {
            sum_now += val;
        }

        return sum_now * 1.0 / len;
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */