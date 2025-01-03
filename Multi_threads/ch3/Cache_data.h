#include <unordered_map>
#include <shared_mutex>

class Cache_data {
private:
  std::unordered_map<std::string, std::string> m;
  mutable std::shared_mutex mutex;

public:
  Cache_data() {}

  std::string find_entry(std::string const& domain) {
    std::shared_lock<std::shared_mutex> lk(mutex);
    return (m.find(domain) == m.end()) ? "no data" : m[domain];
  }

  void update_entry(std::string const& domain, std::string const& details) {
    std::lock_guard<std::shared_mutex> lk(mutex);
    m[domain] = details;
  }
};