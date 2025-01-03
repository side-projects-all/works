/*
Design and implement a data structure for a compressed string iterator. The given compressed string will be in the form of each letter followed by a positive integer representing the number of this letter existing in the original uncompressed string.

Implement the StringIterator class:

    next() Returns the next character if the original string still has uncompressed characters, otherwise returns a white space.
    hasNext() Returns true if there is any letter needs to be uncompressed in the original string, otherwise returns false.

 

Example 1:

Input
["StringIterator", "next", "next", "next", "next", "next", "next", "hasNext", "next", "hasNext"]
[["L1e2t1C1o1d1e1"], [], [], [], [], [], [], [], [], []]
Output
[null, "L", "e", "e", "t", "C", "o", true, "d", true]

Explanation
StringIterator stringIterator = new StringIterator("L1e2t1C1o1d1e1");
stringIterator.next(); // return "L"
stringIterator.next(); // return "e"
stringIterator.next(); // return "e"
stringIterator.next(); // return "t"
stringIterator.next(); // return "C"
stringIterator.next(); // return "o"
stringIterator.hasNext(); // return True
stringIterator.next(); // return "d"
stringIterator.hasNext(); // return True

 

Constraints:

    1 <= compressedString.length <= 1000
    compressedString consists of lower-case an upper-case English letters and digits.
    The number of a single character repetitions in compressedString is in the range [1, 10^9]
    At most 100 calls will be made to next and hasNext.


*/

class StringIterator {
private:
    /*
    int index;
    int len;
    std::priority_queue<std::pair<int, char>, std::vector<std::pair<int, char>>, 
                                                    std::greater<std::pair<int, char>>> pq;
    */
    
    std::string str;
    int num;
    int i;
    char c;

public:
    StringIterator(string compressedString) {
        
        str = compressedString;
        num = -1;
        i = 0;
        

        /*
        index = 1;
        len = 0;
        for (int i = 1; i < compressedString.size(); ++i) {

            if (!(compressedString[i] >= '0' && compressedString[i] <= '9')) {
                continue;
            }

            int start = i;
            int end = i;
            while (end < compressedString.size() && (compressedString[end] >= '0' && compressedString[end] <= '9')) {
                ++end;
            }
            
            len += std::stoi(compressedString.substr(start, end - start));
            pq.push({len, compressedString[start - 1]});

            i = end;
        }
        */
        
    }
    
    char next() {
        
        if(hasNext()){
            num--;
            return c;
        }
        return ' ';
        
        /*
        if (index <= pq.top().first) {
            ++index;
            return pq.top().second;
        }

        if (!pq.empty()) {
            pq.pop();
        }
        
        if (index < len) {
            ++index;
            return pq.top().second;
        }
        
        return ' ';
        */
        
    }
    
    bool hasNext() {
        
        if(num > 0){
            return true;
        }
        if(i >= str.size()){
            return false;
        }
        c = str[i++];
        int j = i;
        while(j < str.size() && str[j] >= '0' && str[j] <= '9'){
            j++;
        }
        num = stoi(str.substr(i,j-i));
        i = j;
        return true;
        
        
        //return (index <= len);
        
    }
};

/**
 * Your StringIterator object will be instantiated and called as such:
 * StringIterator* obj = new StringIterator(compressedString);
 * char param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */