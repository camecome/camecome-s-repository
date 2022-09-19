#include <iostream>

void PrintArray(int *array, int array_len){
    for (int i = 0; i < array_len; ++i){
        std::cout << array[i] << ' ';
    }
    std::cout << '\n';
}

struct Stack {
    int value;
    Stack *next;
    Stack *prev;

    void Add(int v) {}
};
int main(){


    return 0;
}