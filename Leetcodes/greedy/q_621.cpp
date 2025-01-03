/*
You are given an array of CPU tasks, each represented by letters A to Z, and a cooling time, n. Each cycle or interval allows the completion of one task. Tasks can be completed in any order, but there's a constraint: identical tasks must be separated by at least n intervals due to cooling time.

​Return the minimum number of intervals required to complete all tasks.

 

Example 1:

Input: tasks = ["A","A","A","B","B","B"], n = 2

Output: 8

Explanation: A possible sequence is: A -> B -> idle -> A -> B -> idle -> A -> B.

After completing task A, you must wait two cycles before doing A again. The same applies to task B. In the 3rd interval, neither A nor B can be done, so you idle. By the 4th cycle, you can do A again as 2 intervals have passed.

Example 2:

Input: tasks = ["A","C","A","B","D","B"], n = 1

Output: 6

Explanation: A possible sequence is: A -> B -> C -> D -> A -> B.

With a cooling interval of 1, you can repeat a task after just one other task.

Example 3:

Input: tasks = ["A","A","A", "B","B","B"], n = 3

Output: 10

Explanation: A possible sequence is: A -> B -> idle -> idle -> A -> B -> idle -> idle -> A -> B.

There are only two types of tasks, A and B, which need to be separated by 3 intervals. This leads to idling twice between repetitions of these tasks.

 

Constraints:

    1 <= tasks.length <= 10^4
    tasks[i] is an uppercase English letter.
    0 <= n <= 100


*/

class Solution {
private:
    int bygGreedy(vector<char>& tasks, int n) {
        int freq[26] = { 0 };
        int maxFreq = 0;
        int maxFreqCnt = 0;
        for (char c : tasks) {

            ++freq[c - 'A'];

            if (maxFreq == freq[c - 'A']) {
                ++maxFreqCnt;
            } else if (maxFreq < freq[c - 'A']) {
                maxFreq = freq[c - 'A'];
                maxFreqCnt = 1;
            }
        }
        int N = tasks.size();
        int partCnt = maxFreq - 1;
        int partLen = n - (maxFreqCnt - 1);
        int emptySlots = partCnt * partLen;
        int availableTasks = N - maxFreq * maxFreqCnt;
        int idles = std::max(0, emptySlots - availableTasks);

        return N + idles;
    }
    int byPQ(vector<char>& tasks, int n) {
        int freq[26] = { 0 };
        for (char c : tasks) {
            ++freq[c - 'A'];
        }

        std::priority_queue<int> pq;
        for (int i = 0; i < 26; ++i) {
            if (freq[i] > 0) {
                pq.push(freq[i]);
            }
        }

        int time = 0;
        while (!pq.empty()) {
            int cycle = n + 1;
            std::vector<int> store;
            int taskCnt = 0;

            while (cycle-- && !pq.empty()) {
                if (pq.top() > 1) {
                    store.push_back(pq.top() - 1);
                }
                pq.pop();
                ++taskCnt;
            }

            for (int &v : store) {
                pq.push(v);
            }

            time += (pq.empty() ? taskCnt : n + 1);
        }

        return time;
    }
public:
    int leastInterval(vector<char>& tasks, int n) {
        //return byPQ(tasks, n);
        
        return bygGreedy(tasks, n);
    }
};