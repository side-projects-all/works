#include "Sortings.h"
#include <iostream>

bool Sortings::is_inverse(int x, int y, bool is_asc) {
  if (!is_asc) {
    return x < y;
  }

  return x > y;
}

void Sortings::insertion_sort(std::vector<int>& arr, bool is_asc) {

  for (int i = 1; i < arr.size(); ++i) {
    int curr = arr[i];
    int j = i - 1;
    while (j >= 0 && is_inverse(arr[j], curr, is_asc)) {
      arr[j + 1] = arr[j];
      --j;
    }

    arr[j + 1] = curr;
  }
}

void Sortings::quick_sort_iterative(int *arr, int elements) {
    #define MAX_LEVEL 300
    int piv;
    int beg[MAX_LEVEL];     //recursion stored left bound
    int end[MAX_LEVEL];     //recursion stored right bound
    int i = 0;              //recursive level
    int L;
    int R;
    int swap;               //for choosing smaller part to do partition

    beg[0] = 0;
    end[0] = elements;

    while (i >= 0) {
        L = beg[i];         //left bound
        R = end[i] - 1;     //right bound

        if (L < R) {
            piv = arr[L];

            //do partition
            while (L < R) {
                while (arr[R] >= piv && L < R)  --R;
                    
                if (L < R) arr[L++] = arr[R];

                while (arr[L] <= piv && L < R)  ++L;

                if (L < R) arr[R--] = arr[L];
            }

            arr[L] = piv;           //move pivot
            beg[i + 1] = L + 1;     //set arguments of next level recursion, right part
            end[i + 1] = end[i];    //set arguments of next level recursion, right part
            end[i++] = L;           //right bound of left part and move to next level

            //switch left part and right part if the right part were larger
            if (end[i] - beg[i] > end[i - 1] - beg[i - 1]) {
                swap = beg[i];
                beg[i] = beg[i - 1];
                beg[i - 1] = swap;

                swap = end[i];
                end[i] = end[i - 1];
                end[i - 1] = swap;
            }

        } else {
            --i;
        }
    }
}

void Sortings::quick_sort(std::vector<int>& arr, int low, int high) {
  if (low >= high) {
    return;
  }

  int pivot = partition(arr, low, high);
  quick_sort(arr, low, pivot - 1);
  quick_sort(arr, pivot + 1, high);
}

int Sortings::partition(std::vector<int>& arr, int low, int high) {
  int pivot = arr[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; ++j) {
    if (arr[j] <= pivot) {
      ++i;
      std::swap(arr[i], arr[j]);
    }
  }

  std::swap(arr[i + 1], arr[high]);

  return i + 1;
}


void Sortings::merge_sort(std::vector<int>& arr, int left, int right){
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;
  Sortings::merge_sort(arr, left, mid);
  Sortings::merge_sort(arr, mid + 1, right);
  Sortings::merge(arr, left, mid, right);
}

void Sortings::merge(std::vector<int>& arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;
  std::vector<int> left_arr(n1);
  std::vector<int> right_arr(n2);

  for (int i = 0; i < n1; ++i) {
    left_arr[i] = arr[left + i];
  }
  for (int i = 0; i < n2; ++i) {
    right_arr[i] = arr[mid + 1 + i];
  }

  int i = 0;
  int j = 0;
  int k = left;
  while (i < n1 && j < n2) {

    if (left_arr[i] <= right_arr[j]) {
      arr[k] = left_arr[i];
      ++i;

    } else {
      arr[k] = right_arr[j];
      ++j;
    }

    ++k;
  }

  while (i < n1) {
    arr[k] = left_arr[i];
    ++i;
    ++k;
  }

  while (j < n2) {
    arr[k] = right_arr[j];
    ++j;
    ++k;
  }

}

void Sortings::max_heapify(std::vector<int>& arr, int len, int i) {
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  int max = i;

  if (left < len && arr[left] > arr[max]) {
    max = left;
  }

  if (right < len && arr[right] > arr[max]) {
    max = right;
  }

  if (max != i) {
    int tmp = arr[i];
    arr[i] = arr[max];
    arr[max] = tmp;
    max_heapify(arr, len, max);
  }
}

void Sortings::heap_sort(std::vector<int>& arr) {
  for (int i = arr.size() / 2 - 1; i >= 0; --i) {
      max_heapify(arr, arr.size(), i);
  }

  for (int i = arr.size() - 1; i > 0; --i) {
    int tmp = arr[i];
    arr[i] = arr[0];
    arr[0] = tmp;

    max_heapify(arr, i, 0);
  }
}

void Sortings::show_vals(std::vector<int>& arr) {
  for (int& v : arr) {
    std::cout << v << "";
  }
  std::cout << "\n";
}