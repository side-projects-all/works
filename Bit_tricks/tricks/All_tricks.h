#include <iostream>
#include <bitset>
#include <limits.h>
#include <stdio.h>

void invert_endian() {
    unsigned invert;
    unsigned x = 0x1234;
    unsigned char* p = (unsigned char*)&x;
    unsigned char* ip = (unsigned char*)&invert;

    std::cout << "before: " << x;

    ip[0] = p[3];
    ip[1] = p[2];
    ip[2] = p[1];
    ip[3] = p[0];

    std::cout << "after: " << invert;
}
void little_or_big_endian() {
    unsigned short word = 0x1234;
    unsigned char* p = (unsigned char*)&word;

    if (p[0] == 0x12) {
        std::cout << "big endian\n";
    } else {
        std::cout << "little endian\n";
    }
}

void count_bits_1() {
    unsigned int data = 133;
    unsigned int cp = data;
    int cnt = 0;

    while (data != 0) {
        data = data & (data - 1);
        ++cnt;
    }

    std::cout << "data: " << cp << " has " << cnt << " ones in binary expression\n";
}

void count_bits_faster() {
    unsigned int mask[] = { 0x55555555, 0x33333333, 0x0f0f0f0f, 0x00ff00ff, 0x0000ffff };

    unsigned int data = 189;
    unsigned int cp = data;

    for (int i = 0, shift = 1; i < 5; ++i, shift *= 2) {
        data = (data & mask[i]) + ((data >> shift) & mask[i]);
    }

    std::cout << "data: " << cp << " has " << data << " ones in binary expression\n";
}

void Compute_the_sign_of_an_integer() {
    int v = -14;
    int sign;
    std::cout << "v: " << std::bitset<32>(v) << "\n";

    //c++裡 CHAR_BIT means number of bits in a byte 
    int val = v >> (sizeof(int) * CHAR_BIT - 1);
    std::cout << "sizeof(int): " << sizeof(int) << " val: " << std::bitset<32>(val) << "\n";
    sign = (v != 0) | (v >> (sizeof(int) * CHAR_BIT - 1));
    std::cout << "sign: " << sign << "\n";
}

void Detect_if_two_integers_have_opposite_signs() {
    int x = -10;
    int y = 7;
    bool f = ((x ^ y) < 0); //這是因為最左邊位元的關係吧?

    std::cout << f << "\n";
}
void Compute_the_integer_absolute_value_without_branching() {
    int v = -15;
    unsigned int r;
    int const mask = v >> sizeof(int) * CHAR_BIT - 1;
    std::cout << "mask: " << mask << "\n";

    std::cout << "(v + mask): " << (v + mask) << "\n";
    r = (v + mask) ^ mask;  //(v + mask)剛加完時，不會加1變二的補數，還是1的補數，直接XOR 得正數
    std::cout << "r1: " << r << "\n";
    std::cout << "(v ^ mask): " << (v ^ mask) << "\n";
    r = (v ^ mask) - mask;  //二進位減法是將被減數取二的補數，再相加
    std::cout << "r2: " << r << "\n";
}
void Compute_the_min_or_max_of_two_int_without_branching() {
    int x = -99;
    int y = 0;
    int r;

    //因為 -(x < y)的關係，x較小就變-1，2的補數，全1，and 前面的xor，再xor y，只剩x；
    //相反 x較大就變0，and 0，即0，y ^ 0還是y
    r = y ^ ((x ^ y) & -(x < y)); //min   
    std::cout << "min: " << r << "\n";

    r = x ^ ((x ^ y) & -(x < y)); //max
    std::cout << "max: " << r << "\n";
}

void if_an_int_is_a_pow_of_2() {
    unsigned int v = 0;
    bool f;

    f = (v & (v - 1)) == 0; // 這個的 0 也是 power of 2
    std::cout << "is pow of 2: " << f << "\n";

    f = v && !(v & (v - 1));  // 這個的 0 就不視為 power of 2
    std::cout << "is pow of 2: " << f << "\n";
}

