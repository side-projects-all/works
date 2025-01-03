#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack: std::exception {
  const char* what() const noexcept override { return "empty_stack"; }
};

template<typename T>
class Threadsafe_stack {
private:
  
  std::stack<T> data;
  mutable std::mutex m;

public:
  Threadsafe_stack() {}
  ~Threadsafe_stack() {}

  //copy constructor
  Threadsafe_stack(const Threadsafe_stack& other) {
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data;
  }

  //delete assign operator
  Threadsafe_stack& operator=(const Threadsafe_stack&) = delete;

  void push(T new_val) {
    std::lock_guard<std::mutex> lock(m);
    data.push(std::move(new_val));
  }

  std::shared_ptr<T> pop() {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      throw empty_stack();
    }

    std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
    data.pop();
    return res;
  }

  void pop(T& val) {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      throw empty_stack();
    }

    val = data.top();
    data.pop();
  }

  bool empty() const {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }

};