#include <iostream>

void Faster() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

int GetByte(long long number, int n) { return number >> (8 * n) & 255; }

void Sort(long long* arr, int elem_num, int n) {
  int cnt[256] = {};
  for (int i = 0; i < elem_num; ++i) {
    cnt[GetByte(arr[i], n)] += 1;
  }
  int pref[256];
  pref[0] = 0;
  for (int i = 1; i < 256; ++i) {
    pref[i] = pref[i - 1] + cnt[i - 1];
  }
  auto res = new long long[elem_num];
  for (int i = 0; i < elem_num; ++i) {
    res[pref[GetByte(arr[i], n)]++] = arr[i];
  }
  for (int i = 0; i < elem_num; ++i) {
    arr[i] = res[i];
  }
  delete[] res;
}

void LSDSort(long long* data, int size) {
  for (int byte = 0; byte < 8; ++byte) {
    Sort(data, size, byte);
  }
}

int main() {
  Faster();
  int n;
  std::cin >> n;
  auto* data = new long long[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> data[i];
  }
  LSDSort(data, n);
  for (int i = 0; i < n; ++i) {
    std::cout << data[i] << '\n';
  }
  delete[] data;
}
