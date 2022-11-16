#include <iostream>

struct Stack {
  typedef struct StackObj {
    int value;
    int min_value;
    struct StackObj* prev;
  } OBJ;

  OBJ* top_elem = nullptr;
  int stack_len = 0;

  void Push(int& value) {
    OBJ* ptr = new OBJ;
    ptr->value = value;
    ptr->prev = top_elem;
    if (stack_len == 0) {
      ptr->min_value = value;
    } else if (stack_len > 0) {
      ptr->min_value =
          value > top_elem->min_value ? top_elem->min_value : value;
    }
    top_elem = ptr;
    ++stack_len;
  }

  int Pop() {
    int pop_value = top_elem->value;
    OBJ* temp_ptr = top_elem->prev;
    delete top_elem;
    top_elem = temp_ptr;
    --stack_len;
    return pop_value;
  }

  void StackClear() {
    for (int i = 0; i < stack_len; ++i) {
      OBJ* temp_ptr = top_elem->prev;
      delete top_elem;
      top_elem = temp_ptr;
    }
    stack_len = 0;
  }
};

struct Queue {
  Stack add;
  Stack del;

  void Rearrange() {
    int num = add.stack_len;
    for (int i = 0; i < num; ++i) {
      int value = add.Pop();
      del.Push(value);
    }
  }

  void Enqueue(int& value) {
    add.Push(value);
    printf("ok\n");
  }

  void Dequeue() {
    if (del.stack_len + add.stack_len == 0) {
      printf("error\n");
    } else if (del.stack_len + add.stack_len > 0) {
      if (del.stack_len == 0) {
        Rearrange();
      }
      printf("%i\n", del.Pop());
    }
  }

  void Front() {
    if (del.stack_len + add.stack_len == 0) {
      printf("error\n");
    } else if (del.stack_len + add.stack_len > 0) {
      if (del.stack_len == 0) {
        Rearrange();
      }
      printf("%i\n", del.top_elem->value);
    }
  }

  void Size() const { printf("%i\n", del.stack_len + add.stack_len); }

  void Clear() {
    add.StackClear();
    del.StackClear();
    printf("ok\n");
  }

  void QueueMin() const {
    if (del.stack_len + add.stack_len == 0) {
      printf("error\n");
    } else if (del.stack_len == 0) {
      printf("%i\n", add.top_elem->min_value);
    } else if (add.stack_len == 0) {
      printf("%i\n", del.top_elem->min_value);
    } else {
      printf("%i\n", del.top_elem->min_value > add.top_elem->min_value
                     ? add.top_elem->min_value
                     : del.top_elem->min_value);
    }
  }
};

void Handler(int& it_number) {
  Queue queue;
  std::string det;
  for (int i = 0; i < it_number; ++i) {
    std::cin >> det;
    if (det == "enqueue") {
      int value;
      std::cin >> value;
      queue.Enqueue(value);
    } else if (det == "dequeue") {
      queue.Dequeue();
    } else if (det == "front") {
      queue.Front();
    } else if (det == "size") {
      queue.Size();
    } else if (det == "clear") {
      queue.Clear();
    } else if (det == "min") {
      queue.QueueMin();
    } else {
      continue;
    }
  }
  queue.add.StackClear();
  queue.del.StackClear();
}

int main() {
  int number;
  std::cin >> number;
  Handler(number);
  return 0;
}
