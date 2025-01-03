#include <exception>
#include <memory>
#include <mutex>
#include <queue>
#include <condition_variable>

template<typename T>
class Threadsafe_queue {
private:
  
  std::queue<T> data;
  mutable std::mutex m;
  std::condition_variable cv;

public:
  Threadsafe_queue() {}
  ~Threadsafe_queue() {}

  //copy constructor
  Threadsafe_queue(const Threadsafe_queue& other) {
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data;
  }

  //delete assign operator
  Threadsafe_queue& operator=(const Threadsafe_queue&) = delete;

  void push(T new_val) {
    std::lock_guard<std::mutex> lock(m);
    data.push(new_val);
    cv.notify_one();
  }

  void wait_n_pop(T& val) {
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock, [this] { return !data.empty(); });

    val = data.front();
    data.pop();
  }

  std::shared_ptr<T> wait_n_pop() {
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock, [this] { return !data.empty(); });

    std::shared_ptr<T> res(std::make_shared<T>(data.front()));
    data.pop();
    return res;
  }

  bool try_pop(T& val) {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      return false;
    }

    val = data.front();
    data.pop();
    return true;
  }

  std::shared_ptr<T> try_pop() {
    std::unique_lock<std::mutex> lock(m);
    if (data.empty()) {
      return std::shared_ptr<T>();
    }

    std::shared_ptr<T> res(std::make_shared<T>(data.front()));
    data.pop();
    return res;
  }

  bool empty() const {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }

};