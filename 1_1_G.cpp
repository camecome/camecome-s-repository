#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  int number;
  std::cin >> number;
  auto* array = new double[number + 1];
  double value;
  for (int i = 1; i < number + 1; ++i) {
    std::cin >> value;
    array[i] = std::log2(value) + array[i - 1];
  }
  std::cin >> number;
  int left;
  int right;
  for (int i = 0; i < number; ++i) {
    std::cin >> left;
    std::cin >> right;
    value = array[right + 1] - array[left];
    std::cout << std::fixed << std::setprecision(10)
              << std::pow(2, value * (1. / (right - left + 1))) << std::endl;
  }
  delete[] array;
}
