/*
Reverse bits of a given 32 bits unsigned integer.

Note:

    Note that in some languages, such as Java, there is no unsigned integer type. In this case, both input and output will be given as a signed integer type. They should not affect your implementation, as the integer's internal binary representation is the same, whether it is signed or unsigned.
    In Java, the compiler represents the signed integers using 2's complement notation. Therefore, in Example 2 above, the input represents the signed integer -3 and the output represents the signed integer -1073741825.

 

Example 1:

Input: n = 00000010100101000001111010011100
Output:    964176192 (00111001011110000010100101000000)
Explanation: The input binary string 00000010100101000001111010011100 represents the unsigned integer 43261596, so return 964176192 which its binary representation is 00111001011110000010100101000000.

Example 2:

Input: n = 11111111111111111111111111111101
Output:   3221225471 (10111111111111111111111111111111)
Explanation: The input binary string 11111111111111111111111111111101 represents the unsigned integer 4294967293, so return 3221225471 which its binary representation is 10111111111111111111111111111111.

 

Constraints:

    The input must be a binary string of length 32

*/

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        /* method 1, the point is (n & 1) << power!!!!
        uint32_t ret = 0, power = 31;
        while (n != 0) {
          ret += (n & 1) << power;
          n = n >> 1;
          power -= 1;
        }
        return ret;
        */
        
        //method 2 by Byte
        /*
        uint32_t ret = 0;
        uint32_t power = 24;
        
        while(n != 0) {
            ret += byByte(n & 0xff) << power;
            n = n >> 8;
            power -= 8;
        }
        
        return ret;
        */
        
        //method 3 by Mask
        n = (n >> 16) | (n << 16);
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
        return n;
    }
    
private:
    /*
    std::unordered_map<uint32_t, uint32_t> cache;
    
    uint32_t byByte(uint32_t byte) {
        if (cache.find(byte) != cache.end()) {
            return cache[byte];
        }
        
        uint32_t val = (byte * 0x0202020202 & 0x010884422010) % 1023;
        cache.emplace(byte, val);
        
        return val;
    }*/
};