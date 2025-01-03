#include "All_tricks.h"
#include <bitset>

void All_tricks::Compute_the_sign_of_an_integer() {
  int v = -14;
  int sign;
  std::cout << "v: " << std::bitset<32>(v) << "\n";

  //c++裡 CHAR_BIT means number of bits in a byte 
  int val = v >> (sizeof(int) * CHAR_BIT - 1);
  std::cout << "sizeof(int): " << sizeof(int) << " val: " << std::bitset<32>(val) << "\n";
  sign = (v != 0) | (v >> (sizeof(int) * CHAR_BIT - 1));
  std::cout << "sign: " << sign << "\n";
}

void All_tricks::Detect_if_two_integers_have_opposite_signs() {
  int x = -10;
  int y = 7;
  bool f = ((x ^ y) < 0); //這是因為最左邊位元的關係吧?

  std::cout << f << "\n";
}
void All_tricks::Compute_the_integer_absolute_value_without_branching() {
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
