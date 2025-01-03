#include <mutex>
#include <utility>

//using unique lock for swapping
class X {
private:
  int val;
  std::mutex m;
public:
  X(int const& v) : val{ v } {}

  friend void swap(X& lhs, X& rhs) {
    if (&lhs == &rhs) {
      return;
    }

    std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);
    std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);
    std::lock(lock_a, lock_b);
    std::swap(lhs.val, rhs.val);
  }

  int get_val() {
    return val;
  }
};