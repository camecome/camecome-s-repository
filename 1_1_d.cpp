#include <iostream>

struct LinkedList {
  typedef struct LstObj {
    int value;
    struct LstObj* prev;
    struct LstObj* next;
  } OBJ;

  OBJ* head = nullptr;
  OBJ* tail = nullptr;
  OBJ* middle = nullptr;
  int count_obj = 0;

  void PushToTheEnd(int& value) {
    OBJ* ptr = new OBJ;
    ptr->value = value;
    ptr->prev = tail;
    ptr->next = nullptr;
    if (count_obj > 0) {
      if (count_obj % 2 == 0) {
        OBJ* temp_ptr1 = middle->next;
        middle = temp_ptr1;
        tail->next = ptr;
      } else if (count_obj % 2 != 0) {
        tail->next = ptr;
      }
    } else if (count_obj == 0) {
      head = middle = ptr;
    }
    tail = ptr;
    ++count_obj;
  }

  void PushToTheMiddle(int& value) {
    OBJ* ptr = new OBJ;
    ptr->value = value;
    ptr->prev = middle;
    if (count_obj == 0) {
      ptr->next = nullptr;
      head = tail = middle = ptr;
    } else if (count_obj == 1) {
      ptr->next = nullptr;
      middle->next = ptr;
      tail = ptr;
    } else if (count_obj > 1) {
      ptr->next = middle->next;
      middle->next = ptr;
      middle->next->prev = ptr;
      if (count_obj % 2 == 0) {
        middle = ptr;
      }
    }
    ++count_obj;
  }

  void PopTheFrontOne() {
    if (head != nullptr) {
      std::cout << head->value << std::endl;
      if (count_obj == 1) {
        delete head;
        head = tail = middle = nullptr;
      } else if (count_obj >= 2) {
        head->next->prev = nullptr;
        OBJ* temp_ptr = head->next;
        delete head;
        head = temp_ptr;
        if (count_obj % 2 == 0) {
          if (count_obj == 2) {
            middle = temp_ptr;
          } else {
            middle = middle->next;
          }
        }
      }
      --count_obj;
    } else {
      std::cout << "error!" << std::endl;
    }
  }

  void Clear() {
    if (head == nullptr) {
      return;
    }
    OBJ* c;
    for (int i = 0; i < count_obj; ++i) {
      c = head->next;
      delete head;
      head = c;
    }
  }
};

void Handler(int& it_number) {
  LinkedList lin_list;
  for (int i = 0; i < it_number; ++i) {
    char det;
    int val;
    std::cin >> det;
    if (det == '+') {
      std::cin >> val;
      lin_list.PushToTheEnd(val);
    } else if (det == '*') {
      std::cin >> val;
      lin_list.PushToTheMiddle(val);
    } else if (det == '-') {
      lin_list.PopTheFrontOne();
    } else {
      continue;
    }
  }
  lin_list.Clear();
}

int main() {
  int num;
  std::cin >> num;
  Handler(num);
  return 0;
}
