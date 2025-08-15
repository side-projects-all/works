#include<vector>

class Sortings {
private:
  void merge(std::vector<int>& arr, int left, int mid, int right);
  int partition(std::vector<int>& arr, int low, int high);
  void max_heapify(std::vector<int>& arr, int len, int i);
  bool is_inverse(int x, int y, bool is_asc);

public:
  Sortings() {}

  ~Sortings() {}

  void insertion_sort(std::vector<int>& arr, bool is_asc);
  void quick_sort(std::vector<int>& arr, int low, int high);
  void quick_sort_iterative(int *arr, int elements);
  void merge_sort(std::vector<int>& arr, int left, int right);
  void heap_sort(std::vector<int>& arr);
  void show_vals(std::vector<int>& arr);
};