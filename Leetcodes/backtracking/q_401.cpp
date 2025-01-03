/*
A binary watch has 4 LEDs on the top to represent the hours (0-11), and 6 LEDs on the bottom to represent the minutes (0-59). Each LED represents a zero or one, with the least significant bit on the right.

    For example, the below binary watch reads "4:51".

Given an integer turnedOn which represents the number of LEDs that are currently on (ignoring the PM), return all possible times the watch could represent. You may return the answer in any order.

The hour must not contain a leading zero.

    For example, "01:00" is not valid. It should be "1:00".

The minute must consist of two digits and may contain a leading zero.

    For example, "10:2" is not valid. It should be "10:02".

 

Example 1:

Input: turnedOn = 1
Output: ["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]

Example 2:

Input: turnedOn = 9
Output: []

 

Constraints:

    0 <= turnedOn <= 10


*/

class Solution {
private:
    void backtrack(int hr, int min, int i, int turnedOnRemain, 
                        std::vector<int>& hour, std::vector<int>& minute, 
                                            std::vector<std::string>& result) {

        if (turnedOnRemain == 0) {
            std::string s = std::to_string(hr) + (min < 10 ? ":0" : ":") + std::to_string(min);
            result.push_back(s);
            return;
        }

        for (int total = i; total < hour.size() + minute.size(); ++total) {
            if (total < minute.size()) {
                min += minute[total];

                if (min < 60) {
                    backtrack(hr, min, total + 1, turnedOnRemain - 1, hour, minute, result);
                }

                min -= minute[total];

            } else {
                hr += hour[total - minute.size()];

                if (hr < 12) {
                    backtrack(hr, min, total + 1, turnedOnRemain - 1, hour, minute, result);
                }

                hr -= hour[total - minute.size()];;
            }
        }
    }
public:
    vector<string> readBinaryWatch(int turnedOn) {

        //bit mask
        /*
        vector<string>ans;
        for(int hr = 0; hr < 12; hr++){
            for(int min = 0; min < 60;min++){
                if(__builtin_popcount(hr) + __builtin_popcount(min) == turnedOn){
                    if(min < 10){
                        ans.push_back(to_string(hr) + ":0" + to_string(min));
                    }
                    else{
                        ans.push_back(to_string(hr) + ":" + to_string(min));
                    }
                }
            }
        }
        return ans;
        */

        //dp
        /*
        vector<int>dp(60,0);
        vector<string>ans;
        for(int i=1;i<60;i++)
            dp[i]=dp[i/2]+(i&1);
        for(int hr=0;hr<12;hr++)
        {
            for(int min=0;min<60;min++)
            {
                if((dp[hr]+dp[min])==turnedOn)
                {
                    string str="";
                    if(min<10){
                        str+=(to_string(hr)+":0"+to_string(min));
                    }
                    else{
                        str+=(to_string(hr)+":"+to_string(min));
                    }
                    ans.emplace_back(str);
                }
            }
        } 
        return ans;   
        */

        //backtrack
        std::vector<int> hour = { 1,2,4,8 };
        std::vector<int> minute = { 1,2,4,8,16,32 };
        std::vector<string> res;

        backtrack(0, 0, 0, turnedOn, hour, minute, res);

        return res;
    }
};