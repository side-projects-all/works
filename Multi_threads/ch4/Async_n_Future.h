#include <algorithm>
#include <future>
#include <iostream>
#include <string>
#include <mutex>
#include <numeric>

std::mutex async_lock;
struct Async_X {
  void show_val(int val, const std::string& str) {
    std::lock_guard<std::mutex> lg(async_lock);
    std::cout << str << ' ' << val << '\n';
  }

  void only_str(const std::string& str) {
    std::lock_guard<std::mutex> lg(async_lock);
    std::cout << str << '\n';
  }

  int operator()(int i) {
    std::lock_guard<std::mutex> lg(async_lock);
    std::cout << i << '\n';

    return i + 10;
  }
};

template<typename RandomIt>
int parallel_sum(RandomIt b, RandomIt e) {
  auto len = e - b;
  if (len < 1000) {
    return std::accumulate(b, e, 0);
  }

  RandomIt mid = b + len / 2;
  auto handle = std::async(std::launch::async, parallel_sum<RandomIt>, mid, e);
  int sum = parallel_sum(b, mid);

  return sum + handle.get();
}