#ifdef __cplusplus
extern "C" {
#endif

void sign_extending_from_a_constant_bit_width () {
    //what we need this? preventing a negative becomes a large positive value when widened.
    int x;
    int r;
    struct { signed int x:5; } s;
    s.x = x;  //limited 5 bits extends to full 32 bits
    r = s.x;
}

void sign_extending_from_a_variable_bit_width () {
    /*
        以5 bits -7(11001) 和 extend to 8 bits為例
        m 做完 1U << (b - 1) 變 00010000
        x 做完 x & ((1U << b) - 1) 變 00011001
        x ^ m 變 00001001 去扣 m，等同加上 m的2的補數 11110000
        (x ^ m) - m 等同 00001001 + 11110000 = 11111001 !! extended!
    */
    unsigned b; //原x有的bits
    int x;      //要extend的目標
    int r;      //extend後的結果
    int const m = 1U << (b - 1);  //要用的mask

    x = x & ((1U << b) - 1);  //找出整個x的bits
    r = (x ^ m) - m;
}

void sign_extending_from_a_variable_bit_width_in_3_operations() {
    unsigned b = 5; // number of bits representing the number in x
    int x = -10;      // sign extend this b-bit number to r
    int r;      // resulting sign-extended number

    /*
        CHAR_BIT 基本上 8 bits, 在做往左位移!
        sizeof(x) 取它幾個bytes, 以int x為例, 就是4bytes
        假設b = 5, 即5個bits, 4 * 8 - 5 = 27, 以 x = -10 (10110) 為例, 
        multipliers[5] = 1U << 27 = 134,217,728, 
        x * multipliers[b] = 2,952,790,016, 在bits 呈現下可以用unsigned 表示，但沒辦法用signed int 表示,
        而且最高bit 是1, 所以呈現上，等同計算 2,952,790,016 - 2^32 = –1 342 177 280, 
        trick 在把原本的bits 左移到unsigned integer 的區域, 移了(1U << ((sizeof(x) * CHAR_BIT) - B)), 當要轉signed integer呈現時, 就要扣 2^32,
        後續再除也就是在做右移原本左移的bit數, 精巧的unsigned, signed 轉換
    */

    //#define M(B) (1U << ((sizeof(x) * CHAR_BIT) - B))       //原本的compiler 不給過
    //加了(int) 強制轉型，這不符合用 bit‑pattern interpretation when you switch from unsigned to signed ?
    #define M(B) (int)(1U << ((sizeof(x) * CHAR_BIT) - B))    
    static int const multipliers[] = 
    {
      0,     M(1),  M(2),  M(3),  M(4),  M(5),  M(6),  M(7),
      M(8),  M(9),  M(10), M(11), M(12), M(13), M(14), M(15),
      M(16), M(17), M(18), M(19), M(20), M(21), M(22), M(23),
      M(24), M(25), M(26), M(27), M(28), M(29), M(30), M(31),
      M(32)
    }; // (add more if using more than 64 bits)
    static int const divisors[] = 
    {
      1,    ~M(1),  M(2),  M(3),  M(4),  M(5),  M(6),  M(7),
      M(8),  M(9),  M(10), M(11), M(12), M(13), M(14), M(15),
      M(16), M(17), M(18), M(19), M(20), M(21), M(22), M(23),
      M(24), M(25), M(26), M(27), M(28), M(29), M(30), M(31),
      M(32)
    }; // (add more for 64 bits)

    #undef M

    r = (x * multipliers[b]) / divisors[b];
    std::cout << r;
}

void conditionally_set_or_clear_bits_without_branching() {
    //啥場景用這個? 例如圖片bit 有highlight的bit, 當是false, 就移掉這些bits, or decode/encode 加減某些bits
    bool f;             // conditional flag
    unsigned int m;     // the bit mask
    unsigned int w;     // the word to modify: if (f) w |= m; else w &= ~m; 

    w ^= (-f ^ w) & m;

    //or 
    w = (w & ~m) | (-f & m);
}

void conditionally_negate_a_value_without_ranching() {
    //這等同要取正的或負的的選擇, 用bitwise 去掉branching

    //true 時 不變負
    bool fDontNegate;   // Flag indicating we should not negate v.
    int v;              // Input value to negate if fDontNegate is false.
    int r;              // result = fDontNegate ? v : -v;
    r = (fDontNegate ^ (fDontNegate - 1)) * v;

    //true 時 變負
    bool fNegate;       // Flag indicating if we should negate v.
    int v1;             // Input value to negate if fNegate is true.
    int r1;             // result = fNegate ? -v : v;
    r1 = (v1 ^ -fNegate) + fNegate;
}

void merge_bits_from_two_values_according_to_a_mask() {
    //這些bitwise operation 根本是從boolean algebra的運算推出來的吧
    //所以數位邏輯設計學好 bitwise operation沒煩惱
    unsigned int a;             // value to merge in non-masked bits
    unsigned int b;             // value to merge in masked bits
    unsigned int mask;          // 1 where bits from b should be selected; 0 where from a.
    unsigned int r;             // result of (a & ~mask) | (b & mask) goes here
    
    //這個式子推完可以變成右邊那個!
    r = a ^ ((a ^ b) & mask);   //r = (a & mask) | (b & ~mask);
}

void counting_bits_set_by_lookup_table() {
    // 這是8 bits的table, 會產生0-255個值, 每個所對應的 1的數量!
    // 因為只有8個bits, B6(2): 指6, 7二個bits是 11(192 to 255), 
    // B6(1): 有二種, 代表6, 7二個bits是 10(128 to 191), 01(64 to 127), 
    // B6(0): 剩下的0 to 63, 
    // 所以是以高位的第6bit去做區分!
    // 基本一次產生4個值的對應, 所以想做4個值一組, 
    // 一個B4 對4個B2, 共16個 B2, 4個B4, 共64個 B2,
    // 一個B6 又對 4個 B4, 共256個B2 
    static const unsigned char BitsSetTable256[256] = 
    {
    #   define B2(n) n,     n+1,     n+1,     n+2
    #   define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
    #   define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
        B6(0), B6(1), B6(1), B6(2)
    };

    unsigned int v; // count the number of bits set in 32-bit value v
    unsigned int c; // c is the total bits set in v

    // Option 1:    用在32bit, 就分段 各8bits, 位移 & 0xff, 取出對應table的值
    // 為什麼分段可行? 因為是2的倍數
    c = BitsSetTable256[v & 0xff] + 
        BitsSetTable256[(v >> 8) & 0xff] + 
        BitsSetTable256[(v >> 16) & 0xff] + 
        BitsSetTable256[v >> 24]; 

    // Option 2:
    unsigned char * p = (unsigned char *) &v;
    c = BitsSetTable256[p[0]] + 
        BitsSetTable256[p[1]] + 
        BitsSetTable256[p[2]] +	
        BitsSetTable256[p[3]];


    // To initially generate the table algorithmically:
    static unsigned char BitsSetTable256_2[256];
    BitsSetTable256_2[0] = 0;
    for (int i = 0; i < 256; i++) {
        BitsSetTable256_2[i] = (i & 1) + BitsSetTable256[i / 2];
    }
}

void counting_bits_set_Brian_Kernighans_way() {
    /*
        這蠻好理解的, 就每次跟差1的數字bit wise, 直到數字變0停下, 在些之前就累加count
     */
    unsigned int v; // count the number of bits set in v
    unsigned int c; // c accumulates the total bits set in v
    for (c = 0; v; c++) {
        v &= v - 1; // clear the least significant bit set
    }
}

void counting_bits_set_in_14_24_or_32_bit_words_using_64_bit_instructions() {

    unsigned int v; // count the number of bits set in v
    unsigned int c; // c accumulates the total bits set in v

    // 別忘記這些數字是用16進位表示的, 0x200040008001ULL 等同 (1<<45) + (1<<30) + (1<<15) + (1<<0) 在16進位表示, 
    // v * 0x200040008001ULL == (v << 45) + (v << 30) + (v << 15) + (v << 0) , v 去做 shift + add!
    // 這樣就分成了每15個bits的區間, 不重疊, 
    // bits  63 … 46 |45 … 31 |30 … 16 |15 … 1 | 0 , 共64 bits
    //          (v)       (v)      (v)    (v)
    // 14個bits只會落在最右的15 to 1的區間, 用15個1 去 and mask, 留下1, 最後再mod 0xf, 
    // 每個區間4 bits, 1111, 即 % 15, 等同每4個bits取出它們的1加起來!
    // 可以想 masked_value mod 15 = (d₀ + d₁ + … + dₖ) mod 15.

    // option 1, for at most 14-bit values in v: 14bit 乘上 48 bits 為62bits, 在0-63bits以內!
    c = (v * 0x200040008001ULL & 0x111111111111111ULL) % 0xf;

    //下面也都是類似的概念
    // option 2, for at most 24-bit values in v:
    c =  ((v & 0xfff) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
    c += (((v & 0xfff000) >> 12) * 0x1001001001001ULL & 0x84210842108421ULL) 
        % 0x1f;

    // option 3, for at most 32-bit values in v:
    c =  ((v & 0xfff) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
    c += (((v & 0xfff000) >> 12) * 0x1001001001001ULL & 0x84210842108421ULL) % 
        0x1f;
    c += ((v >> 24) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
}

void counting_bits_set_in_parallel() {
    //就是上面做 count_bits_faster() 的原始版!
    unsigned int v; // count bits set in this (32-bit value)
    unsigned int c; // store the total here
    static const int S[] = {1, 2, 4, 8, 16}; // Magic Binary Numbers
    static const int B[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF, 0x0000FFFF};

    // 這樣看 0x55555555 
    // bits:    7  6    5  4    3  2    1  0
    //          b7 b6   b5 b4   b3 b2   b1 b0
    // groups: [b7 b6] [b5 b4] [b3 b2] [b1 b0]
    // 操作 [b1 b0], 就2個bits 最大就3 (2進位 -> 11), 做((v >> 1) & 01), 等同保留高位 b1的值,
    // 而原本值 二進位可能 3: 11, 2: 10, 1: 01, 0: 00, 所以一相減 即v - ((v >> 1) & B[0]), 等同是找出了這2個bits有幾個1!

    c = v - ((v >> 1) & B[0]);
    //後面同樣都是高位的1保留移到低位              
    c = ((c >> S[1]) & B[1]) + (c & B[1]);  //這是4個bits的操作, 前2位高位bits保留至低位2bits, 再加上原低位2bits的1!
    c = ((c >> S[2]) + c) & B[2];           //這是8個bits的操作
    c = ((c >> S[3]) + c) & B[3];           //這是16個bits的操作
    c = ((c >> S[4]) + c) & B[4];

    /* 
        The B array, expressed as binary, is:

        B[0] = 0x55555555 = 01010101 01010101 01010101 01010101 這是2個bits 1對對去算幾個1
        B[1] = 0x33333333 = 00110011 00110011 00110011 00110011
        B[2] = 0x0F0F0F0F = 00001111 00001111 00001111 00001111
        B[3] = 0x00FF00FF = 00000000 11111111 00000000 11111111
        B[4] = 0x0000FFFF = 00000000 00000000 11111111 11111111
    */

    //
}
#ifdef __cplusplus
}
#endif