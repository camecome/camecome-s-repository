#include <iostream>

void Faster() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

struct BinaryHeap {
  int* max_heap = new int[2 * 100000 + 1];
  int* min_heap = new int[2 * 100000 + 1];
  int* max_ptr = new int[2 * 100000 + 1];
  int* min_ptr = new int[2 * 100000 + 1];
  int elem_num = 0;

  void SiftUpMin(int v) const {
    while (v > 1) {
      if (min_heap[v] < min_heap[v / 2]) {
        std::swap(max_ptr[min_ptr[v]], max_ptr[min_ptr[v / 2]]);
        std::swap(min_ptr[v], min_ptr[v / 2]);
        std::swap(min_heap[v], min_heap[v / 2]);
        v = v / 2;
      } else {
        break;
      }
    }
  }

  void SiftDownMin(int v) const {
    while (2 * v <= elem_num) {
      int u = 2 * v;
      if (u + 1 <= elem_num && min_heap[u + 1] < min_heap[u]) {
        ++u;
      }
      if (min_heap[u] < min_heap[v]) {
        std::swap(max_ptr[min_ptr[v]], max_ptr[min_ptr[u]]);
        std::swap(min_ptr[v], min_ptr[u]);
        std::swap(min_heap[u], min_heap[v]);
        v = u;
      } else {
        break;
      }
    }
  }

  void SiftUpMax(int v) const {
    while (v > 1) {
      if (max_heap[v] > max_heap[v / 2]) {
        std::swap(min_ptr[max_ptr[v]], min_ptr[max_ptr[v / 2]]);
        std::swap(max_ptr[v], max_ptr[v / 2]);
        std::swap(max_heap[v], max_heap[v / 2]);
        v = v / 2;
      } else {
        break;
      }
    }
  }

  void SiftDownMax(int v) const {
    while (2 * v <= elem_num) {
      int u = 2 * v;
      if (u + 1 <= elem_num && max_heap[u + 1] > max_heap[u]) {
        ++u;
      }
      if (max_heap[u] > max_heap[v]) {
        std::swap(min_ptr[max_ptr[v]], min_ptr[max_ptr[u]]);
        std::swap(max_ptr[v], max_ptr[u]);
        std::swap(max_heap[u], max_heap[v]);
        v = u;
      } else {
        break;
      }
    }
  }

  void ExtractMax() {
    if (elem_num == 0) {
      std::cout << "error" << '\n';
    } else {
      int ind = std::min(max_ptr[1], elem_num - 1);
      std::cout << max_heap[1] << '\n';

      min_heap[max_ptr[1]] = min_heap[elem_num];
      min_ptr[max_ptr[1]] = min_ptr[elem_num];
      max_ptr[min_ptr[max_ptr[1]]] = max_ptr[1];

      max_heap[1] = max_heap[elem_num];
      max_ptr[1] = max_ptr[elem_num];
      min_ptr[max_ptr[1]] = 1;

      --elem_num;
      SiftUpMin(ind);
      SiftDownMax(1);
    }
  }

  void ExtractMin() {
    if (elem_num == 0) {
      std::cout << "error" << '\n';
    } else {
      int ind = std::min(min_ptr[1], elem_num - 1);
      std::cout << min_heap[1] << '\n';

      max_heap[min_ptr[1]] = max_heap[elem_num];
      max_ptr[min_ptr[1]] = max_ptr[elem_num];
      min_ptr[max_ptr[min_ptr[1]]] = min_ptr[1];

      min_heap[1] = min_heap[elem_num];
      min_ptr[1] = min_ptr[elem_num];
      max_ptr[min_ptr[1]] = 1;

      --elem_num;
      SiftUpMax(ind);
      SiftDownMin(1);
    }
  }

  void Insert(int& value) {
    ++elem_num;
    max_heap[elem_num] = value;
    min_heap[elem_num] = value;
    min_ptr[elem_num] = elem_num;
    max_ptr[elem_num] = elem_num;
    SiftUpMax(elem_num);
    SiftUpMin(elem_num);
    std::cout << "ok" << '\n';
  }

  void GetMin() {
    if (elem_num == 0) {
      std::cout << "error" << '\n';
    } else {
      std::cout << min_heap[1] << '\n';
    }
  }

  void GetMax() {
    if (elem_num == 0) {
      std::cout << "error" << '\n';
    } else {
      std::cout << max_heap[1] << '\n';
    }
  }

  void Clear() {
    elem_num = 0;
    std::cout << "ok" << '\n';
  }
};

int main() {
  Faster();
  BinaryHeap bin_heap;
  int number;
  int value;
  std::cin >> number;
  std::string det;
  for (int i = 0; i < number; ++i) {
    std::cin >> det;
    if (det == "insert") {
      std::cin >> value;
      bin_heap.Insert(value);
    } else if (det == "extract_min") {
      bin_heap.ExtractMin();
    } else if (det == "get_min") {
      bin_heap.GetMin();
    } else if (det == "extract_max") {
      bin_heap.ExtractMax();
    } else if (det == "get_max") {
      bin_heap.GetMax();
    } else if (det == "size") {
      std::cout << bin_heap.elem_num << '\n';
    } else if (det == "clear") {
      bin_heap.Clear();
    } else {
      continue;
    }
  }
  delete[] bin_heap.max_heap;
  delete[] bin_heap.min_heap;
  delete[] bin_heap.max_ptr;
  delete[] bin_heap.min_ptr;
}
