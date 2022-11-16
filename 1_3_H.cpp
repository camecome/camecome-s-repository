#include <cmath>
#include <iostream>

int Find2(int x) {
  if (x == 1) {
    return 0;
  }
  --x;
  for (int k = 0; k <= 4; ++k) {
    x |= x >> (1 << k);
  }
  return (int)std::log2(++x / 2);
}

struct Node {
  int min1 = INT32_MAX;
  int min2 = INT32_MAX;
  int index1 = -1;
  int index2 = -1;
};

void GetMin(Node** arr, int& left, int& right) {
  int k = Find2(right - left + 1);
  Node node1 = arr[k][left];
  Node node2 = arr[k][right - (int)std::pow(2, k) + 1];
  if (node1.index1 == node2.index1) {
    std::cout << std::min(node1.min2, node2.min2) << '\n';
    return;
  }
  if (node1.index2 == node2.index2) {
    std::cout << std::max(node1.min1, node2.min1) << "\n";
    return;
  }
  if (node1.min1 >= node2.min1) {
    if (node1.min1 <= node2.min2) {
      std::cout << node1.min1 << '\n';
    } else {
      std::cout << node2.min2 << '\n';
    }
  } else {
    if (node2.min1 <= node1.min2) {
      std::cout << node2.min1 << '\n';
    } else {
      std::cout << node1.min2 << '\n';
    }
  }
}

Node ConstructNode(Node node1, Node node2) {
  Node node;
  if (node1.min1 >= node2.min1) {
    node.min1 = node2.min1;
    node.index1 = node2.index1;
    if (node1.min1 <= node2.min2) {
      node.min2 = node1.min1;
      node.index2 = node1.index1;
    } else {
      node.min2 = node2.min2;
      node.index2 = node2.index2;
    }
  } else {
    node.min1 = node1.min1;
    node.index1 = node1.index1;
    if (node2.min1 <= node1.min2) {
      node.min2 = node2.min1;
      node.index2 = node2.index1;
    } else {
      node.min2 = node1.min2;
      node.index2 = node1.index2;
    }
  }
  return node;
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;

  int value;
  int* source_arr = new int[n + 1];
  for (int i = 1; i < n + 1; ++i) {
    std::cin >> value;
    source_arr[i] = value;
  }

  int rows = n + 1;
  int cols = (int)std::log2(n) + 1;

  Node** sparse_table = new Node*[cols];
  for (int i = 0; i < cols; ++i) {
    sparse_table[i] = new Node[rows];
  }

  for (int i = 1; i < rows; ++i) {
    sparse_table[0][i].min1 = source_arr[i];
    sparse_table[0][i].index1 = i;
  }

  for (int k = 1; k < cols; ++k) {
    for (int i = 1; i < rows; ++i) {
      if (i + (int)std::pow(2, k) > rows) {
        break;
      }
      int j = i + (int)std::pow(2, k - 1);
      Node node1 = sparse_table[k - 1][i];
      Node node2 = sparse_table[k - 1][j];
      sparse_table[k][i] = ConstructNode(node1, node2);
    }
  }

  int left;
  int right;
  for (int i = 0; i < m; ++i) {
    std::cin >> left >> right;
    GetMin(sparse_table, left, right);
  }

  for (int i = 0; i < cols; ++i) {
    delete[] sparse_table[i];
  }
  delete[] sparse_table;

  delete[] source_arr;
}
