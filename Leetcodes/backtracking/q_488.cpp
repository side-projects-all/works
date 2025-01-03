/*
You are playing a variation of the game Zuma.

In this variation of Zuma, there is a single row of colored balls on a board, where each ball can be colored red 'R', yellow 'Y', blue 'B', green 'G', or white 'W'. You also have several colored balls in your hand.

Your goal is to clear all of the balls from the board. On each turn:

    Pick any ball from your hand and insert it in between two balls in the row or on either end of the row.
    If there is a group of three or more consecutive balls of the same color, remove the group of balls from the board.
        If this removal causes more groups of three or more of the same color to form, then continue removing each group until there are none left.
    If there are no more balls on the board, then you win the game.
    Repeat this process until you either win or do not have any more balls in your hand.

Given a string board, representing the row of balls on the board, and a string hand, representing the balls in your hand, return the minimum number of balls you have to insert to clear all the balls from the board. If you cannot clear all the balls from the board using the balls in your hand, return -1.

 

Example 1:

Input: board = "WRRBBW", hand = "RB"
Output: -1
Explanation: It is impossible to clear all the balls. The best you can do is:
- Insert 'R' so the board becomes WRRRBBW. WRRRBBW -> WBBW.
- Insert 'B' so the board becomes WBBBW. WBBBW -> WW.
There are still balls remaining on the board, and you are out of balls to insert.

Example 2:

Input: board = "WWRRBBWW", hand = "WRBRW"
Output: 2
Explanation: To make the board empty:
- Insert 'R' so the board becomes WWRRRBBWW. WWRRRBBWW -> WWBBWW.
- Insert 'B' so the board becomes WWBBBWW. WWBBBWW -> WWWW -> empty.
2 balls from your hand were needed to clear the board.

Example 3:

Input: board = "G", hand = "GGGGG"
Output: 2
Explanation: To make the board empty:
- Insert 'G' so the board becomes GG.
- Insert 'G' so the board becomes GGG. GGG -> empty.
2 balls from your hand were needed to clear the board.

 

Constraints:

    1 <= board.length <= 16
    1 <= hand.length <= 5
    board and hand consist of the characters 'R', 'Y', 'B', 'G', and 'W'.
    The initial row of balls on the board will not have any groups of three or more consecutive balls of the same color.


*/

class Solution {
public:
int findMinStep(string board, string hand) {
	vector<int> freq(26, 0);
	for(char c: hand)
		freq[c - 'A']++;
	unordered_map<string, int> cache;
	return dfs(board, freq, cache);
}

int dfs(string board, vector<int>& freq, unordered_map<string, int>& cache) {
    //就是存取map的key，要弄出unique key所以才這樣做
    std::string key = board + "#" + serialize(freq);    
	if(cache.count(key)) {
        return cache[key];
    }
	int r = INT_MAX;
	if(board.length() == 0) {            // base case => we have removed all the balls from table
		r = 0;
	} else {
		for(int i = 0; i < board.length(); i++) {     // try inserting a ball from hand at every position on row of balls
			for(int j = 0; j < freq.size(); j++) {       // try all the balls at every position

                //j 代表各個字母
                bool worthTrying = false;
                if(board[i] - 'A' == j) {

                    worthTrying = true; //字母一樣可以試

                } else if(0 < i && board[i] == board[i - 1] && board[i] - 'A' != j) {

                    worthTrying = true; //字母跟前一個一樣但跟j這個的字母不一樣也可以試
                }
                    
                // only if the frequency is more than 0, skipping this line will lead to runtime error
				if(freq[j] > 0 && worthTrying) {      
					board.insert(board.begin() + i, j + 'A');   // insert ball at ith index
					freq[j]--;    // update the frequency of ball

					string newStr = updateBoard(board);   // remove groups of 3 or more if possible
					int steps = dfs(newStr, freq, cache);   // recursively call the function for the new string board
					if(steps != -1) {    // steps will be -1 if we can't remove all the balls using this combination
						r = min(r, steps + 1);
					}

					freq[j]++;  // restore the frequency
					board.erase(board.begin() + i);   // remove the ball from this position to try next combination
				}
			}
		}
	}

	if(r == INT_MAX) r = -1;   // we can't remove all the balls
	cache[key] = r;
	return r;
}

string updateBoard(string board) {
	 int start = 0;
	 int end = 0; 
	 int boardLen = board.length();
	 while(start < boardLen) {
		 while(end < boardLen && board[start] == board[end]) {
			 end++;   // increment end pointer if consecutive balls are of same color
		 }
		 
		/* here, end will point to the ball next to consecutive balls of same color 
		such that  number of balls of same color = end - start */
		
		 if(end - start >= 3) {   // remove if 3 or more balls
			 string newBoard = board.substr(0, start) + board.substr(end); 
			 return updateBoard(newBoard);     // recursively check if there are more groups in the new string
		 } else {
			 start = end;
		 }
	 }
	 return board;
}

string serialize(vector<int>& freq) {
    string key = "";
    for(int i = 0; i < freq.size(); i++) {
        if(freq[i] > 0) {
            std::string s1 = to_string((char) i + 'A');
            std::string s2 = to_string(freq[i]);
            key += s1 + s2;

        }
        
    }
    return key;
}  
};