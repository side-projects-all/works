/*
A password is considered strong if the below conditions are all met:

    It has at least 6 characters and at most 20 characters.
    It contains at least one lowercase letter, at least one uppercase letter, and at least one digit.
    It does not contain three repeating characters in a row (i.e., "Baaabb0" is weak, but "Baaba0" is strong).

Given a string password, return the minimum number of steps required to make password strong. if password is already strong, return 0.

In one step, you can:

    Insert one character to password,
    Delete one character from password, or
    Replace one character of password with another character.

 

Example 1:

Input: password = "a"
Output: 5

Example 2:

Input: password = "aA1"
Output: 3

Example 3:

Input: password = "1337C0d3"
Output: 0

 

Constraints:

    1 <= password.length <= 50
    password consists of letters, digits, dot '.' or exclamation mark '!'.


*/


class Solution {
public:
    int strongPasswordChecker(string password) {
        int n = password.size();
        
        //for condition 2
        bool hasLower = false;
        bool hasUpper = false;
        bool hasDigit = false;
        int missingTypes = 3; // Initially assume we are missing all three types

        for (char c : password) {
            if (std::islower(c)) hasLower = true;
            if (std::isupper(c)) hasUpper = true;
            if (std::isdigit(c)) hasDigit = true;
        }

        if (hasLower) --missingTypes;
        if (hasUpper) --missingTypes;
        if (hasDigit) --missingTypes;
        
        //for condition 3
        // Count sequences of three or more consecutive repeating characters
        int changeCount = 0;
        std::vector<int> repeats; // lengths of sequences of repeating characters
        
        for (int i = 2; i < n; ++i) {
            if (password[i] == password[i - 1] && password[i] == password[i - 2]) {

                int len = 2;
                while (i < n && password[i] == password[i - 1]) {
                    ++len;
                    ++i;
                }
                repeats.push_back(len);
            }
        }
        
        int totalChange = 0;
        int totalDelete = 0;
        
        for (int len : repeats) {
            //len means the length of repeating characters
            //changeCount means
            //counting for how many characters have to be changed
            changeCount += len / 3; 
        }
        
        //based on condition 1 to handle
        if (n < 6) {
            return std::max(missingTypes, 6 - n);

        } else if (n <= 20) {
            return std::max(missingTypes, changeCount);

        } else {

            //handling characters more than 20
            totalDelete = n - 20;
            
            //priority is important, 1. len % 3 == 0, 2. len % 3 == 1, 3. other conditions
            for (int& len : repeats) {
                if (totalDelete <= 0) break;

                if (len % 3 == 0) {
                    int toDelete = std::min(totalDelete, 1);
                    totalDelete -= toDelete;
                    len -= toDelete;
                    changeCount -= toDelete;    //"replace" substituted by 1 "delete"
                }
            }

            for (int& len : repeats) {
                if (totalDelete <= 0) break;

                if (len % 3 == 1) {
                    int toDelete = std::min(totalDelete, 2);
                    totalDelete -= toDelete;
                    len -= toDelete;
                    changeCount -= toDelete / 2;    //"replace" substituted by 2 "delete"
                }
            }

            for (int& len : repeats) {
                if (totalDelete <= 0) break;

                int toDelete = std::min(totalDelete, len - 2);
                totalDelete -= toDelete;
                len -= toDelete;
                
                //this means if you delete by 3, how many "replace" you do not have to do?
                changeCount -= toDelete / 3;    //"replace" substituted by 3 "delete"
            }

            return n - 20 + std::max(missingTypes, changeCount);
        }
    }
};