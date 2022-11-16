#include <iostream>

void Faster() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

struct BinaryHeap {
  long long* heap = new long long[1000000 + 1];
  long long* ptr = new long long[1000000 + 1];
  long long* num = new long long[1000000 + 1];
  long long heap_len = 0;

  void Exchange(long long v1, long long v2) {
    std::swap(heap[v1], heap[v2]);
    std::swap(ptr[num[v1]], ptr[num[v2]]);
    std::swap(num[v1], num[v2]);
  }

  void SiftUp(long long v) {
    while (v > 1) {
      if (heap[v] < heap[v / 2]) {
        Exchange(v, v / 2);
        v /= 2;
      } else {
        break;
      }
    }
  }

  void SiftDown(long long v) {
    while (2 * v <= heap_len) {
      long long u = 2 * v;
      if (u + 1 <= heap_len && heap[u + 1] < heap[u]) {
        ++u;
      }
      if (heap[u] < heap[v]) {
        Exchange(u, v);
        v = u;
      } else {
        break;
      }
    }
  }

  void Insert(long long& value, long long index) {
    ++heap_len;
    heap[heap_len] = value;
    ptr[index] = heap_len;
    num[heap_len] = index;
    SiftUp(heap_len);
  }

  void DecreaseKey(long long pointer, long long& delta) {
    heap[ptr[pointer]] -= delta;
    SiftUp(ptr[pointer]);
  }

  void GetMin() { std::cout << heap[1] << '\n'; }

  void ExtractMin() {
    heap[1] = heap[heap_len];
    ptr[num[heap_len]] = 1;
    ptr[num[1]] = 0;
    num[1] = num[heap_len];
    --heap_len;
    SiftDown(1);
  }
};

int main() {
  Faster();
  BinaryHeap bin_heap;
  long long req_number;
  long long value;
  long long index;
  std::string det;
  std::cin >> req_number;
  for (long long i = 1; i < req_number + 1; ++i) {
    std::cin >> det;
    if (det == "insert") {
      std::cin >> value;
      bin_heap.Insert(value, i);
    } else if (det == "extractMin") {
      bin_heap.ExtractMin();
    } else if (det == "getMin") {
      bin_heap.GetMin();
    } else if (det == "decreaseKey") {
      std::cin >> index;
      std::cin >> value;
      bin_heap.DecreaseKey(index, value);
    } else {
      continue;
    }
  }
  delete[] bin_heap.heap;
  delete[] bin_heap.ptr;
  delete[] bin_heap.num;
}
