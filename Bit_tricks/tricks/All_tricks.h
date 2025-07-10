#include <iostream>
#include <bitset>

class All_tricks {
private:

public:
  All_tricks() {

  }

  ~All_tricks() {

  }

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

    r = y ^ ((x ^ y) & -(x < y)); //min
    std::cout << "min: " << r << "\n";

    r = x ^ ((x ^ y) & -(x < y)); //max
    std::cout << "max: " << r << "\n";
  }
  /*
  void Compute_the_sign_of_an_integer();
  void Compute_the_integer_absolute_value_without_branching();
  void Detect_if_two_integers_have_opposite_signs();
  */
};
