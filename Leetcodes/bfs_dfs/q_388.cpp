/*
Suppose we have a file system that stores both files and directories. An example of one system is represented in the following picture:

Here, we have dir as the only directory in the root. dir contains two subdirectories, subdir1 and subdir2. subdir1 contains a file file1.ext and subdirectory subsubdir1. subdir2 contains a subdirectory subsubdir2, which contains a file file2.ext.

In text form, it looks like this (with ⟶ representing the tab character):

dir
⟶ subdir1
⟶ ⟶ file1.ext
⟶ ⟶ subsubdir1
⟶ subdir2
⟶ ⟶ subsubdir2
⟶ ⟶ ⟶ file2.ext

If we were to write this representation in code, it will look like this: "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext". Note that the '\n' and '\t' are the new-line and tab characters.

Every file and directory has a unique absolute path in the file system, which is the order of directories that must be opened to reach the file/directory itself, all concatenated by '/'s. Using the above example, the absolute path to file2.ext is "dir/subdir2/subsubdir2/file2.ext". Each directory name consists of letters, digits, and/or spaces. Each file name is of the form name.extension, where name and extension consist of letters, digits, and/or spaces.

Given a string input representing the file system in the explained format, return the length of the longest absolute path to a file in the abstracted file system. If there is no file in the system, return 0.

Note that the testcases are generated such that the file system is valid and no file or directory name has length 0.

 

Example 1:

Input: input = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"
Output: 20
Explanation: We have only one file, and the absolute path is "dir/subdir2/file.ext" of length 20.

Example 2:

Input: input = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
Output: 32
Explanation: We have two files:
"dir/subdir1/file1.ext" of length 21
"dir/subdir2/subsubdir2/file2.ext" of length 32.
We return 32 since it is the longest absolute path to a file.

Example 3:

Input: input = "a"
Output: 0
Explanation: We do not have any files, just a single directory named "a".

 

Constraints:

    1 <= input.length <= 10^4
    input may contain lowercase or uppercase English letters, a new line character '\n', a tab character '\t', a dot '.', a space ' ', and digits.
    All file and directory names have positive length.


*/

class Solution {
public:
    //the nuance:
    //when we find the file name, it must be came from its parent-directory, 
    //so we already had the depth of its parent-directory, 
    //and if there were several directory before its parent-directory, 
    //it means they all have the same depth, 
    //and the newest value of those the same depth key would be updated by its parent-directory.
    //That is why this will work

    int lengthLongestPath(string input) {
        int longest = 0;
        std::unordered_map<int, int> lengthMap; //key: depth, value: length
        lengthMap[0] = 0;   //for the usage while the scenario is at root

        std::istringstream iss(input);
        std::string sub;

        //std::getline read unitl '\n' and put into sub
        while (std::getline(iss, sub)) {
            std::size_t nameBegin = sub.find_last_of('\t') + 1;

            //because the index will start frome 0, the nameBegin means the count of '\t;
            int depth = nameBegin;
            std::string name = sub.substr(nameBegin);

            if (name.find('.') != std::string::npos) {
                //if it is a file, we compare the length of whole path
                longest = std::max(longest, lengthMap[depth] + static_cast<int>(name.size()));
            } else {
                //if this is a directory, we record its depth
                //the +1 means we add one length for forward slash
                lengthMap[depth + 1] = lengthMap[depth] + static_cast<int>(name.size()) + 1;
            }
        }

        return longest;
    }
};