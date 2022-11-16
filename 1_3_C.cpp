#include <iostream>

void Faster() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

struct Node {
  int max_value;
  int index;
  int tl;
  int tr;
  Node* left_ptr = nullptr;
  Node* right_ptr = nullptr;

  Node(int max_value, int index, int tl, int tr)
      : max_value(max_value), index(index), tl(tl), tr(tr) {}
};

struct DynSegTree {
  Node* root;
  int n;

  explicit DynSegTree(int& n) : n(n) { root = new Node(0, -1, 1, n); }

  void Update(Node* v, int& value, int& index) {
    if (v->tl == v->tr) {
      v->max_value = value;
      v->index = index;
      return;
    }
    if (v->max_value <= value) {
      v->max_value = value;
      v->index = index;
    }
    int mid = (v->tl + v->tr) >> 1;
    if (index <= mid) {
      if (v->left_ptr == nullptr) {
        v->left_ptr = new Node(0, -1, v->tl, mid);
      }
      Update(v->left_ptr, value, index);
    } else if (index >= mid + 1) {
      if (v->right_ptr == nullptr) {
        v->right_ptr = new Node(0, -1, mid + 1, v->tr);
      }
      Update(v->right_ptr, value, index);
    }
  }

  long long GetMinIndex(Node* v, int value, int index) {
    if (v->tl == v->tr) {
      return v->index;
    }
    long long ans1 = INT64_MAX;
    long long ans2 = INT64_MAX;
    if (v->left_ptr != nullptr && v->left_ptr->tr >= index &&
        v->left_ptr->max_value >= value) {
      ans1 = GetMinIndex(v->left_ptr, value, index);
    }
    if (ans1 != INT64_MAX) {
      return ans1;
    }
    if (v->right_ptr != nullptr && v->right_ptr->max_value >= value) {
      ans2 = GetMinIndex(v->right_ptr, value, index);
    }
    return std::min(ans1, ans2);
  }

  void Delete(Node* v) const {
    if (v->tl == v->tr) {
      delete v;
      return;
    }
    if (v->left_ptr != nullptr) {
      Delete(v->left_ptr);
    }
    if (v->right_ptr != nullptr) {
      Delete(v->right_ptr);
    }
    delete v;
  }

  ~DynSegTree() { Delete(root); }
};

int main() {
  Faster();
  int n;
  int m;
  std::cin >> n >> m;
  DynSegTree tree(n);
  int index;
  int value;
  for (int i = 1; i < n + 1; ++i) {
    std::cin >> value;
    tree.Update(tree.root, value, i);
  }

  int cmd;
  for (int i = 0; i < m; ++i) {
    std::cin >> cmd >> index >> value;
    if (cmd == 1) {
      long long ans = tree.GetMinIndex(tree.root, value, index);
      if (ans == INT64_MAX) {
        std::cout << -1 << '\n';
      } else {
        std::cout << ans << '\n';
      }
    } else {
      tree.Update(tree.root, value, index);
    }
  }
}
